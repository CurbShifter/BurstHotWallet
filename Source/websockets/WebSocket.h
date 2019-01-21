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

#ifndef __JUCE_WebSocket_JUCEHEADER__
#define __JUCE_WebSocket_JUCEHEADER__

class WebSocketServer;

#include "JuceHeader.h"
#include "hl_sha1wrapper.h"
#include "Base64.h"

#include "StreamingWebSocket.h"
//==============================================================================
/**
    based on JUCE library socket
*/
class WebSocket    : private Thread
{
public:
    WebSocket (bool callbacksOnMessageThread = true, uint32 magicMessageHeaderNumber = 0xf2b49e2c);
    ~WebSocket();
    bool connectToSocket (const String& hostName,
                          int portNumber,
                          int timeOutMillisecs);
    bool connectToPipe (const String& pipeName, int pipeReceiveMessageTimeoutMs);
    bool createPipe (const String& pipeName, int pipeReceiveMessageTimeoutMs);
    void disconnect();
    bool isConnected() const;
    StreamingSocket* getSocket() const noexcept                 { return socket; }
    NamedPipe* getPipe() const noexcept                         { return pipe; }

    String getConnectedHostName() const;
    bool sendMessage (const MemoryBlock& message);
    virtual void connectionMade() = 0;
    virtual void connectionLost() = 0;
    virtual void messageReceived (const MemoryBlock& message) = 0;

	void SetSocketType(int socketTypeIn) { socketType = socketTypeIn; };
	int GetSocketType() { return socketType; };
	MemoryBlock EncodeFrame(const MemoryBlock& message);
	MemoryBlock DecodeFrame(const MemoryBlock& message);
	MemoryBlock EncodeFrameHixie76(const MemoryBlock& message);
	MemoryBlock DecodeFrameHixie76(const MemoryBlock& message);
	bool sendHandShake (const MemoryBlock& message);
	
private:
    //==============================================================================
    WeakReference<WebSocket>::Master masterReference;
    friend class WeakReference<WebSocket>;
    CriticalSection pipeAndSocketLock;
    ScopedPointer <StreamingSocket> socket;
    ScopedPointer <NamedPipe> pipe;
    bool callbackConnectionState;
    const bool useMessageThread;
    const uint32 magicMessageHeader;
    int pipeReceiveMessageTimeout;
	int socketType;

    friend class WebSocketServer;
    void initialiseWithSocket (StreamingSocket*);
    void initialiseWithPipe (NamedPipe*);
    void connectionMadeInt();
    void connectionLostInt();
    void deliverDataInt (const MemoryBlock&);
    bool readNextMessageInt();
    void run() override;
};

#endif   // __JUCE_WebSocket_JUCEHEADER__
