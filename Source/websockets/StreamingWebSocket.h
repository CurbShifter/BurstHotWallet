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

#ifndef __WEBSOCKET_JUCEHEADER__
#define __WEBSOCKET_JUCEHEADER__

#include "JuceHeader.h"
// based on JUCE library StreamingSocket

class StreamingWebSocket
{
public:
     StreamingWebSocket();
    ~StreamingWebSocket();
    bool bindToPort (int localPortNumber);
    bool connect (const String& remoteHostname,
                  int remotePortNumber,
                  int timeOutMillisecs = 3000);
    bool isConnected() const noexcept                           { return connected; }
    void close();
    const String& getHostName() const noexcept                  { return hostName; }
    int getPort() const noexcept                                { return portNumber; }
    bool isLocal() const noexcept;
    int waitUntilReady (bool readyForReading,
                        int timeoutMsecs) const;
    int read (void* destBuffer, int maxBytesToRead,
              bool blockUntilSpecifiedAmountHasArrived);
    int write (const void* sourceBuffer, int numBytesToWrite);
    bool createListener (int portNumber, const String& localHostName = String::empty);
    StreamingWebSocket* waitForNextConnection() const;

private:
    //==============================================================================
    String hostName;
    int volatile portNumber, handle;
    bool connected, isListener;

    StreamingWebSocket (const String& hostname, int portNumber, int handle);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StreamingWebSocket);
};

#endif   // __JUCE_SOCKET_JUCEHEADER__
