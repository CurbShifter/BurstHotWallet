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

#include "WebSocket.h"

WebSocket::WebSocket (const bool callbacksOnMessageThread, const uint32 magicMessageHeaderNumber)
    : Thread ("websocket connection"),
      callbackConnectionState (false),
      useMessageThread (callbacksOnMessageThread),
      magicMessageHeader (magicMessageHeaderNumber),
      pipeReceiveMessageTimeout (-1),
	  socketType (0)
{
}

WebSocket::~WebSocket()
{
    callbackConnectionState = false;
	if (socket)
		disconnect();
    masterReference.clear();
}

//==============================================================================
bool WebSocket::connectToSocket (const String& hostName,
                                              const int portNumber,
                                              const int timeOutMillisecs)
{
    disconnect();

    const ScopedLock sl (pipeAndSocketLock);
    socket = new StreamingSocket();

    if (socket->connect (hostName, portNumber, timeOutMillisecs))
    {
        connectionMadeInt();
        startThread();
        return true;
    }
    else
    {
        socket = nullptr;
        return false;
    }
}

bool WebSocket::connectToPipe (const String& pipeName, const int timeoutMs)
{
    disconnect();

    ScopedPointer <NamedPipe> newPipe (new NamedPipe());

    if (newPipe->openExisting (pipeName))
    {
        const ScopedLock sl (pipeAndSocketLock);
        pipeReceiveMessageTimeout = timeoutMs;
        initialiseWithPipe (newPipe.release());
        return true;
    }

    return false;
}

bool WebSocket::createPipe (const String& pipeName, const int timeoutMs)
{
    disconnect();

    ScopedPointer <NamedPipe> newPipe (new NamedPipe());

    if (newPipe->createNewPipe (pipeName))
    {
        const ScopedLock sl (pipeAndSocketLock);
        pipeReceiveMessageTimeout = timeoutMs;
        initialiseWithPipe (newPipe.release());
        return true;
    }

    return false;
}

void WebSocket::disconnect()
{
	stopThread(1000);
    if (socket != nullptr)
        socket->close();

    if (pipe != nullptr)
        pipe->close();

    stopThread (4000);

    {
        const ScopedLock sl (pipeAndSocketLock);
        socket = nullptr;
        pipe = nullptr;
    }

    connectionLostInt();
}

bool WebSocket::isConnected() const
{
    const ScopedLock sl (pipeAndSocketLock);

    return ((socket != nullptr && socket->isConnected())
              || (pipe != nullptr && pipe->isOpen()))
            && isThreadRunning();
}

String WebSocket::getConnectedHostName() const
{
    if (pipe != nullptr)
        return "localhost";

    if (socket != nullptr)
    {
        if (! socket->isLocal())
            return socket->getHostName();

        return "localhost";
    }

    return String::empty;
}

//==============================================================================
bool WebSocket::sendMessage (const MemoryBlock& message)
{
    uint32 messageHeader[2];
    messageHeader [0] = ByteOrder::swapIfBigEndian (magicMessageHeader);
    messageHeader [1] = ByteOrder::swapIfBigEndian ((uint32) message.getSize());

    MemoryBlock messageData (sizeof (messageHeader) + message.getSize());
    messageData.copyFrom (messageHeader, 0, sizeof (messageHeader));
    messageData.copyFrom (message.getData(), sizeof (messageHeader), message.getSize());

    int bytesWritten = 0;

    const ScopedLock sl (pipeAndSocketLock);

	MemoryBlock mem;
	if(socketType == 2)
		mem = EncodeFrameHixie76(message);
	else if(socketType == 1)
		mem = (message);
	else mem = EncodeFrame(message);


	if (socket != nullptr)
	{
		//if (socket->waitUntilReady(true, 1000) == 1)
			bytesWritten = socket->write(mem.getData(), (int)mem.getSize());
	}
    else if (pipe != nullptr)
        bytesWritten = pipe->write (mem.getData(), (int) mem.getSize(), pipeReceiveMessageTimeout);

//	Logger::writeToLog("bytesWritten " + String(bytesWritten) + " socketType " + String(socketType));
    return bytesWritten == (int) mem.getSize();
}

//==============================================================================
void WebSocket::initialiseWithSocket (StreamingSocket* const socket_)
{
    jassert (socket == nullptr);
    socket = socket_;
    connectionMadeInt();
    startThread();
}

void WebSocket::initialiseWithPipe (NamedPipe* const pipe_)
{
    jassert (pipe == nullptr);
    pipe = pipe_;
    connectionMadeInt();
    startThread();
}

//==============================================================================
struct ConnectionStateMessage  : public MessageManager::MessageBase
{
    ConnectionStateMessage (WebSocket* owner_, bool connectionMade_) noexcept
        : owner (owner_), connectionMade (connectionMade_)
    {}

    void messageCallback()
    {
        if (WebSocket* const ipc = owner)
        {
            if (connectionMade)
                ipc->connectionMade();
            else
                ipc->connectionLost();
        }
    }

    WeakReference<WebSocket> owner;
    bool connectionMade;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConnectionStateMessage)
};

void WebSocket::connectionMadeInt()
{
    if (! callbackConnectionState)
    {
        callbackConnectionState = true;

        if (useMessageThread)
            (new ConnectionStateMessage (this, true))->post();
        else
            connectionMade();
    }
}

void WebSocket::connectionLostInt()
{
    if (callbackConnectionState)
    {
        callbackConnectionState = false;

        if (useMessageThread)
            (new ConnectionStateMessage (this, false))->post();
        else
            connectionLost();
    }
}

struct DataDeliveryMessage  : public Message
{
    DataDeliveryMessage (WebSocket* ipc, const MemoryBlock& d)
        : owner (ipc), data (d)
    {}

    void messageCallback()
    {
        if (WebSocket* const ipc = owner)
            ipc->messageReceived (data);
    }

    WeakReference<WebSocket> owner;
    MemoryBlock data;
};

void WebSocket::deliverDataInt (const MemoryBlock& data)
{
    jassert (callbackConnectionState);

    if (useMessageThread)
        (new DataDeliveryMessage (this, data))->post();
    else
        messageReceived (data);
}

//==============================================================================
bool WebSocket::readNextMessageInt()
{
	int bytesInMessage = 1024;
	int bytesIn = 1;

	MemoryBlock messageData(bytesInMessage, true);
	int bytesRead = 0;
	{
		if (threadShouldExit())
			return false;

		const int numThisTime = jmin(bytesInMessage, 65536);
		void* const data = addBytesToPointer(messageData.getData(), bytesRead);


		bytesIn = socket != nullptr ? socket->read(data, numThisTime, false)
			: pipe->read(data, numThisTime, -1);
		messageData.setSize(bytesIn);

		bytesRead += bytesIn;
		bytesInMessage -= bytesIn;
	}

	if (bytesRead >= 0)
	{
		int foundEnd = 0;
		char *tdata = (char *)messageData.getData();
		if (tdata)
		{
			while (tdata[foundEnd] != 0 && foundEnd < 1024)
				foundEnd++;

			String messageDataStr(CharPointer_UTF8((CharPointer_UTF8::CharType*)messageData.getData()),
				CharPointer_UTF8((CharPointer_UTF8::CharType*)messageData.getData() + foundEnd));

			int isHandshake = messageDataStr.indexOf("HTTP/1.1");
			if (isHandshake < 0) {
				if (socketType == -1)
					socketType = 1;
				if (socketType == 2)
					deliverDataInt(DecodeFrameHixie76(messageData));
				else if (socketType == 1)
					deliverDataInt(messageData);// pinguin
				else deliverDataInt(DecodeFrame(messageData));
			}
			else
			{ // Do web handshake
				String response;
				MemoryBlock responseHixie76;
				int pos = messageDataStr.indexOf("Sec-WebSocket-Key:");
				if (pos > 0){
					socketType = 0; // hybi (10?)
					response.append("HTTP/1.1 101 Switching Protocols\r\n", strlen("HTTP/1.1 101 Switching Protocols\r\n"));
					response.append("Upgrade: websocket\r\n", strlen("Upgrade: websocket\r\n"));
					response.append("Connection: Upgrade\r\n", strlen("Connection: Upgrade\r\n"));

					messageDataStr = messageDataStr.substring(pos + 19, pos + 19 + 24);
					String magic = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
					messageDataStr.append(magic, magic.length());

					hashwrapper *myWrapper = new sha1wrapper();
					std::string hash1 = myWrapper->getHashFromString(std::string(messageDataStr.toUTF8()));
					if (myWrapper)
						delete myWrapper;

					MemoryBlock hashBlock;
					String hashS(hash1.c_str());
					for (int i = 0; i < hashS.length(); i += 2){
						int v = hashS.substring(i, i + 2).getHexValue32();
						hashBlock.append(&v, 1);
					}

					std::string hash1b64;
					hash1b64 = base64_encode(reinterpret_cast<const unsigned char*>(hashBlock.getData()), (unsigned int)hashBlock.getSize());
					String encoded(hash1b64.c_str());

					response.append("Sec-WebSocket-Accept: ", strlen("Sec-WebSocket-Accept: "));
					response.append(encoded, encoded.length());
					response.append("\r\n\r\n", strlen("\r\n\r\n"));

					MemoryBlock mem;
					mem.append(response.getCharPointer(), response.length());

					if (!sendHandShake(mem)) // send the handshake reply
						connectionLost();
				}
				pos = messageDataStr.indexOf("Sec-WebSocket-Key1:");
				if (pos > 0)
				{
					socketType = 2; // hixie 76
					// RESPONSE hixie 75 !
					/*HTTP/1.1 101 Web Socket Protocol HandShake
					Upgrade: WebSocket
					Connection: Upgrade
					WebSocket-Origin: */

					responseHixie76.append("HTTP/1.1 101 WebSocket Protocol HandShake\r\n", strlen("HTTP/1.1 101 WebSocket Protocol HandShake\r\n"));
					responseHixie76.append("Upgrade: WebSocket\r\n", strlen("Upgrade: WebSocket\r\n"));
					responseHixie76.append("Connection: Upgrade\r\n", strlen("Connection: Upgrade\r\n"));

					// location
					pos = messageDataStr.indexOf("Host: ") + 6;
					int pos2 = messageDataStr.indexOf(pos, "\r\n");
					String location = messageDataStr.substring(pos, pos2);


					// Origin
					pos = messageDataStr.indexOf("Origin: ");
					if (pos < 0)
					{
						pos = messageDataStr.indexOf("Sec-WebSocket-Origin: ");
						if (pos > 0)
							pos += strlen("Sec-WebSocket-Origin: ");
					}
					else pos += 8;
					pos2 = messageDataStr.indexOf(pos, "\r\n");
					String origin = messageDataStr.substring(pos, pos2);

					responseHixie76.append("Sec-WebSocket-Origin: ", strlen("Sec-WebSocket-Origin: "));
					responseHixie76.append(origin.getCharPointer().getAddress(), origin.length()); // http://example.com
					responseHixie76.append("\r\n", strlen("\r\n"));

					responseHixie76.append("Sec-WebSocket-Location: ws://", strlen("Sec-WebSocket-Location: ws://"));
					responseHixie76.append(location.getCharPointer().getAddress(), location.length()); // ws://example.com/demo */
					responseHixie76.append("/\r\n", strlen("/\r\n"));
					responseHixie76.append("\r\n", strlen("\r\n"));

					pos = messageDataStr.indexOf("Sec-WebSocket-Key1:") + 20;
					pos2 = messageDataStr.indexOf(pos, "\r\n");
					String key1 = messageDataStr.substring(pos, pos2);//

					pos = messageDataStr.indexOf("Sec-WebSocket-Key2:") + 20;
					pos2 = messageDataStr.indexOf(pos, "\r\n");
					String key2 = messageDataStr.substring(pos, pos2);

					MemoryBlock request;
					request.append((unsigned char *)messageData.getData() + (messageData.getSize() - 8), (size_t)8);

					// Extract each digit from Sec-WebSocket-Key1 and concatenate them
					// Count the number of spaces in Sec-WebSocket-Key1
					String space(" ");
					String::CharPointerType spaceP = space.getCharPointer();
					String key1t;
					int spaces1 = 0;
					String::CharPointerType t1 = (key1.getCharPointer());
					for (int i = 0; i < key1.length(); i++)
					{
						if (t1.isDigit())
							key1t.append(t1, 1);
						if (*t1 == *spaceP)
							spaces1++;
						t1++;
					}
					// Divide #1 by #2 and convert it to a 32 bit big-endian integer (network byte order)
					int k1 = key1t.getIntValue() / spaces1;

					// Extract each digit from Sec-WebSocket-Key2 and concatenate them
					// Count the number of spaces in Sec-WebSocket-Key2
					String key2t;
					int spaces2 = 0;
					String::CharPointerType t2 = key2.getCharPointer();
					for (int i = 0; i < key2.length(); i++)
					{
						if (t2.isDigit())
							key2t.append(t2, 1);
						if (*t2 == *spaceP)
							spaces2++;
						t2++;
					}
					// Divide #1 by #2  //0947fa63
					int k2 = key2t.getIntValue() / spaces2;

					// So if we concatenate these parts we get <0947fa630a5510d3546d5b4b20543275>. Notice this is 16 bytes total.
					MemoryBlock contentated;
					// and convert it to a 32 bit big-endian integer (network byte order)
					unsigned char kt;
					kt = (unsigned char)(k1 >> 24) & 0xFF;
					contentated.append(&(kt), 1);
					kt = (unsigned char)(k1 >> 16) & 0xFF;
					contentated.append(&(kt), 1);
					kt = (unsigned char)(k1 >> 8) & 0xFF;
					contentated.append(&(kt), 1);
					kt = (unsigned char)(k1)& 0xFF;
					contentated.append(&(kt), 1);

					kt = (unsigned char)(k2 >> 24) & 0xFF;
					contentated.append(&(kt), 1);
					kt = (unsigned char)(k2 >> 16) & 0xFF;
					contentated.append(&(kt), 1);
					kt = (unsigned char)(k2 >> 8) & 0xFF;
					contentated.append(&(kt), 1);
					kt = (unsigned char)(k2)& 0xFF;
					contentated.append(&(kt), 1);

					contentated.append(request.getData(), 8);

					// The last step is to calculate the MD5 hash of <0947fa630a5510d3546d5b4b20543275>.
					// You should get <66514a2c664e2f344634217e4b7e4d48> as the result. This is the result printed in hexadecimal.
					MD5 md5hash(contentated);
					MemoryBlock responsekey = md5hash.getRawChecksumData();//.toString()

					responseHixie76.append(responsekey.getData(), responsekey.getSize());
					if (!sendHandShake(responseHixie76)) // send the handshake reply
						connectionLost();
				}
				// ! In addition, because WebSockets can co-exist with other HTTP traffic over port 80 and 443, firewalls will not have to be re-configured.
			}
		}
	}
	else
	{
		if (socket != nullptr)
		{
			const ScopedLock sl(pipeAndSocketLock);
			socket = nullptr;
		}

		connectionLostInt();
		return false;
	}	
	return true;
}

void WebSocket::run()
{
    while (! threadShouldExit())
    {
        if (socket != nullptr)
        {
            const int ready = socket->waitUntilReady (true, 0);

            if (ready < 0)
            {
                {
                    const ScopedLock sl (pipeAndSocketLock);
                    socket = nullptr;
                }

                connectionLostInt();
                break;
            }
            else if (ready > 0)
            {
                if (! readNextMessageInt())
                    break;
            }
            else
            {
                Thread::sleep (1);
            }
        }
        else if (pipe != nullptr)
        {
            if (! pipe->isOpen())
            {
                {
                    const ScopedLock sl (pipeAndSocketLock);
                    pipe = nullptr;
                }

                connectionLostInt();
                break;
            }
            else
            {
                if (! readNextMessageInt())
                    break;
            }
        }
        else
        {
            break;
        }
    }
}

//==============================================================================
bool WebSocket::sendHandShake (const MemoryBlock& message)
{
    int bytesWritten = 0;
    const ScopedLock sl (pipeAndSocketLock);

    if (socket != nullptr)
        bytesWritten = socket->write (message.getData(), (int) message.getSize());
    else if (pipe != nullptr)
        bytesWritten = pipe->write (message.getData(), (int) message.getSize(), pipeReceiveMessageTimeout);

    return bytesWritten == (int) message.getSize();
}

//==============================================================================
MemoryBlock WebSocket::EncodeFrameHixie76(const MemoryBlock& message)
{
	/* http://stackoverflow.com/questions/9239466/what-are-the-protocol-differences-between-websockets-versions
	In Hixie-76, the frames were prefixed with 0x00 and suffixed with 0xff. 
	There was no way to determine the length of the frame except by receiving/buffering all 
	the way to the end of the frame. In the HyBi series (after HyBi-00) the frame length 
	is part of the prefix/header and there is no suffix.*/

	MemoryBlock output;
	bool encoded = false;
	if(encoded){ // alleen voor client?
		unsigned char frametype = 0x80;
		output.append(&frametype, 1);

		unsigned long int le = message.getSize();
		unsigned long int tfull = le;
		unsigned char t = 0;
		
		while(tfull > 0) {
			t = (tfull) &0x7F; // get lower 7 bits
			tfull = (tfull >> 7) &0x01FFFFFF; // remove 7 bit from ori
			if(tfull > 0) // check if is still bigger
				t = t + 0x80;
			output.append(&t, 1);
		}
		output.append(message.getData(), message.getSize());
	}
	else {
		unsigned char start = 0x00;
		output.append(&start, 1);
		output.append(message.getData(), message.getSize());
		unsigned char end = 0xFF;
		output.append(&end, 1);
	}
	return output;
}

//==============================================================================
MemoryBlock WebSocket::DecodeFrameHixie76(const MemoryBlock& message)
{
	MemoryBlock output;
	if(message.getSize() > 1){
		unsigned char *data = (unsigned char*)message.getData();
		if(data[0] &0x80){
			if(data[0] == 0xFF){
				int idx=1;
				unsigned long int len = data[idx] &0x80;
				while(data[idx] &0x80) {
					len *= 128; // << 7
					idx++;
					len += data[idx] &0x80;
				}
				output.append(&data[idx+1], message.getSize()-(idx+1));
			}
		}
		else if(data[0] == 0x00){
			output.append(&data[1], message.getSize()-2); //no 0x00 and 0xFF
		}		
	}
	return output;
}

//==============================================================================
MemoryBlock WebSocket::EncodeFrame(const MemoryBlock& message)
{
	/*this format is as follows:
    one byte which contains the type of data (and some additional info which is out of scope for a trivial server)
    one byte which contains the length
    either two or eight bytes if the length does not fit in the second byte (the second byte is then a code saying how many bytes are used for the length)
    the actual (raw) data */
	const size_t size = message.getSize();
	MemoryBlock outmessage;

	int destinationOffset = 2;
	if(size <= 125){ //1 byte
		outmessage.ensureSize(2 + size, true);
		unsigned char *data = (unsigned char *)outmessage.getData();
		data[0] = 129; //text frame
		data[1] = (unsigned char)size;
	}
	else if(size <= 65535){//2 bytes
		outmessage.ensureSize(4 + size, true);
		unsigned char *data = (unsigned char *)outmessage.getData();
		data[0] = 129; //text frame
		data[1] = 126;
		data[2] = (unsigned char)((size >> 8) & 0xFF);
		data[3] = (unsigned char)((size)& 0xFF);

		destinationOffset = 4;
	}
	else {
		outmessage.ensureSize(10 + size, true); // 8 bytes
		unsigned char *data = (unsigned char *)outmessage.getData();
		unsigned long long le = size;
		data[0] = 129; //text frame
		data[1] = 127;
		data[2] = (le >> 56) &0xFF;
		data[3] = (le >> 48) &0xFF;
		data[4] = (le >> 40) &0xFF;
		data[5] = (le >> 32) &0xFF;
		data[6] = (le >> 24) &0xFF;
		data[7] = (le >> 16) &0xFF;
		data[8] = (le >> 8) &0xFF;
		data[9] = (le) &0xFF;

		destinationOffset = 10;
	}
	outmessage.copyFrom(message.getData(), destinationOffset, size);

	return outmessage;
}

//==============================================================================
MemoryBlock WebSocket::DecodeFrame(const MemoryBlock& message)
{
	MemoryBlock outmessage;
	unsigned char *data = (unsigned char*)message.getData();

	/*	The frames you obtain are in the following format:
	- one byte which contains the type of data
    - one byte which contains the length
    - either two or eight additional bytes if the length did not fit in the second byte
    - four bytes which are the masks (= decoding keys)
    - the actual data
	*/
	bool isTextFrame = false;
	if(data[0] == 129){// text frame
		isTextFrame = true;
	}
	if(isTextFrame){
		/* The second byte and the additional two or eight bytes need some parsing, 
			because you need to know how many bytes are used for the length (you need to know where the real data starts). 
			The length itself is usually not necessary since you have the data already. 
			The first bit of the second byte is always 1 which means the data is masked (= encoded). 
			Messages from the client to the server are always masked. You need to remove that first bit 
			by doing secondByte AND 0111 1111. There are two cases in which the resulting byte does not 
			represent the length because it did not fit in the second byte:
			a second byte of 0111 1110, or 126, means the following two bytes are used for the length
			a second byte of 0111 1111, or 127, means the following eight bytes are used for the length */
		unsigned char mask[4];
		unsigned long int leng = 0;
		size_t idx=0;
		bool isEncoded = (data[1] &0x80)? true: false;

		switch(data[1] &0x7F){ //The first bit of the second byte is always 1 which means the data is masked (= encoded). Messages from the client to the server are always masked. You need to remove that first bit
			//There are two cases in which the resulting byte does not represent the length because it did not fit in the second byte:
			case 126: {
				leng = (data[2] << 8);
				leng += data[3];

				mask[0] = data[4];
				mask[1] = data[5];
				mask[2] = data[6];
				mask[3] = data[7];

				idx = (isEncoded)? 8: 4;
			} break;
			case 127: {
				leng = data[2] << 8;
				leng = (leng + data[3]) << 8;
				leng = (leng + data[4]) << 8;
				leng = (leng + data[5]) << 8;
				leng = (leng + data[6]) << 8;
				leng = (leng + data[7]) << 8;
				leng = (leng + data[8]) << 8;
				leng = (leng + data[9]) << 8;

				mask[0] = data[10];
				mask[1] = data[11];
				mask[2] = data[12];
				mask[3] = data[13];

				idx = (isEncoded)? 14: 10;
			} break;
			case 0: { // raar length is 0
				const char* c = (const char*)message.getData();
				for(size_t i=0; i<message.getSize()-4; i++){
					if(c[i] == 'L' && c[i+1] == 'V' &&
						c[i+2] == 'L' && c[i+3] == 'V'){
						idx = i;
						i = message.getSize();
					}
				}
			} break;
			default: {
				leng = data[1] &0x7F;

				mask[0] = data[2];
				mask[1] = data[3];
				mask[2] = data[4];
				mask[3] = data[5];

				idx = (isEncoded)? 6: 2;
			} break;
		};
		if(isEncoded){	
			for(unsigned int i=0; i<leng && i<message.getSize(); i++){
				char masked = (data[i+idx] ^ mask[i %4]);
				outmessage.append(&masked, 1);
			}
		}
		else
		{
			outmessage.append((reinterpret_cast<unsigned char*>(message.getData()))+idx, message.getSize()-idx);
		}
	}
	else {
		outmessage.append(message.getData(), message.getSize());
	}

	return outmessage;
}

