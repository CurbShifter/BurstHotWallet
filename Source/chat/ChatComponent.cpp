/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "BurstSocket.h"

#define CHAT_INSTRUCTIONS_TITLE "BurstChat BETA"
#define CHAT_INSTRUCTIONS "BurstChat messages are fast, cheap and exist only temporary on the network. Any recipients need to be online at the same time!\n\n\
Socket tokens are traded while chatting, designed to open the network and make the chat message transactions free.\n\n\
Enter a channel name (a burst alias or address or number) to enter a public group chatroom or a private one-on-one chat.\n\n\
Note; NO guarantees are given! Creating a new wallet with a low balance is recommended."
//[/Headers]

#include "ChatComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ChatComponent::ChatComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (menu = new Menu());
    menu->setName ("menu");


    //[UserPreSize]
//	drawable1 = Drawable::createFromImageData(BinaryData::leafdew_svg, BinaryData::leafdew_svgSize);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	menu->addChatListener(this);
	addMenuListener(menu);

	burning = true;
	slot = 0;
	pressure = 0.f;
	activeMessages = 0;
	maxActive = 0;
	notify = 0;
	next_banner_poll_ms = 0;

	ActivateTab(-1, false);

	startTimer(INTERFACE_UPDATE_MS);
    //[/Constructor]
}

ChatComponent::~ChatComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	const String accountRS = burstSocket.GetAccountRS();
	StringArray sa = menu->GetRoomNames();
	interfaceListeners.call(&InterfaceListener::SetAppValue, accountRS + "-openTabs", sa.joinIntoString(","));

	burstSocket.CloseSocket();
    //[/Destructor_pre]

    menu = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
	drawable1 = nullptr;
    //[/Destructor]
}

//==============================================================================
void ChatComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	/*
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    g.setColour (Colour (0xff77b517));
    g.fillRect (180, 4, 436, 44);

    g.setColour (Colour (0xff3f514e));
    g.fillRect (180, 48, 436, 440);

    //[UserPaint] Add your own custom painting code here..
	*/

	g.setColour(Colour(0xff3f514e));
	g.fillRect(getBounds().withZeroOrigin().withTrimmedLeft(200).toFloat());

	//g.setColour(Colours::black);
	//g.drawImage(cachedImage_leaf_jpg_1, getBounds().withZeroOrigin().withTrimmedLeft(200).toFloat(), juce::RectanglePlacement::Flags::fillDestination);

	g.setGradientFill(ColourGradient(Colours::black.withAlpha(0.75f), 0.0f, getHeight() / 2, Colour(0x00142014), 0.0f, getHeight(), false));
	g.fillAll();

	g.setColour(Colours::white);
	g.setFont(30);
	g.drawFittedText(CHAT_INSTRUCTIONS_TITLE, getBounds().withZeroOrigin().withTrimmedLeft(200).reduced(50).withHeight(70), Justification::left, 10, 1.f);
	g.setFont(20);
	g.setColour(Colours::whitesmoke);
	g.drawFittedText(CHAT_INSTRUCTIONS, getBounds().withZeroOrigin().withTrimmedLeft(200).reduced(70).withTrimmedTop(60), Justification::left, 10, 1.f);
    //[/UserPaint]
}

void ChatComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	/*
    //[/UserPreResize]

    menu->setBounds (0, 0, 176, 488);
    //[UserResized] Add your own custom resize handling here..
	*/
	juce::Rectangle<float> r = getBounds().withZeroOrigin().toFloat();

	const int cSize = 120;
	const int cH = 48;
	const int tgw = 50;
	const int topH = 16;
	const int menuWidth = 200;

	juce::Rectangle<int> ri2(r.withHeight(topH).withTrimmedLeft(3).withTrimmedRight((cSize + tgw)).reduced(0, 1).translated(0, 2).toNearestInt());
	juce::Rectangle<int> ri0(r.withHeight(cH - topH).withTrimmedLeft(3).withTrimmedRight((cSize + tgw)).reduced(0, 3).translated(0, topH).toNearestInt());
	juce::Rectangle<int> ri1(r.withHeight(cH / 2).translated(0, cH / 4).withTrimmedLeft(r.getWidth() - (cSize + tgw)).withTrimmedRight(tgw).reduced(0, 3).toNearestInt());

	menu->setBounds(r.withWidth(menuWidth).toNearestInt());

	for (int i = 0; i < chatComponents.size(); i++)
		chatComponents.getReference(i)->setBounds(r.withTrimmedLeft(menuWidth).toNearestInt());
    //[/UserResized]
}

bool ChatComponent::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
#ifdef _DEBUG
	if (key.isKeyCode(key.F12Key))
	{
		if (NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Create asset?"))
		{
			String str = burstSocket.CreateAsset();
			NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "asset ID: " + str + " copied to clipboard");
			SystemClipboard::copyTextToClipboard(str);
		}
	}
	else if (key.isKeyCode(key.F11Key))
	{
		if (NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Fill order book?"))
		{
			for (uint64 step = 0; step < SOCKET_ASSET_ORDERBOOK_MAX_STEPS; step++)
			{
				String r = burstSocket.FillOrderBook(step);
				NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, String(step+1) + " of " + String(SOCKET_ASSET_ORDERBOOK_MAX_STEPS) + ":\n" + r);
			}
			NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Fill order book done.");
		}
	}
	else return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
#endif
	return true;
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ChatComponent::SetNode(const String server, const bool allowNonSSL)
{
	const ScopedLock lock(burstSktLock);
	burstSocket.SetNode(server);
}

void ChatComponent::SetSecretPhrase(const String passphrase)
{
	RemoveAllTabs();

	const ScopedLock lock(burstSktLock);
	CloseSocket();
	burstSocket.SetSecretPhrase(passphrase);

	menu->SetAccountRS(burstSocket.GetAccountRS());

	if(passphrase.isNotEmpty())
		OpenChannels();
}

void ChatComponent::SetForceSSL_TSL(const bool forceSSLOn)
{
	const ScopedLock lock(burstSktLock);
	burstSocket.SetForceSSL_TSL(forceSSLOn);
}

void ChatComponent::SetNodeHop(const bool hopOn)
{
	const ScopedLock lock(burstSktLock);
	//burstSocket.EnableNodeHop(hopOn ? 7 : 0);
}

void ChatComponent::GetHoldSize(int &holdMultiplier)
{
	const ScopedLock lock(burstSktLock);
	holdMultiplier = burstSocket.GetHoldSize();
}

void ChatComponent::SetHoldSize(const int newHoldMultiplier)
{
	const ScopedLock lock(burstSktLock);
	burstSocket.SetHoldSize(newHoldMultiplier);
}

void ChatComponent::textEditorTextChanged(TextEditor &) //Called when the user changes the text in some way.
{
}
void ChatComponent::textEditorReturnKeyPressed(TextEditor &) //Called when the user presses the return key.
{
}
void ChatComponent::textEditorEscapeKeyPressed(TextEditor &/*editor*/) //Called when the user presses the escape key.
{
}
void ChatComponent::textEditorFocusLost(TextEditor &) //Called when the text editor loses focus.
{
}

void ChatComponent::OpenChannels()
{
	const String accountRS = burstSocket.GetAccountRS();

	String openTabs;
	interfaceListeners.call(&InterfaceListener::GetAppValue, accountRS + "-openTabs", openTabs);
	StringArray sa = StringArray::fromTokens(openTabs, ",", "");
	if (sa.size() > 0)
	{
		for (int i = 0; i < sa.size(); i++)
			NewTab(sa[i], !(sa[i].startsWithChar('#')), false);
	}
	else NewTab("HotWallet", false, false);

	menuListeners.call(&MenuListener::ReloadChannelItems);
}

void ChatComponent::Init()
{
	String tokenHoldSize;
	interfaceListeners.call(&InterfaceListener::GetAppValue, "tokenHoldSize", tokenHoldSize);
	int tokenHoldSizeInt = tokenHoldSize.getIntValue();
	SetHoldSize(tokenHoldSizeInt);
}

bool ChatComponent::CheckOpenChannel()
{
	if (balance.getLargeIntValue() > 200000000)
	{
		OpenSocket(); // auto open the socket if needed
		return true;
	}
	else if (balance.getLargeIntValue() < 200000000)
	{
		NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "balance is too low: " + balance + " NQT");
	}
	return false;
}

void ChatComponent::SocketSendMessage(const String port, const String txt, const bool encrypted)
{
	if (CheckOpenChannel())
		burstSocket.SocketSendMessage(port.isEmpty() ? burstSocket.GetAccountRS() : port, txt, encrypted);
}

void ChatComponent::SocketSendFile(const String port, const File f, const bool encrypted)
{
	if (CheckOpenChannel())
		burstSocket.SocketSendFile(port.isEmpty() ? burstSocket.GetAccountRS() : port, f, encrypted);
}

void ChatComponent::SaveFileStream(File dir, MemoryBlock hash)
{
	if (dir.exists() == false)
		return;

	char type = 0;
	BurstSocket::BurstSocketThread::txPacketIn tx;
	String name;
	MemoryBlock data;
	burstSocket.GetDataStreamPacket(hash, type, tx, name, data);
	if (data.getSize() > 0 && name.isNotEmpty())
	{
		if (dir.getChildFile(name).existsAsFile() == false ||
			(dir.getChildFile(name).existsAsFile() && NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, "Overwrite existing file?") == 1))
		{
			if (dir.getChildFile(name).deleteFile())
				dir.getChildFile(name).appendData(data.getData(), data.getSize());
			else NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Failed to save ! existing file could not be removed?");
		}
	}
}

void ChatComponent::SetAssetsBalances(const StringPairArray assetsBalances)
{
	this->assetsBalances = assetsBalances;
	this->balance = assetsBalances["0"];

	menuListeners.call(&MenuListener::SetAccountRS, burstSocket.GetAccountRS());
}

void ChatComponent::ActivateTab(const int index, const bool forceShow)
{
	if (index < 0)
	{
		for (int i = 0; i < chatComponents.size(); i++)
			chatComponents.getReference(i)->setVisible(false);
		repaint();
	}
	else
	{
		for (int i = 0; i < chatComponents.size(); i++)
			chatComponents.getReference(i)->setVisible(index == i && forceShow);
	}
}

void ChatComponent::NewTab(const String recipient, bool isPrivate, bool forceShow)
{
	String targetAddress = recipient.trim();
	if (targetAddress.isEmpty())
		return;

	if (targetAddress.startsWithChar('#') || targetAddress.startsWithChar('@'))
		targetAddress = targetAddress.substring(1);
	bool global = targetAddress.startsWithChar('*');

	if (targetAddress.contains(";"))
	{
		// check if any of the aliases is already open as a tab.
		StringArray aliases = StringArray::fromTokens(targetAddress, ";", "");
		targetAddress = menu->FindActiveTabWithAlias(aliases);
	}
	int tab_idx = -1;
	String targetId = burstSocket.convertToAccountID(targetAddress, true);
	if (targetId.isNotEmpty() || global) // check validity of recipient, (resolve alias/str to BURST RS)
	{
		String name;
		if (global == false)
			name = ((isPrivate ? "" : "#") + (isPrivate && targetAddress.startsWithChar('@') ? targetAddress.substring(1) : targetAddress));
		else
		{
			name = "*";
			targetId = burstSocket.GetAccountID();
			targetAddress = "*";
			isPrivate = true;
		}

		//tab_idx = menu->GetRoomNames().indexOf(name, true, 0);
		// convert room names to account ids
		// find index of targetId
		StringArray roomNames = menu->GetRoomNames();
		for (int i = 0; i < roomNames.size(); i++)
		{
			String roomId = burstSocket.convertToAccountID(roomNames[i].replaceCharacters("#@", "  ").trim(), true);
			if (roomId.compareIgnoreCase(targetId) == 0 && // same id
				(isPrivate == !(roomNames[i].contains("#")))) // check private or public
				tab_idx = i;
		}

		if (tab_idx == -1) // check if a tab with same settings exists
		{
			if (menu->GetRoomNames().size() < 100) // no more than 100 tabs
			{
				uint64 senderID = burstSocket.GetUINT64(burstSocket.GetAccountID());
				ChatBox *chatBox = new ChatBox(senderID, burstSocket.GetUINT64(targetId), targetAddress, isPrivate);
				if (chatBox)
				{
					addChildComponent(chatBox, 0);

					chatComponents.add(chatBox);
					menu->AddTab(name, burstSocket.GetUINT64(burstSocket.GetAccountID()), burstSocket.GetUINT64(targetId), targetAddress, isPrivate, -1, forceShow);

					Viewport *messageViewport = (Viewport *)chatBox->findChildWithID("messageViewport");
					chatBox->addListener(this);
					addChatBoxListener(chatBox);

					if (messageViewport)
					{
						MessageList *messageList = (MessageList *)messageViewport->getViewedComponent();
						if (messageList)
						{
							messageList->addChatListener(this);
							addMessageListListener(messageList);
						}
					}
					{
						juce::Rectangle<float> r = getBounds().toFloat();
						const int menuWidth = 200;
						chatBox->setBounds(r.withTrimmedTop(28).withTrimmedLeft(menuWidth).toNearestInt());
					}
					resized();
				}
			}
		}
		else
		{ // show the existing tab
			if (forceShow)
				menuListeners.call(&MenuListener::ActivateTab, tab_idx, true);
		}
	}
	else
	{
		if (forceShow && burstSocket.getConstants().isNotEmpty())
			NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Invalid address !");
	}
}

void ChatComponent::RemoveAllTabs()
{
	for (int tabIndex = 0; tabIndex < chatComponents.size(); tabIndex++)
		RemoveTab(tabIndex);
}

void ChatComponent::RemoveTab(int tabIndex)
{
	if (tabIndex >= 0 && tabIndex < chatComponents.size())
	{
		ChatBox *chatBox = chatComponents.getReference(tabIndex);
		removeChatBoxListener(chatBox);

		Viewport *messageViewport = (Viewport *)chatBox->findChildWithID("messageViewport");
		if (messageViewport)
		{
			MessageList *messageList = (MessageList *)messageViewport->getViewedComponent();
			if (messageList)
				removeMessageListListener(messageList);
		}
		chatComponents.remove(tabIndex);
		menuListeners.call(&MenuListener::RemoveTab, tabIndex);
	}
}

void ChatComponent::RemoveTab(uint64 recipientID, bool isPriv)
{
	if (NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Close this tab?") == 1)
	{
		// remove the listeners !
		uint64 senderID = 0;
		uint64 receiverID = 0;
		bool isPrivateChannel = false;
		String receiverChannel;

		int tabIndex = FindTab(recipientID, isPriv,
			senderID,
			receiverID,
			isPrivateChannel,
			receiverChannel);

		RemoveTab(tabIndex);
		ActivateTab(-1, false);
	}
}

void ChatComponent::NotifyTab(uint64 recipientID, uint64 senderID, bool isPriv, String msg)
{
	// TAB NOTIFIER if other tab than current gets a message
	menuListeners.call(&MenuListener::NotifyTab, recipientID, senderID, isPriv, msg);

	if (hasKeyboardFocus(true) == false)
	{
		notify++;
	}
}

int ChatComponent::FindTab(uint64 recipientID, bool isPriv,
	uint64 &senderID,
	uint64 &receiverID,
	bool &isPrivateChannel,
	String &receiverChannel)
{
	for (int i = 0; i < chatComponents.size(); i++)
	{
		ChatBox *chatBox = chatComponents.getReference(i);

		chatBox->GetChatProperties(senderID, receiverID, isPrivateChannel, receiverChannel);

		if (receiverID == recipientID && isPriv == isPrivateChannel)
		{
			return i;
		}
	}
	return -1;
}

void ChatComponent::OpenCloseSocket(const bool open) // called from menu
{
	if (burstSocket.isSocketOpen())
	{
		if (open == false && NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Stop updating chat?"))
			CloseSocket();
	}
	else
	{
		if (open && NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Start updating chat?"))
			OpenSocket();
	}
}

void ChatComponent::OpenSocket()
{
	if (burstSocket.isSocketOpen() == false)
	{
		burstSocket.OpenSocket();
		menuListeners.call(&MenuListener::SetStatusText, "online", 0.f);
		menuListeners.call(&MenuListener::SetIsOnline, true);

		String stayOnlineStr;
		interfaceListeners.call(&InterfaceListener::GetAppValue, "stayOnline", stayOnlineStr);
		const bool stayOnline = stayOnlineStr.getIntValue() > 0;

	}
}

void ChatComponent::CloseSocket()
{
	if (burstSocket.isSocketOpen())
	{
		burstSocket.CloseSocket();
		menuListeners.call(&MenuListener::SetStatusText, "offline", 1.f);
		menuListeners.call(&MenuListener::SetIsOnline, false);
	}
}

void ChatComponent::SetForceBlock(const bool stayOnline)
{
	burstSocket.SetForceBlock(stayOnline);
}

void ChatComponent::timerCallback()
{
	if (burstSocket.isSocketOpen())
	{
		BurstSocket::BurstSocketThread::txPacketIn p = BurstSocket::BurstSocketThread::initPacketIn();
		uint64 id = burstSocket.GetUINT64(burstSocket.GetAccountID());
		while (burstSocket.SocketPollMessage(p))
		{
			if (p.recipient == id && p.encrypted) // check if its a DM to the local user. and auto open a DM tab if needed
			{
				BurstAddress burstAddress;
				String tabName(burstAddress.encode(p.sender)); //GetAccountDisplayName(p.sender, tabName);
				NewTab(tabName, true, false);
			}
			messageListListeners.call(&MessageListListener::AddMessage, p); // push into tabs
		}

		burstSocket.GetStatus(burning, slot, pressure, activeMessages, maxActive);

		chatBoxListeners.call(&ChatBoxListener::SetMaxETx, maxActive - activeMessages);

		double prog = (double)activeMessages / (double)maxActive;
		String statusText("online ");
		if (burning)
			statusText += ("slot " + String(slot + 1) + " " + String((int)(pressure * 100)) + "%");
		else statusText += (String(activeMessages) + " / " + String(maxActive) + " Tx");

		menuListeners.call(&MenuListener::SetStatusText, statusText, prog);

		if (notify > 0)
		{
			notify = 0;

			interfaceListeners.call(&InterfaceListener::SystemTrayNotify, "New message(s)", "", true);

#ifdef JUCE_WINDOWS
			FLASHWINFO fwi;
			fwi.cbSize = sizeof(fwi);
			fwi.hwnd = static_cast<HWND>(getWindowHandle());
			fwi.dwFlags = FLASHW_TIMERNOFG | FLASHW_TRAY; // FLASHW_ALL
			fwi.uCount = 10;
			fwi.dwTimeout = 0;
			FlashWindowEx(&fwi);
#elif JUCE_MAC
			//MacOSUserNotification notifier; // depreciated
			//notifier.Send(ProjectInfo::projectName, msg.toUTF8());
#endif
		}

		repaint();
	}
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ChatComponent" componentName=""
                 parentClasses="public TextEditorListener, public Timer, public ChatComponentListener, public Component"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <METHODS>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff000000">
    <RECT pos="180 4 436 44" fill="solid: ff77b517" hasStroke="0"/>
    <RECT pos="180 48 436 440" fill="solid: ff3f514e" hasStroke="0"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="menu" id="fd2ff7007855d980" memberName="menu" virtualName=""
                    explicitFocusOrder="0" pos="0 0 176 488" class="Menu" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
