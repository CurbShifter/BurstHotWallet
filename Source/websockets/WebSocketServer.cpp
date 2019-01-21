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

#include "WebSocketServer.h"

WebSocketServer::WebSocketServer()
    : Thread ("WebSocketServer")
{
}

WebSocketServer::~WebSocketServer()
{
    stop();
}

//==============================================================================
bool WebSocketServer::beginWaitingForSocket (const int portNumber)
{
    stop();

    socket = new StreamingSocket();

    if (socket->createListener (portNumber))
    {
        startThread();
        return true;
    }

    socket = nullptr;
    return false;
}

void WebSocketServer::stop()
{
    signalThreadShouldExit();

    if (socket != nullptr)
        socket->close();

    stopThread (4000);
    socket = nullptr;
}

void WebSocketServer::run()
{
    while ((! threadShouldExit()) && socket != nullptr)
    {
        ScopedPointer <StreamingSocket> clientSocket (socket->waitForNextConnection());

        if (clientSocket != nullptr)
        {
            WebSocket* newConnection = createConnectionObject();

            if (newConnection != nullptr)
                newConnection->initialiseWithSocket (clientSocket.release());
        }
    }
}
