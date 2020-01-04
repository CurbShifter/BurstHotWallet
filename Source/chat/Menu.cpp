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
//[/Headers]

#include "Menu.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Menu::Menu ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (privateChatButton = new TextButton ("privateChatButton"));
    privateChatButton->setTooltip (TRANS("A private encrypted chat between you and the account entered above"));
    privateChatButton->setExplicitFocusOrder (6);
    privateChatButton->setButtonText (TRANS("Open private chat"));
    privateChatButton->addListener (this);
    privateChatButton->setColour (TextButton::buttonColourId, Colour (0xff191919));
    privateChatButton->setColour (TextButton::buttonOnColourId, Colour (0xff404040));
    privateChatButton->setColour (TextButton::textColourOffId, Colours::white);
    privateChatButton->setColour (TextButton::textColourOnId, Colours::white);

    addAndMakeVisible (publicRoomButton = new TextButton ("publicRoomButton"));
    publicRoomButton->setTooltip (TRANS("Will open or enter a room for the account entered above. The chat will be visible to anyone! Others can connect to this same room to talk to you"));
    publicRoomButton->setExplicitFocusOrder (5);
    publicRoomButton->setButtonText (TRANS("Open public room"));
    publicRoomButton->addListener (this);
    publicRoomButton->setColour (TextButton::buttonColourId, Colour (0xff77b517));
    publicRoomButton->setColour (TextButton::buttonOnColourId, Colours::chartreuse);
    publicRoomButton->setColour (TextButton::textColourOffId, Colours::white);
    publicRoomButton->setColour (TextButton::textColourOnId, Colours::white);

    addAndMakeVisible (channelNameComboBox = new ComboBox ("channelNameComboBox"));
    channelNameComboBox->setTooltip (TRANS("Select a room from the pop-up list. Or enter an alias, RS or account ID. \n"
    "for example: \n"
    "Agora\n"
    "BURST-XXX.. or \n"
    "1234"));
    channelNameComboBox->setExplicitFocusOrder (4);
    channelNameComboBox->setEditableText (true);
    channelNameComboBox->setJustificationType (Justification::centredLeft);
    channelNameComboBox->setTextWhenNothingSelected (TRANS("BurstExtensions"));
    channelNameComboBox->setTextWhenNoChoicesAvailable (TRANS("BurstExtensions"));
    channelNameComboBox->addListener (this);

    addAndMakeVisible (slotFeeButton = new TextButton ("slotFeeButton"));
    slotFeeButton->setTooltip (TRANS("Current client network status"));
    slotFeeButton->setButtonText (TRANS("0/0 messages"));
    slotFeeButton->addListener (this);
    slotFeeButton->setColour (TextButton::buttonColourId, Colour (0x00bbbbff));
    slotFeeButton->setColour (TextButton::textColourOffId, Colours::black);
    slotFeeButton->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (chatlist = new ListBox());
    chatlist->setName ("chatlist");


    //[UserPreSize]
	sourceModel.setParent(this);
	chatlist->setModel(&sourceModel);
	chatlist->setRowHeight(28);

	isOnline = false;

	channelNameComboBox->setTextWhenNothingSelected(TRANS("channel name"));
	channelNameComboBox->setTextWhenNoChoicesAvailable(TRANS("channel name"));

	channelNameComboBox->addItem("HotWallet", 1);
	channelNameComboBox->addItem("*", 2);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	slotFeeButton->setButtonText("BurstChat");
	slotFeeButton->setColour(TextButton::buttonColourId, Colour(0xFF388c3d));
    //[/Constructor]
}

Menu::~Menu()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    privateChatButton = nullptr;
    publicRoomButton = nullptr;
    channelNameComboBox = nullptr;
    slotFeeButton = nullptr;
    chatlist = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Menu::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    /*
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
	*/
	g.fillAll(Colour(0xffd2d2d2));
    //[/UserPaint]
}

void Menu::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	/*
    //[/UserPreResize]

    privateChatButton->setBounds (0, 256, 160, 24);
    publicRoomButton->setBounds (0, 224, 160, 24);
    channelNameComboBox->setBounds (0, 192, 160, 24);
    slotFeeButton->setBounds (0, 0, 160, 48);
    chatlist->setBounds (0, 56, 160, 128);
    //[UserResized] Add your own custom resize handling here..
	*/
	juce::Rectangle<float> r = getBounds().withZeroOrigin().toFloat();

	int baseH = 40;
	int baseH2 = 35;

	slotFeeButton->setBounds(r.withHeight(baseH).reduced(5).toNearestInt());

	chatlist->setBounds(
		0,
		slotFeeButton->getBottom() + 20,
		(int)r.getWidth(),
		(int)(r.getHeight() - ((((uint64)slotFeeButton->getBottom()) + 20L) + (baseH2 * 3.5))));

	channelNameComboBox->setBounds(r.withTrimmedTop(r.getHeight() - (baseH2 * 3.5f)).withHeight(baseH2).reduced(2).toNearestInt());
	publicRoomButton->setBounds(r.withTrimmedTop(r.getHeight() - (baseH2 * 2.5f)).withHeight(baseH2).reduced(1).toNearestInt());
	privateChatButton->setBounds(r.withTrimmedTop(r.getHeight() - (baseH2 * 1.5f)).withHeight(baseH2).reduced(1).toNearestInt());
    //[/UserResized]
}

void Menu::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == privateChatButton)
    {
        //[UserButtonCode_privateChatButton] -- add your button handler code here..
		RequestNewTab(true);
        //[/UserButtonCode_privateChatButton]
    }
    else if (buttonThatWasClicked == publicRoomButton)
    {
        //[UserButtonCode_publicRoomButton] -- add your button handler code here..
		RequestNewTab(false);
        //[/UserButtonCode_publicRoomButton]
    }
    else if (buttonThatWasClicked == slotFeeButton)
    {
        //[UserButtonCode_slotFeeButton] -- add your button handler code here..
		ScopedPointer<PopupMenu> contextMenu;
		contextMenu = new PopupMenu;

		String stayOnlineStr;
		interfaceListeners.call(&InterfaceListener::GetAppValue, "stayOnline", stayOnlineStr);
		const bool stayOnline = stayOnlineStr.getIntValue() > 0;
		
		contextMenu->addItem(1, "Online, check for incoming messages", true, isOnline);
		contextMenu->addItem(2, "Support mode, keep chat channel open while away (optional)", true, stayOnline);

		int result = contextMenu->show();
		if (result == 1)
			ToggleSocket();
		else if (result == 2)
		{
			if (NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Turn " + String(stayOnline ? "off" : "on") + " 'stay online'?"))
			{ // toggle stay online
				String newSetting = stayOnline ? "0" : "1";
				interfaceListeners.call(&InterfaceListener::SetAppValue, "stayOnline", newSetting);
				chatListeners.call(&ChatComponentListener::SetForceBlock, !stayOnline);
			}
		}
        //[/UserButtonCode_slotFeeButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void Menu::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == channelNameComboBox)
    {
        //[UserComboBoxCode_channelNameComboBox] -- add your combo box handling code here..
		receiverChannel = channelNameComboBox->getText();
        //[/UserComboBoxCode_channelNameComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void Menu::RequestNewTab(bool priv, String name)
{
	if (name.isEmpty())
		name = channelNameComboBox->getText();
	if (name.isEmpty())
		name = channelNameComboBox->getTextWhenNothingSelected();

	if (name.isNotEmpty())
		chatListeners.call(&ChatComponentListener::NewTab, name, priv, true);
	else NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Please enter a BURST address, alias or account ID.");

	String channelsList;
	interfaceListeners.call(&InterfaceListener::GetAppValue, accountRS + "-openTabs", channelsList);
	StringArray sa = StringArray::fromTokens(channelsList, ",", "'");
	int idx = sa.indexOf(name);
	if (idx == -1)
	{
		if (sa.size() > 10)
			sa.removeRange(10, sa.size() - 10);
	}
	else
	{
		sa.removeString(name);
	}
	sa.insert(0, name);
	channelsList = sa.joinIntoString(",");
	interfaceListeners.call(&InterfaceListener::SetAppValue, accountRS + "-openTabs", channelsList);

	ReloadChannelItems();
	chatlist->updateContent();
}

void Menu::AddTab(const String &tabName, uint64 senderID, uint64 receiverID, String receiver, bool privateChannel, const int insertIndex, const bool forceShow)
{
	tabprops tp;
	tp.name = tabName;
	tp.senderID = senderID;
	tp.receiverID = receiverID;
	tp.receiver = receiver;
	tp.privateChannel = privateChannel;
	tp.notify = 0;
	tabs.add(tp);

	ReloadChannelItems();

	ActivateTab(tabs.size() - 1, forceShow);
	chatlist->updateContent();
}

void Menu::RemoveTab(const int index)
{
	tabs.remove(index);
	chatlist->updateContent();
	chatlist->deselectAllRows();
}

void Menu::TriggerRemoveTab(const int index)
{
	if (index < tabs.size())
	{
		tabprops &tp = tabs.getReference(index);
		chatListeners.call(&ChatComponentListener::RemoveTab, tp.receiverID, tp.privateChannel);
	}
}

void Menu::ReloadChannelItems()
{
	String channelsList;
	interfaceListeners.call(&InterfaceListener::GetAppValue, accountRS + "-openTabs", channelsList);
	StringArray sa = StringArray::fromTokens(channelsList.replaceCharacters("#@", "  "), ",", "");
	sa.removeDuplicates(true);

	String name = channelNameComboBox->getText();
	channelNameComboBox->clear(dontSendNotification);
	channelNameComboBox->addItemList(sa, 1);
	if (name.isNotEmpty())
		channelNameComboBox->setText(name);
	else channelNameComboBox->setSelectedItemIndex(0, dontSendNotification);
}

String Menu::FindActiveTabWithAlias(StringArray aliases)
{
	String targetAddress;
	if (aliases.size() > 0)
	{
		targetAddress = String::empty;
		for (int i = 0; i < aliases.size(); i++)
		{
			StringArray tabNames = GetRoomNames();
			if (tabNames.contains(aliases[i]))
				targetAddress = aliases[i];
		}
		if (targetAddress.isEmpty()) // else just take the 1st alias as target
			targetAddress = aliases[0];
	}
	return targetAddress;
}

void Menu::SetIsOnline(const bool online)
{
	isOnline = online;
}

void Menu::SetStatusText(const String msg, const double progress)
{
	Colour c = Colours::white;
	if (progress > 0.9)
		c = Colours::red;
	else if (progress > 0.7)
		c = Colours::orangered;
	slotFeeButton->setColour(Label::textColourId, c);
	slotFeeButton->setButtonText(msg);
}

void Menu::NotifyTab(uint64 recipientID, uint64 senderID, bool isPrivate, String msg)
{
	// TODO
	int selectedRow = chatlist->getSelectedRow();
	for (int i = 0; i < tabs.size(); i++)
	{
		tabprops &tp = tabs.getReference(i);

		// update notifiers for each tab where needed
		if (i != selectedRow &&
			((tp.receiverID == recipientID && isPrivate == false && tp.privateChannel == false) || // room message
			((tp.receiverID == senderID || tp.receiverID == recipientID) && isPrivate && tp.privateChannel) || // private message
			(tp.senderID == tp.receiverID && tp.privateChannel) || // tab wants to have everything
			(tp.receiverID == 0 && senderID == 0)))
		{
			tp.notify = 1;
		}
	}
}

void Menu::ActivateTab(const int index, const bool forceShow)
{
	if (index < 0)
		chatlist->deselectAllRows();
	chatListeners.call(&ChatComponentListener::ActivateTab, index, forceShow);
}

StringArray Menu::GetRoomNames()
{
	StringArray tabNames;
	for (int i = 0; i < tabs.size(); i++)
		tabNames.add(tabs[i].name);
	return tabNames;
}

void Menu::SetAccountRS(const String rs)
{
	accountRS = rs;
}

// RoomsListBoxModel -------------------------------------------------------------
void Menu::RoomsListBoxModel::setParent(Menu *menuIn)
{
	this->menu = menuIn;
}

void Menu::RoomsListBoxModel::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
	Colour notifyColor(0xfff7cc1f);
	Colour selectionColor(Colours::lightgrey.withAlpha(0.5f));
	if (rowIsSelected)
		g.fillAll(selectionColor);

	Array<tabprops> tp = menu->getTabs();
	StringArray names = menu->GetRoomNames();

	if (tp[rowNumber].notify == 1)
	{
		g.setColour(notifyColor);
		g.fillRect(Rectangle<float>(0.f, 0.f, (float)width, (float)height).reduced(2));
	}

	if (tp[rowNumber].privateChannel && (tp[rowNumber].notify == 0))
	{
		/*if (rowIsSelected)
			g.setColour(selectionColor);
		else */
		g.setColour(Colours::black);
	}
	else g.setColour(Colours::darkgrey);

	g.setFont(height * (rowIsSelected ? 0.6f : 0.5f));

	g.drawText(names[rowNumber],
		5, 0, width, height,
		Justification::centredLeft, true);
}


int Menu::RoomsListBoxModel::getNumRows()
{
	return menu->GetRoomNames().size();
}

void Menu::RoomsListBoxModel::listBoxItemClicked(int row, const MouseEvent& e)
{
	if (row < menu->tabs.size())
	{
		tabprops &tp = menu->tabs.getReference(row);
		tp.notify = 0;
	}

	if (e.mods.isRightButtonDown())
	{
		ScopedPointer<PopupMenu> contextMenu;
		contextMenu = new PopupMenu;
		contextMenu->addItem(1, "Close", true);
		const int result = contextMenu->show();
		if (result == 1)
			menu->TriggerRemoveTab(row);
	}
	else menu->ActivateTab(row, true);
}

void Menu::RoomsListBoxModel::listBoxItemDoubleClicked(int row, const MouseEvent&)
{

}

void Menu::RoomsListBoxModel::backgroundClicked(const MouseEvent&)
{
	menu->ActivateTab(-1, true);
}

void Menu::RoomsListBoxModel::selectedRowsChanged(int lastRowSelected)
{
}

void Menu::RoomsListBoxModel::deleteKeyPressed(int lastRowSelected)
{
	menu->TriggerRemoveTab(lastRowSelected);
}

void Menu::RoomsListBoxModel::returnKeyPressed(int lastRowSelected)
{

}

void Menu::RoomsListBoxModel::listWasScrolled()
{

}

String Menu::RoomsListBoxModel::getTooltipForRow(int row)
{
	return menu->GetRoomNames()[row];
}

void Menu::CloseSocket()
{
	chatListeners.call(&ChatComponentListener::OpenCloseSocket, false);
}

void Menu::ToggleSocket()
{
	chatListeners.call(&ChatComponentListener::OpenCloseSocket, !isOnline); // toggle
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Menu" componentName="" parentClasses="public Component, public MenuListener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTBUTTON name="privateChatButton" id="f0ea0b5d7731d786" memberName="privateChatButton"
              virtualName="" explicitFocusOrder="6" pos="0 256 160 24" tooltip="A private encrypted chat between you and the account entered above"
              bgColOff="ff191919" bgColOn="ff404040" textCol="ffffffff" textColOn="ffffffff"
              buttonText="Open private chat" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="publicRoomButton" id="44c667f1ea9925fa" memberName="publicRoomButton"
              virtualName="" explicitFocusOrder="5" pos="0 224 160 24" tooltip="Will open or enter a room for the account entered above. The chat will be visible to anyone! Others can connect to this same room to talk to you"
              bgColOff="ff77b517" bgColOn="ff7fff00" textCol="ffffffff" textColOn="ffffffff"
              buttonText="Open public room" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <COMBOBOX name="channelNameComboBox" id="9ae0400f7201afbe" memberName="channelNameComboBox"
            virtualName="" explicitFocusOrder="4" pos="0 192 160 24" tooltip="Select a room from the pop-up list. Or enter an alias, RS or account ID. &#10;for example: &#10;Agora&#10;BURST-XXX.. or &#10;1234"
            editable="1" layout="33" items="" textWhenNonSelected="BurstExtensions"
            textWhenNoItems="BurstExtensions"/>
  <TEXTBUTTON name="slotFeeButton" id="5180c560f2965319" memberName="slotFeeButton"
              virtualName="" explicitFocusOrder="0" pos="0 0 160 48" tooltip="Current client network status"
              bgColOff="bbbbff" textCol="ff000000" textColOn="ff000000" buttonText="0/0 messages"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="chatlist" id="ebba032c1dfb209c" memberName="chatlist" virtualName=""
                    explicitFocusOrder="0" pos="0 56 160 128" class="ListBox" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
