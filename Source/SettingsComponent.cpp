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

#include "SettingsComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "Version.h"
//[/MiscUserDefs]

//==============================================================================
SettingsComponent::SettingsComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (passPhraseTextEditor = new TextEditor ("passPhraseTextEditor"));
    passPhraseTextEditor->setTooltip (TRANS("Enter your existing pass phrase here. Or you can create a new wallet here. A red background indicates a phrase shorter than 35 characters, which is not recommended !"));
    passPhraseTextEditor->setMultiLine (false);
    passPhraseTextEditor->setReturnKeyStartsNewLine (false);
    passPhraseTextEditor->setReadOnly (false);
    passPhraseTextEditor->setScrollbarsShown (false);
    passPhraseTextEditor->setCaretVisible (true);
    passPhraseTextEditor->setPopupMenuEnabled (true);
    passPhraseTextEditor->setText (String());

    addAndMakeVisible (lockButton = new TextButton ("lockButton"));
    lockButton->setTooltip (TRANS("Locks the app now. And clears the pass phrase. You will need to enter the PIN to unlock it again."));
    lockButton->setButtonText (TRANS("Log out"));
    lockButton->addListener (this);
    lockButton->setColour (TextButton::buttonColourId, Colours::white);
    lockButton->setColour (TextButton::buttonOnColourId, Colours::white);
    lockButton->setColour (TextButton::textColourOffId, Colours::black);
    lockButton->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (myPassPhraseButton = new TextButton ("myPassPhraseButton"));
    myPassPhraseButton->setTooltip (TRANS("Pop-up menu with pass phrase options"));
    myPassPhraseButton->setButtonText (TRANS("My pass phrase"));
    myPassPhraseButton->addListener (this);
    myPassPhraseButton->setColour (TextButton::buttonColourId, Colours::white);
    myPassPhraseButton->setColour (TextButton::buttonOnColourId, Colours::white);
    myPassPhraseButton->setColour (TextButton::textColourOffId, Colours::black);
    myPassPhraseButton->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (cmcButton = new TextButton ("cmcButton"));
    cmcButton->setTooltip (TRANS("Pop-up menu with currency options"));
    cmcButton->setButtonText (TRANS("Currency type"));
    cmcButton->addListener (this);
    cmcButton->setColour (TextButton::buttonColourId, Colours::white);
    cmcButton->setColour (TextButton::buttonOnColourId, Colours::white);
    cmcButton->setColour (TextButton::textColourOffId, Colours::black);
    cmcButton->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (cmcTextEditor = new TextEditor ("cmcTextEditor"));
    cmcTextEditor->setTooltip (TRANS("Enter your coinmarketcap.com API key to view the amounts in other currency values."));
    cmcTextEditor->setMultiLine (false);
    cmcTextEditor->setReturnKeyStartsNewLine (false);
    cmcTextEditor->setReadOnly (false);
    cmcTextEditor->setScrollbarsShown (false);
    cmcTextEditor->setCaretVisible (true);
    cmcTextEditor->setPopupMenuEnabled (true);
    cmcTextEditor->setText (String());


    //[UserPreSize]
	passPhraseTextEditor->setMultiLine(false);
	passPhraseTextEditor->setReturnKeyStartsNewLine(false);
	passPhraseTextEditor->setReadOnly(false);
	passPhraseTextEditor->setScrollbarsShown(false);
	passPhraseTextEditor->setCaretVisible(true);
	passPhraseTextEditor->setPopupMenuEnabled(true);
	passPhraseTextEditor->setPasswordCharacter(0x2022);
	passPhraseTextEditor->addListener(this);
	passPhraseTextEditor->setTextToShowWhenEmpty("My account", Colours::grey);
	passPhraseTextEditor->setVisible(false);

	cmcTextEditor->setTextToShowWhenEmpty("Your coinmarketcap.com API key (not affiliated)", Colours::grey);
	cmcTextEditor->addListener(this);
	cmcTextEditor->setVisible(false);

	currencyType = 0;
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	EnableControls(true);
    //[/Constructor]
}

SettingsComponent::~SettingsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    passPhraseTextEditor = nullptr;
    lockButton = nullptr;
    myPassPhraseButton = nullptr;
    cmcButton = nullptr;
    cmcTextEditor = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SettingsComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	/*
    //[/UserPrePaint]

    g.fillAll (Colour (0xffdfdfdf));

    //[UserPaint] Add your own custom painting code here..
	*/
	g.fillAll(Colour(0xffdfdfdf));
    //[/UserPaint]
}

void SettingsComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	/*
    //[/UserPreResize]

    passPhraseTextEditor->setBounds (136, 72, 360, 24);
    lockButton->setBounds (8, 40, 120, 24);
    myPassPhraseButton->setBounds (8, 72, 120, 24);
    cmcButton->setBounds (8, 104, 120, 24);
    cmcTextEditor->setBounds (136, 104, 360, 24);
    //[UserResized] Add your own custom resize handling here..
	*/
	const int col = 140;
	const int rowH = 22;
	const int pad = 15;
	Rectangle<int> r = getBounds().withPosition(0, 0).reduced(pad);

	Rectangle<int> r1 = r.withHeight(rowH);
	Rectangle<int> r2 = r1.translated(0, rowH + 3);
	Rectangle<int> r3 = r2.translated(0, rowH + 3);

	const int bw = 150;
	lockButton->setBounds(r1.withWidth(bw));
	myPassPhraseButton->setBounds(r2.withWidth(bw));
	cmcButton->setBounds(r3.withWidth(bw));

	passPhraseTextEditor->setBounds(r2.withTrimmedLeft(bw + 5));
	cmcTextEditor->setBounds(r3.withTrimmedLeft(bw + 5));

    //[/UserResized]
}

void SettingsComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == lockButton)
    {
        //[UserButtonCode_lockButton] -- add your button handler code here..
		interfaceListeners.call(&InterfaceListener::UnloadPassPhrase);
        //[/UserButtonCode_lockButton]
    }
    else if (buttonThatWasClicked == myPassPhraseButton)
    {
        //[UserButtonCode_myPassPhraseButton] -- add your button handler code here..
		bool editingPassPhrase = passPhraseTextEditor->isVisible();
		ScopedPointer<PopupMenu> contextMenu;
		contextMenu = new PopupMenu;

		contextMenu->addItem(7, "Copy public address to clipboard", true);
		contextMenu->addItem(1, "Change my access PIN code", true);
		contextMenu->addItem(5, "Manual edit pass phrase", true, editingPassPhrase);
		contextMenu->addItem(3, "Import pass phrase (plain text!)", true);
		contextMenu->addItem(2, "Export pass phrase (plain text!)", true);
		contextMenu->addItem(6, "Generate new account / pass phrase", true);

		int result = contextMenu->show();
		if (result == 1)
		{// "Change PIN"
			ChangePIN();
		}
		else if (result == 2)
		{// "Export pass phrase"
			ExportWallet();
		}
		else if (result == 3)
		{// "Import pass phrase"
			ImportWallet();
		}
		else if (result == 5)
		{// "Set manual pass phrase (existing wallet)"
			passPhraseTextEditor->setVisible(!editingPassPhrase);
		}
		else if (result == 6)
		{// "Make new pass phrase"
			NewWallet();
		}
		else if (result == 7)
		{
			SystemClipboard::copyTextToClipboard(addressRS);
			NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Address " + addressRS + "\nis copied to clipboard");
		}

		contextMenu = nullptr;
        //[/UserButtonCode_myPassPhraseButton]
    }
    else if (buttonThatWasClicked == cmcButton)
    {
        //[UserButtonCode_cmcButton] -- add your button handler code here..
		bool editing = cmcTextEditor->isVisible();
		ScopedPointer<PopupMenu> contextMenu;
		contextMenu = new PopupMenu;

		ScopedPointer<PopupMenu> contextSubMenu;
		contextSubMenu = new PopupMenu;

		contextMenu->addItem(1, "Set your coinmarketcap.com/api key", true, editing);
		contextMenu->addItem(7, "Get API key (opens browser) works with free Basic account", true, editing);

		if (cmcTextEditor->getText().isNotEmpty())
		{
			contextSubMenu->addItem(2, "BURST", true, currencyType == 0);
			contextSubMenu->addItem(3, "BTC", true, currencyType == 1);
			contextSubMenu->addItem(4, "USD", true, currencyType == 2);
			contextSubMenu->addItem(5, "EUR", true, currencyType == 3);
			contextSubMenu->addItem(6, "GBP", true, currencyType == 4);
		}
		contextMenu->addSubMenu("Display currency", *contextSubMenu, true);
		
		int result = contextMenu->show();
		if (result == 1)
		{
			cmcTextEditor->setVisible(!editing);
		}
		else if (result == 7)
		{
			URL url("https://coinmarketcap.com/api/");
			url.launchInDefaultBrowser();
		}
		else if (result > 1)
		{
			SetCurrencyType(result - 2);
		}

		contextMenu = nullptr;
		contextSubMenu = nullptr;
        //[/UserButtonCode_cmcButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SettingsComponent::textEditorTextChanged(TextEditor &editor) //Called when the user changes the text in some way.
{
	if (passPhraseTextEditor == &editor)
	{
		SetSecretPhrase(editor.getText());
	}
	if (cmcTextEditor == &editor)
	{
		interfaceListeners.call(&InterfaceListener::SetCMCkey, editor.getText());
	}
}

void SettingsComponent::textEditorReturnKeyPressed(TextEditor &editor) //Called when the user presses the return key.
{
	if (passPhraseTextEditor == &editor)
	{
		interfaceListeners.call(&InterfaceListener::SavePassPhraseWithNewPIN, editor.getText());
		SetSecretPhrase(editor.getText());
	}
	if (cmcTextEditor == &editor)
	{
		interfaceListeners.call(&InterfaceListener::SetCMCkey, editor.getText());
	}
}

void SettingsComponent::textEditorEscapeKeyPressed(TextEditor &/*editor*/) //Called when the user presses the escape key.
{
}
void SettingsComponent::textEditorFocusLost(TextEditor &editor) //Called when the text editor loses focus.
{
}

void SettingsComponent::SetSecretPhrase(const String str)
{
	passPhraseTextEditor->setText(str, dontSendNotification);
	if (passPhraseTextEditor->getText().length() >= 35)
		passPhraseTextEditor->setColour(TextEditor::backgroundColourId, Colours::white);
	else passPhraseTextEditor->setColour(TextEditor::backgroundColourId, Colours::red);
}

void SettingsComponent::SetBurstRS(const String rs)
{
	addressRS = (rs);
}

void SettingsComponent::EnableControls(const bool on)
{
	passPhraseTextEditor->setEnabled(on);
}

void SettingsComponent::ExportWallet()
{
	FileChooser myChooser("Select the location to save your wallet pass phrase...", File::getSpecialLocation(File::userDesktopDirectory), "*.*");
	if (myChooser.browseForDirectory() && addressRS.isNotEmpty())
	{
		File f = myChooser.getResult().getChildFile(addressRS).withFileExtension("txt");
		f.appendText(passPhraseTextEditor->getText());

		if (myChooser.getResult().getChildFile(addressRS).withFileExtension("txt").existsAsFile())
			NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "File saved !\n\nSecurly backup the pass phrase file and keep it private !\n" + f.getFullPathName());
		else NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Failed to create file !\n" + f.getFullPathName());
	}
}

void SettingsComponent::ImportWallet()
{
	if (NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, "Import a wallet pass phrase?\nPlease make sure to export and BACKUP YOUR CURRENT PASS PHRASE!\nHotWallet only holds 1 account at a time.") == 1)
	{
		FileChooser myChooser("Select the wallet pass phrase file...", File::getSpecialLocation(File::userDesktopDirectory), "*.*");
		if (myChooser.browseForFileToOpen())
		{
			File f = myChooser.getResult();
			String passPhrase = f.loadFileAsString();

			if (passPhrase.isEmpty())
				NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "No passphrase found in file:\n" + f.getFullPathName());
			else
			{
				interfaceListeners.call(&InterfaceListener::SavePassPhraseWithNewPIN, passPhrase);
				SetSecretPhrase(passPhrase);
			}
		}
	}
}

void SettingsComponent::ChangePIN()
{
	if (NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, "Change the PIN that protects your passphrase?") == 1)
	{
		interfaceListeners.call(&InterfaceListener::SavePassPhraseWithNewPIN, passPhraseTextEditor->getText());
	}
}

void SettingsComponent::CreateWallet()
{
	MemoryBlock wordListMb = MemoryBlock(brswordlist_txt, brswordlist_txtSize);
	StringArray wordList = StringArray::fromLines(wordListMb.toString());
	juce::Random r(Time::currentTimeMillis());
	String passPhrase;
	for (int i = 0; i < 12; i++)
	{
		unsigned int randInt = r.nextInt();
		passPhrase += wordList[randInt % wordList.size()];
		if (i < 11)
			passPhrase += " ";
	}
	interfaceListeners.call(&InterfaceListener::SavePassPhraseWithNewPIN, passPhrase);
	SetSecretPhrase(passPhrase);
}

void SettingsComponent::SetCMCkey(const String key)
{
	cmcTextEditor->setText(key, dontSendNotification);
}

void SettingsComponent::SetCurrencyType(const String currency)
{
	if (currency.compare("BTC") == 0)
		currencyType = 1;
	else if (currency.compare("USD") == 0)
		currencyType = 2;
	else if (currency.compare("EUR") == 0)
		currencyType = 3;
	else if (currency.compare("GBP") == 0)
		currencyType = 4;
	else currencyType = 0; // BURST
}

void SettingsComponent::SetCurrencyType(const int type)
{
	currencyType = type;
	if (type == 0)
		interfaceListeners.call(&InterfaceListener::SetCurrencyType, "BURST");
	else if (type == 1)
		interfaceListeners.call(&InterfaceListener::SetCurrencyType, "BTC");
	else if (type == 2)
		interfaceListeners.call(&InterfaceListener::SetCurrencyType, "USD");
	else if (type == 3)
		interfaceListeners.call(&InterfaceListener::SetCurrencyType, "EUR");
	else if (type == 4)
		interfaceListeners.call(&InterfaceListener::SetCurrencyType, "GBP");
}

void SettingsComponent::NewWallet()
{
	if (NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, "Create new wallet pass phrase?\nPlease make sure to export and BACKUP YOUR CURRENT PASS PHRASE!\nHotWallet only holds 1 account at a time.") == 1)
	{
		CreateWallet();
	}
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SettingsComponent" componentName=""
                 parentClasses="public TextEditorListener, public Component, public SettingsListener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffdfdfdf"/>
  <TEXTEDITOR name="passPhraseTextEditor" id="f0cbabb6811d2f5" memberName="passPhraseTextEditor"
              virtualName="" explicitFocusOrder="0" pos="136 72 360 24" tooltip="Enter your existing pass phrase here. Or you can create a new wallet here. A red background indicates a phrase shorter than 35 characters, which is not recommended !"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTBUTTON name="lockButton" id="2b10438639a15113" memberName="lockButton"
              virtualName="" explicitFocusOrder="0" pos="8 40 120 24" tooltip="Locks the app now. And clears the pass phrase. You will need to enter the PIN to unlock it again."
              bgColOff="ffffffff" bgColOn="ffffffff" textCol="ff000000" textColOn="ff000000"
              buttonText="Log out" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="myPassPhraseButton" id="a57dbbdc113f5472" memberName="myPassPhraseButton"
              virtualName="" explicitFocusOrder="0" pos="8 72 120 24" tooltip="Pop-up menu with pass phrase options"
              bgColOff="ffffffff" bgColOn="ffffffff" textCol="ff000000" textColOn="ff000000"
              buttonText="My pass phrase" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="cmcButton" id="6d710c0347734f90" memberName="cmcButton"
              virtualName="" explicitFocusOrder="0" pos="8 104 120 24" tooltip="Pop-up menu with currency options"
              bgColOff="ffffffff" bgColOn="ffffffff" textCol="ff000000" textColOn="ff000000"
              buttonText="Currency type" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTEDITOR name="cmcTextEditor" id="40e0f00b7b45b6de" memberName="cmcTextEditor"
              virtualName="" explicitFocusOrder="0" pos="136 104 360 24" tooltip="Enter your coinmarketcap.com API key to view the amounts in other currency values."
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: brswordlist_txt, 10493, "BRS-wordlist.txt"
static const unsigned char resource_SettingsComponent_brswordlist_txt[] = { 108,105,107,101,10,106,117,115,116,10,108,111,118,101,10,107,110,111,119,10,110,101,118,101,114,10,119,97,110,116,10,116,105,
109,101,10,111,117,116,10,116,104,101,114,101,10,109,97,107,101,10,108,111,111,107,10,101,121,101,10,100,111,119,110,10,111,110,108,121,10,116,104,105,110,107,10,104,101,97,114,116,10,98,97,99,107,10,
116,104,101,110,10,105,110,116,111,10,97,98,111,117,116,10,109,111,114,101,10,97,119,97,121,10,115,116,105,108,108,10,116,104,101,109,10,116,97,107,101,10,116,104,105,110,103,10,101,118,101,110,10,116,
104,114,111,117,103,104,10,108,111,110,103,10,97,108,119,97,121,115,10,119,111,114,108,100,10,116,111,111,10,102,114,105,101,110,100,10,116,101,108,108,10,116,114,121,10,104,97,110,100,10,116,104,111,
117,103,104,116,10,111,118,101,114,10,104,101,114,101,10,111,116,104,101,114,10,110,101,101,100,10,115,109,105,108,101,10,97,103,97,105,110,10,109,117,99,104,10,99,114,121,10,98,101,101,110,10,110,105,
103,104,116,10,101,118,101,114,10,108,105,116,116,108,101,10,115,97,105,100,10,101,110,100,10,115,111,109,101,10,116,104,111,115,101,10,97,114,111,117,110,100,10,109,105,110,100,10,112,101,111,112,108,
101,10,103,105,114,108,10,108,101,97,118,101,10,100,114,101,97,109,10,108,101,102,116,10,116,117,114,110,10,109,121,115,101,108,102,10,103,105,118,101,10,110,111,116,104,105,110,103,10,114,101,97,108,
108,121,10,111,102,102,10,98,101,102,111,114,101,10,115,111,109,101,116,104,105,110,103,10,102,105,110,100,10,119,97,108,107,10,119,105,115,104,10,103,111,111,100,10,111,110,99,101,10,112,108,97,99,101,
10,97,115,107,10,115,116,111,112,10,107,101,101,112,10,119,97,116,99,104,10,115,101,101,109,10,101,118,101,114,121,116,104,105,110,103,10,119,97,105,116,10,103,111,116,10,121,101,116,10,109,97,100,101,
10,114,101,109,101,109,98,101,114,10,115,116,97,114,116,10,97,108,111,110,101,10,114,117,110,10,104,111,112,101,10,109,97,121,98,101,10,98,101,108,105,101,118,101,10,98,111,100,121,10,104,97,116,101,10,
97,102,116,101,114,10,99,108,111,115,101,10,116,97,108,107,10,115,116,97,110,100,10,111,119,110,10,101,97,99,104,10,104,117,114,116,10,104,101,108,112,10,104,111,109,101,10,103,111,100,10,115,111,117,
108,10,110,101,119,10,109,97,110,121,10,116,119,111,10,105,110,115,105,100,101,10,115,104,111,117,108,100,10,116,114,117,101,10,102,105,114,115,116,10,102,101,97,114,10,109,101,97,110,10,98,101,116,116,
101,114,10,112,108,97,121,10,97,110,111,116,104,101,114,10,103,111,110,101,10,99,104,97,110,103,101,10,117,115,101,10,119,111,110,100,101,114,10,115,111,109,101,111,110,101,10,104,97,105,114,10,99,111,
108,100,10,111,112,101,110,10,98,101,115,116,10,97,110,121,10,98,101,104,105,110,100,10,104,97,112,112,101,110,10,119,97,116,101,114,10,100,97,114,107,10,108,97,117,103,104,10,115,116,97,121,10,102,111,
114,101,118,101,114,10,110,97,109,101,10,119,111,114,107,10,115,104,111,119,10,115,107,121,10,98,114,101,97,107,10,99,97,109,101,10,100,101,101,112,10,100,111,111,114,10,112,117,116,10,98,108,97,99,107,
10,116,111,103,101,116,104,101,114,10,117,112,111,110,10,104,97,112,112,121,10,115,117,99,104,10,103,114,101,97,116,10,119,104,105,116,101,10,109,97,116,116,101,114,10,102,105,108,108,10,112,97,115,116,
10,112,108,101,97,115,101,10,98,117,114,110,10,99,97,117,115,101,10,101,110,111,117,103,104,10,116,111,117,99,104,10,109,111,109,101,110,116,10,115,111,111,110,10,118,111,105,99,101,10,115,99,114,101,
97,109,10,97,110,121,116,104,105,110,103,10,115,116,97,114,101,10,115,111,117,110,100,10,114,101,100,10,101,118,101,114,121,111,110,101,10,104,105,100,101,10,107,105,115,115,10,116,114,117,116,104,10,
100,101,97,116,104,10,98,101,97,117,116,105,102,117,108,10,109,105,110,101,10,98,108,111,111,100,10,98,114,111,107,101,110,10,118,101,114,121,10,112,97,115,115,10,110,101,120,116,10,102,111,114,103,101,
116,10,116,114,101,101,10,119,114,111,110,103,10,97,105,114,10,109,111,116,104,101,114,10,117,110,100,101,114,115,116,97,110,100,10,108,105,112,10,104,105,116,10,119,97,108,108,10,109,101,109,111,114,
121,10,115,108,101,101,112,10,102,114,101,101,10,104,105,103,104,10,114,101,97,108,105,122,101,10,115,99,104,111,111,108,10,109,105,103,104,116,10,115,107,105,110,10,115,119,101,101,116,10,112,101,114,
102,101,99,116,10,98,108,117,101,10,107,105,108,108,10,98,114,101,97,116,104,10,100,97,110,99,101,10,97,103,97,105,110,115,116,10,102,108,121,10,98,101,116,119,101,101,110,10,103,114,111,119,10,115,116,
114,111,110,103,10,117,110,100,101,114,10,108,105,115,116,101,110,10,98,114,105,110,103,10,115,111,109,101,116,105,109,101,115,10,115,112,101,97,107,10,112,117,108,108,10,112,101,114,115,111,110,10,98,
101,99,111,109,101,10,102,97,109,105,108,121,10,98,101,103,105,110,10,103,114,111,117,110,100,10,114,101,97,108,10,115,109,97,108,108,10,102,97,116,104,101,114,10,115,117,114,101,10,102,101,101,116,10,
114,101,115,116,10,121,111,117,110,103,10,102,105,110,97,108,108,121,10,108,97,110,100,10,97,99,114,111,115,115,10,116,111,100,97,121,10,100,105,102,102,101,114,101,110,116,10,103,117,121,10,108,105,110,
101,10,102,105,114,101,10,114,101,97,115,111,110,10,114,101,97,99,104,10,115,101,99,111,110,100,10,115,108,111,119,108,121,10,119,114,105,116,101,10,101,97,116,10,115,109,101,108,108,10,109,111,117,116,
104,10,115,116,101,112,10,108,101,97,114,110,10,116,104,114,101,101,10,102,108,111,111,114,10,112,114,111,109,105,115,101,10,98,114,101,97,116,104,101,10,100,97,114,107,110,101,115,115,10,112,117,115,
104,10,101,97,114,116,104,10,103,117,101,115,115,10,115,97,118,101,10,115,111,110,103,10,97,98,111,118,101,10,97,108,111,110,103,10,98,111,116,104,10,99,111,108,111,114,10,104,111,117,115,101,10,97,108,
109,111,115,116,10,115,111,114,114,121,10,97,110,121,109,111,114,101,10,98,114,111,116,104,101,114,10,111,107,97,121,10,100,101,97,114,10,103,97,109,101,10,102,97,100,101,10,97,108,114,101,97,100,121,
10,97,112,97,114,116,10,119,97,114,109,10,98,101,97,117,116,121,10,104,101,97,114,100,10,110,111,116,105,99,101,10,113,117,101,115,116,105,111,110,10,115,104,105,110,101,10,98,101,103,97,110,10,112,105,
101,99,101,10,119,104,111,108,101,10,115,104,97,100,111,119,10,115,101,99,114,101,116,10,115,116,114,101,101,116,10,119,105,116,104,105,110,10,102,105,110,103,101,114,10,112,111,105,110,116,10,109,111,
114,110,105,110,103,10,119,104,105,115,112,101,114,10,99,104,105,108,100,10,109,111,111,110,10,103,114,101,101,110,10,115,116,111,114,121,10,103,108,97,115,115,10,107,105,100,10,115,105,108,101,110,99,
101,10,115,105,110,99,101,10,115,111,102,116,10,121,111,117,114,115,101,108,102,10,101,109,112,116,121,10,115,104,97,108,108,10,97,110,103,101,108,10,97,110,115,119,101,114,10,98,97,98,121,10,98,114,105,
103,104,116,10,100,97,100,10,112,97,116,104,10,119,111,114,114,121,10,104,111,117,114,10,100,114,111,112,10,102,111,108,108,111,119,10,112,111,119,101,114,10,119,97,114,10,104,97,108,102,10,102,108,111,
119,10,104,101,97,118,101,110,10,97,99,116,10,99,104,97,110,99,101,10,102,97,99,116,10,108,101,97,115,116,10,116,105,114,101,100,10,99,104,105,108,100,114,101,110,10,110,101,97,114,10,113,117,105,116,
101,10,97,102,114,97,105,100,10,114,105,115,101,10,115,101,97,10,116,97,115,116,101,10,119,105,110,100,111,119,10,99,111,118,101,114,10,110,105,99,101,10,116,114,117,115,116,10,108,111,116,10,115,97,100,
10,99,111,111,108,10,102,111,114,99,101,10,112,101,97,99,101,10,114,101,116,117,114,110,10,98,108,105,110,100,10,101,97,115,121,10,114,101,97,100,121,10,114,111,108,108,10,114,111,115,101,10,100,114,105,
118,101,10,104,101,108,100,10,109,117,115,105,99,10,98,101,110,101,97,116,104,10,104,97,110,103,10,109,111,109,10,112,97,105,110,116,10,101,109,111,116,105,111,110,10,113,117,105,101,116,10,99,108,101,
97,114,10,99,108,111,117,100,10,102,101,119,10,112,114,101,116,116,121,10,98,105,114,100,10,111,117,116,115,105,100,101,10,112,97,112,101,114,10,112,105,99,116,117,114,101,10,102,114,111,110,116,10,114,
111,99,107,10,115,105,109,112,108,101,10,97,110,121,111,110,101,10,109,101,97,110,116,10,114,101,97,108,105,116,121,10,114,111,97,100,10,115,101,110,115,101,10,119,97,115,116,101,10,98,105,116,10,108,
101,97,102,10,116,104,97,110,107,10,104,97,112,112,105,110,101,115,115,10,109,101,101,116,10,109,101,110,10,115,109,111,107,101,10,116,114,117,108,121,10,100,101,99,105,100,101,10,115,101,108,102,10,97,
103,101,10,98,111,111,107,10,102,111,114,109,10,97,108,105,118,101,10,99,97,114,114,121,10,101,115,99,97,112,101,10,100,97,109,110,10,105,110,115,116,101,97,100,10,97,98,108,101,10,105,99,101,10,109,105,
110,117,116,101,10,116,104,114,111,119,10,99,97,116,99,104,10,108,101,103,10,114,105,110,103,10,99,111,117,114,115,101,10,103,111,111,100,98,121,101,10,108,101,97,100,10,112,111,101,109,10,115,105,99,
107,10,99,111,114,110,101,114,10,100,101,115,105,114,101,10,107,110,111,119,110,10,112,114,111,98,108,101,109,10,114,101,109,105,110,100,10,115,104,111,117,108,100,101,114,10,115,117,112,112,111,115,101,
10,116,111,119,97,114,100,10,119,97,118,101,10,100,114,105,110,107,10,106,117,109,112,10,119,111,109,97,110,10,112,114,101,116,101,110,100,10,115,105,115,116,101,114,10,119,101,101,107,10,104,117,109,
97,110,10,106,111,121,10,99,114,97,99,107,10,103,114,101,121,10,112,114,97,121,10,115,117,114,112,114,105,115,101,10,100,114,121,10,107,110,101,101,10,108,101,115,115,10,115,101,97,114,99,104,10,98,108,
101,101,100,10,99,97,117,103,104,116,10,99,108,101,97,110,10,101,109,98,114,97,99,101,10,102,117,116,117,114,101,10,107,105,110,103,10,115,111,110,10,115,111,114,114,111,119,10,99,104,101,115,116,10,104,
117,103,10,114,101,109,97,105,110,10,115,97,116,10,119,111,114,116,104,10,98,108,111,119,10,100,97,100,100,121,10,102,105,110,97,108,10,112,97,114,101,110,116,10,116,105,103,104,116,10,97,108,115,111,
10,99,114,101,97,116,101,10,108,111,110,101,108,121,10,115,97,102,101,10,99,114,111,115,115,10,100,114,101,115,115,10,101,118,105,108,10,115,105,108,101,110,116,10,98,111,110,101,10,102,97,116,101,10,
112,101,114,104,97,112,115,10,97,110,103,101,114,10,99,108,97,115,115,10,115,99,97,114,10,115,110,111,119,10,116,105,110,121,10,116,111,110,105,103,104,116,10,99,111,110,116,105,110,117,101,10,99,111,
110,116,114,111,108,10,100,111,103,10,101,100,103,101,10,109,105,114,114,111,114,10,109,111,110,116,104,10,115,117,100,100,101,110,108,121,10,99,111,109,102,111,114,116,10,103,105,118,101,110,10,108,111,
117,100,10,113,117,105,99,107,108,121,10,103,97,122,101,10,112,108,97,110,10,114,117,115,104,10,115,116,111,110,101,10,116,111,119,110,10,98,97,116,116,108,101,10,105,103,110,111,114,101,10,115,112,105,
114,105,116,10,115,116,111,111,100,10,115,116,117,112,105,100,10,121,111,117,114,115,10,98,114,111,119,110,10,98,117,105,108,100,10,100,117,115,116,10,104,101,121,10,107,101,112,116,10,112,97,121,10,112,
104,111,110,101,10,116,119,105,115,116,10,97,108,116,104,111,117,103,104,10,98,97,108,108,10,98,101,121,111,110,100,10,104,105,100,100,101,110,10,110,111,115,101,10,116,97,107,101,110,10,102,97,105,108,
10,102,108,111,97,116,10,112,117,114,101,10,115,111,109,101,104,111,119,10,119,97,115,104,10,119,114,97,112,10,97,110,103,114,121,10,99,104,101,101,107,10,99,114,101,97,116,117,114,101,10,102,111,114,
103,111,116,116,101,110,10,104,101,97,116,10,114,105,112,10,115,105,110,103,108,101,10,115,112,97,99,101,10,115,112,101,99,105,97,108,10,119,101,97,107,10,119,104,97,116,101,118,101,114,10,121,101,108,
108,10,97,110,121,119,97,121,10,98,108,97,109,101,10,106,111,98,10,99,104,111,111,115,101,10,99,111,117,110,116,114,121,10,99,117,114,115,101,10,100,114,105,102,116,10,101,99,104,111,10,102,105,103,117,
114,101,10,103,114,101,119,10,108,97,117,103,104,116,101,114,10,110,101,99,107,10,115,117,102,102,101,114,10,119,111,114,115,101,10,121,101,97,104,10,100,105,115,97,112,112,101,97,114,10,102,111,111,116,
10,102,111,114,119,97,114,100,10,107,110,105,102,101,10,109,101,115,115,10,115,111,109,101,119,104,101,114,101,10,115,116,111,109,97,99,104,10,115,116,111,114,109,10,98,101,103,10,105,100,101,97,10,108,
105,102,116,10,111,102,102,101,114,10,98,114,101,101,122,101,10,102,105,101,108,100,10,102,105,118,101,10,111,102,116,101,110,10,115,105,109,112,108,121,10,115,116,117,99,107,10,119,105,110,10,97,108,
108,111,119,10,99,111,110,102,117,115,101,10,101,110,106,111,121,10,101,120,99,101,112,116,10,102,108,111,119,101,114,10,115,101,101,107,10,115,116,114,101,110,103,116,104,10,99,97,108,109,10,103,114,
105,110,10,103,117,110,10,104,101,97,118,121,10,104,105,108,108,10,108,97,114,103,101,10,111,99,101,97,110,10,115,104,111,101,10,115,105,103,104,10,115,116,114,97,105,103,104,116,10,115,117,109,109,101,
114,10,116,111,110,103,117,101,10,97,99,99,101,112,116,10,99,114,97,122,121,10,101,118,101,114,121,100,97,121,10,101,120,105,115,116,10,103,114,97,115,115,10,109,105,115,116,97,107,101,10,115,101,110,
116,10,115,104,117,116,10,115,117,114,114,111,117,110,100,10,116,97,98,108,101,10,97,99,104,101,10,98,114,97,105,110,10,100,101,115,116,114,111,121,10,104,101,97,108,10,110,97,116,117,114,101,10,115,104,
111,117,116,10,115,105,103,110,10,115,116,97,105,110,10,99,104,111,105,99,101,10,100,111,117,98,116,10,103,108,97,110,99,101,10,103,108,111,119,10,109,111,117,110,116,97,105,110,10,113,117,101,101,110,
10,115,116,114,97,110,103,101,114,10,116,104,114,111,97,116,10,116,111,109,111,114,114,111,119,10,99,105,116,121,10,101,105,116,104,101,114,10,102,105,115,104,10,102,108,97,109,101,10,114,97,116,104,101,
114,10,115,104,97,112,101,10,115,112,105,110,10,115,112,114,101,97,100,10,97,115,104,10,100,105,115,116,97,110,99,101,10,102,105,110,105,115,104,10,105,109,97,103,101,10,105,109,97,103,105,110,101,10,
105,109,112,111,114,116,97,110,116,10,110,111,98,111,100,121,10,115,104,97,116,116,101,114,10,119,97,114,109,116,104,10,98,101,99,97,109,101,10,102,101,101,100,10,102,108,101,115,104,10,102,117,110,110,
121,10,108,117,115,116,10,115,104,105,114,116,10,116,114,111,117,98,108,101,10,121,101,108,108,111,119,10,97,116,116,101,110,116,105,111,110,10,98,97,114,101,10,98,105,116,101,10,109,111,110,101,121,10,
112,114,111,116,101,99,116,10,97,109,97,122,101,10,97,112,112,101,97,114,10,98,111,114,110,10,99,104,111,107,101,10,99,111,109,112,108,101,116,101,108,121,10,100,97,117,103,104,116,101,114,10,102,114,
101,115,104,10,102,114,105,101,110,100,115,104,105,112,10,103,101,110,116,108,101,10,112,114,111,98,97,98,108,121,10,115,105,120,10,100,101,115,101,114,118,101,10,101,120,112,101,99,116,10,103,114,97,
98,10,109,105,100,100,108,101,10,110,105,103,104,116,109,97,114,101,10,114,105,118,101,114,10,116,104,111,117,115,97,110,100,10,119,101,105,103,104,116,10,119,111,114,115,116,10,119,111,117,110,100,10,
98,97,114,101,108,121,10,98,111,116,116,108,101,10,99,114,101,97,109,10,114,101,103,114,101,116,10,114,101,108,97,116,105,111,110,115,104,105,112,10,115,116,105,99,107,10,116,101,115,116,10,99,114,117,
115,104,10,101,110,100,108,101,115,115,10,102,97,117,108,116,10,105,116,115,101,108,102,10,114,117,108,101,10,115,112,105,108,108,10,97,114,116,10,99,105,114,99,108,101,10,106,111,105,110,10,107,105,99,
107,10,109,97,115,107,10,109,97,115,116,101,114,10,112,97,115,115,105,111,110,10,113,117,105,99,107,10,114,97,105,115,101,10,115,109,111,111,116,104,10,117,110,108,101,115,115,10,119,97,110,100,101,114,
10,97,99,116,117,97,108,108,121,10,98,114,111,107,101,10,99,104,97,105,114,10,100,101,97,108,10,102,97,118,111,114,105,116,101,10,103,105,102,116,10,110,111,116,101,10,110,117,109,98,101,114,10,115,119,
101,97,116,10,98,111,120,10,99,104,105,108,108,10,99,108,111,116,104,101,115,10,108,97,100,121,10,109,97,114,107,10,112,97,114,107,10,112,111,111,114,10,115,97,100,110,101,115,115,10,116,105,101,10,97,
110,105,109,97,108,10,98,101,108,111,110,103,10,98,114,117,115,104,10,99,111,110,115,117,109,101,10,100,97,119,110,10,102,111,114,101,115,116,10,105,110,110,111,99,101,110,116,10,112,101,110,10,112,114,
105,100,101,10,115,116,114,101,97,109,10,116,104,105,99,107,10,99,108,97,121,10,99,111,109,112,108,101,116,101,10,99,111,117,110,116,10,100,114,97,119,10,102,97,105,116,104,10,112,114,101,115,115,10,115,
105,108,118,101,114,10,115,116,114,117,103,103,108,101,10,115,117,114,102,97,99,101,10,116,97,117,103,104,116,10,116,101,97,99,104,10,119,101,116,10,98,108,101,115,115,10,99,104,97,115,101,10,99,108,105,
109,98,10,101,110,116,101,114,10,108,101,116,116,101,114,10,109,101,108,116,10,109,101,116,97,108,10,109,111,118,105,101,10,115,116,114,101,116,99,104,10,115,119,105,110,103,10,118,105,115,105,111,110,
10,119,105,102,101,10,98,101,115,105,100,101,10,99,114,97,115,104,10,102,111,114,103,111,116,10,103,117,105,100,101,10,104,97,117,110,116,10,106,111,107,101,10,107,110,111,99,107,10,112,108,97,110,116,
10,112,111,117,114,10,112,114,111,118,101,10,114,101,118,101,97,108,10,115,116,101,97,108,10,115,116,117,102,102,10,116,114,105,112,10,119,111,111,100,10,119,114,105,115,116,10,98,111,116,104,101,114,
10,98,111,116,116,111,109,10,99,114,97,119,108,10,99,114,111,119,100,10,102,105,120,10,102,111,114,103,105,118,101,10,102,114,111,119,110,10,103,114,97,99,101,10,108,111,111,115,101,10,108,117,99,107,
121,10,112,97,114,116,121,10,114,101,108,101,97,115,101,10,115,117,114,101,108,121,10,115,117,114,118,105,118,101,10,116,101,97,99,104,101,114,10,103,101,110,116,108,121,10,103,114,105,112,10,115,112,
101,101,100,10,115,117,105,99,105,100,101,10,116,114,97,118,101,108,10,116,114,101,97,116,10,118,101,105,110,10,119,114,105,116,116,101,110,10,99,97,103,101,10,99,104,97,105,110,10,99,111,110,118,101,
114,115,97,116,105,111,110,10,100,97,116,101,10,101,110,101,109,121,10,104,111,119,101,118,101,114,10,105,110,116,101,114,101,115,116,10,109,105,108,108,105,111,110,10,112,97,103,101,10,112,105,110,107,
10,112,114,111,117,100,10,115,119,97,121,10,116,104,101,109,115,101,108,118,101,115,10,119,105,110,116,101,114,10,99,104,117,114,99,104,10,99,114,117,101,108,10,99,117,112,10,100,101,109,111,110,10,101,
120,112,101,114,105,101,110,99,101,10,102,114,101,101,100,111,109,10,112,97,105,114,10,112,111,112,10,112,117,114,112,111,115,101,10,114,101,115,112,101,99,116,10,115,104,111,111,116,10,115,111,102,116,
108,121,10,115,116,97,116,101,10,115,116,114,97,110,103,101,10,98,97,114,10,98,105,114,116,104,10,99,117,114,108,10,100,105,114,116,10,101,120,99,117,115,101,10,108,111,114,100,10,108,111,118,101,108,
121,10,109,111,110,115,116,101,114,10,111,114,100,101,114,10,112,97,99,107,10,112,97,110,116,115,10,112,111,111,108,10,115,99,101,110,101,10,115,101,118,101,110,10,115,104,97,109,101,10,115,108,105,100,
101,10,117,103,108,121,10,97,109,111,110,103,10,98,108,97,100,101,10,98,108,111,110,100,101,10,99,108,111,115,101,116,10,99,114,101,101,107,10,100,101,110,121,10,100,114,117,103,10,101,116,101,114,110,
105,116,121,10,103,97,105,110,10,103,114,97,100,101,10,104,97,110,100,108,101,10,107,101,121,10,108,105,110,103,101,114,10,112,97,108,101,10,112,114,101,112,97,114,101,10,115,119,97,108,108,111,119,10,
115,119,105,109,10,116,114,101,109,98,108,101,10,119,104,101,101,108,10,119,111,110,10,99,97,115,116,10,99,105,103,97,114,101,116,116,101,10,99,108,97,105,109,10,99,111,108,108,101,103,101,10,100,105,
114,101,99,116,105,111,110,10,100,105,114,116,121,10,103,97,116,104,101,114,10,103,104,111,115,116,10,104,117,110,100,114,101,100,10,108,111,115,115,10,108,117,110,103,10,111,114,97,110,103,101,10,112,
114,101,115,101,110,116,10,115,119,101,97,114,10,115,119,105,114,108,10,116,119,105,99,101,10,119,105,108,100,10,98,105,116,116,101,114,10,98,108,97,110,107,101,116,10,100,111,99,116,111,114,10,101,118,
101,114,121,119,104,101,114,101,10,102,108,97,115,104,10,103,114,111,119,110,10,107,110,111,119,108,101,100,103,101,10,110,117,109,98,10,112,114,101,115,115,117,114,101,10,114,97,100,105,111,10,114,101,
112,101,97,116,10,114,117,105,110,10,115,112,101,110,100,10,117,110,107,110,111,119,110,10,98,117,121,10,99,108,111,99,107,10,100,101,118,105,108,10,101,97,114,108,121,10,102,97,108,115,101,10,102,97,
110,116,97,115,121,10,112,111,117,110,100,10,112,114,101,99,105,111,117,115,10,114,101,102,117,115,101,10,115,104,101,101,116,10,116,101,101,116,104,10,119,101,108,99,111,109,101,10,97,100,100,10,97,104,
101,97,100,10,98,108,111,99,107,10,98,117,114,121,10,99,97,114,101,115,115,10,99,111,110,116,101,110,116,10,100,101,112,116,104,10,100,101,115,112,105,116,101,10,100,105,115,116,97,110,116,10,109,97,114,
114,121,10,112,117,114,112,108,101,10,116,104,114,101,119,10,119,104,101,110,101,118,101,114,10,98,111,109,98,10,100,117,108,108,10,101,97,115,105,108,121,10,103,114,97,115,112,10,104,111,115,112,105,
116,97,108,10,105,110,110,111,99,101,110,99,101,10,110,111,114,109,97,108,10,114,101,99,101,105,118,101,10,114,101,112,108,121,10,114,104,121,109,101,10,115,104,97,100,101,10,115,111,109,101,100,97,121,
10,115,119,111,114,100,10,116,111,101,10,118,105,115,105,116,10,97,115,108,101,101,112,10,98,111,117,103,104,116,10,99,101,110,116,101,114,10,99,111,110,115,105,100,101,114,10,102,108,97,116,10,104,101,
114,111,10,104,105,115,116,111,114,121,10,105,110,107,10,105,110,115,97,110,101,10,109,117,115,99,108,101,10,109,121,115,116,101,114,121,10,112,111,99,107,101,116,10,114,101,102,108,101,99,116,105,111,
110,10,115,104,111,118,101,10,115,105,108,101,110,116,108,121,10,115,109,97,114,116,10,115,111,108,100,105,101,114,10,115,112,111,116,10,115,116,114,101,115,115,10,116,114,97,105,110,10,116,121,112,101,
10,118,105,101,119,10,119,104,101,116,104,101,114,10,98,117,115,10,101,110,101,114,103,121,10,101,120,112,108,97,105,110,10,104,111,108,121,10,104,117,110,103,101,114,10,105,110,99,104,10,109,97,103,105,
99,10,109,105,120,10,110,111,105,115,101,10,110,111,119,104,101,114,101,10,112,114,97,121,101,114,10,112,114,101,115,101,110,99,101,10,115,104,111,99,107,10,115,110,97,112,10,115,112,105,100,101,114,10,
115,116,117,100,121,10,116,104,117,110,100,101,114,10,116,114,97,105,108,10,97,100,109,105,116,10,97,103,114,101,101,10,98,97,103,10,98,97,110,103,10,98,111,117,110,100,10,98,117,116,116,101,114,102,108,
121,10,99,117,116,101,10,101,120,97,99,116,108,121,10,101,120,112,108,111,100,101,10,102,97,109,105,108,105,97,114,10,102,111,108,100,10,102,117,114,116,104,101,114,10,112,105,101,114,99,101,10,114,101,
102,108,101,99,116,10,115,99,101,110,116,10,115,101,108,102,105,115,104,10,115,104,97,114,112,10,115,105,110,107,10,115,112,114,105,110,103,10,115,116,117,109,98,108,101,10,117,110,105,118,101,114,115,
101,10,119,101,101,112,10,119,111,109,101,110,10,119,111,110,100,101,114,102,117,108,10,97,99,116,105,111,110,10,97,110,99,105,101,110,116,10,97,116,116,101,109,112,116,10,97,118,111,105,100,10,98,105,
114,116,104,100,97,121,10,98,114,97,110,99,104,10,99,104,111,99,111,108,97,116,101,10,99,111,114,101,10,100,101,112,114,101,115,115,10,100,114,117,110,107,10,101,115,112,101,99,105,97,108,108,121,10,102,
111,99,117,115,10,102,114,117,105,116,10,104,111,110,101,115,116,10,109,97,116,99,104,10,112,97,108,109,10,112,101,114,102,101,99,116,108,121,10,112,105,108,108,111,119,10,112,105,116,121,10,112,111,105,
115,111,110,10,114,111,97,114,10,115,104,105,102,116,10,115,108,105,103,104,116,108,121,10,116,104,117,109,112,10,116,114,117,99,107,10,116,117,110,101,10,116,119,101,110,116,121,10,117,110,97,98,108,
101,10,119,105,112,101,10,119,114,111,116,101,10,99,111,97,116,10,99,111,110,115,116,97,110,116,10,100,105,110,110,101,114,10,100,114,111,118,101,10,101,103,103,10,101,116,101,114,110,97,108,10,102,108,
105,103,104,116,10,102,108,111,111,100,10,102,114,97,109,101,10,102,114,101,97,107,10,103,97,115,112,10,103,108,97,100,10,104,111,108,108,111,119,10,109,111,116,105,111,110,10,112,101,101,114,10,112,108,
97,115,116,105,99,10,114,111,111,116,10,115,99,114,101,101,110,10,115,101,97,115,111,110,10,115,116,105,110,103,10,115,116,114,105,107,101,10,116,101,97,109,10,117,110,108,105,107,101,10,118,105,99,116,
105,109,10,118,111,108,117,109,101,10,119,97,114,110,10,119,101,105,114,100,10,97,116,116,97,99,107,10,97,119,97,105,116,10,97,119,97,107,101,10,98,117,105,108,116,10,99,104,97,114,109,10,99,114,97,118,
101,10,100,101,115,112,97,105,114,10,102,111,117,103,104,116,10,103,114,97,110,116,10,103,114,105,101,102,10,104,111,114,115,101,10,108,105,109,105,116,10,109,101,115,115,97,103,101,10,114,105,112,112,
108,101,10,115,97,110,105,116,121,10,115,99,97,116,116,101,114,10,115,101,114,118,101,10,115,112,108,105,116,10,115,116,114,105,110,103,10,116,114,105,99,107,10,97,110,110,111,121,10,98,108,117,114,10,
98,111,97,116,10,98,114,97,118,101,10,99,108,101,97,114,108,121,10,99,108,105,110,103,10,99,111,110,110,101,99,116,10,102,105,115,116,10,102,111,114,116,104,10,105,109,97,103,105,110,97,116,105,111,110,
10,105,114,111,110,10,106,111,99,107,10,106,117,100,103,101,10,108,101,115,115,111,110,10,109,105,108,107,10,109,105,115,101,114,121,10,110,97,105,108,10,110,97,107,101,100,10,111,117,114,115,101,108,
118,101,115,10,112,111,101,116,10,112,111,115,115,105,98,108,101,10,112,114,105,110,99,101,115,115,10,115,97,105,108,10,115,105,122,101,10,115,110,97,107,101,10,115,111,99,105,101,116,121,10,115,116,114,
111,107,101,10,116,111,114,116,117,114,101,10,116,111,115,115,10,116,114,97,99,101,10,119,105,115,101,10,98,108,111,111,109,10,98,117,108,108,101,116,10,99,101,108,108,10,99,104,101,99,107,10,99,111,115,
116,10,100,97,114,108,105,110,103,10,100,117,114,105,110,103,10,102,111,111,116,115,116,101,112,10,102,114,97,103,105,108,101,10,104,97,108,108,119,97,121,10,104,97,114,100,108,121,10,104,111,114,105,
122,111,110,10,105,110,118,105,115,105,98,108,101,10,106,111,117,114,110,101,121,10,109,105,100,110,105,103,104,116,10,109,117,100,10,110,111,100,10,112,97,117,115,101,10,114,101,108,97,120,10,115,104,
105,118,101,114,10,115,117,100,100,101,110,10,118,97,108,117,101,10,121,111,117,116,104,10,97,98,117,115,101,10,97,100,109,105,114,101,10,98,108,105,110,107,10,98,114,101,97,115,116,10,98,114,117,105,
115,101,10,99,111,110,115,116,97,110,116,108,121,10,99,111,117,112,108,101,10,99,114,101,101,112,10,99,117,114,118,101,10,100,105,102,102,101,114,101,110,99,101,10,100,117,109,98,10,101,109,112,116,105,
110,101,115,115,10,103,111,116,116,97,10,104,111,110,111,114,10,112,108,97,105,110,10,112,108,97,110,101,116,10,114,101,99,97,108,108,10,114,117,98,10,115,104,105,112,10,115,108,97,109,10,115,111,97,114,
10,115,111,109,101,98,111,100,121,10,116,105,103,104,116,108,121,10,119,101,97,116,104,101,114,10,97,100,111,114,101,10,97,112,112,114,111,97,99,104,10,98,111,110,100,10,98,114,101,97,100,10,98,117,114,
115,116,10,99,97,110,100,108,101,10,99,111,102,102,101,101,10,99,111,117,115,105,110,10,99,114,105,109,101,10,100,101,115,101,114,116,10,102,108,117,116,116,101,114,10,102,114,111,122,101,110,10,103,114,
97,110,100,10,104,101,101,108,10,104,101,108,108,111,10,108,97,110,103,117,97,103,101,10,108,101,118,101,108,10,109,111,118,101,109,101,110,116,10,112,108,101,97,115,117,114,101,10,112,111,119,101,114,
102,117,108,10,114,97,110,100,111,109,10,114,104,121,116,104,109,10,115,101,116,116,108,101,10,115,105,108,108,121,10,115,108,97,112,10,115,111,114,116,10,115,112,111,107,101,110,10,115,116,101,101,108,
10,116,104,114,101,97,116,101,110,10,116,117,109,98,108,101,10,117,112,115,101,116,10,97,115,105,100,101,10,97,119,107,119,97,114,100,10,98,101,101,10,98,108,97,110,107,10,98,111,97,114,100,10,98,117,
116,116,111,110,10,99,97,114,100,10,99,97,114,101,102,117,108,108,121,10,99,111,109,112,108,97,105,110,10,99,114,97,112,10,100,101,101,112,108,121,10,100,105,115,99,111,118,101,114,10,100,114,97,103,10,
100,114,101,97,100,10,101,102,102,111,114,116,10,101,110,116,105,114,101,10,102,97,105,114,121,10,103,105,97,110,116,10,103,111,116,116,101,110,10,103,114,101,101,116,10,105,108,108,117,115,105,111,110,
10,106,101,97,110,115,10,108,101,97,112,10,108,105,113,117,105,100,10,109,97,114,99,104,10,109,101,110,100,10,110,101,114,118,111,117,115,10,110,105,110,101,10,114,101,112,108,97,99,101,10,114,111,112,
101,10,115,112,105,110,101,10,115,116,111,108,101,10,116,101,114,114,111,114,10,97,99,99,105,100,101,110,116,10,97,112,112,108,101,10,98,97,108,97,110,99,101,10,98,111,111,109,10,99,104,105,108,100,104,
111,111,100,10,99,111,108,108,101,99,116,10,100,101,109,97,110,100,10,100,101,112,114,101,115,115,105,111,110,10,101,118,101,110,116,117,97,108,108,121,10,102,97,105,110,116,10,103,108,97,114,101,10,103,
111,97,108,10,103,114,111,117,112,10,104,111,110,101,121,10,107,105,116,99,104,101,110,10,108,97,105,100,10,108,105,109,98,10,109,97,99,104,105,110,101,10,109,101,114,101,10,109,111,108,100,10,109,117,
114,100,101,114,10,110,101,114,118,101,10,112,97,105,110,102,117,108,10,112,111,101,116,114,121,10,112,114,105,110,99,101,10,114,97,98,98,105,116,10,115,104,101,108,116,101,114,10,115,104,111,114,101,
10,115,104,111,119,101,114,10,115,111,111,116,104,101,10,115,116,97,105,114,10,115,116,101,97,100,121,10,115,117,110,108,105,103,104,116,10,116,97,110,103,108,101,10,116,101,97,115,101,10,116,114,101,
97,115,117,114,101,10,117,110,99,108,101,10,98,101,103,117,110,10,98,108,105,115,115,10,99,97,110,118,97,115,10,99,104,101,101,114,10,99,108,97,119,10,99,108,117,116,99,104,10,99,111,109,109,105,116,10,
99,114,105,109,115,111,110,10,99,114,121,115,116,97,108,10,100,101,108,105,103,104,116,10,100,111,108,108,10,101,120,105,115,116,101,110,99,101,10,101,120,112,114,101,115,115,10,102,111,103,10,102,111,
111,116,98,97,108,108,10,103,97,121,10,103,111,111,115,101,10,103,117,97,114,100,10,104,97,116,114,101,100,10,105,108,108,117,109,105,110,97,116,101,10,109,97,115,115,10,109,97,116,104,10,109,111,117,
114,110,10,114,105,99,104,10,114,111,117,103,104,10,115,107,105,112,10,115,116,105,114,10,115,116,117,100,101,110,116,10,115,116,121,108,101,10,115,117,112,112,111,114,116,10,116,104,111,114,110,10,116,
111,117,103,104,10,121,97,114,100,10,121,101,97,114,110,10,121,101,115,116,101,114,100,97,121,10,97,100,118,105,99,101,10,97,112,112,114,101,99,105,97,116,101,10,97,117,116,117,109,110,10,98,97,110,107,
10,98,101,97,109,10,98,111,119,108,10,99,97,112,116,117,114,101,10,99,97,114,118,101,10,99,111,108,108,97,112,115,101,10,99,111,110,102,117,115,105,111,110,10,99,114,101,97,116,105,111,110,10,100,111,
118,101,10,102,101,97,116,104,101,114,10,103,105,114,108,102,114,105,101,110,100,10,103,108,111,114,121,10,103,111,118,101,114,110,109,101,110,116,10,104,97,114,115,104,10,104,111,112,10,105,110,110,101,
114,10,108,111,115,101,114,10,109,111,111,110,108,105,103,104,116,10,110,101,105,103,104,98,111,114,10,110,101,105,116,104,101,114,10,112,101,97,99,104,10,112,105,103,10,112,114,97,105,115,101,10,115,
99,114,101,119,10,115,104,105,101,108,100,10,115,104,105,109,109,101,114,10,115,110,101,97,107,10,115,116,97,98,10,115,117,98,106,101,99,116,10,116,104,114,111,117,103,104,111,117,116,10,116,104,114,111,
119,110,10,116,111,119,101,114,10,116,119,105,114,108,10,119,111,119,10,97,114,109,121,10,97,114,114,105,118,101,10,98,97,116,104,114,111,111,109,10,98,117,109,112,10,99,101,97,115,101,10,99,111,111,107,
105,101,10,99,111,117,99,104,10,99,111,117,114,97,103,101,10,100,105,109,10,103,117,105,108,116,10,104,111,119,108,10,104,117,109,10,104,117,115,98,97,110,100,10,105,110,115,117,108,116,10,108,101,100,
10,108,117,110,99,104,10,109,111,99,107,10,109,111,115,116,108,121,10,110,97,116,117,114,97,108,10,110,101,97,114,108,121,10,110,101,101,100,108,101,10,110,101,114,100,10,112,101,97,99,101,102,117,108,
10,112,101,114,102,101,99,116,105,111,110,10,112,105,108,101,10,112,114,105,99,101,10,114,101,109,111,118,101,10,114,111,97,109,10,115,97,110,99,116,117,97,114,121,10,115,101,114,105,111,117,115,10,115,
104,105,110,121,10,115,104,111,111,107,10,115,111,98,10,115,116,111,108,101,110,10,116,97,112,10,118,97,105,110,10,118,111,105,100,10,119,97,114,114,105,111,114,10,119,114,105,110,107,108,101,10,97,102,
102,101,99,116,105,111,110,10,97,112,111,108,111,103,105,122,101,10,98,108,111,115,115,111,109,10,98,111,117,110,99,101,10,98,114,105,100,103,101,10,99,104,101,97,112,10,99,114,117,109,98,108,101,10,100,
101,99,105,115,105,111,110,10,100,101,115,99,101,110,100,10,100,101,115,112,101,114,97,116,101,108,121,10,100,105,103,10,100,111,116,10,102,108,105,112,10,102,114,105,103,104,116,101,110,10,104,101,97,
114,116,98,101,97,116,10,104,117,103,101,10,108,97,122,121,10,108,105,99,107,10,111,100,100,10,111,112,105,110,105,111,110,10,112,114,111,99,101,115,115,10,112,117,122,122,108,101,10,113,117,105,101,116,
108,121,10,114,101,116,114,101,97,116,10,115,99,111,114,101,10,115,101,110,116,101,110,99,101,10,115,101,112,97,114,97,116,101,10,115,105,116,117,97,116,105,111,110,10,115,107,105,108,108,10,115,111,97,
107,10,115,113,117,97,114,101,10,115,116,114,97,121,10,116,97,105,110,116,10,116,97,115,107,10,116,105,100,101,10,117,110,100,101,114,110,101,97,116,104,10,118,101,105,108,10,119,104,105,115,116,108,101,
10,97,110,121,119,104,101,114,101,10,98,101,100,114,111,111,109,10,98,105,100,10,98,108,111,111,100,121,10,98,117,114,100,101,110,10,99,97,114,101,102,117,108,10,99,111,109,112,97,114,101,10,99,111,110,
99,101,114,110,10,99,117,114,116,97,105,110,10,100,101,99,97,121,10,100,101,102,101,97,116,10,100,101,115,99,114,105,98,101,10,100,111,117,98,108,101,10,100,114,101,97,109,101,114,10,100,114,105,118,101,
114,10,100,119,101,108,108,10,101,118,101,110,105,110,103,10,102,108,97,114,101,10,102,108,105,99,107,101,114,10,103,114,97,110,100,109,97,10,103,117,105,116,97,114,10,104,97,114,109,10,104,111,114,114,
105,98,108,101,10,104,117,110,103,114,121,10,105,110,100,101,101,100,10,108,97,99,101,10,109,101,108,111,100,121,10,109,111,110,107,101,121,10,110,97,116,105,111,110,10,111,98,106,101,99,116,10,111,98,
118,105,111,117,115,108,121,10,114,97,105,110,98,111,119,10,115,97,108,116,10,115,99,114,97,116,99,104,10,115,104,111,119,110,10,115,104,121,10,115,116,97,103,101,10,115,116,117,110,10,116,104,105,114,
100,10,116,105,99,107,108,101,10,117,115,101,108,101,115,115,10,119,101,97,107,110,101,115,115,10,119,111,114,115,104,105,112,10,119,111,114,116,104,108,101,115,115,10,97,102,116,101,114,110,111,111,110,
10,98,101,97,114,100,10,98,111,121,102,114,105,101,110,100,10,98,117,98,98,108,101,10,98,117,115,121,10,99,101,114,116,97,105,110,10,99,104,105,110,10,99,111,110,99,114,101,116,101,10,100,101,115,107,
10,100,105,97,109,111,110,100,10,100,111,111,109,10,100,114,97,119,110,10,100,117,101,10,102,101,108,105,99,105,116,121,10,102,114,101,101,122,101,10,102,114,111,115,116,10,103,97,114,100,101,110,10,103,
108,105,100,101,10,104,97,114,109,111,110,121,10,104,111,112,101,102,117,108,108,121,10,104,117,110,116,10,106,101,97,108,111,117,115,10,108,105,103,104,116,110,105,110,103,10,109,97,109,97,10,109,101,
114,99,121,10,112,101,101,108,10,112,104,121,115,105,99,97,108,10,112,111,115,105,116,105,111,110,10,112,117,108,115,101,10,112,117,110,99,104,10,113,117,105,116,10,114,97,110,116,10,114,101,115,112,111,
110,100,10,115,97,108,116,121,10,115,97,110,101,10,115,97,116,105,115,102,121,10,115,97,118,105,111,114,10,115,104,101,101,112,10,115,108,101,112,116,10,115,111,99,105,97,108,10,115,112,111,114,116,10,
116,117,99,107,10,117,116,116,101,114,10,118,97,108,108,101,121,10,119,111,108,102,10,97,105,109,10,97,108,97,115,10,97,108,116,101,114,10,97,114,114,111,119,10,97,119,97,107,101,110,10,98,101,97,116,
101,110,10,98,101,108,105,101,102,10,98,114,97,110,100,10,99,101,105,108,105,110,103,10,99,104,101,101,115,101,10,99,108,117,101,10,99,111,110,102,105,100,101,110,99,101,10,99,111,110,110,101,99,116,105,
111,110,10,100,97,105,108,121,10,100,105,115,103,117,105,115,101,10,101,97,103,101,114,10,101,114,97,115,101,10,101,115,115,101,110,99,101,10,101,118,101,114,121,116,105,109,101,10,101,120,112,114,101,
115,115,105,111,110,10,102,97,110,10,102,108,97,103,10,102,108,105,114,116,10,102,111,117,108,10,102,117,114,10,103,105,103,103,108,101,10,103,108,111,114,105,111,117,115,10,105,103,110,111,114,97,110,
99,101,10,108,97,119,10,108,105,102,101,108,101,115,115,10,109,101,97,115,117,114,101,10,109,105,103,104,116,121,10,109,117,115,101,10,110,111,114,116,104,10,111,112,112,111,115,105,116,101,10,112,97,
114,97,100,105,115,101,10,112,97,116,105,101,110,99,101,10,112,97,116,105,101,110,116,10,112,101,110,99,105,108,10,112,101,116,97,108,10,112,108,97,116,101,10,112,111,110,100,101,114,10,112,111,115,115,
105,98,108,121,10,112,114,97,99,116,105,99,101,10,115,108,105,99,101,10,115,112,101,108,108,10,115,116,111,99,107,10,115,116,114,105,102,101,10,115,116,114,105,112,10,115,117,102,102,111,99,97,116,101,
10,115,117,105,116,10,116,101,110,100,101,114,10,116,111,111,108,10,116,114,97,100,101,10,118,101,108,118,101,116,10,118,101,114,115,101,10,119,97,105,115,116,10,119,105,116,99,104,10,97,117,110,116,10,
98,101,110,99,104,10,98,111,108,100,10,99,97,112,10,99,101,114,116,97,105,110,108,121,10,99,108,105,99,107,10,99,111,109,112,97,110,105,111,110,10,99,114,101,97,116,111,114,10,100,97,114,116,10,100,101,
108,105,99,97,116,101,10,100,101,116,101,114,109,105,110,101,10,100,105,115,104,10,100,114,97,103,111,110,10,100,114,97,109,97,10,100,114,117,109,10,100,117,100,101,10,101,118,101,114,121,98,111,100,121,
10,102,101,97,115,116,10,102,111,114,101,104,101,97,100,10,102,111,114,109,101,114,10,102,114,105,103,104,116,10,102,117,108,108,121,10,103,97,115,10,104,111,111,107,10,104,117,114,108,10,105,110,118,
105,116,101,10,106,117,105,99,101,10,109,97,110,97,103,101,10,109,111,114,97,108,10,112,111,115,115,101,115,115,10,114,97,119,10,114,101,98,101,108,10,114,111,121,97,108,10,115,99,97,108,101,10,115,99,
97,114,121,10,115,101,118,101,114,97,108,10,115,108,105,103,104,116,10,115,116,117,98,98,111,114,110,10,115,119,101,108,108,10,116,97,108,101,110,116,10,116,101,97,10,116,101,114,114,105,98,108,101,10,
116,104,114,101,97,100,10,116,111,114,109,101,110,116,10,116,114,105,99,107,108,101,10,117,115,117,97,108,108,121,10,118,97,115,116,10,118,105,111,108,101,110,99,101,10,119,101,97,118,101,10,97,99,105,
100,10,97,103,111,110,121,10,97,115,104,97,109,101,100,10,97,119,101,10,98,101,108,108,121,10,98,108,101,110,100,10,98,108,117,115,104,10,99,104,97,114,97,99,116,101,114,10,99,104,101,97,116,10,99,111,
109,109,111,110,10,99,111,109,112,97,110,121,10,99,111,119,97,114,100,10,99,114,101,97,107,10,100,97,110,103,101,114,10,100,101,97,100,108,121,10,100,101,102,101,110,115,101,10,100,101,102,105,110,101,
10,100,101,112,101,110,100,10,100,101,115,112,101,114,97,116,101,10,100,101,115,116,105,110,97,116,105,111,110,10,100,101,119,10,100,117,99,107,10,100,117,115,116,121,10,101,109,98,97,114,114,97,115,115,
10,101,110,103,105,110,101,10,101,120,97,109,112,108,101,10,101,120,112,108,111,114,101,10,102,111,101,10,102,114,101,101,108,121,10,102,114,117,115,116,114,97,116,101,10,103,101,110,101,114,97,116,105,
111,110,10,103,108,111,118,101,10,103,117,105,108,116,121,10,104,101,97,108,116,104,10,104,117,114,114,121,10,105,100,105,111,116,10,105,109,112,111,115,115,105,98,108,101,10,105,110,104,97,108,101,10,
106,97,119,10,107,105,110,103,100,111,109,10,109,101,110,116,105,111,110,10,109,105,115,116,10,109,111,97,110,10,109,117,109,98,108,101,10,109,117,116,116,101,114,10,111,98,115,101,114,118,101,10,111,
100,101,10,112,97,116,104,101,116,105,99,10,112,97,116,116,101,114,110,10,112,105,101,10,112,114,101,102,101,114,10,112,117,102,102,10,114,97,112,101,10,114,97,114,101,10,114,101,118,101,110,103,101,10,
114,117,100,101,10,115,99,114,97,112,101,10,115,112,105,114,97,108,10,115,113,117,101,101,122,101,10,115,116,114,97,105,110,10,115,117,110,115,101,116,10,115,117,115,112,101,110,100,10,115,121,109,112,
97,116,104,121,10,116,104,105,103,104,10,116,104,114,111,110,101,10,116,111,116,97,108,10,117,110,115,101,101,110,10,119,101,97,112,111,110,10,119,101,97,114,121,0,0};

const char* SettingsComponent::brswordlist_txt = (const char*) resource_SettingsComponent_brswordlist_txt;
const int SettingsComponent::brswordlist_txtSize = 10493;


//[EndFile] You can add extra defines here...
//[/EndFile]
