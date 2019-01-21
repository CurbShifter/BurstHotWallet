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

#include "PinComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PinComponent::PinComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (textButton_1 = new TextButton ("pinButton"));
    textButton_1->setButtonText (TRANS("1"));
    textButton_1->addListener (this);
    textButton_1->setColour (TextButton::buttonColourId, Colour (0xff8d8d8d));
    textButton_1->setColour (TextButton::buttonOnColourId, Colour (0xffbebebe));

    addAndMakeVisible (unlockHeaderLabel = new Label ("unlockHeaderLabel",
                                                      TRANS("Enter PIN to unlock")));
    unlockHeaderLabel->setFont (Font (18.00f, Font::plain));
    unlockHeaderLabel->setJustificationType (Justification::centred);
    unlockHeaderLabel->setEditable (false, false, false);
    unlockHeaderLabel->setColour (TextEditor::textColourId, Colour (0xffd2d2d2));
    unlockHeaderLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textButton_2 = new TextButton ("pinButton"));
    textButton_2->setButtonText (TRANS("2"));
    textButton_2->addListener (this);
    textButton_2->setColour (TextButton::buttonColourId, Colour (0xff8d8d8d));
    textButton_2->setColour (TextButton::buttonOnColourId, Colour (0xffbebebe));

    addAndMakeVisible (textButton_3 = new TextButton ("pinButton"));
    textButton_3->setButtonText (TRANS("3"));
    textButton_3->addListener (this);
    textButton_3->setColour (TextButton::buttonColourId, Colour (0xff8d8d8d));
    textButton_3->setColour (TextButton::buttonOnColourId, Colour (0xffbebebe));

    addAndMakeVisible (textButton_4 = new TextButton ("pinButton"));
    textButton_4->setButtonText (TRANS("4"));
    textButton_4->addListener (this);
    textButton_4->setColour (TextButton::buttonColourId, Colour (0xff8d8d8d));
    textButton_4->setColour (TextButton::buttonOnColourId, Colour (0xffbebebe));

    addAndMakeVisible (textButton_5 = new TextButton ("pinButton"));
    textButton_5->setButtonText (TRANS("5"));
    textButton_5->addListener (this);
    textButton_5->setColour (TextButton::buttonColourId, Colour (0xff8d8d8d));
    textButton_5->setColour (TextButton::buttonOnColourId, Colour (0xffbebebe));

    addAndMakeVisible (textButton_6 = new TextButton ("pinButton"));
    textButton_6->setButtonText (TRANS("6"));
    textButton_6->addListener (this);
    textButton_6->setColour (TextButton::buttonColourId, Colour (0xff8d8d8d));
    textButton_6->setColour (TextButton::buttonOnColourId, Colour (0xffbebebe));

    addAndMakeVisible (textButton_7 = new TextButton ("pinButton"));
    textButton_7->setButtonText (TRANS("7"));
    textButton_7->addListener (this);
    textButton_7->setColour (TextButton::buttonColourId, Colour (0xff8d8d8d));
    textButton_7->setColour (TextButton::buttonOnColourId, Colour (0xffbebebe));

    addAndMakeVisible (textButton_8 = new TextButton ("pinButton"));
    textButton_8->setButtonText (TRANS("8"));
    textButton_8->addListener (this);
    textButton_8->setColour (TextButton::buttonColourId, Colour (0xff8d8d8d));
    textButton_8->setColour (TextButton::buttonOnColourId, Colour (0xffbebebe));

    addAndMakeVisible (textButton_9 = new TextButton ("pinButton"));
    textButton_9->setButtonText (TRANS("9"));
    textButton_9->addListener (this);
    textButton_9->setColour (TextButton::buttonColourId, Colour (0xff8d8d8d));
    textButton_9->setColour (TextButton::buttonOnColourId, Colour (0xffbebebe));

    addAndMakeVisible (textButton_0 = new TextButton ("pinButton"));
    textButton_0->setButtonText (TRANS("0"));
    textButton_0->addListener (this);
    textButton_0->setColour (TextButton::buttonColourId, Colour (0xff8d8d8d));
    textButton_0->setColour (TextButton::buttonOnColourId, Colour (0xffbebebe));

    addAndMakeVisible (pinInputTextEditor = new TextEditor ("pinInputTextEditor"));
    pinInputTextEditor->setMultiLine (false);
    pinInputTextEditor->setReturnKeyStartsNewLine (false);
    pinInputTextEditor->setReadOnly (false);
    pinInputTextEditor->setScrollbarsShown (false);
    pinInputTextEditor->setCaretVisible (true);
    pinInputTextEditor->setPopupMenuEnabled (false);
    pinInputTextEditor->setText (String());

    addAndMakeVisible (saveHeaderLabel = new Label ("saveHeaderLabel",
                                                    TRANS("A new wallet has been generated for you. Protect the wallet pass phrase by entering a personal PIN code. \n"
                                                    "The PIN may contain any character. The keypad is only for convenience.")));
    saveHeaderLabel->setFont (Font (18.00f, Font::plain));
    saveHeaderLabel->setJustificationType (Justification::centred);
    saveHeaderLabel->setEditable (false, false, false);
    saveHeaderLabel->setColour (TextEditor::textColourId, Colour (0xffd2d2d2));
    saveHeaderLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (unlockButton = new TextButton ("unlockButton"));
    unlockButton->setButtonText (TRANS("unlock"));
    unlockButton->addListener (this);
    unlockButton->setColour (TextButton::buttonColourId, Colour (0xff77b517));
    unlockButton->setColour (TextButton::buttonOnColourId, Colour (0xff77b517));
    unlockButton->setColour (TextButton::textColourOffId, Colours::white);

    addAndMakeVisible (saveButton = new TextButton ("saveButton"));
    saveButton->setButtonText (TRANS("Save pass phrase with PIN code"));
    saveButton->addListener (this);
    saveButton->setColour (TextButton::buttonColourId, Colour (0xff77b517));
    saveButton->setColour (TextButton::buttonOnColourId, Colour (0xff77b517));
    saveButton->setColour (TextButton::textColourOffId, Colours::white);
    saveButton->setColour (TextButton::textColourOnId, Colours::white);

    addAndMakeVisible (saveHeaderLabel2 = new Label ("saveHeaderLabel",
                                                     TRANS("Ensure you remember the PIN and keep it private !")));
    saveHeaderLabel2->setFont (Font (15.00f, Font::plain));
    saveHeaderLabel2->setJustificationType (Justification::centred);
    saveHeaderLabel2->setEditable (false, false, false);
    saveHeaderLabel2->setColour (Label::backgroundColourId, Colours::white);
    saveHeaderLabel2->setColour (Label::textColourId, Colour (0xff8d1212));
    saveHeaderLabel2->setColour (Label::outlineColourId, Colours::red);
    saveHeaderLabel2->setColour (TextEditor::textColourId, Colour (0xffd2d2d2));
    saveHeaderLabel2->setColour (TextEditor::backgroundColourId, Colours::white);

    addAndMakeVisible (accountsComboBox = new ComboBox ("accountsComboBox"));
    accountsComboBox->setEditableText (false);
    accountsComboBox->setJustificationType (Justification::centredLeft);
    accountsComboBox->setTextWhenNothingSelected (TRANS("Account 1"));
    accountsComboBox->setTextWhenNoChoicesAvailable (TRANS("No Accounts"));
    accountsComboBox->addItem (TRANS("Account 1"), 1);
    accountsComboBox->addListener (this);

    addAndMakeVisible (textButton_10 = new TextButton ("pinButton"));
    textButton_10->setButtonText (TRANS("x"));
    textButton_10->addListener (this);
    textButton_10->setColour (TextButton::buttonColourId, Colour (0xff8d8d8d));
    textButton_10->setColour (TextButton::buttonOnColourId, Colour (0x00bebebe));

    addAndMakeVisible (newAccountButton = new TextButton ("newAccountButton"));
    newAccountButton->setButtonText (TRANS("New"));
    newAccountButton->addListener (this);
    newAccountButton->setColour (TextButton::buttonColourId, Colour (0xff8d8d8d));
    newAccountButton->setColour (TextButton::buttonOnColourId, Colour (0xff8d8d8d));
    newAccountButton->setColour (TextButton::textColourOffId, Colours::white);

    addAndMakeVisible (delAccountButton = new TextButton ("delAccountButton"));
    delAccountButton->setButtonText (TRANS("Del"));
    delAccountButton->addListener (this);
    delAccountButton->setColour (TextButton::buttonColourId, Colour (0xff8d8d8d));
    delAccountButton->setColour (TextButton::buttonOnColourId, Colour (0xff8d8d8d));
    delAccountButton->setColour (TextButton::textColourOffId, Colours::white);


    //[UserPreSize]
	pinInputTextEditor->addListener(this);
	accountsComboBox->setVisible(false);
	newAccountButton->setVisible(false);
	delAccountButton->setVisible(false);

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	pinInputTextEditor->setPasswordCharacter(0x2022);
	pinInputTextEditor->grabKeyboardFocus();
    //[/Constructor]
}

PinComponent::~PinComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    textButton_1 = nullptr;
    unlockHeaderLabel = nullptr;
    textButton_2 = nullptr;
    textButton_3 = nullptr;
    textButton_4 = nullptr;
    textButton_5 = nullptr;
    textButton_6 = nullptr;
    textButton_7 = nullptr;
    textButton_8 = nullptr;
    textButton_9 = nullptr;
    textButton_0 = nullptr;
    pinInputTextEditor = nullptr;
    saveHeaderLabel = nullptr;
    unlockButton = nullptr;
    saveButton = nullptr;
    saveHeaderLabel2 = nullptr;
    accountsComboBox = nullptr;
    textButton_10 = nullptr;
    newAccountButton = nullptr;
    delAccountButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PinComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    /*
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setGradientFill (ColourGradient (Colour (0xffebeff4),
                                       80.0f, 200.0f,
                                       Colour (0xffb8b8b8),
                                       104.0f, 528.0f,
                                       false));
    g.fillRect (12, 12, 532, 508);

    //[UserPaint] Add your own custom painting code here..
	*/
    g.setGradientFill (ColourGradient (Colour (0xffebeff4),
                                       80.0f, 200.0f,
                                       Colour (0xffb8b8b8),
                                       104.0f, 528.0f,
                                       false));
	g.fillAll();

	int buttonSize = 50;
	Rectangle<int> r = getBounds().withPosition(0, 0).reduced(25);
	Rectangle<int> keypad(r.withTop(pinInputTextEditor->getY() + 10).withHeight(pinInputTextEditor->getHeight() + (buttonSize * 4)).withSizeKeepingCentre(buttonSize * 3, buttonSize * 4));

	g.setColour(Colour(0xffb8b8b8));
	g.fillRoundedRectangle(keypad.expanded(30).toFloat(), 5.f);
    //[/UserPaint]
}

void PinComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    /*
    //[/UserPreResize]

    textButton_1->setBounds (136, 272, 32, 24);
    unlockHeaderLabel->setBounds (368, 160, 208, 24);
    textButton_2->setBounds (176, 272, 32, 24);
    textButton_3->setBounds (216, 272, 32, 24);
    textButton_4->setBounds (136, 240, 32, 24);
    textButton_5->setBounds (176, 240, 32, 24);
    textButton_6->setBounds (216, 240, 32, 24);
    textButton_7->setBounds (136, 208, 32, 24);
    textButton_8->setBounds (176, 208, 32, 24);
    textButton_9->setBounds (216, 208, 32, 24);
    textButton_0->setBounds (176, 304, 32, 24);
    pinInputTextEditor->setBounds (128, 168, 96, 24);
    saveHeaderLabel->setBounds (16, 48, 360, 104);
    unlockButton->setBounds (392, 240, 176, 32);
    saveButton->setBounds (96, 392, 208, 32);
    saveHeaderLabel2->setBounds (64, 344, 288, 40);
    accountsComboBox->setBounds (24, 16, 176, 24);
    textButton_10->setBounds (232, 168, 32, 24);
    newAccountButton->setBounds (208, 16, 64, 24);
    delAccountButton->setBounds (272, 16, 64, 24);
    //[UserResized] Add your own custom resize handling here..
	*/

	Rectangle<int> r = getBounds().withPosition(0, 0).reduced(20);

	int w = r.getWidth();
	int accountsHeight = 5;
	int headerHeight = 80;

	accountsComboBox->setBounds(r.withHeight(accountsHeight).withSizeKeepingCentre(w - 200, accountsHeight));
	newAccountButton->setBounds(r.withHeight(accountsHeight).withSizeKeepingCentre(50, accountsHeight).withX(accountsComboBox->getRight()));
	delAccountButton->setBounds(r.withHeight(accountsHeight).withSizeKeepingCentre(50, accountsHeight).withX(newAccountButton->getRight()));
	
	unlockHeaderLabel->setBounds(r.withHeight(headerHeight).withSizeKeepingCentre(w, headerHeight));
	saveHeaderLabel->setBounds(unlockHeaderLabel->getBounds());

	int buttonSize = 50;
	pinInputTextEditor->setBounds(r.withTop(unlockHeaderLabel->getBottom() + (buttonSize)).withHeight(buttonSize / 2).withSizeKeepingCentre(buttonSize * 3, buttonSize / 2));
	textButton_10->setBounds(pinInputTextEditor->getBounds().withX(pinInputTextEditor->getRight()).withWidth(pinInputTextEditor->getHeight()));

	Rectangle<int> keypad(r.withTop(pinInputTextEditor->getBottom() + 10).withHeight(buttonSize * 4).withSizeKeepingCentre(buttonSize * 3, buttonSize * 4));
	textButton_1->setBounds(keypad.withWidth(keypad.getWidth() / 3).withHeight(keypad.getHeight() / 4).translated(0, keypad.getHeight() / 4 * 2));
	textButton_2->setBounds(keypad.withWidth(keypad.getWidth() / 3).withHeight(keypad.getHeight() / 4).translated(keypad.getWidth() / 3, keypad.getHeight() / 4 * 2));
	textButton_3->setBounds(keypad.withWidth(keypad.getWidth() / 3).withHeight(keypad.getHeight() / 4).translated(keypad.getWidth() / 3 * 2, keypad.getHeight() / 4 * 2));

	textButton_4->setBounds(keypad.withWidth(keypad.getWidth() / 3).withHeight(keypad.getHeight() / 4).translated(0, keypad.getHeight() / 4));
	textButton_5->setBounds(keypad.withWidth(keypad.getWidth() / 3).withHeight(keypad.getHeight() / 4).translated(keypad.getWidth() / 3, keypad.getHeight() / 4));
	textButton_6->setBounds(keypad.withWidth(keypad.getWidth() / 3).withHeight(keypad.getHeight() / 4).translated(keypad.getWidth() / 3 * 2, keypad.getHeight() / 4));

	textButton_7->setBounds(keypad.withWidth(keypad.getWidth() / 3).withHeight(keypad.getHeight() / 4).translated(0, 0));
	textButton_8->setBounds(keypad.withWidth(keypad.getWidth() / 3).withHeight(keypad.getHeight() / 4).translated(keypad.getWidth() / 3, 0));
	textButton_9->setBounds(keypad.withWidth(keypad.getWidth() / 3).withHeight(keypad.getHeight() / 4).translated(keypad.getWidth() / 3 * 2, 0));

	textButton_0->setBounds(keypad.withWidth(keypad.getWidth() / 3).withHeight(keypad.getHeight() / 4).translated(keypad.getWidth() / 3, keypad.getHeight() / 4 * 3));

	saveHeaderLabel2->setBounds(r.withTop(textButton_0->getBottom() + 40).withHeight(buttonSize + 10).withSizeKeepingCentre(buttonSize * 6, buttonSize + 5));
	saveButton->setBounds(saveHeaderLabel2->getBounds().translated(0, saveHeaderLabel2->getHeight() + 5));

	unlockButton->setBounds(saveHeaderLabel2->getBounds());
    //[/UserResized]
}

void PinComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButton_1)
    {
        //[UserButtonCode_textButton_1] -- add your button handler code here..
		pinInputTextEditor->setText(pinInputTextEditor->getText() + "1", false);
        //[/UserButtonCode_textButton_1]
    }
    else if (buttonThatWasClicked == textButton_2)
    {
        //[UserButtonCode_textButton_2] -- add your button handler code here..
		pinInputTextEditor->setText(pinInputTextEditor->getText() + "2", false);
        //[/UserButtonCode_textButton_2]
    }
    else if (buttonThatWasClicked == textButton_3)
    {
        //[UserButtonCode_textButton_3] -- add your button handler code here..
		pinInputTextEditor->setText(pinInputTextEditor->getText() + "3", false);
        //[/UserButtonCode_textButton_3]
    }
    else if (buttonThatWasClicked == textButton_4)
    {
        //[UserButtonCode_textButton_4] -- add your button handler code here..
		pinInputTextEditor->setText(pinInputTextEditor->getText() + "4", false);
        //[/UserButtonCode_textButton_4]
    }
    else if (buttonThatWasClicked == textButton_5)
    {
        //[UserButtonCode_textButton_5] -- add your button handler code here..
		pinInputTextEditor->setText(pinInputTextEditor->getText() + "5", false);
        //[/UserButtonCode_textButton_5]
    }
    else if (buttonThatWasClicked == textButton_6)
    {
        //[UserButtonCode_textButton_6] -- add your button handler code here..
		pinInputTextEditor->setText(pinInputTextEditor->getText() + "6", false);
        //[/UserButtonCode_textButton_6]
    }
    else if (buttonThatWasClicked == textButton_7)
    {
        //[UserButtonCode_textButton_7] -- add your button handler code here..
		pinInputTextEditor->setText(pinInputTextEditor->getText() + "7", false);
        //[/UserButtonCode_textButton_7]
    }
    else if (buttonThatWasClicked == textButton_8)
    {
        //[UserButtonCode_textButton_8] -- add your button handler code here..
		pinInputTextEditor->setText(pinInputTextEditor->getText() + "8", false);
        //[/UserButtonCode_textButton_8]
    }
    else if (buttonThatWasClicked == textButton_9)
    {
        //[UserButtonCode_textButton_9] -- add your button handler code here..
		pinInputTextEditor->setText(pinInputTextEditor->getText() + "9", false);
        //[/UserButtonCode_textButton_9]
    }
    else if (buttonThatWasClicked == textButton_0)
    {
        //[UserButtonCode_textButton_0] -- add your button handler code here..
		pinInputTextEditor->setText(pinInputTextEditor->getText() + "0", false);
        //[/UserButtonCode_textButton_0]
    }
    else if (buttonThatWasClicked == unlockButton)
    {
        //[UserButtonCode_unlockButton] -- add your button handler code here..
		interfaceListeners.call(&InterfaceListener::LoadPassPhraseReturn, pinInputTextEditor->getText());
		this->passPhrase = String::empty;
		pinInputTextEditor->setText(String::empty);
        //[/UserButtonCode_unlockButton]
    }
    else if (buttonThatWasClicked == saveButton)
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..
		SavePassPhrase();
        //[/UserButtonCode_saveButton]
    }
    else if (buttonThatWasClicked == textButton_10)
    {
        //[UserButtonCode_textButton_10] -- add your button handler code here..
		pinInputTextEditor->setText(String::empty);
        //[/UserButtonCode_textButton_10]
    }
    else if (buttonThatWasClicked == newAccountButton)
    {
        //[UserButtonCode_newAccountButton] -- add your button handler code here..
        //[/UserButtonCode_newAccountButton]
    }
    else if (buttonThatWasClicked == delAccountButton)
    {
        //[UserButtonCode_delAccountButton] -- add your button handler code here..
        //[/UserButtonCode_delAccountButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PinComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == accountsComboBox)
    {
        //[UserComboBoxCode_accountsComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_accountsComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

bool PinComponent::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PinComponent::textEditorTextChanged(TextEditor &/*editor*/) //Called when the user changes the text in some way.
{
}

void PinComponent::textEditorReturnKeyPressed(TextEditor &editor) //Called when the user presses the return key.
{
	if (pinInputTextEditor == &editor)
	{
		if (unlockButton->isVisible())
		{
			interfaceListeners.call(&InterfaceListener::LoadPassPhraseReturn, pinInputTextEditor->getText());
			this->passPhrase = String::empty;
			pinInputTextEditor->setText(String::empty);
		}
		else if (saveButton->isVisible())
		{
			SavePassPhrase();
		}
	}
}

void PinComponent::textEditorEscapeKeyPressed(TextEditor &/*editor*/) //Called when the user presses the escape key.
{
}
void PinComponent::textEditorFocusLost(TextEditor &/*editor*/) //Called when the text editor loses focus.
{
}

void PinComponent::setMode(String passPhrase)
{
	bool unlockOn = false;
	bool saveOn = false;

	this->passPhrase = passPhrase;
	if (passPhrase.isEmpty())
	{ // load / unlock
		unlockOn = true;
		pinInputTextEditor->setPasswordCharacter(0x2022);
	}
	else
	{ // save
		saveOn = true;
		pinInputTextEditor->setPasswordCharacter(0);
	}
	pinInputTextEditor->grabKeyboardFocus();

	unlockHeaderLabel->setVisible(unlockOn);
	unlockButton->setVisible(unlockOn);
	saveHeaderLabel->setVisible(saveOn);
	saveHeaderLabel2->setVisible(saveOn);
	saveButton->setVisible(saveOn);
}

void PinComponent::SavePassPhrase()
{
	if (NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Use this PIN code to protect your pass phrase?") == 1)
	{
		interfaceListeners.call(&InterfaceListener::SavePassPhrase, this->passPhrase, pinInputTextEditor->getText());
		this->passPhrase = String::empty;
		pinInputTextEditor->setText(String::empty);
	}
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PinComponent" componentName=""
                 parentClasses="public TextEditorListener, public Component, public PinComponentListener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <METHODS>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="12 12 532 508" fill="linear: 80 200, 104 528, 0=ffebeff4, 1=ffb8b8b8"
          hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="pinButton" id="c5da649f6145a1e0" memberName="textButton_1"
              virtualName="" explicitFocusOrder="0" pos="136 272 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="1" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="unlockHeaderLabel" id="9f31257814ffb142" memberName="unlockHeaderLabel"
         virtualName="" explicitFocusOrder="0" pos="368 160 208 24" edTextCol="ffd2d2d2"
         edBkgCol="0" labelText="Enter PIN to unlock" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="18" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="pinButton" id="e452bd5566ed72cb" memberName="textButton_2"
              virtualName="" explicitFocusOrder="0" pos="176 272 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="2" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="902fc968b19c9d53" memberName="textButton_3"
              virtualName="" explicitFocusOrder="0" pos="216 272 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="3" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="f683210d4b29b921" memberName="textButton_4"
              virtualName="" explicitFocusOrder="0" pos="136 240 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="4" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="fbade77027b676c3" memberName="textButton_5"
              virtualName="" explicitFocusOrder="0" pos="176 240 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="5" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="54718537e4140ae7" memberName="textButton_6"
              virtualName="" explicitFocusOrder="0" pos="216 240 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="6" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="5352fed6e60e6822" memberName="textButton_7"
              virtualName="" explicitFocusOrder="0" pos="136 208 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="7" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="4bacdc21758ad0ec" memberName="textButton_8"
              virtualName="" explicitFocusOrder="0" pos="176 208 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="8" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="643f7522b46f05ef" memberName="textButton_9"
              virtualName="" explicitFocusOrder="0" pos="216 208 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="9" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="dfb8b82c6ed69480" memberName="textButton_0"
              virtualName="" explicitFocusOrder="0" pos="176 304 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="0" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTEDITOR name="pinInputTextEditor" id="2b67f70e06f1ba4e" memberName="pinInputTextEditor"
              virtualName="" explicitFocusOrder="0" pos="128 168 96 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <LABEL name="saveHeaderLabel" id="244a523d3fc4027" memberName="saveHeaderLabel"
         virtualName="" explicitFocusOrder="0" pos="16 48 360 104" edTextCol="ffd2d2d2"
         edBkgCol="0" labelText="A new wallet has been generated for you. Protect the wallet pass phrase by entering a personal PIN code. &#10;The PIN may contain any character. The keypad is only for convenience."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="18" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="unlockButton" id="33e3372e57fc5d7c" memberName="unlockButton"
              virtualName="" explicitFocusOrder="0" pos="392 240 176 32" bgColOff="ff77b517"
              bgColOn="ff77b517" textCol="ffffffff" buttonText="unlock" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="saveButton" id="394fe95e7b293295" memberName="saveButton"
              virtualName="" explicitFocusOrder="0" pos="96 392 208 32" bgColOff="ff77b517"
              bgColOn="ff77b517" textCol="ffffffff" textColOn="ffffffff" buttonText="Save pass phrase with PIN code"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="saveHeaderLabel" id="c9a19ae588203789" memberName="saveHeaderLabel2"
         virtualName="" explicitFocusOrder="0" pos="64 344 288 40" bkgCol="ffffffff"
         textCol="ff8d1212" outlineCol="ffff0000" edTextCol="ffd2d2d2"
         edBkgCol="ffffffff" labelText="Ensure you remember the PIN and keep it private !"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <COMBOBOX name="accountsComboBox" id="86424fa522b3afca" memberName="accountsComboBox"
            virtualName="" explicitFocusOrder="0" pos="24 16 176 24" editable="0"
            layout="33" items="Account 1" textWhenNonSelected="Account 1"
            textWhenNoItems="No Accounts"/>
  <TEXTBUTTON name="pinButton" id="31341edeff5fffa9" memberName="textButton_10"
              virtualName="" explicitFocusOrder="0" pos="232 168 32 24" bgColOff="ff8d8d8d"
              bgColOn="bebebe" buttonText="x" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="newAccountButton" id="8c1001de04072832" memberName="newAccountButton"
              virtualName="" explicitFocusOrder="0" pos="208 16 64 24" bgColOff="ff8d8d8d"
              bgColOn="ff8d8d8d" textCol="ffffffff" buttonText="New" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="delAccountButton" id="8dbcb7aa8e999b6d" memberName="delAccountButton"
              virtualName="" explicitFocusOrder="0" pos="272 16 64 24" bgColOff="ff8d8d8d"
              bgColOn="ff8d8d8d" textCol="ffffffff" buttonText="Del" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
