/*
  ==============================================================================

    MessageList.cpp
    Created: 22 Oct 2018 1:44:15am
    Author:  Jorn

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MessageList.h"

#define ENABLE_MESSGE_LOG 0

//==============================================================================
MessageList::MessageList()
{
	senderID = 0;
	receiverID = 0;
	linesNum = 0;
	isPrivate = false;
	
	Random rand;
	String msg;
	if (rand.nextInt() % 512 == 0)      msg = ("CurbShifter *tips hat*");
	else if (rand.nextInt() % 512 == 0) msg = ("Not your keys? not your crypto !");
	else if (rand.nextInt() % 128 == 0) msg = ("This unstopable chat runs on the Burstcoin network");
	else msg = ("Keep your pass phrase safe! Do not give it to anyone !");

	BurstSocket::BurstSocketThread::txPacketIn txPacket = BurstSocket::BurstSocketThread::initPacketIn();
	msg.copyToUTF8(&(txPacket.message[0]), MAX_TXDATASIZE);
	txPacket.messageSize = msg.length();
	txPacket.isText = true;
	txPacket.timestamp = Time::currentTimeMillis() / 1000;
	txPacket.txid = 0;
	txPacket.sender = senderID;
	txPacket.recipient = receiverID;

	txPackets.add(txPacket);
	
	setSize(600, 400);
}

MessageList::~MessageList()
{
#if ENABLE_MESSGE_LOG == 1
	log = nullptr;
#endif
}

void MessageList::paint (Graphics& g)
{
    g.fillAll (Colours::transparentWhite);   // clear the background

	bool global = (senderID == receiverID && isPrivate);
	const int rowH = 36;
	juce::Rectangle<int> clip = g.getClipBounds().expanded(0, rowH);
	bubbles.clearQuick();
	const int baseWidth = (getWidth() - 28);
	int lines = 0;
	int timeHeight = 12;
	int maxMessages = 1000;
	
	for (int i = txPackets.size() - 1; i >= jmax<int>(txPackets.size() - maxMessages, 0); i--)
	{
		const BurstSocket::BurstSocketThread::txPacketIn tx = txPackets[i];
		String msg(&(tx.message[0]), tx.messageSize);
		
		Colour meBgColor(0xffacffa3);
		Colour senderBgColor(0xffb1ddff);
		Colour timeColor(isPrivate && !global ? Colours::whitesmoke.withAlpha(0.5f) : Colours::grey);
		Colour outlineColor(Colours::lightgrey.withAlpha(0.3f));
		Colour txtColor(tx.txid == 0 ? Colours::black.withAlpha(0.3f) : Colours::black);
				
		if (tx.isText == false)
		{
			msg = msg.upToFirstOccurrenceOf(" [", false, true) + " \ndouble click to save";
			txtColor = (isPrivate && !global ? Colour(0xff92bbdc) : Colour(0xff00569c));
			outlineColor = Colours::black;
		}
		const bool date = ((Time::currentTimeMillis() / 1000) - tx.timestamp > 60 * 60 * 24);
		const String tcStr(Time(tx.timestamp * 1000).toString(date, true, true));
		const String sender(accountNames[String(tx.sender)].replace(";", " / "));
		const String recipient(accountNames[String(tx.recipient)].replace(";", " / "));
		

		g.setFont(18);
		float textWidth = (float)g.getCurrentFont().getStringWidth(msg);
		int numLines = (int)(((float)textWidth / baseWidth) + 1) + (msg.retainCharacters("\n").length());
		lines += numLines;
		int y1 = getHeight() - ((timeHeight * ((txPackets.size()-1) - i)) + (rowH * lines));
		int h = (numLines * (rowH - timeHeight));
		bool myMessage = tx.sender == senderID;
		int cornerSize = 6;
				
		// BUBBLE
		int scrollBarWidth = 15;
		juce::Rectangle<float> bubble(5.f, y1, getWidth() - 10.f - scrollBarWidth, h);

		if (clip.contains(bubble.toNearestInt()))
		{
			// TEXT
			GlyphArrangement arr = DrawFittedText(g, msg, bubble.reduced(10, 7).toNearestInt(), myMessage ? Justification::right : Justification::left, numLines, 1.0f);
			float newWidth = arr.getBoundingBox(0, arr.getNumGlyphs(), true).getWidth();

			if (myMessage)
				bubble = bubble.withTrimmedLeft(bubble.getWidth() - (newWidth + 20));
			else bubble.setWidth(newWidth + 20);
			bubbles.add(bubble); // click tracker
			
			g.setColour(outlineColor);
			g.drawRoundedRectangle(bubble, cornerSize, 2);
			g.setColour(myMessage ? meBgColor : senderBgColor);
			g.fillRoundedRectangle(bubble, cornerSize);

			g.setColour(txtColor);
			arr.draw(g);

			// TIME and SENDER
			g.setColour(timeColor);
			g.setFont(15.0f);
			g.drawSingleLineText(
				tcStr + (isPrivate && !global ? "" : (" " + sender)) + (global && recipient.isNotEmpty() ? " to " + recipient : ""),
				myMessage ? getWidth() - 10.f - scrollBarWidth : 10, 
				y1 - 5,
				myMessage ? Justification::right : Justification::left);
		}
	}
	linesNum = lines;

	int h = ((jmax<int>(linesNum, txPackets.size())) * rowH) + ((txPackets.size() + 1) * (timeHeight));
	if (h != getHeight())
	{
		bool isAtBottom = false; // if the view is at bottom. them make sure it stays there
		listenersChatBox.call(&ChatBoxListener::PrimeResize, isAtBottom);
		setSize(getWidth(), h);
		if (isAtBottom)
			listenersChatBox.call(&ChatBoxListener::ScrollToBottom, h);
	}
}

GlyphArrangement MessageList::DrawFittedText(Graphics& g, const String& text, juce::Rectangle<int> area,
	Justification justification,
	const int maximumNumberOfLines,
	const float minimumHorizontalScale)
{
	GlyphArrangement arr;
	if (text.isNotEmpty() && (!area.isEmpty()) && g.getInternalContext().clipRegionIntersects(area))
	{
		arr.addFittedText(g.getInternalContext().getFont(), text,
			(float)area.getX(), (float)area.getY(),
			(float)area.getWidth(), (float)area.getHeight(),
			justification,
			maximumNumberOfLines,
			minimumHorizontalScale);
	}
	return arr;
}

void MessageList::resized()
{
}

void MessageList::mouseDown(const MouseEvent& event)
{
}

void MessageList::mouseDoubleClick(const MouseEvent& event)
{
	Point<int> point = event.getPosition();
	juce::Rectangle<float> pr(point.toFloat(), point.toFloat());
	for (int i = 0; i < bubbles.size(); i++)
	{
		if (bubbles[i].contains(pr))
		{
			const int rIdx = txPackets.size() - (i + 1);
			if (rIdx >= 0)
			{ // check if its text or a file stream/download
				BurstSocket::BurstSocketThread::txPacketIn tx = txPackets[rIdx];
				String msg(&(tx.message[0]), tx.messageSize);
				if (tx.isText)
					SystemClipboard::copyTextToClipboard(msg);
				else
				{
					String fileStr(msg.upToFirstOccurrenceOf("[", false, true));
					FileChooser dirChooser("Save " + fileStr + "to folder...", File::getSpecialLocation(File::userDesktopDirectory), "*.*");
					if (dirChooser.browseForDirectory())
					{
						String hashStr(msg.fromLastOccurrenceOf("[", false, true).upToFirstOccurrenceOf("]", false, true));
						MemoryBlock hash;
						hash.loadFromHexString(hashStr);
						chatListeners.call(&ChatComponentListener::SaveFileStream, dirChooser.getResult(), hash);
					}
				}
			}
		}
		else if (bubbles[i].translated(0, -12).withHeight(12).contains(pr))
		{
			const int rIdx = txPackets.size() - (i + 1);
			if (rIdx >= 0)
			{ // check if its text or a file stream/download
				BurstSocket::BurstSocketThread::txPacketIn tx = txPackets[rIdx];
				const String sender(accountNames[String(tx.sender)].replace(";", " / "));
				SystemClipboard::copyTextToClipboard(sender);
			}
		}
	}
}

void MessageList::AddUnconfirmedSendMessage(String msg)
{
	BurstSocket::BurstSocketThread::txPacketIn txPacket = BurstSocket::BurstSocketThread::initPacketIn();
	msg.copyToUTF8(&(txPacket.message[0]), MAX_TXDATASIZE);
	txPacket.messageSize = msg.length();
	txPacket.isText = true;
	txPacket.timestamp = Time::currentTimeMillis() / 1000;
	txPacket.txid = 0;
	txPacket.sender = senderID;
	txPacket.recipient = receiverID;

	AddPacketToList(txPacket);

	String displayName;
	if (accountNames[String(txPacket.sender)].isEmpty())
	{
		interfaceListeners.call(&InterfaceListener::GetAccountDisplayName, txPacket.sender, String(txPacket.sender), displayName);
		accountNames.set(String(txPacket.sender), displayName);
	}
	if (accountNames[String(txPacket.recipient)].isEmpty())
	{
		interfaceListeners.call(&InterfaceListener::GetAccountDisplayName, txPacket.recipient, String(txPacket.recipient), displayName);
		accountNames.set(String(txPacket.recipient), displayName);
	}

	int rowH = 25;
	int h = (jmax<int>(linesNum, txPackets.size()) * rowH) + (txPackets.size() * rowH);
	if (h != getHeight())
	{
		bool isAtBottom = false; // if the view is at bottom. them make sure it stays there
		listenersChatBox.call(&ChatBoxListener::PrimeResize, isAtBottom);
		setSize(getWidth(), h);
		if (isAtBottom)
			listenersChatBox.call(&ChatBoxListener::ScrollToBottom, h);
	}

	repaint();
}

void MessageList::SetFilters(uint64 idSender, uint64 idReceiver, bool isPrivate)
{
	senderID = idSender;
	receiverID = idReceiver;
	this->isPrivate = isPrivate;

	if (idSender != 0 || idReceiver != 0 || isPrivate != 0) // ignore new tab
	{
#if ENABLE_MESSGE_LOG == 1
		const File logFileToWriteTo(File::getSpecialLocation(File::SpecialLocationType::userDocumentsDirectory).getChildFile(ProjectInfo::projectName).getChildFile(String(idReceiver) + "-" + String(idReceiver) + "-" + String(isPrivate)).withFileExtension("chatlog"));
		if (logFileToWriteTo.existsAsFile())
		{ // load the old messages
			StringArray lines;
			logFileToWriteTo.readLines(lines);
			Array<uint64> addresses;
			for (int i = 0; i < lines.size(); i++)
			{
				BurstSocket::BurstSocketThread::txPacketIn txPacket = BurstSocket::BurstSocketThread::initPacketIn();
				var jsonStructure;
				Result r = JSON::parse(lines[i], jsonStructure);
				txPacket.timestamp = GetUINT64(jsonStructure.getProperty("t", String::empty).toString());
				if (txPacket.timestamp > 0)
				{
					txPacket.txid = 1;
					
					txPacket.sender = (uint64)juce::VariantConverter<int64>::fromVar(jsonStructure["s"]);// json var doesnt handle uint64 well.
					txPacket.recipient = (uint64)juce::VariantConverter<int64>::fromVar(jsonStructure["r"]);
					txPacket.encrypted = jsonStructure.getProperty("e", String::empty).toString().getIntValue();
					txPacket.isText = true;
					String str = jsonStructure.getProperty("m", String::empty).toString();
					str.copyToUTF8(&(txPacket.message[0]), MAX_TXDATASIZE);
					txPacket.messageSize = str.length();
					AddPacketToList(txPacket);
					String sA = jsonStructure.getProperty("sA", String::empty);
					String rA = jsonStructure.getProperty("rA", String::empty);
					if (sA.isNotEmpty())
						accountNames.set(String(txPacket.sender), sA);
					if (rA.isNotEmpty())
						accountNames.set(String(txPacket.recipient), rA);
				}
			}
		}
		if (!log && logFileToWriteTo.getFullPathName().isNotEmpty())
			log = new FileLogger(logFileToWriteTo, "", 1000 * 1000);
#endif // ENABLE_MESSGE_LOG
	}
}

void MessageList::AddPacketToList(BurstSocket::BurstSocketThread::txPacketIn txPacket)
{
	txPackets.add(txPacket);
	if (txPackets.size() > 512) // anti overflow
		txPackets.remove(0);
}

void MessageList::AddMessage(BurstSocket::BurstSocketThread::txPacketIn txPacket)
{
		// check if txPacket is meant for this list
	if (((receiverID == txPacket.recipient && txPacket.encrypted == false && isPrivate == false) || // room message
		((receiverID == txPacket.sender || receiverID == txPacket.recipient) && txPacket.encrypted && isPrivate) || // private message
		(senderID == receiverID && isPrivate) || // tab wants to have everything
		(receiverID == 0 && senderID == 0)))
	{
		String displayName;
		if (accountNames[String(txPacket.sender)].isEmpty())
		{
			interfaceListeners.call(&InterfaceListener::GetAccountDisplayName, txPacket.sender, String(txPacket.sender), displayName);
			accountNames.set(String(txPacket.sender), displayName);
		}
		if (accountNames[String(txPacket.recipient)].isEmpty())
		{
			interfaceListeners.call(&InterfaceListener::GetAccountDisplayName, txPacket.recipient, String(txPacket.recipient), displayName);
			accountNames.set(String(txPacket.recipient), displayName);
		}

		// Update unconfirmed messages
		bool replaced = false;
		bool duplicate = false;		
		for (int i = 0; i < txPackets.size(); i++)
		{
			if (txPacket.sender == senderID && 
				(txPackets[i].txid == 0 && txPackets[i].recipient != 0) &&
				!replaced)
			{
				String str1(&(txPacket.message[0]), txPacket.messageSize);
				String str2(&(txPackets[i].message[0]), txPackets[i].messageSize);
				if (str1.compare(str2) == 0)
				{
					txPackets.getReference(i) = txPacket;
					replaced = true;
				}
				else if (str1.contains(" [") && str1.endsWith("]"))
				{ // data stream / file upload
					String fileName = String(str1.upToFirstOccurrenceOf(" [", false, true)).trim();
					if (fileName.isNotEmpty() && (fileName.compare(str2) == 0))
					{
						txPackets.getReference(i) = txPacket;
						replaced = true;
					}
				}
			}
			if (txPackets[i].txid == txPacket.txid)
				duplicate = true;
		}
		if (!replaced && !duplicate) // or just add it to the list
			AddPacketToList(txPacket);

		
		if (duplicate == false)
		{
			String msg;
			char *t = &(txPacket.message[0]);
			if (t != nullptr && CharPointer_ASCII::isValidString(t, txPacket.messageSize));
			msg = String(&(txPacket.message[0]), txPacket.messageSize);

#if ENABLE_MESSGE_LOG == 1
			String logOn;
			interfaceListeners.call(&InterfaceListener::GetAppValue, "log", logOn);
			if (log && logOn.getIntValue() > 0)
			{ // keep a log. will be reloaded at next open tab
				const String senderAlias(accountNames[String(txPacket.sender)]);
				const String recipientAlias(accountNames[String(txPacket.recipient)]);

				String jsonMsg = "{\"t\":" + String(txPacket.timestamp) + ",";
				jsonMsg += "\"sA\":\"" + JSON::escapeString(senderAlias) + "\",";
				jsonMsg += "\"rA\":\"" + JSON::escapeString(recipientAlias) + "\",";
				jsonMsg += "\"s\":" + String(txPacket.sender) + ",";
				jsonMsg += "\"r\":" + String(txPacket.recipient) + ",";
				jsonMsg += "\"e\":" + String(txPacket.encrypted) + ",";

				if (msg.isNotEmpty())
				{
					jsonMsg += "\"m\":\"" + JSON::escapeString(msg) + "\"}"; // CRASH non valid string
					log->logMessage(jsonMsg);
				}
			}
#endif //ENABLE_MESSGE_LOG
			chatListeners.call(&ChatComponentListener::NotifyTab, txPacket.sender, txPacket.recipient, txPacket.encrypted, msg);

			int rowH = 25;
			int h = (jmax<int>(linesNum, txPackets.size()) * rowH) + (txPackets.size() * rowH);
			if (h != getHeight())
			{
				bool isAtBottom = false; // if the view is at bottom. them make sure it stays there
				listenersChatBox.call(&ChatBoxListener::PrimeResize, isAtBottom);
				setSize(getWidth(), h);
				if (isAtBottom)
					listenersChatBox.call(&ChatBoxListener::ScrollToBottom, h);
			}
		}
		repaint();
	}
}
