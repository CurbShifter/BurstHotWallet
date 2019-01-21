/*
==============================================================================
Copyright (C) 2019  CurbShifter

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================
*/


#include "JuceHeader.h"
// based on JUCE library StreamingSocket

#if JUCE_WINDOWS
 #include <winsock2.h>
 #include <ws2tcpip.h>

 #if JUCE_MSVC
  #pragma warning (push)
  #pragma warning (disable : 4127 4389 4018)
 #endif

#else
 #if JUCE_LINUX || JUCE_ANDROID
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/errno.h>
  #include <unistd.h>
  #include <netinet/in.h>
 #endif

 #include <fcntl.h>
 #include <netdb.h>
 #include <arpa/inet.h>
 #include <netinet/tcp.h>
#endif

#ifndef AI_NUMERICSERV  // (missing in older Mac SDKs)
 #define AI_NUMERICSERV 0x1000
#endif

#include "StreamingWebSocket.h"

#if JUCE_WINDOWS
 typedef int       juce_socklen_t;
#else
 typedef socklen_t juce_socklen_t;
#endif

//==============================================================================
namespace WebSocketHelpers
{
    void initSockets()
    {
       #if JUCE_WINDOWS
        static bool socketsStarted = false;

        if (! socketsStarted)
        {
            socketsStarted = true;

            WSADATA wsaData;
            const WORD wVersionRequested = MAKEWORD (1, 1);
            WSAStartup (wVersionRequested, &wsaData);
        }
       #endif
    }

    bool resetSocketOptions (const int handle, const bool isDatagram, const bool allowBroadcast) noexcept
    {
        const int sndBufSize = 65536;
        const int rcvBufSize = 65536;
        const int one = 1;

        return handle > 0
#if defined (SO_NOSIGPIPE)
		&& setsockopt (handle, SOL_SOCKET, SO_NOSIGPIPE, (const char*) &one, sizeof (one)) == 0
#endif
		&& setsockopt (handle, SOL_SOCKET, SO_RCVBUF, (const char*) &rcvBufSize, sizeof (rcvBufSize)) == 0
		&& setsockopt (handle, SOL_SOCKET, SO_SNDBUF, (const char*) &sndBufSize, sizeof (sndBufSize)) == 0
		&& (isDatagram ? ((! allowBroadcast) || setsockopt (handle, SOL_SOCKET, SO_BROADCAST, (const char*) &one, sizeof (one)) == 0)
			: (setsockopt (handle, IPPROTO_TCP, TCP_NODELAY, (const char*) &one, sizeof (one)) == 0));
    }

    bool bindSocketToPort (const int handle, const int port) noexcept
    {
        if (handle <= 0 || port <= 0)
            return false;

        struct sockaddr_in servTmpAddr = { 0 };
        servTmpAddr.sin_family = PF_INET;
        servTmpAddr.sin_addr.s_addr = htonl (INADDR_ANY);
        servTmpAddr.sin_port = htons ((uint16) port);

        return bind (handle, (struct sockaddr*) &servTmpAddr, sizeof (struct sockaddr_in)) >= 0;
    }

    int readSocket (const int handle,
                    void* const destBuffer, const int maxBytesToRead,
                    bool volatile& connected,
                    const bool blockUntilSpecifiedAmountHasArrived) noexcept
    {
        int bytesRead = 0;

        while (bytesRead < maxBytesToRead)
        {
            int bytesThisTime;

           #if JUCE_WINDOWS
            bytesThisTime = recv (handle, static_cast<char*> (destBuffer) + bytesRead, maxBytesToRead - bytesRead, 0);
           #else
            while ((bytesThisTime = (int) ::read (handle, addBytesToPointer (destBuffer, bytesRead), maxBytesToRead - bytesRead)) < 0
                     && errno == EINTR
                     && connected)
            {
            }
           #endif

            if (bytesThisTime <= 0 || ! connected)
            {
                if (bytesRead == 0)
                    bytesRead = -1;

                break;
            }

            bytesRead += bytesThisTime;

            if (! blockUntilSpecifiedAmountHasArrived)
                break;
        }

        return bytesRead;
    }

    int waitForReadiness (const int handle, const bool forReading, const int timeoutMsecs) noexcept
    {
        struct timeval timeout;
        struct timeval* timeoutp;

        if (timeoutMsecs >= 0)
        {
            timeout.tv_sec = timeoutMsecs / 1000;
            timeout.tv_usec = (timeoutMsecs % 1000) * 1000;
            timeoutp = &timeout;
        }
        else
        {
            timeoutp = 0;
        }

        fd_set rset, wset;
        FD_ZERO (&rset);
        FD_SET (handle, &rset);
        FD_ZERO (&wset);
        FD_SET (handle, &wset);

        fd_set* const prset = forReading ? &rset : nullptr;
        fd_set* const pwset = forReading ? nullptr : &wset;

       #if JUCE_WINDOWS
        if (select (handle + 1, prset, pwset, 0, timeoutp) < 0)
            return -1;
       #else
        {
            int result;
            while ((result = select (handle + 1, prset, pwset, 0, timeoutp)) < 0
                    && errno == EINTR)
            {
            }

            if (result < 0)
                return -1;
        }
       #endif

        {
            int opt;
            juce_socklen_t len = sizeof (opt);
//SO_ERROR | SO_NOSIGPIPE
            if (getsockopt (handle, SOL_SOCKET, SO_ERROR, (char*) &opt, &len) < 0
                 || opt != 0)
                return -1;
        }

        return FD_ISSET (handle, forReading ? &rset : &wset) ? 1 : 0;
    }

    bool setSocketBlockingState (const int handle, const bool shouldBlock) noexcept
    {
       #if JUCE_WINDOWS
        u_long nonBlocking = shouldBlock ? 0 : 1;
        return ioctlsocket (handle, FIONBIO, &nonBlocking) == 0;
       #else
        int socketFlags = fcntl (handle, F_GETFL, 0);

        if (socketFlags == -1)
            return false;

        if (shouldBlock)
            socketFlags &= ~O_NONBLOCK;
        else
            socketFlags |= O_NONBLOCK;

        return fcntl (handle, F_SETFL, socketFlags) == 0;
       #endif
    }

    bool connectSocket (int volatile& handle,
                        const bool isDatagram,
                        void** serverAddress,
                        const String& hostName,
                        const int portNumber,
                        const int timeOutMillisecs) noexcept
    {
        struct addrinfo hints = { 0 };
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = isDatagram ? SOCK_DGRAM : SOCK_STREAM;
        hints.ai_flags = AI_NUMERICSERV;

        struct addrinfo* info = nullptr;
        if (getaddrinfo (hostName.toUTF8(), String (portNumber).toUTF8(), &hints, &info) != 0 || info == 0)
            return false;

        if (handle < 0)
            handle = (int) socket (info->ai_family, info->ai_socktype, 0);

        if (handle < 0)
        {
            freeaddrinfo (info);
            return false;
        }

        if (isDatagram)
        {
            struct sockaddr* s = new struct sockaddr();
            *s = *(info->ai_addr);
            *serverAddress = s;

            freeaddrinfo (info);
            return true;
        }

        setSocketBlockingState (handle, false);
        const int result = ::connect (handle, info->ai_addr, (int) info->ai_addrlen);
        freeaddrinfo (info);

        if (result < 0)
        {
           #if JUCE_WINDOWS
            if (result == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK)
           #else
            if (errno == EINPROGRESS)
           #endif
            {
                if (waitForReadiness (handle, false, timeOutMillisecs) != 1)
                {
                    setSocketBlockingState (handle, true);
                    return false;
                }
            }
        }

        setSocketBlockingState (handle, true);
        resetSocketOptions (handle, false, false);

        return true;
    }
}

//==============================================================================
StreamingWebSocket::StreamingWebSocket()
    : portNumber (0),
      handle (-1),
      connected (false),
      isListener (false)
{
    WebSocketHelpers::initSockets();
}

StreamingWebSocket::StreamingWebSocket (const String& hostName_,
                                  const int portNumber_,
                                  const int handle_)
    : hostName (hostName_),
      portNumber (portNumber_),
      handle (handle_),
      connected (true),
      isListener (false)
{
    WebSocketHelpers::initSockets();
    WebSocketHelpers::resetSocketOptions (handle_, false, false);
}

StreamingWebSocket::~StreamingWebSocket()
{
    close();
}

//==============================================================================
int StreamingWebSocket::read (void* destBuffer, const int maxBytesToRead, const bool blockUntilSpecifiedAmountHasArrived)
{
	if(waitUntilReady(true, 1) <= 0)
		return -1;

    return (connected && ! isListener) ? WebSocketHelpers::readSocket (handle, destBuffer, maxBytesToRead, connected, blockUntilSpecifiedAmountHasArrived)
                                       : -1;
}

int StreamingWebSocket::write (const void* sourceBuffer, const int numBytesToWrite)
{
    if (isListener || ! connected)
        return -1;

   #if JUCE_WINDOWS
    return send (handle, (const char*) sourceBuffer, numBytesToWrite, 0);
   #else
    int result;

    while ((result = (int) ::write (handle, sourceBuffer, numBytesToWrite)) < 0
            && errno == EINTR)
    {
    }

    return result;
   #endif
}

//==============================================================================
int StreamingWebSocket::waitUntilReady (const bool readyForReading,
                                     const int timeoutMsecs) const
{
    return connected ? WebSocketHelpers::waitForReadiness (handle, readyForReading, timeoutMsecs)
                     : -1;
}

//==============================================================================
bool StreamingWebSocket::bindToPort (const int port)
{
    return WebSocketHelpers::bindSocketToPort (handle, port);
}

bool StreamingWebSocket::connect (const String& remoteHostName,
                               const int remotePortNumber,
                               const int timeOutMillisecs)
{
    if (isListener)
    {
        jassertfalse;    // a listener socket can't connect to another one!
        return false;
    }

    if (connected)
        close();

    hostName = remoteHostName;
    portNumber = remotePortNumber;
    isListener = false;

    connected = WebSocketHelpers::connectSocket (handle, false, 0, remoteHostName,
                                              remotePortNumber, timeOutMillisecs);

    if (! (connected && WebSocketHelpers::resetSocketOptions (handle, false, false)))
    {
        close();
        return false;
    }

    return true;
}

void StreamingWebSocket::close()
{
	juce::String emptyStr;
	hostName = emptyStr;//String::empty;
    portNumber = 0;
    handle = -1;
    isListener = false;

#if JUCE_WINDOWS
    if (handle != SOCKET_ERROR || connected)
        closesocket (handle);

    connected = false;
   #else
    if (connected)
    {
        connected = false;

        if (isListener)
        {
            // need to do this to interrupt the accept() function..
            StreamingWebSocket temp;
            temp.connect ("localhost", portNumber, 1000);
        }
    }

    if (handle != -1)
        ::close (handle);
   #endif

}

//==============================================================================
bool StreamingWebSocket::createListener (const int newPortNumber, const String& localHostName)
{
    if (connected)
        close();

    hostName = "listener";
    portNumber = newPortNumber;
    isListener = true;

    struct sockaddr_in servTmpAddr = { 0 };
    servTmpAddr.sin_family = PF_INET;
    servTmpAddr.sin_addr.s_addr = htonl (INADDR_ANY);

    if (localHostName.isNotEmpty())
        servTmpAddr.sin_addr.s_addr = ::inet_addr (localHostName.toUTF8());

    servTmpAddr.sin_port = htons ((uint16) portNumber);

    handle = (int) socket (AF_INET, SOCK_STREAM, 0);

    if (handle < 0)
        return false;

    const int reuse = 1;
    setsockopt (handle, SOL_SOCKET, SO_REUSEADDR, (const char*) &reuse, sizeof (reuse));
#if defined (SO_NOSIGPIPE)
	const int one = 1;
	setsockopt (handle, SOL_SOCKET, SO_NOSIGPIPE, (const char*) &one, sizeof (one));
#endif
    if (bind (handle, (struct sockaddr*) &servTmpAddr, sizeof (struct sockaddr_in)) < 0
         || listen (handle, SOMAXCONN) < 0)
    {
        close();
        return false;
    }

    connected = true;
    return true;
}

StreamingWebSocket* StreamingWebSocket::waitForNextConnection() const
{
    jassert (isListener || ! connected); // to call this method, you first have to use createListener() to
                                         // prepare this socket as a listener.

    if (connected && isListener)
    {
        struct sockaddr address;
        juce_socklen_t len = sizeof (sockaddr);
        const int newSocket = (int) accept (handle, &address, &len);

        if (newSocket >= 0 && connected)
            return new StreamingWebSocket (inet_ntoa (((struct sockaddr_in*) &address)->sin_addr),
                                        portNumber, newSocket);
    }

    return nullptr;
}

bool StreamingWebSocket::isLocal() const noexcept
{
    return hostName == "127.0.0.1";
}

#if JUCE_MSVC
 #pragma warning (pop)
#endif
