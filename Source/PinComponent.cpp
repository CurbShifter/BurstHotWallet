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

    addAndMakeVisible (newWalletLabel = new Label ("newWalletLabel",
                                                   TRANS("Make new or import a Burstcoin wallet")));
    newWalletLabel->setFont (Font (18.00f, Font::plain));
    newWalletLabel->setJustificationType (Justification::centred);
    newWalletLabel->setEditable (false, false, false);
    newWalletLabel->setColour (TextEditor::textColourId, Colour (0xffd2d2d2));
    newWalletLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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

    addAndMakeVisible (ensurePinLabel = new Label ("ensurePinLabel",
                                                   TRANS("Ensure you remember the PIN and keep it private !")));
    ensurePinLabel->setFont (Font (15.00f, Font::plain));
    ensurePinLabel->setJustificationType (Justification::centred);
    ensurePinLabel->setEditable (false, false, false);
    ensurePinLabel->setColour (Label::backgroundColourId, Colours::white);
    ensurePinLabel->setColour (Label::textColourId, Colour (0xff8d1212));
    ensurePinLabel->setColour (Label::outlineColourId, Colours::red);
    ensurePinLabel->setColour (TextEditor::textColourId, Colour (0xffd2d2d2));
    ensurePinLabel->setColour (TextEditor::backgroundColourId, Colours::white);

    addAndMakeVisible (textButton_10 = new TextButton ("pinButton"));
    textButton_10->setButtonText (TRANS("x"));
    textButton_10->addListener (this);
    textButton_10->setColour (TextButton::buttonColourId, Colour (0xff8d8d8d));
    textButton_10->setColour (TextButton::buttonOnColourId, Colour (0x00bebebe));

    addAndMakeVisible (passPhraseLabel = new Label ("passPhraseLabel",
                                                    TRANS("pass phrase\n")));
    passPhraseLabel->setFont (Font (20.00f, Font::plain));
    passPhraseLabel->setJustificationType (Justification::centred);
    passPhraseLabel->setEditable (false, false, false);
    passPhraseLabel->setColour (Label::backgroundColourId, Colours::white);
    passPhraseLabel->setColour (Label::textColourId, Colour (0xff0037bf));
    passPhraseLabel->setColour (Label::outlineColourId, Colour (0xff0090ff));
    passPhraseLabel->setColour (TextEditor::textColourId, Colour (0xffd2d2d2));
    passPhraseLabel->setColour (TextEditor::backgroundColourId, Colours::white);

    addAndMakeVisible (importantLabel = new Label ("importantLabel",
                                                   TRANS("IMPORTANT !\n"
                                                   "Copy your 24 word pass phrase on paper.\n"
                                                   "All words are lowercase and seperated by a space.\n"
                                                   "Store it securely !\n"
                                                   "\n"
                                                   "This ensures you can always recover your wallet.")));
    importantLabel->setFont (Font (18.00f, Font::plain));
    importantLabel->setJustificationType (Justification::centred);
    importantLabel->setEditable (false, false, false);
    importantLabel->setColour (Label::backgroundColourId, Colours::white);
    importantLabel->setColour (Label::textColourId, Colour (0xfffa0d0d));
    importantLabel->setColour (Label::outlineColourId, Colours::red);
    importantLabel->setColour (TextEditor::textColourId, Colours::white);
    importantLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (protectHeaderLabel = new Label ("protectHeaderLabel",
                                                       TRANS("Protect the wallet pass phrase by entering a personal PIN code. \n"
                                                       "The PIN may contain any character. The keypad is for convenience.")));
    protectHeaderLabel->setFont (Font (18.00f, Font::plain));
    protectHeaderLabel->setJustificationType (Justification::centred);
    protectHeaderLabel->setEditable (false, false, false);
    protectHeaderLabel->setColour (TextEditor::textColourId, Colour (0xffd2d2d2));
    protectHeaderLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (addressLabel = new Label ("addressLabel",
                                                 TRANS("BURST-address")));
    addressLabel->setFont (Font (25.00f, Font::plain));
    addressLabel->setJustificationType (Justification::centredLeft);
    addressLabel->setEditable (false, false, false);
    addressLabel->setColour (TextEditor::textColourId, Colour (0xffd2d2d2));
    addressLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (refreshButton = new TextButton ("refreshButton"));
    refreshButton->setTooltip (TRANS("Generate a new one, if you dont like this one"));
    refreshButton->setButtonText (TRANS("new"));
    refreshButton->addListener (this);
    refreshButton->setColour (TextButton::buttonColourId, Colour (0xffe13a3a));
    refreshButton->setColour (TextButton::buttonOnColourId, Colour (0xff8d8d8d));

    addAndMakeVisible (importButton = new TextButton ("importButton"));
    importButton->setButtonText (TRANS("import pass phrase"));
    importButton->addListener (this);
    importButton->setColour (TextButton::buttonColourId, Colour (0xff3770d0));
    importButton->setColour (TextButton::buttonOnColourId, Colour (0xff8d8d8d));

    addAndMakeVisible (copiedTextButton = new TextButton ("copiedTextButton"));
    copiedTextButton->setButtonText (TRANS("Okay, I copied my pass phrase"));
    copiedTextButton->addListener (this);
    copiedTextButton->setColour (TextButton::buttonColourId, Colour (0xff77b517));
    copiedTextButton->setColour (TextButton::buttonOnColourId, Colour (0xff77b517));

    addAndMakeVisible (passPhraseTextEditor = new TextEditor ("passPhraseTextEditor"));
    passPhraseTextEditor->setMultiLine (false);
    passPhraseTextEditor->setReturnKeyStartsNewLine (false);
    passPhraseTextEditor->setReadOnly (false);
    passPhraseTextEditor->setScrollbarsShown (true);
    passPhraseTextEditor->setCaretVisible (true);
    passPhraseTextEditor->setPopupMenuEnabled (true);
    passPhraseTextEditor->setText (String());

    addAndMakeVisible (enterPassPhraseLabel = new Label ("enterPassPhraseLabel",
                                                         TRANS("Enter your exact pass phrase.\n"
                                                         "You can check if its correct when the BURST address below matches.")));
    enterPassPhraseLabel->setFont (Font (18.00f, Font::plain));
    enterPassPhraseLabel->setJustificationType (Justification::centred);
    enterPassPhraseLabel->setEditable (false, false, false);
    enterPassPhraseLabel->setColour (TextEditor::textColourId, Colour (0xffd2d2d2));
    enterPassPhraseLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (savePassPhraseButton = new TextButton ("savePassPhraseButton"));
    savePassPhraseButton->setButtonText (TRANS("Save (encrypted)"));
    savePassPhraseButton->addListener (this);
    savePassPhraseButton->setColour (TextButton::buttonColourId, Colour (0xff77b517));
    savePassPhraseButton->setColour (TextButton::buttonOnColourId, Colour (0xff77b517));

    addAndMakeVisible (enterAddressLabel = new Label ("enterAddressLabel",
                                                      TRANS("BURST-address")));
    enterAddressLabel->setFont (Font (25.00f, Font::plain));
    enterAddressLabel->setJustificationType (Justification::centred);
    enterAddressLabel->setEditable (false, false, false);
    enterAddressLabel->setColour (TextEditor::textColourId, Colour (0xffd2d2d2));
    enterAddressLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (newButton = new TextButton ("newButton"));
    newButton->setButtonText (TRANS("create a new wallet"));
    newButton->addListener (this);
    newButton->setColour (TextButton::buttonColourId, Colour (0xff77b517));
    newButton->setColour (TextButton::buttonOnColourId, Colour (0xff77b517));

    addAndMakeVisible (backToStartButton = new TextButton ("backToStartButton"));
    backToStartButton->setButtonText (TRANS("back"));
    backToStartButton->addListener (this);
    backToStartButton->setColour (TextButton::buttonColourId, Colour (0xffbebebe));
    backToStartButton->setColour (TextButton::buttonOnColourId, Colour (0xff8d8d8d));

    drawable1 = Drawable::createFromImageData (burstHotWalletlogo_svg, burstHotWalletlogo_svgSize);
    drawable2 = Drawable::createFromImageData (burst_logo_white_svg, burst_logo_white_svgSize);

    //[UserPreSize]
	pinInputTextEditor->addListener(this);
	passPhraseTextEditor->addListener(this);

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	pinInputTextEditor->setPasswordCharacter(0x2022);
	pinInputTextEditor->grabKeyboardFocus();

	firstOn = false;
	newOn = false;
	importOn = false;
	savePinOn = false;
	unlockOn = false;
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
    newWalletLabel = nullptr;
    unlockButton = nullptr;
    saveButton = nullptr;
    ensurePinLabel = nullptr;
    textButton_10 = nullptr;
    passPhraseLabel = nullptr;
    importantLabel = nullptr;
    protectHeaderLabel = nullptr;
    addressLabel = nullptr;
    refreshButton = nullptr;
    importButton = nullptr;
    copiedTextButton = nullptr;
    passPhraseTextEditor = nullptr;
    enterPassPhraseLabel = nullptr;
    savePassPhraseButton = nullptr;
    enterAddressLabel = nullptr;
    newButton = nullptr;
    backToStartButton = nullptr;
    drawable1 = nullptr;
    drawable2 = nullptr;


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

    g.setGradientFill (ColourGradient (Colour (0xff93c3ff),
                                       80.0f, 200.0f,
                                       Colour (0xff537088),
                                       104.0f, 528.0f,
                                       false));
    g.fillRect (12, 12, 532, 508);

    g.setColour (Colours::black);
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, Rectangle<float> (524, 12, 212, 100),
                               RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.000f);

    g.setColour (Colours::black);
    jassert (drawable2 != 0);
    if (drawable2 != 0)
        drawable2->drawWithin (g, Rectangle<float> (444, 364, 304, 100),
                               RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.000f);

    //[UserPaint] Add your own custom painting code here..
	*/
	g.setGradientFill(ColourGradient(Colour(0xff93c3ff),
		80.0f, 200.0f,
		Colour(0xff537088),
		104.0f, 528.0f,
		false));
	g.fillAll();

	int buttonSize = 50;
	Rectangle<int> r = getBounds().withPosition(0, 0).reduced(25);
	if (savePinOn || unlockOn)
	{
		Rectangle<int> keypad(r.withTop(pinInputTextEditor->getY() + 10).withHeight(pinInputTextEditor->getHeight() + (buttonSize * 4)).withSizeKeepingCentre(buttonSize * 3, buttonSize * 4));

		g.setColour(Colour(0xffb8b8b8));
		g.fillRoundedRectangle(keypad.expanded(30).toFloat(), 5.f);
	}

	if (firstOn)
	{
		g.setColour(Colours::black);
		jassert(drawable2 != 0);
		if (drawable2 != 0)
			drawable2->drawWithin(g, Rectangle<float>(getBounds().withTrimmedTop(50).withHeight(45).withTrimmedRight((getWidth() / 2) + 10).toFloat()),
			RectanglePlacement::xRight | RectanglePlacement::onlyReduceInSize, 1.000f);

		jassert(drawable1 != 0);
		if (drawable1 != 0)
			drawable1->drawWithin(g, Rectangle<float>(getBounds().withTrimmedTop(50).withHeight(80).withTrimmedLeft((getWidth() / 2) + 10).toFloat()),
			RectanglePlacement::xLeft | RectanglePlacement::onlyReduceInSize, 1.000f);
	}
    //[/UserPaint]
}

void PinComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    /*
    //[/UserPreResize]

    textButton_1->setBounds (120, 576, 32, 24);
    unlockHeaderLabel->setBounds (48, 432, 264, 24);
    textButton_2->setBounds (160, 576, 32, 24);
    textButton_3->setBounds (200, 576, 32, 24);
    textButton_4->setBounds (120, 544, 32, 24);
    textButton_5->setBounds (160, 544, 32, 24);
    textButton_6->setBounds (200, 544, 32, 24);
    textButton_7->setBounds (120, 512, 32, 24);
    textButton_8->setBounds (160, 512, 32, 24);
    textButton_9->setBounds (200, 512, 32, 24);
    textButton_0->setBounds (160, 608, 32, 24);
    pinInputTextEditor->setBounds (112, 472, 96, 24);
    newWalletLabel->setBounds (32, 16, 408, 32);
    unlockButton->setBounds (96, 664, 176, 32);
    saveButton->setBounds (376, 664, 208, 32);
    ensurePinLabel->setBounds (328, 616, 320, 40);
    textButton_10->setBounds (216, 472, 32, 24);
    passPhraseLabel->setBounds (32, 248, 408, 104);
    importantLabel->setBounds (32, 136, 408, 104);
    protectHeaderLabel->setBounds (328, 432, 320, 88);
    addressLabel->setBounds (32, 96, 312, 24);
    refreshButton->setBounds (360, 104, 80, 24);
    importButton->setBounds (240, 56, 80, 24);
    copiedTextButton->setBounds (32, 360, 408, 24);
    passPhraseTextEditor->setBounds (464, 176, 232, 152);
    enterPassPhraseLabel->setBounds (472, 128, 216, 40);
    savePassPhraseButton->setBounds (464, 360, 232, 24);
    enterAddressLabel->setBounds (464, 328, 232, 25);
    newButton->setBounds (136, 56, 80, 24);
    backToStartButton->setBounds (400, 56, 80, 24);
    //[UserResized] Add your own custom resize handling here..
	*/

	Rectangle<int> r = getBounds().withPosition(0, 0).reduced(20);

	int w = r.getWidth();
	int accountsHeight = 5;
	int headerHeight = 80;

	// first
	newWalletLabel->setBounds(r.reduced(20).withHeight(100).translated(0, 60));
	newButton->setBounds(r.reduced(20).withTrimmedTop(100).withTrimmedRight((getWidth() - 30) / 2).withHeight(50).translated(0, 60));
	importButton->setBounds(r.reduced(20).withTrimmedTop(100).withTrimmedLeft((getWidth() - 30) / 2).withHeight(50).translated(0, 60));

	// keypad
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

	// new
	int pad = 10;
	importantLabel->setBounds(r.reduced(40).withHeight(150));
	addressLabel->setBounds(r.reduced(20).withTrimmedTop(importantLabel->getBottom() + pad).withWidth(getWidth() - 140).withHeight(30));
	refreshButton->setBounds(r.reduced(20).withTrimmedTop(importantLabel->getBottom() + pad).withTrimmedLeft(getWidth() - 140).withHeight(30));
	passPhraseLabel->setBounds(r.reduced(20).withTrimmedTop(addressLabel->getBottom() + pad).withHeight(150));
	copiedTextButton->setBounds(r.reduced(20).withTrimmedTop(passPhraseLabel->getBottom()).withHeight(30));

	// import
	enterPassPhraseLabel->setBounds(r.reduced(20).withHeight(80));
	passPhraseTextEditor->setBounds(r.reduced(20).withTrimmedTop(enterPassPhraseLabel->getBottom() + pad).withHeight(120));
	enterAddressLabel->setBounds(r.reduced(20).withTrimmedTop(passPhraseTextEditor->getBottom() - 20 + pad).withHeight(50));
	savePassPhraseButton->setBounds(r.reduced(20).withTrimmedTop(enterAddressLabel->getBottom() - 20 + pad).withHeight(30));

	backToStartButton->setBounds(5, 5, 100, 20);

	// save pin
	protectHeaderLabel->setBounds(r.withHeight(headerHeight).withSizeKeepingCentre(w, headerHeight));
	ensurePinLabel->setBounds(r.withTop(textButton_0->getBottom() + 40).withHeight(buttonSize + 10).withSizeKeepingCentre(buttonSize * 6, buttonSize + 5));
	saveButton->setBounds(ensurePinLabel->getBounds().translated(0, ensurePinLabel->getHeight() + 5));

	// unlock
	unlockHeaderLabel->setBounds(r.withHeight(headerHeight).withSizeKeepingCentre(w, headerHeight));
	unlockButton->setBounds(ensurePinLabel->getBounds());


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
		ClearMemory();
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
    else if (buttonThatWasClicked == refreshButton)
    {
        //[UserButtonCode_refreshButton] -- add your button handler code here..
		setViewMode(2);
        //[/UserButtonCode_refreshButton]
    }
    else if (buttonThatWasClicked == importButton)
    {
        //[UserButtonCode_importButton] -- add your button handler code here..
		setViewMode(3);
        //[/UserButtonCode_importButton]
    }
    else if (buttonThatWasClicked == copiedTextButton)
    {
        //[UserButtonCode_copiedTextButton] -- add your button handler code here..
		setViewMode(4);
        //[/UserButtonCode_copiedTextButton]
    }
    else if (buttonThatWasClicked == savePassPhraseButton)
    {
        //[UserButtonCode_savePassPhraseButton] -- add your button handler code here..
		setViewMode(4);
		passPhraseTextEditor->clear();
        //[/UserButtonCode_savePassPhraseButton]
    }
    else if (buttonThatWasClicked == newButton)
    {
        //[UserButtonCode_newButton] -- add your button handler code here..
		setViewMode(2);
        //[/UserButtonCode_newButton]
    }
    else if (buttonThatWasClicked == backToStartButton)
    {
        //[UserButtonCode_backToStartButton] -- add your button handler code here..
		setViewMode(1);
        //[/UserButtonCode_backToStartButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

bool PinComponent::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PinComponent::textEditorTextChanged(TextEditor &editor) //Called when the user changes the text in some way.
{
	if (passPhraseTextEditor == &editor)
	{
		burstKit.SetSecretPhrase(passPhraseTextEditor->getText());
		if (passPhraseTextEditor->getText().isNotEmpty())
		{
			enterAddressLabel->setText(burstKit.GetAccountRS(), sendNotification);
			savePassPhraseButton->setEnabled(true);
		}
		else
		{
			enterAddressLabel->setText("-", sendNotification);
			savePassPhraseButton->setEnabled(false);
		}
	}
}

void PinComponent::textEditorReturnKeyPressed(TextEditor &editor) //Called when the user presses the return key.
{
	if (pinInputTextEditor == &editor)
	{
		if (unlockButton->isVisible())
		{
			interfaceListeners.call(&InterfaceListener::LoadPassPhraseReturn, pinInputTextEditor->getText());
			ClearMemory();
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

void PinComponent::setViewMode(const int mode, const String passPhrase)
{
	//burstKit.SetSecretPhrase(passPhrase);

	firstOn = false;
	newOn = false;
	importOn = false;
	savePinOn = false;
	unlockOn = false;

	passPhraseLabel->setText(NewPassPhrase(), dontSendNotification);

	if (mode == 1) // first screen (import / new)
	{
		burstKit.SetSecretPhrase(String::empty);
		firstOn = true;
	}
	else if (mode == 2)
	{
		newOn = true;

		burstKit.SetSecretPhrase(NewPassPhrase());
		passPhraseLabel->setText(burstKit.GetSecretPhraseString(), dontSendNotification);
		addressLabel->setText(burstKit.GetAccountRS(), dontSendNotification);
	}
	else if (mode == 3)
	{
		burstKit.SetSecretPhrase(String::empty);
		importOn = true;
	}
	else if (mode == 4)
	{
		if (passPhrase.isNotEmpty())
			burstKit.SetSecretPhrase(passPhrase);
		savePinOn = true;
	}
	else if (mode == 5)
	{
		burstKit.SetSecretPhrase(String::empty);
		unlockOn = true;
	}

	{
		// first
		newWalletLabel->setVisible(firstOn);
		newButton->setVisible(firstOn);
		importButton->setVisible(firstOn);

		// keypad
		pinInputTextEditor->setVisible(unlockOn || savePinOn);
		pinInputTextEditor->setPasswordCharacter(savePinOn ? 0 : 0x2022);
		if (pinInputTextEditor->isVisible())
			pinInputTextEditor->grabKeyboardFocus();
		textButton_10->setVisible(unlockOn || savePinOn);
		textButton_1->setVisible(unlockOn || savePinOn);
		textButton_2->setVisible(unlockOn || savePinOn);
		textButton_3->setVisible(unlockOn || savePinOn);
		textButton_4->setVisible(unlockOn || savePinOn);
		textButton_5->setVisible(unlockOn || savePinOn);
		textButton_6->setVisible(unlockOn || savePinOn);
		textButton_7->setVisible(unlockOn || savePinOn);
		textButton_8->setVisible(unlockOn || savePinOn);
		textButton_9->setVisible(unlockOn || savePinOn);
		textButton_0->setVisible(unlockOn || savePinOn);

		// new
		addressLabel->setVisible(newOn);
		refreshButton->setVisible(newOn);
		importantLabel->setVisible(newOn);
		passPhraseLabel->setVisible(newOn);
		copiedTextButton->setVisible(newOn);

		// import
		passPhraseTextEditor->setVisible(importOn);
		enterPassPhraseLabel->setVisible(importOn);
		savePassPhraseButton->setVisible(importOn);
		enterAddressLabel->setVisible(importOn);

		backToStartButton->setVisible(newOn || importOn);

		// save pin
		protectHeaderLabel->setVisible(savePinOn);
		ensurePinLabel->setVisible(savePinOn);
		saveButton->setVisible(savePinOn);

		// unlock
		unlockHeaderLabel->setVisible(unlockOn);
		unlockButton->setVisible(unlockOn);
	}
	repaint();
}

String PinComponent::NewPassPhrase()
{
	MemoryBlock wordListMb = MemoryBlock(brswordlist_txt, brswordlist_txtSize);
	StringArray wordList = StringArray::fromLines(wordListMb.toString());
	juce::Random r(Time::currentTimeMillis());
	String passPhrase;
	for (int i = 0; i < 24; i++)
	{
		unsigned int randInt = r.nextInt(wordList.size());
		passPhrase += wordList[randInt];
		if (i < 24 - 1)
			passPhrase += " ";
	}
	return passPhrase;
}

void PinComponent::SavePassPhrase()
{
	if (NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Use this PIN code to protect your pass phrase?") == 1)
	{
		interfaceListeners.call(&InterfaceListener::SavePassPhrase, burstKit.GetSecretPhraseString(), pinInputTextEditor->getText());
		ClearMemory();
	}
}

void PinComponent::ClearMemory()
{
	burstKit.SetSecretPhrase(String::empty);
	pinInputTextEditor->setText(String::empty);
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
    <RECT pos="12 12 532 508" fill="linear: 80 200, 104 528, 0=ff93c3ff, 1=ff537088"
          hasStroke="0"/>
    <IMAGE pos="524 12 212 100" resource="burstHotWalletlogo_svg" opacity="1"
           mode="2"/>
    <IMAGE pos="444 364 304 100" resource="burst_logo_white_svg" opacity="1"
           mode="2"/>
  </BACKGROUND>
  <TEXTBUTTON name="pinButton" id="c5da649f6145a1e0" memberName="textButton_1"
              virtualName="" explicitFocusOrder="0" pos="120 576 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="1" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="unlockHeaderLabel" id="9f31257814ffb142" memberName="unlockHeaderLabel"
         virtualName="" explicitFocusOrder="0" pos="48 432 264 24" edTextCol="ffd2d2d2"
         edBkgCol="0" labelText="Enter PIN to unlock" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="18" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="pinButton" id="e452bd5566ed72cb" memberName="textButton_2"
              virtualName="" explicitFocusOrder="0" pos="160 576 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="2" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="902fc968b19c9d53" memberName="textButton_3"
              virtualName="" explicitFocusOrder="0" pos="200 576 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="3" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="f683210d4b29b921" memberName="textButton_4"
              virtualName="" explicitFocusOrder="0" pos="120 544 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="4" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="fbade77027b676c3" memberName="textButton_5"
              virtualName="" explicitFocusOrder="0" pos="160 544 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="5" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="54718537e4140ae7" memberName="textButton_6"
              virtualName="" explicitFocusOrder="0" pos="200 544 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="6" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="5352fed6e60e6822" memberName="textButton_7"
              virtualName="" explicitFocusOrder="0" pos="120 512 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="7" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="4bacdc21758ad0ec" memberName="textButton_8"
              virtualName="" explicitFocusOrder="0" pos="160 512 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="8" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="643f7522b46f05ef" memberName="textButton_9"
              virtualName="" explicitFocusOrder="0" pos="200 512 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="9" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="pinButton" id="dfb8b82c6ed69480" memberName="textButton_0"
              virtualName="" explicitFocusOrder="0" pos="160 608 32 24" bgColOff="ff8d8d8d"
              bgColOn="ffbebebe" buttonText="0" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTEDITOR name="pinInputTextEditor" id="2b67f70e06f1ba4e" memberName="pinInputTextEditor"
              virtualName="" explicitFocusOrder="0" pos="112 472 96 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <LABEL name="newWalletLabel" id="244a523d3fc4027" memberName="newWalletLabel"
         virtualName="" explicitFocusOrder="0" pos="32 16 408 32" edTextCol="ffd2d2d2"
         edBkgCol="0" labelText="Make new or import a Burstcoin wallet"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="18" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="unlockButton" id="33e3372e57fc5d7c" memberName="unlockButton"
              virtualName="" explicitFocusOrder="0" pos="96 664 176 32" bgColOff="ff77b517"
              bgColOn="ff77b517" textCol="ffffffff" buttonText="unlock" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="saveButton" id="394fe95e7b293295" memberName="saveButton"
              virtualName="" explicitFocusOrder="0" pos="376 664 208 32" bgColOff="ff77b517"
              bgColOn="ff77b517" textCol="ffffffff" textColOn="ffffffff" buttonText="Save pass phrase with PIN code"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="ensurePinLabel" id="c9a19ae588203789" memberName="ensurePinLabel"
         virtualName="" explicitFocusOrder="0" pos="328 616 320 40" bkgCol="ffffffff"
         textCol="ff8d1212" outlineCol="ffff0000" edTextCol="ffd2d2d2"
         edBkgCol="ffffffff" labelText="Ensure you remember the PIN and keep it private !"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="pinButton" id="31341edeff5fffa9" memberName="textButton_10"
              virtualName="" explicitFocusOrder="0" pos="216 472 32 24" bgColOff="ff8d8d8d"
              bgColOn="bebebe" buttonText="x" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="passPhraseLabel" id="833feaa02d4e20e1" memberName="passPhraseLabel"
         virtualName="" explicitFocusOrder="0" pos="32 248 408 104" bkgCol="ffffffff"
         textCol="ff0037bf" outlineCol="ff0090ff" edTextCol="ffd2d2d2"
         edBkgCol="ffffffff" labelText="pass phrase&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="20" bold="0" italic="0" justification="36"/>
  <LABEL name="importantLabel" id="2d0de8ef31015c72" memberName="importantLabel"
         virtualName="" explicitFocusOrder="0" pos="32 136 408 104" bkgCol="ffffffff"
         textCol="fffa0d0d" outlineCol="ffff0000" edTextCol="ffffffff"
         edBkgCol="0" labelText="IMPORTANT !&#10;Copy your 24 word pass phrase on paper.&#10;All words are lowercase and seperated by a space.&#10;Store it securely !&#10;&#10;This ensures you can always recover your wallet."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="18" bold="0" italic="0" justification="36"/>
  <LABEL name="protectHeaderLabel" id="7231f81c9a91ac23" memberName="protectHeaderLabel"
         virtualName="" explicitFocusOrder="0" pos="328 432 320 88" edTextCol="ffd2d2d2"
         edBkgCol="0" labelText="Protect the wallet pass phrase by entering a personal PIN code. &#10;The PIN may contain any character. The keypad is for convenience."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="18" bold="0" italic="0" justification="36"/>
  <LABEL name="addressLabel" id="271d36f5ad829a89" memberName="addressLabel"
         virtualName="" explicitFocusOrder="0" pos="32 96 312 24" edTextCol="ffd2d2d2"
         edBkgCol="0" labelText="BURST-address" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="25" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="refreshButton" id="3b82e2dd2b7f5bae" memberName="refreshButton"
              virtualName="" explicitFocusOrder="0" pos="360 104 80 24" tooltip="Generate a new one, if you dont like this one"
              bgColOff="ffe13a3a" bgColOn="ff8d8d8d" buttonText="new" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="importButton" id="7617d54c57455844" memberName="importButton"
              virtualName="" explicitFocusOrder="0" pos="240 56 80 24" bgColOff="ff3770d0"
              bgColOn="ff8d8d8d" buttonText="import pass phrase" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="copiedTextButton" id="1fab30f2599e6318" memberName="copiedTextButton"
              virtualName="" explicitFocusOrder="0" pos="32 360 408 24" bgColOff="ff77b517"
              bgColOn="ff77b517" buttonText="Okay, I copied my pass phrase"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="passPhraseTextEditor" id="327932a5680b189d" memberName="passPhraseTextEditor"
              virtualName="" explicitFocusOrder="0" pos="464 176 232 152" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="enterPassPhraseLabel" id="7a2b5c39c3b79600" memberName="enterPassPhraseLabel"
         virtualName="" explicitFocusOrder="0" pos="472 128 216 40" edTextCol="ffd2d2d2"
         edBkgCol="0" labelText="Enter your exact pass phrase.&#10;You can check if its correct when the BURST address below matches."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="18" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="savePassPhraseButton" id="422992e6136d83c4" memberName="savePassPhraseButton"
              virtualName="" explicitFocusOrder="0" pos="464 360 232 24" bgColOff="ff77b517"
              bgColOn="ff77b517" buttonText="Save (encrypted)" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="enterAddressLabel" id="de69e0fb985e9592" memberName="enterAddressLabel"
         virtualName="" explicitFocusOrder="0" pos="464 328 232 25" edTextCol="ffd2d2d2"
         edBkgCol="0" labelText="BURST-address" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="25" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="newButton" id="536e3078320f4c27" memberName="newButton"
              virtualName="" explicitFocusOrder="0" pos="136 56 80 24" bgColOff="ff77b517"
              bgColOn="ff77b517" buttonText="create a new wallet" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="backToStartButton" id="b6f6a3eaf56dc963" memberName="backToStartButton"
              virtualName="" explicitFocusOrder="0" pos="400 56 80 24" bgColOff="ffbebebe"
              bgColOn="ff8d8d8d" buttonText="back" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: brswordlist_txt, 10493, "BRS-wordlist.txt"
static const unsigned char resource_PinComponent_brswordlist_txt[] = { 108,105,107,101,10,106,117,115,116,10,108,111,118,101,10,107,110,111,119,10,110,101,118,101,114,10,119,97,110,116,10,116,105,109,
101,10,111,117,116,10,116,104,101,114,101,10,109,97,107,101,10,108,111,111,107,10,101,121,101,10,100,111,119,110,10,111,110,108,121,10,116,104,105,110,107,10,104,101,97,114,116,10,98,97,99,107,10,116,
104,101,110,10,105,110,116,111,10,97,98,111,117,116,10,109,111,114,101,10,97,119,97,121,10,115,116,105,108,108,10,116,104,101,109,10,116,97,107,101,10,116,104,105,110,103,10,101,118,101,110,10,116,104,
114,111,117,103,104,10,108,111,110,103,10,97,108,119,97,121,115,10,119,111,114,108,100,10,116,111,111,10,102,114,105,101,110,100,10,116,101,108,108,10,116,114,121,10,104,97,110,100,10,116,104,111,117,
103,104,116,10,111,118,101,114,10,104,101,114,101,10,111,116,104,101,114,10,110,101,101,100,10,115,109,105,108,101,10,97,103,97,105,110,10,109,117,99,104,10,99,114,121,10,98,101,101,110,10,110,105,103,
104,116,10,101,118,101,114,10,108,105,116,116,108,101,10,115,97,105,100,10,101,110,100,10,115,111,109,101,10,116,104,111,115,101,10,97,114,111,117,110,100,10,109,105,110,100,10,112,101,111,112,108,101,
10,103,105,114,108,10,108,101,97,118,101,10,100,114,101,97,109,10,108,101,102,116,10,116,117,114,110,10,109,121,115,101,108,102,10,103,105,118,101,10,110,111,116,104,105,110,103,10,114,101,97,108,108,
121,10,111,102,102,10,98,101,102,111,114,101,10,115,111,109,101,116,104,105,110,103,10,102,105,110,100,10,119,97,108,107,10,119,105,115,104,10,103,111,111,100,10,111,110,99,101,10,112,108,97,99,101,10,
97,115,107,10,115,116,111,112,10,107,101,101,112,10,119,97,116,99,104,10,115,101,101,109,10,101,118,101,114,121,116,104,105,110,103,10,119,97,105,116,10,103,111,116,10,121,101,116,10,109,97,100,101,10,
114,101,109,101,109,98,101,114,10,115,116,97,114,116,10,97,108,111,110,101,10,114,117,110,10,104,111,112,101,10,109,97,121,98,101,10,98,101,108,105,101,118,101,10,98,111,100,121,10,104,97,116,101,10,97,
102,116,101,114,10,99,108,111,115,101,10,116,97,108,107,10,115,116,97,110,100,10,111,119,110,10,101,97,99,104,10,104,117,114,116,10,104,101,108,112,10,104,111,109,101,10,103,111,100,10,115,111,117,108,
10,110,101,119,10,109,97,110,121,10,116,119,111,10,105,110,115,105,100,101,10,115,104,111,117,108,100,10,116,114,117,101,10,102,105,114,115,116,10,102,101,97,114,10,109,101,97,110,10,98,101,116,116,101,
114,10,112,108,97,121,10,97,110,111,116,104,101,114,10,103,111,110,101,10,99,104,97,110,103,101,10,117,115,101,10,119,111,110,100,101,114,10,115,111,109,101,111,110,101,10,104,97,105,114,10,99,111,108,
100,10,111,112,101,110,10,98,101,115,116,10,97,110,121,10,98,101,104,105,110,100,10,104,97,112,112,101,110,10,119,97,116,101,114,10,100,97,114,107,10,108,97,117,103,104,10,115,116,97,121,10,102,111,114,
101,118,101,114,10,110,97,109,101,10,119,111,114,107,10,115,104,111,119,10,115,107,121,10,98,114,101,97,107,10,99,97,109,101,10,100,101,101,112,10,100,111,111,114,10,112,117,116,10,98,108,97,99,107,10,
116,111,103,101,116,104,101,114,10,117,112,111,110,10,104,97,112,112,121,10,115,117,99,104,10,103,114,101,97,116,10,119,104,105,116,101,10,109,97,116,116,101,114,10,102,105,108,108,10,112,97,115,116,10,
112,108,101,97,115,101,10,98,117,114,110,10,99,97,117,115,101,10,101,110,111,117,103,104,10,116,111,117,99,104,10,109,111,109,101,110,116,10,115,111,111,110,10,118,111,105,99,101,10,115,99,114,101,97,
109,10,97,110,121,116,104,105,110,103,10,115,116,97,114,101,10,115,111,117,110,100,10,114,101,100,10,101,118,101,114,121,111,110,101,10,104,105,100,101,10,107,105,115,115,10,116,114,117,116,104,10,100,
101,97,116,104,10,98,101,97,117,116,105,102,117,108,10,109,105,110,101,10,98,108,111,111,100,10,98,114,111,107,101,110,10,118,101,114,121,10,112,97,115,115,10,110,101,120,116,10,102,111,114,103,101,116,
10,116,114,101,101,10,119,114,111,110,103,10,97,105,114,10,109,111,116,104,101,114,10,117,110,100,101,114,115,116,97,110,100,10,108,105,112,10,104,105,116,10,119,97,108,108,10,109,101,109,111,114,121,
10,115,108,101,101,112,10,102,114,101,101,10,104,105,103,104,10,114,101,97,108,105,122,101,10,115,99,104,111,111,108,10,109,105,103,104,116,10,115,107,105,110,10,115,119,101,101,116,10,112,101,114,102,
101,99,116,10,98,108,117,101,10,107,105,108,108,10,98,114,101,97,116,104,10,100,97,110,99,101,10,97,103,97,105,110,115,116,10,102,108,121,10,98,101,116,119,101,101,110,10,103,114,111,119,10,115,116,114,
111,110,103,10,117,110,100,101,114,10,108,105,115,116,101,110,10,98,114,105,110,103,10,115,111,109,101,116,105,109,101,115,10,115,112,101,97,107,10,112,117,108,108,10,112,101,114,115,111,110,10,98,101,
99,111,109,101,10,102,97,109,105,108,121,10,98,101,103,105,110,10,103,114,111,117,110,100,10,114,101,97,108,10,115,109,97,108,108,10,102,97,116,104,101,114,10,115,117,114,101,10,102,101,101,116,10,114,
101,115,116,10,121,111,117,110,103,10,102,105,110,97,108,108,121,10,108,97,110,100,10,97,99,114,111,115,115,10,116,111,100,97,121,10,100,105,102,102,101,114,101,110,116,10,103,117,121,10,108,105,110,101,
10,102,105,114,101,10,114,101,97,115,111,110,10,114,101,97,99,104,10,115,101,99,111,110,100,10,115,108,111,119,108,121,10,119,114,105,116,101,10,101,97,116,10,115,109,101,108,108,10,109,111,117,116,104,
10,115,116,101,112,10,108,101,97,114,110,10,116,104,114,101,101,10,102,108,111,111,114,10,112,114,111,109,105,115,101,10,98,114,101,97,116,104,101,10,100,97,114,107,110,101,115,115,10,112,117,115,104,
10,101,97,114,116,104,10,103,117,101,115,115,10,115,97,118,101,10,115,111,110,103,10,97,98,111,118,101,10,97,108,111,110,103,10,98,111,116,104,10,99,111,108,111,114,10,104,111,117,115,101,10,97,108,109,
111,115,116,10,115,111,114,114,121,10,97,110,121,109,111,114,101,10,98,114,111,116,104,101,114,10,111,107,97,121,10,100,101,97,114,10,103,97,109,101,10,102,97,100,101,10,97,108,114,101,97,100,121,10,97,
112,97,114,116,10,119,97,114,109,10,98,101,97,117,116,121,10,104,101,97,114,100,10,110,111,116,105,99,101,10,113,117,101,115,116,105,111,110,10,115,104,105,110,101,10,98,101,103,97,110,10,112,105,101,
99,101,10,119,104,111,108,101,10,115,104,97,100,111,119,10,115,101,99,114,101,116,10,115,116,114,101,101,116,10,119,105,116,104,105,110,10,102,105,110,103,101,114,10,112,111,105,110,116,10,109,111,114,
110,105,110,103,10,119,104,105,115,112,101,114,10,99,104,105,108,100,10,109,111,111,110,10,103,114,101,101,110,10,115,116,111,114,121,10,103,108,97,115,115,10,107,105,100,10,115,105,108,101,110,99,101,
10,115,105,110,99,101,10,115,111,102,116,10,121,111,117,114,115,101,108,102,10,101,109,112,116,121,10,115,104,97,108,108,10,97,110,103,101,108,10,97,110,115,119,101,114,10,98,97,98,121,10,98,114,105,103,
104,116,10,100,97,100,10,112,97,116,104,10,119,111,114,114,121,10,104,111,117,114,10,100,114,111,112,10,102,111,108,108,111,119,10,112,111,119,101,114,10,119,97,114,10,104,97,108,102,10,102,108,111,119,
10,104,101,97,118,101,110,10,97,99,116,10,99,104,97,110,99,101,10,102,97,99,116,10,108,101,97,115,116,10,116,105,114,101,100,10,99,104,105,108,100,114,101,110,10,110,101,97,114,10,113,117,105,116,101,
10,97,102,114,97,105,100,10,114,105,115,101,10,115,101,97,10,116,97,115,116,101,10,119,105,110,100,111,119,10,99,111,118,101,114,10,110,105,99,101,10,116,114,117,115,116,10,108,111,116,10,115,97,100,10,
99,111,111,108,10,102,111,114,99,101,10,112,101,97,99,101,10,114,101,116,117,114,110,10,98,108,105,110,100,10,101,97,115,121,10,114,101,97,100,121,10,114,111,108,108,10,114,111,115,101,10,100,114,105,
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

const char* PinComponent::brswordlist_txt = (const char*) resource_PinComponent_brswordlist_txt;
const int PinComponent::brswordlist_txtSize = 10493;

// JUCER_RESOURCE: burstHotWalletlogo_svg, 15546, "BurstHotWallet-logo.svg"
static const unsigned char resource_PinComponent_burstHotWalletlogo_svg[] = { 60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,110,99,111,100,105,110,103,61,34,85,84,70,45,56,
34,32,115,116,97,110,100,97,108,111,110,101,61,34,110,111,34,63,62,10,60,33,45,45,32,71,101,110,101,114,97,116,111,114,58,32,65,100,111,98,101,32,73,108,108,117,115,116,114,97,116,111,114,32,49,56,46,
49,46,49,44,32,83,86,71,32,69,120,112,111,114,116,32,80,108,117,103,45,73,110,32,46,32,83,86,71,32,86,101,114,115,105,111,110,58,32,54,46,48,48,32,66,117,105,108,100,32,48,41,32,32,45,45,62,10,10,60,115,
118,103,10,32,32,32,120,109,108,110,115,58,100,99,61,34,104,116,116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,101,108,101,109,101,110,116,115,47,49,46,49,47,34,10,32,32,32,120,109,108,110,
115,58,99,99,61,34,104,116,116,112,58,47,47,99,114,101,97,116,105,118,101,99,111,109,109,111,110,115,46,111,114,103,47,110,115,35,34,10,32,32,32,120,109,108,110,115,58,114,100,102,61,34,104,116,116,112,
58,47,47,119,119,119,46,119,51,46,111,114,103,47,49,57,57,57,47,48,50,47,50,50,45,114,100,102,45,115,121,110,116,97,120,45,110,115,35,34,10,32,32,32,120,109,108,110,115,58,115,118,103,61,34,104,116,116,
112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,10,32,32,32,120,109,108,110,115,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,
115,118,103,34,10,32,32,32,120,109,108,110,115,58,115,111,100,105,112,111,100,105,61,34,104,116,116,112,58,47,47,115,111,100,105,112,111,100,105,46,115,111,117,114,99,101,102,111,114,103,101,46,110,101,
116,47,68,84,68,47,115,111,100,105,112,111,100,105,45,48,46,100,116,100,34,10,32,32,32,120,109,108,110,115,58,105,110,107,115,99,97,112,101,61,34,104,116,116,112,58,47,47,119,119,119,46,105,110,107,115,
99,97,112,101,46,111,114,103,47,110,97,109,101,115,112,97,99,101,115,47,105,110,107,115,99,97,112,101,34,10,32,32,32,118,101,114,115,105,111,110,61,34,49,46,49,34,10,32,32,32,105,100,61,34,67,97,112,97,
95,49,34,10,32,32,32,120,61,34,48,112,120,34,10,32,32,32,121,61,34,48,112,120,34,10,32,32,32,118,105,101,119,66,111,120,61,34,48,32,48,32,53,57,57,46,57,57,57,57,55,32,51,53,57,46,57,57,57,57,57,34,10,
32,32,32,120,109,108,58,115,112,97,99,101,61,34,112,114,101,115,101,114,118,101,34,10,32,32,32,115,111,100,105,112,111,100,105,58,100,111,99,110,97,109,101,61,34,66,117,114,115,116,72,111,116,87,97,108,
108,101,116,45,108,111,103,111,46,115,118,103,34,10,32,32,32,105,110,107,115,99,97,112,101,58,118,101,114,115,105,111,110,61,34,48,46,57,50,46,49,32,114,49,53,51,55,49,34,10,32,32,32,119,105,100,116,104,
61,34,54,48,48,34,10,32,32,32,104,101,105,103,104,116,61,34,51,54,48,34,10,32,32,32,105,110,107,115,99,97,112,101,58,101,120,112,111,114,116,45,102,105,108,101,110,97,109,101,61,34,69,58,92,67,43,43,92,
66,117,114,115,116,92,66,117,114,115,116,72,111,116,87,97,108,108,101,116,92,66,117,114,115,116,72,111,116,87,97,108,108,101,116,46,103,105,116,92,116,114,117,110,107,92,83,111,117,114,99,101,92,66,117,
114,115,116,72,111,116,87,97,108,108,101,116,45,108,111,103,111,45,98,105,103,46,112,110,103,34,10,32,32,32,105,110,107,115,99,97,112,101,58,101,120,112,111,114,116,45,120,100,112,105,61,34,54,53,46,52,
53,52,53,52,52,34,10,32,32,32,105,110,107,115,99,97,112,101,58,101,120,112,111,114,116,45,121,100,112,105,61,34,54,53,46,52,53,52,53,52,52,34,62,60,109,101,116,97,100,97,116,97,10,32,32,32,32,32,105,100,
61,34,109,101,116,97,100,97,116,97,52,49,34,62,60,114,100,102,58,82,68,70,62,60,99,99,58,87,111,114,107,10,32,32,32,32,32,32,32,32,32,114,100,102,58,97,98,111,117,116,61,34,34,62,60,100,99,58,102,111,
114,109,97,116,62,105,109,97,103,101,47,115,118,103,43,120,109,108,60,47,100,99,58,102,111,114,109,97,116,62,60,100,99,58,116,121,112,101,10,32,32,32,32,32,32,32,32,32,32,32,114,100,102,58,114,101,115,
111,117,114,99,101,61,34,104,116,116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,100,99,109,105,116,121,112,101,47,83,116,105,108,108,73,109,97,103,101,34,32,47,62,60,100,99,58,116,105,116,
108,101,62,60,47,100,99,58,116,105,116,108,101,62,60,47,99,99,58,87,111,114,107,62,60,47,114,100,102,58,82,68,70,62,60,47,109,101,116,97,100,97,116,97,62,60,100,101,102,115,10,32,32,32,32,32,105,100,61,
34,100,101,102,115,51,57,34,32,47,62,60,115,111,100,105,112,111,100,105,58,110,97,109,101,100,118,105,101,119,10,32,32,32,32,32,112,97,103,101,99,111,108,111,114,61,34,35,102,102,102,102,102,102,34,10,
32,32,32,32,32,98,111,114,100,101,114,99,111,108,111,114,61,34,35,54,54,54,54,54,54,34,10,32,32,32,32,32,98,111,114,100,101,114,111,112,97,99,105,116,121,61,34,49,34,10,32,32,32,32,32,111,98,106,101,99,
116,116,111,108,101,114,97,110,99,101,61,34,49,48,34,10,32,32,32,32,32,103,114,105,100,116,111,108,101,114,97,110,99,101,61,34,49,48,34,10,32,32,32,32,32,103,117,105,100,101,116,111,108,101,114,97,110,
99,101,61,34,49,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,112,97,103,101,111,112,97,99,105,116,121,61,34,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,112,97,103,101,115,104,
97,100,111,119,61,34,50,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,119,105,100,116,104,61,34,49,49,49,49,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,
105,110,100,111,119,45,104,101,105,103,104,116,61,34,56,53,57,34,10,32,32,32,32,32,105,100,61,34,110,97,109,101,100,118,105,101,119,51,55,34,10,32,32,32,32,32,115,104,111,119,103,114,105,100,61,34,102,
97,108,115,101,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,122,111,111,109,61,34,48,46,55,53,50,50,57,57,49,49,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,120,61,34,50,57,50,46,
55,51,55,56,51,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,121,61,34,50,49,49,46,57,56,55,55,51,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,120,61,34,
49,54,56,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,121,61,34,53,57,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,109,97,120,105,
109,105,122,101,100,61,34,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,117,114,114,101,110,116,45,108,97,121,101,114,61,34,108,97,121,101,114,53,34,10,32,32,32,32,32,105,110,107,115,99,
97,112,101,58,112,97,103,101,99,104,101,99,107,101,114,98,111,97,114,100,61,34,102,97,108,115,101,34,10,32,32,32,32,32,115,104,111,119,98,111,114,100,101,114,61,34,116,114,117,101,34,10,32,32,32,32,32,
98,111,114,100,101,114,108,97,121,101,114,61,34,102,97,108,115,101,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,115,104,111,119,112,97,103,101,115,104,97,100,111,119,61,34,116,114,117,101,34,
32,47,62,60,103,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,103,114,111,117,112,109,111,100,101,61,34,108,97,121,101,114,34,10,32,32,32,32,32,105,100,61,34,108,97,121,101,114,49,34,10,32,32,32,
32,32,105,110,107,115,99,97,112,101,58,108,97,98,101,108,61,34,76,97,121,101,114,32,50,34,10,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,34,10,32,32,
32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,49,52,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,54,34,10,32,32,32,32,32,116,114,97,110,115,
102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,56,34,10,32,32,32,32,32,116,114,97,110,115,102,
111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,49,48,34,10,32,32,32,32,32,116,114,97,110,115,102,111,
114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,49,50,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,
109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,49,52,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,
61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,49,54,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,
34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,49,56,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,
116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,50,48,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,
114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,50,50,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,
97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,50,52,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,
110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,50,54,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,
115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,50,56,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,
108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,51,48,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,
97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,51,50,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,
116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,51,52,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,
101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,97,114,105,97,45,108,97,98,101,108,61,34,66,85,82,78,69,82,32,77,79,68,69,34,10,32,32,32,32,32,115,116,121,108,101,61,
34,102,111,110,116,45,115,116,121,108,101,58,110,111,114,109,97,108,59,102,111,110,116,45,118,97,114,105,97,110,116,58,110,111,114,109,97,108,59,102,111,110,116,45,119,101,105,103,104,116,58,110,111,114,
109,97,108,59,102,111,110,116,45,115,116,114,101,116,99,104,58,110,111,114,109,97,108,59,102,111,110,116,45,115,105,122,101,58,49,49,49,46,52,51,51,49,51,53,57,57,112,120,59,108,105,110,101,45,104,101,
105,103,104,116,58,49,46,50,53,59,102,111,110,116,45,102,97,109,105,108,121,58,39,66,101,98,97,115,32,78,101,117,101,39,59,45,105,110,107,115,99,97,112,101,45,102,111,110,116,45,115,112,101,99,105,102,
105,99,97,116,105,111,110,58,39,66,101,98,97,115,32,78,101,117,101,39,59,108,101,116,116,101,114,45,115,112,97,99,105,110,103,58,48,112,120,59,119,111,114,100,45,115,112,97,99,105,110,103,58,48,112,120,
59,102,105,108,108,58,35,48,48,48,48,48,48,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,58,110,111,110,101,59,115,116,114,111,107,101,45,119,105,100,116,104,58,50,46,
55,56,53,56,50,56,51,53,34,10,32,32,32,32,32,105,100,61,34,116,101,120,116,52,53,50,48,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,51,52,
48,41,34,32,47,62,60,103,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,103,114,111,117,112,109,111,100,101,61,34,108,97,121,101,114,34,10,32,32,32,32,32,105,100,61,34,108,97,121,101,114,50,34,10,
32,32,32,32,32,105,110,107,115,99,97,112,101,58,108,97,98,101,108,61,34,76,97,121,101,114,32,49,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,
45,51,52,48,41,34,10,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,34,32,47,62,60,103,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,103,114,111,117,
112,109,111,100,101,61,34,108,97,121,101,114,34,10,32,32,32,32,32,105,100,61,34,108,97,121,101,114,53,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,108,97,98,101,108,61,34,76,97,121,101,114,32,
52,34,10,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,
40,48,44,45,49,52,41,34,62,60,103,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,34,10,32,32,32,32,32,32,32,116,114,97,110,115,102,111,114,109,
61,34,109,97,116,114,105,120,40,48,46,57,54,55,56,54,48,55,52,44,48,44,48,44,48,46,57,54,55,56,54,48,55,52,44,53,53,51,46,49,54,56,51,54,44,45,49,48,48,55,46,53,53,50,52,41,34,10,32,32,32,32,32,32,32,
105,100,61,34,103,52,53,54,55,45,56,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,59,111,112,97,99,105,116,121,58,
49,59,102,105,108,108,58,35,57,56,101,97,49,97,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,102,105,108,108,45,114,117,108,101,58,110,111,110,122,101,114,111,59,115,116,114,111,107,101,58,
35,48,48,48,48,48,48,59,115,116,114,111,107,101,45,119,105,100,116,104,58,50,48,46,49,54,53,59,115,116,114,111,107,101,45,108,105,110,101,99,97,112,58,98,117,116,116,59,115,116,114,111,107,101,45,108,
105,110,101,106,111,105,110,58,109,105,116,101,114,59,115,116,114,111,107,101,45,109,105,116,101,114,108,105,109,105,116,58,52,59,115,116,114,111,107,101,45,100,97,115,104,97,114,114,97,121,58,110,111,
110,101,59,115,116,114,111,107,101,45,100,97,115,104,111,102,102,115,101,116,58,48,59,115,116,114,111,107,101,45,111,112,97,99,105,116,121,58,49,59,112,97,105,110,116,45,111,114,100,101,114,58,102,105,
108,108,32,109,97,114,107,101,114,115,32,115,116,114,111,107,101,34,10,32,32,32,32,32,32,32,100,61,34,77,32,49,49,55,46,56,57,57,51,55,44,53,49,46,51,54,51,54,48,49,32,72,32,53,55,55,46,57,49,55,55,49,
32,86,32,50,50,56,46,56,50,56,50,55,32,99,32,48,44,48,32,48,46,55,50,57,49,54,44,49,49,46,54,57,57,52,55,32,45,57,46,48,48,57,53,53,44,50,49,46,52,49,53,57,54,32,45,57,46,55,51,56,55,49,44,57,46,55,49,
54,52,57,32,45,50,57,46,55,49,50,51,52,44,49,48,46,50,48,56,49,53,32,45,50,57,46,55,49,50,51,52,44,49,48,46,50,48,56,49,53,32,108,32,45,49,46,49,55,56,44,45,56,52,46,52,55,54,56,32,99,32,45,48,46,48,55,
52,55,44,54,54,46,50,56,57,52,32,48,46,48,57,53,56,44,53,53,46,53,51,53,55,57,32,45,48,46,48,55,57,55,44,49,50,49,46,56,50,52,57,57,32,76,32,50,50,46,48,56,50,55,57,50,44,50,57,54,46,50,54,51,51,55,32,
50,50,46,48,56,50,51,48,56,44,57,54,46,56,53,50,56,50,56,32,90,34,10,32,32,32,32,32,32,32,105,100,61,34,114,101,99,116,52,54,50,51,45,57,45,52,45,57,45,52,34,10,32,32,32,32,32,32,32,105,110,107,115,99,
97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,10,32,32,32,32,32,32,32,115,111,100,105,112,111,100,105,58,110,111,100,101,116,121,112,101,115,61,34,99,
99,99,122,99,99,99,99,99,99,34,32,47,62,60,114,101,99,116,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,59,111,112,97,99,105,116,121,58,49,59,
102,105,108,108,58,35,48,50,48,50,48,50,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,102,105,108,108,45,114,117,108,101,58,110,111,110,122,101,114,111,59,115,116,114,111,107,101,58,110,111,
110,101,59,115,116,114,111,107,101,45,119,105,100,116,104,58,50,56,46,56,52,55,55,48,53,56,52,59,115,116,114,111,107,101,45,108,105,110,101,99,97,112,58,98,117,116,116,59,115,116,114,111,107,101,45,108,
105,110,101,106,111,105,110,58,109,105,116,101,114,59,115,116,114,111,107,101,45,109,105,116,101,114,108,105,109,105,116,58,52,59,115,116,114,111,107,101,45,100,97,115,104,97,114,114,97,121,58,110,111,
110,101,59,115,116,114,111,107,101,45,100,97,115,104,111,102,102,115,101,116,58,48,59,115,116,114,111,107,101,45,111,112,97,99,105,116,121,58,49,59,112,97,105,110,116,45,111,114,100,101,114,58,109,97,
114,107,101,114,115,32,115,116,114,111,107,101,32,102,105,108,108,34,10,32,32,32,32,32,32,32,105,100,61,34,114,101,99,116,52,54,50,51,45,57,45,52,34,10,32,32,32,32,32,32,32,119,105,100,116,104,61,34,52,
57,57,46,53,56,53,55,50,34,10,32,32,32,32,32,32,32,104,101,105,103,104,116,61,34,50,53,56,46,56,48,49,48,51,34,10,32,32,32,32,32,32,32,120,61,34,49,50,46,48,48,48,48,51,49,34,10,32,32,32,32,32,32,32,121,
61,34,57,50,46,55,51,53,50,57,56,34,10,32,32,32,32,32,32,32,114,120,61,34,52,54,46,51,51,52,56,51,57,34,10,32,32,32,32,32,32,32,114,121,61,34,52,54,46,51,51,52,56,51,57,34,32,47,62,60,103,10,32,32,32,
32,32,32,32,97,114,105,97,45,108,97,98,101,108,61,34,72,79,84,87,65,76,76,69,84,34,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,111,110,116,45,115,116,121,108,101,58,110,111,114,109,97,108,59,
102,111,110,116,45,118,97,114,105,97,110,116,58,110,111,114,109,97,108,59,102,111,110,116,45,119,101,105,103,104,116,58,110,111,114,109,97,108,59,102,111,110,116,45,115,116,114,101,116,99,104,58,110,111,
114,109,97,108,59,102,111,110,116,45,115,105,122,101,58,50,54,57,46,55,57,56,48,57,53,55,112,120,59,108,105,110,101,45,104,101,105,103,104,116,58,49,46,50,53,59,102,111,110,116,45,102,97,109,105,108,121,
58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,45,105,110,107,115,99,97,112,101,45,102,111,110,116,45,115,112,101,99,105,102,105,99,97,116,105,111,110,58,39,79,115,116,114,105,99,104,32,83,97,
110,115,39,59,108,101,116,116,101,114,45,115,112,97,99,105,110,103,58,48,112,120,59,119,111,114,100,45,115,112,97,99,105,110,103,58,48,112,120,59,100,105,115,112,108,97,121,58,105,110,108,105,110,101,
59,102,105,108,108,58,35,102,102,102,102,102,102,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,58,110,111,110,101,59,115,116,114,111,107,101,45,119,105,100,116,104,58,
54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,105,100,61,34,116,101,120,116,52,54,50,55,45,48,45,57,34,10,32,32,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,109,97,116,114,105,120,
40,48,46,52,55,54,54,57,57,50,44,48,44,48,44,48,46,52,55,54,54,57,57,49,55,44,49,53,46,50,57,54,56,55,44,53,54,46,53,49,48,53,56,49,41,34,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,
32,56,50,46,56,51,50,51,57,44,50,50,49,46,51,53,54,48,52,32,118,32,45,54,55,46,57,56,57,49,50,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,54,57,44,45,57,46,55,49,50,55,51,32,45,57,46,
55,49,50,55,51,49,44,45,57,46,55,49,50,55,51,32,104,32,45,55,46,53,53,52,51,52,55,32,99,32,45,53,46,51,57,53,57,54,50,44,48,32,45,57,46,55,49,50,55,51,49,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,
51,49,44,57,46,55,49,50,55,51,32,118,32,49,54,50,46,52,49,56,52,54,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,54,57,44,57,46,55,49,50,55,51,32,57,46,55,49,50,55,51,49,44,57,46,55,49,50,55,
51,32,104,32,55,46,53,53,52,51,52,55,32,99,32,53,46,51,57,53,57,54,50,44,48,32,57,46,55,49,50,55,51,49,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,49,44,45,57,46,55,49,50,55,51,32,118,32,45,54,
55,46,55,49,57,51,51,32,104,32,50,57,46,57,52,55,53,57,32,118,32,54,55,46,55,49,57,51,51,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,55,44,57,46,55,49,50,55,51,32,57,46,55,49,50,55,51,44,
57,46,55,49,50,55,51,32,104,32,55,46,53,53,52,51,53,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,86,32,49,
53,51,46,51,54,54,57,50,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,104,32,45,55,46,53,53,52,51,
53,32,99,32,45,53,46,51,57,53,57,54,44,48,32,45,57,46,55,49,50,55,51,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,51,44,57,46,55,49,50,55,51,32,118,32,54,55,46,57,56,57,49,50,32,122,34,10,32,32,32,
32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,
32,32,105,100,61,34,112,97,116,104,52,53,50,52,45,55,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,
32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,49,54,50,46,50,57,54,51,54,44,50,55,50,46,54,49,55,54,56,32,99,32,48,44,50,49,46,51,49,52,48,53,32,53,46,57,51,53,53,54,44,51,
51,46,55,50,52,55,54,32,49,52,46,50,57,57,51,44,52,50,46,48,56,56,53,32,56,46,57,48,51,51,52,44,56,46,54,51,51,53,52,32,50,48,46,50,51,52,56,54,44,49,48,46,55,57,49,57,51,32,50,57,46,57,52,55,53,57,44,
49,48,46,55,57,49,57,51,32,57,46,57,56,50,53,51,44,48,32,50,49,46,51,49,52,48,53,44,45,50,46,49,53,56,51,57,32,51,48,46,50,49,55,51,56,44,45,49,48,46,55,57,49,57,51,32,56,46,51,54,51,55,53,44,45,56,46,
51,54,51,55,52,32,49,52,46,48,50,57,53,49,44,45,50,48,46,55,55,52,52,53,32,49,52,46,48,50,57,53,49,44,45,52,50,46,48,56,56,53,32,118,32,45,55,54,46,51,53,50,56,54,32,99,32,48,44,45,51,52,46,50,54,52,51,
54,32,45,49,52,46,53,54,57,49,44,45,53,50,46,54,49,48,54,51,32,45,52,52,46,50,52,54,56,57,44,45,53,50,46,54,49,48,54,51,32,45,50,57,46,52,48,55,57,57,44,48,32,45,52,52,46,50,52,54,56,57,44,49,56,46,54,
49,54,48,55,32,45,52,52,46,50,52,54,56,57,44,53,50,46,54,49,48,54,51,32,122,32,109,32,50,54,46,57,55,57,56,49,44,45,55,54,46,51,53,50,56,54,32,99,32,48,44,45,49,55,46,53,51,54,56,56,32,53,46,51,57,53,
57,54,44,45,50,53,46,57,48,48,54,50,32,49,55,46,50,54,55,48,56,44,45,50,53,46,57,48,48,54,50,32,49,49,46,54,48,49,51,50,44,48,32,49,55,46,50,54,55,48,56,44,55,46,56,50,52,49,53,32,49,55,46,50,54,55,48,
56,44,50,53,46,57,48,48,54,50,32,118,32,55,54,46,51,53,50,56,54,32,99,32,48,44,49,56,46,51,52,54,50,55,32,45,53,46,57,51,53,53,54,44,50,54,46,49,55,48,52,50,32,45,49,55,46,50,54,55,48,56,44,50,54,46,49,
55,48,52,50,32,45,49,49,46,54,48,49,51,50,44,48,32,45,49,55,46,50,54,55,48,56,44,45,56,46,51,54,51,55,52,32,45,49,55,46,50,54,55,48,56,44,45,50,54,46,49,55,48,52,50,32,122,34,10,32,32,32,32,32,32,32,32,
32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,32,32,105,100,61,
34,112,97,116,104,52,53,50,54,45,49,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,47,62,60,112,
97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,50,55,48,46,56,50,50,54,52,44,49,54,48,46,54,53,49,52,55,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,55,44,57,46,55,49,50,55,51,32,
57,46,55,49,50,55,52,44,57,46,55,49,50,55,51,32,104,32,50,49,46,56,53,51,54,52,32,118,32,49,52,53,46,49,53,49,51,56,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,55,44,57,46,55,49,50,55,51,
32,57,46,55,49,50,55,51,44,57,46,55,49,50,55,51,32,104,32,55,46,50,56,52,53,53,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,44,45,57,46,
55,49,50,55,51,32,86,32,49,55,48,46,51,54,52,50,32,104,32,50,50,46,49,50,51,52,53,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,44,45,57,
46,55,49,50,55,51,32,118,32,45,55,46,53,53,52,51,53,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,
104,32,45,55,48,46,54,56,55,49,32,99,32,45,53,46,51,57,53,57,55,44,48,32,45,57,46,55,49,50,55,52,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,52,44,57,46,55,49,50,55,51,32,122,34,10,32,32,32,32,32,
32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,32,32,
105,100,61,34,112,97,116,104,52,53,50,56,45,51,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,47,
62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,52,53,55,46,48,56,56,55,50,44,49,53,49,46,52,55,56,51,52,32,99,32,45,48,46,56,48,57,52,44,45,52,46,51,49,54,55,55,32,45,53,46,49,50,
54,49,54,44,45,55,46,56,50,52,49,53,32,45,57,46,52,52,50,57,51,44,45,55,46,56,50,52,49,53,32,104,32,45,53,46,57,51,53,53,54,32,99,32,45,52,46,51,49,54,55,55,44,48,32,45,56,46,54,51,51,53,52,44,51,46,53,
48,55,51,56,32,45,57,46,52,52,50,57,52,44,55,46,56,50,52,49,53,32,108,32,45,49,52,46,48,50,57,53,44,56,50,46,48,49,56,54,50,32,45,49,50,46,52,49,48,55,49,44,45,56,49,46,55,52,56,56,51,32,99,32,45,48,46,
56,48,57,51,57,44,45,52,46,53,56,54,53,54,32,45,53,46,49,50,54,49,54,44,45,56,46,48,57,51,57,52,32,45,57,46,55,49,50,55,51,44,45,56,46,48,57,51,57,52,32,104,32,45,55,46,56,50,52,49,53,32,99,32,45,54,46,
50,48,53,51,53,44,48,32,45,49,48,46,50,53,50,51,50,44,53,46,49,50,54,49,55,32,45,57,46,52,52,50,57,51,44,49,49,46,48,54,49,55,50,32,108,32,50,54,46,52,52,48,50,49,44,49,54,50,46,54,56,56,50,54,32,99,32,
48,46,56,48,57,52,44,52,46,51,49,54,55,54,32,52,46,56,53,54,51,55,44,56,46,48,57,51,57,52,32,57,46,52,52,50,57,52,44,56,46,48,57,51,57,52,32,104,32,53,46,57,51,53,53,54,32,99,32,52,46,51,49,54,55,55,44,
48,32,56,46,54,51,51,53,52,44,45,51,46,53,48,55,51,56,32,57,46,52,52,50,57,51,44,45,55,46,56,50,52,49,53,32,108,32,49,52,46,53,54,57,49,44,45,56,54,46,48,54,53,53,57,32,49,52,46,50,57,57,51,44,56,54,46,
48,54,53,53,57,32,99,32,48,46,56,48,57,51,57,44,52,46,51,49,54,55,55,32,53,46,49,50,54,49,54,44,55,46,56,50,52,49,53,32,57,46,52,52,50,57,51,44,55,46,56,50,52,49,53,32,104,32,54,46,50,48,53,51,54,32,99,
32,52,46,53,56,54,53,54,44,48,32,56,46,57,48,51,51,51,44,45,51,46,55,55,55,49,56,32,57,46,55,49,50,55,51,44,45,56,46,48,57,51,57,52,32,108,32,50,53,46,57,48,48,54,49,44,45,49,54,50,46,54,56,56,50,54,32,
99,32,48,46,56,48,57,52,44,45,53,46,57,51,53,53,53,32,45,51,46,55,55,55,49,55,44,45,49,49,46,48,54,49,55,50,32,45,57,46,55,49,50,55,51,44,45,49,49,46,48,54,49,55,50,32,104,32,45,55,46,56,50,52,49,52,32,
99,32,45,52,46,53,56,54,53,55,44,48,32,45,57,46,49,55,51,49,52,44,51,46,53,48,55,51,56,32,45,57,46,55,49,50,55,51,44,56,46,48,57,51,57,52,32,108,32,45,49,50,46,49,52,48,57,50,44,56,49,46,50,48,57,50,51,
32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,
32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,51,48,45,50,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,
114,101,61,34,48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,53,55,54,46,48,57,48,55,53,44,51,49,55,46,57,52,51,55,54,32,99,32,49,46,48,55,57,49,57,44,52,46,48,52,54,57,
55,32,53,46,51,57,53,57,54,44,55,46,53,53,52,51,53,32,57,46,52,52,50,57,51,44,55,46,53,53,52,51,53,32,104,32,55,46,56,50,52,49,53,32,99,32,54,46,52,55,53,49,53,44,48,32,49,48,46,55,57,49,57,50,44,45,53,
46,54,54,53,55,54,32,57,46,52,52,50,57,51,44,45,49,49,46,56,55,49,49,50,32,76,32,53,54,53,46,53,54,56,54,51,44,49,53,49,46,50,48,56,53,52,32,99,32,45,48,46,56,48,57,52,44,45,52,46,48,52,54,57,55,32,45,
53,46,51,57,53,57,55,44,45,55,46,53,53,52,51,53,32,45,57,46,52,52,50,57,52,44,45,55,46,53,53,52,51,53,32,104,32,45,53,46,57,51,53,53,54,32,99,32,45,52,46,48,52,54,57,55,44,48,32,45,56,46,51,54,51,55,52,
44,51,46,53,48,55,51,56,32,45,57,46,52,52,50,57,51,44,55,46,53,53,52,51,53,32,108,32,45,50,52,46,53,53,49,54,51,44,49,48,53,46,52,57,49,48,53,32,45,49,50,46,57,53,48,51,44,53,55,46,49,57,55,50,32,99,32,
45,49,46,51,52,57,44,54,46,50,48,53,51,54,32,50,46,57,54,55,55,55,44,49,49,46,54,48,49,51,50,32,57,46,52,52,50,57,51,44,49,49,46,54,48,49,51,50,32,104,32,55,46,56,50,52,49,52,32,99,32,52,46,48,52,54,57,
55,44,48,32,56,46,51,54,51,55,52,44,45,51,46,53,48,55,51,56,32,57,46,52,52,50,57,52,44,45,55,46,53,53,52,51,53,32,108,32,57,46,52,52,50,57,51,44,45,52,50,46,48,56,56,53,32,104,32,50,55,46,53,49,57,52,
49,32,122,32,77,32,53,53,51,46,49,53,55,57,49,44,50,48,53,46,57,55,55,53,53,32,99,32,53,46,49,50,54,49,55,44,50,50,46,57,51,50,56,52,32,52,46,53,56,54,53,55,44,51,48,46,50,49,55,51,57,32,55,46,53,53,52,
51,53,44,52,51,46,49,54,55,55,32,104,32,45,49,53,46,49,48,56,54,57,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,
101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,51,50,45,53,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,
58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,54,57,54,46,56,48,48,49,50,44,51,48,56,46,
53,48,48,56,51,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,52,44,45,57,46,55,49,50,55,51,32,72,32,54,52,54,46,56,56,55,52,55,32,
86,32,49,53,51,46,51,54,54,57,50,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,52,52,50,57,52,44,45,57,46,55,49,50,55,51,32,104,32,45,55,46,56,
50,52,49,52,32,99,32,45,53,46,51,57,53,57,54,44,48,32,45,57,46,55,49,50,55,51,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,51,44,57,46,55,49,50,55,51,32,118,32,49,54,50,46,52,49,56,52,54,32,99,32,48,
44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,55,44,57,46,55,49,50,55,51,32,57,46,55,49,50,55,51,44,57,46,55,49,50,55,51,32,104,32,53,55,46,52,54,54,57,57,32,99,32,53,46,51,57,53,57,55,44,48,32,57,46,55,
49,50,55,52,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,52,44,45,57,46,55,49,50,55,51,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,
59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,51,52,45,50,34,10,32,32,32,32,32,32,32,32,32,105,
110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,55,56,55,46,52,
51,53,52,51,44,51,48,56,46,53,48,48,56,51,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,72,32,55,
51,55,46,53,50,50,55,56,32,86,32,49,53,51,46,51,54,54,57,50,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,52,52,50,57,51,44,45,57,46,55,49,50,
55,51,32,104,32,45,55,46,56,50,52,49,52,32,99,32,45,53,46,51,57,53,57,55,44,48,32,45,57,46,55,49,50,55,52,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,52,44,57,46,55,49,50,55,51,32,118,32,49,54,50,
46,52,49,56,52,54,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,55,44,57,46,55,49,50,55,51,32,57,46,55,49,50,55,52,44,57,46,55,49,50,55,51,32,104,32,53,55,46,52,54,54,57,57,32,99,32,53,46,51,
57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,
58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,51,54,45,57,34,10,32,
32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,
61,34,109,32,56,49,50,46,53,48,57,55,53,44,49,52,51,46,54,53,52,49,57,32,99,32,45,53,46,51,57,53,57,54,44,48,32,45,57,46,55,49,50,55,51,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,51,44,57,46,55,49,
50,55,51,32,118,32,49,54,50,46,52,49,56,52,54,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,55,44,57,46,55,49,50,55,51,32,57,46,55,49,50,55,51,44,57,46,55,49,50,55,51,32,104,32,53,56,46,50,
55,54,51,57,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,118,32,45,55,46,50,56,52,53,53,32,99,32,48,44,45,
53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,104,32,45,52,49,46,50,55,57,49,49,32,118,32,45,53,48,46,57,57,49,56,
52,32,104,32,51,51,46,57,57,52,53,54,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,52,32,118,32,45,55,46,50,56,
52,53,52,32,99,32,48,44,45,53,46,51,57,53,57,55,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,52,32,45,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,52,32,72,32,56,50,57,46,53,48,55,48,51,32,86,32,
49,55,48,46,51,54,52,50,32,104,32,52,49,46,50,55,57,49,49,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,118,
32,45,55,46,50,56,52,53,53,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,122,34,10,32,32,32,32,32,
32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,32,32,
105,100,61,34,112,97,116,104,52,53,51,56,45,52,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,47,
62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,56,57,55,46,51,54,53,52,57,44,49,54,48,46,54,53,49,52,55,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,55,44,57,46,55,49,
50,55,51,32,57,46,55,49,50,55,51,44,57,46,55,49,50,55,51,32,104,32,50,49,46,56,53,51,54,53,32,118,32,49,52,53,46,49,53,49,51,56,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,55,44,57,46,55,
49,50,55,51,32,57,46,55,49,50,55,51,44,57,46,55,49,50,55,51,32,104,32,55,46,50,56,52,53,53,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,
44,45,57,46,55,49,50,55,51,32,86,32,49,55,48,46,51,54,52,50,32,104,32,50,50,46,49,50,51,52,52,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,
51,44,45,57,46,55,49,50,55,51,32,118,32,45,55,46,53,53,52,51,53,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,51,44,45,57,46,55,49,
50,55,51,32,104,32,45,55,48,46,54,56,55,49,32,99,32,45,53,46,51,57,53,57,54,44,48,32,45,57,46,55,49,50,55,51,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,51,44,57,46,55,49,50,55,51,32,122,34,10,32,
32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,
32,32,32,32,105,100,61,34,112,97,116,104,52,53,52,48,45,48,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,
48,34,32,47,62,60,47,103,62,60,103,10,32,32,32,32,32,32,32,97,114,105,97,45,108,97,98,101,108,61,34,67,65,83,72,34,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,111,110,116,45,115,116,121,108,
101,58,110,111,114,109,97,108,59,102,111,110,116,45,118,97,114,105,97,110,116,58,110,111,114,109,97,108,59,102,111,110,116,45,119,101,105,103,104,116,58,110,111,114,109,97,108,59,102,111,110,116,45,115,
116,114,101,116,99,104,58,110,111,114,109,97,108,59,102,111,110,116,45,115,105,122,101,58,50,54,57,46,55,57,56,48,57,53,55,112,120,59,108,105,110,101,45,104,101,105,103,104,116,58,49,46,50,53,59,102,111,
110,116,45,102,97,109,105,108,121,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,45,105,110,107,115,99,97,112,101,45,102,111,110,116,45,115,112,101,99,105,102,105,99,97,116,105,111,110,58,39,79,
115,116,114,105,99,104,32,83,97,110,115,39,59,108,101,116,116,101,114,45,115,112,97,99,105,110,103,58,48,112,120,59,119,111,114,100,45,115,112,97,99,105,110,103,58,48,112,120,59,100,105,115,112,108,97,
121,58,105,110,108,105,110,101,59,102,105,108,108,58,35,57,56,101,97,49,97,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,58,110,111,110,101,59,115,116,114,111,107,101,
45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,105,100,61,34,116,101,120,116,52,54,50,55,45,52,45,50,45,56,34,10,32,32,32,32,32,32,32,116,114,97,110,115,102,111,114,
109,61,34,109,97,116,114,105,120,40,48,46,52,55,54,54,57,57,50,44,48,44,48,44,48,46,52,55,54,54,57,57,49,55,44,45,50,49,49,46,49,55,53,51,51,44,49,54,56,46,55,51,55,55,53,41,34,62,60,112,97,116,104,10,
32,32,32,32,32,32,32,32,32,100,61,34,109,32,49,48,52,56,46,54,54,53,53,44,50,55,49,46,55,49,53,52,51,32,99,32,48,44,50,49,46,51,49,52,48,53,32,53,46,57,51,53,54,44,51,51,46,55,50,52,55,54,32,49,52,46,
50,57,57,51,44,52,50,46,48,56,56,53,32,56,46,57,48,51,51,44,56,46,54,51,51,53,52,32,49,57,46,57,54,53,49,44,49,48,46,55,57,49,57,51,32,51,48,46,50,49,55,52,44,49,48,46,55,57,49,57,51,32,57,46,55,49,50,
55,44,48,32,50,49,46,48,52,52,50,44,45,50,46,49,53,56,51,57,32,50,57,46,57,52,55,54,44,45,49,48,46,55,57,49,57,51,32,56,46,51,54,51,55,44,45,56,46,51,54,51,55,52,32,49,52,46,48,50,57,53,44,45,50,48,46,
55,55,52,52,53,32,49,52,46,48,50,57,53,44,45,52,50,46,48,56,56,53,32,118,32,45,51,46,55,55,55,49,55,32,99,32,48,44,45,53,46,51,57,53,57,55,32,45,52,46,51,49,54,56,44,45,57,46,55,49,50,55,52,32,45,57,46,
52,52,51,44,45,57,46,55,49,50,55,52,32,104,32,45,55,46,56,50,52,49,32,99,32,45,53,46,51,57,54,44,48,32,45,57,46,55,49,50,55,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,44,57,46,55,49,50,55,52,32,118,
32,51,46,55,55,55,49,55,32,99,32,48,44,57,46,55,49,50,55,51,32,45,49,46,51,52,57,44,49,54,46,57,57,55,50,56,32,45,52,46,53,56,54,54,44,50,49,46,51,49,52,48,53,32,45,50,46,52,50,56,50,44,50,46,54,57,55,
57,56,32,45,55,46,50,56,52,53,44,52,46,56,53,54,51,54,32,45,49,50,46,52,49,48,55,44,52,46,56,53,54,51,54,32,45,49,49,46,54,48,49,51,44,48,32,45,49,55,46,50,54,55,49,44,45,56,46,48,57,51,57,52,32,45,49,
55,46,50,54,55,49,44,45,50,54,46,49,55,48,52,49,32,118,32,45,55,54,46,51,53,50,56,54,32,99,32,48,44,45,49,56,46,48,55,54,52,55,32,53,46,57,51,53,54,44,45,50,53,46,57,48,48,54,50,32,49,55,46,50,54,55,49,
44,45,50,53,46,57,48,48,54,50,32,49,49,46,48,54,49,55,44,48,32,49,54,46,57,57,55,51,44,55,46,56,50,52,49,53,32,49,54,46,57,57,55,51,44,50,53,46,57,48,48,54,50,32,118,32,51,46,55,55,55,49,55,32,99,32,48,
44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,44,57,46,55,49,50,55,51,32,57,46,55,49,50,55,44,57,46,55,49,50,55,51,32,104,32,55,46,56,50,52,49,32,99,32,53,46,49,50,54,50,44,48,32,57,46,52,52,51,44,45,52,
46,51,49,54,55,55,32,57,46,52,52,51,44,45,57,46,55,49,50,55,51,32,118,32,45,51,46,55,55,55,49,55,32,99,32,48,44,45,50,48,46,53,48,52,54,54,32,45,53,46,54,54,53,56,44,45,51,51,46,57,57,52,53,54,32,45,49,
52,46,50,57,57,51,44,45,52,50,46,48,56,56,53,49,32,45,56,46,57,48,51,52,44,45,56,46,48,57,51,57,52,32,45,49,57,46,54,57,53,51,44,45,49,48,46,53,50,50,49,50,32,45,50,57,46,54,55,55,56,44,45,49,48,46,53,
50,50,49,50,32,45,49,48,46,50,53,50,51,44,48,32,45,50,49,46,48,52,52,51,44,50,46,52,50,56,49,56,32,45,50,57,46,57,52,55,54,44,49,48,46,53,50,50,49,50,32,45,56,46,54,51,51,53,44,56,46,48,57,51,57,53,32,
45,49,52,46,53,54,57,49,44,50,49,46,53,56,51,56,53,32,45,49,52,46,53,54,57,49,44,52,50,46,48,56,56,53,49,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,57,56,101,
97,49,97,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,
116,104,52,53,49,53,45,50,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,47,62,60,112,97,116,104,
10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,49,50,50,57,46,48,51,52,44,51,49,55,46,48,52,49,53,49,32,99,32,49,46,48,55,57,50,44,52,46,48,52,54,57,55,32,53,46,51,57,53,57,44,55,46,53,53,52,51,53,32,
57,46,52,52,50,57,44,55,46,53,53,52,51,53,32,104,32,55,46,56,50,52,49,32,99,32,54,46,52,55,53,50,44,48,32,49,48,46,55,57,50,44,45,53,46,54,54,53,55,54,32,57,46,52,52,51,44,45,49,49,46,56,55,49,49,50,32,
108,32,45,51,55,46,50,51,50,50,44,45,49,54,50,46,52,49,56,52,53,32,99,32,45,48,46,56,48,57,52,44,45,52,46,48,52,54,57,56,32,45,53,46,51,57,53,57,44,45,55,46,53,53,52,51,53,32,45,57,46,52,52,50,57,44,45,
55,46,53,53,52,51,53,32,104,32,45,53,46,57,51,53,54,32,99,32,45,52,46,48,52,54,57,44,48,32,45,56,46,51,54,51,55,44,51,46,53,48,55,51,55,32,45,57,46,52,52,50,57,44,55,46,53,53,52,51,53,32,108,32,45,50,
52,46,53,53,49,54,44,49,48,53,46,52,57,49,48,53,32,45,49,50,46,57,53,48,51,44,53,55,46,49,57,55,50,32,99,32,45,49,46,51,52,57,44,54,46,50,48,53,51,53,32,50,46,57,54,55,56,44,49,49,46,54,48,49,51,50,32,
57,46,52,52,50,57,44,49,49,46,54,48,49,51,50,32,104,32,55,46,56,50,52,50,32,99,32,52,46,48,52,54,57,44,48,32,56,46,51,54,51,55,44,45,51,46,53,48,55,51,56,32,57,46,52,52,50,57,44,45,55,46,53,53,52,51,53,
32,108,32,57,46,52,52,50,57,44,45,52,50,46,48,56,56,53,32,104,32,50,55,46,53,49,57,52,32,122,32,77,32,49,50,48,54,46,49,48,49,49,44,50,48,53,46,48,55,53,51,32,99,32,53,46,49,50,54,50,44,50,50,46,57,51,
50,56,52,32,52,46,53,56,54,54,44,51,48,46,50,49,55,51,57,32,55,46,53,53,52,52,44,52,51,46,49,54,55,54,57,32,104,32,45,49,53,46,49,48,56,55,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,
34,102,105,108,108,58,35,57,56,101,97,49,97,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,
32,32,32,32,105,100,61,34,112,97,116,104,52,53,49,55,45,51,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,
48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,49,50,54,56,46,52,49,54,49,44,50,55,49,46,55,49,53,52,51,32,99,32,48,44,51,53,46,51,52,51,53,53,32,49,52,46,56,51,56,56,
44,53,50,46,54,49,48,54,51,32,52,52,46,53,49,54,54,44,53,50,46,54,49,48,54,51,32,50,56,46,53,57,56,54,44,48,32,52,52,46,53,49,54,55,44,45,49,54,46,49,56,55,56,57,32,52,52,46,53,49,54,55,44,45,52,54,46,
52,48,53,50,55,32,48,44,45,50,54,46,49,55,48,52,50,32,45,49,56,46,48,55,54,52,44,45,51,57,46,57,51,48,49,50,32,45,51,53,46,56,56,51,49,44,45,53,51,46,54,56,57,56,51,32,104,32,48,46,50,54,57,56,32,99,32,
45,49,51,46,50,50,48,49,44,45,49,48,46,50,53,50,51,50,32,45,50,54,46,52,52,48,50,44,45,50,48,46,55,55,52,52,53,32,45,50,54,46,52,52,48,50,44,45,51,52,46,53,51,52,49,53,32,48,44,45,49,52,46,48,50,57,53,
32,54,46,50,48,53,51,44,45,50,48,46,50,51,52,56,54,32,49,55,46,53,51,54,56,44,45,50,48,46,50,51,52,56,54,32,49,49,46,56,55,49,50,44,48,32,49,55,46,53,51,54,57,44,56,46,48,57,51,57,52,32,49,55,46,53,51,
54,57,44,50,53,46,57,48,48,54,50,32,118,32,51,46,55,55,55,49,55,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,56,44,57,46,55,49,50,55,51,32,57,46,55,49,50,55,44,57,46,55,49,50,55,51,32,104,32,
55,46,53,53,52,52,32,99,32,53,46,51,57,54,44,48,32,57,46,55,49,50,55,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,44,45,57,46,55,49,50,55,51,32,118,32,45,51,46,55,55,55,49,55,32,99,32,48,44,45,51,52,
46,50,54,52,51,54,32,45,49,53,46,51,55,56,53,44,45,53,50,46,56,56,48,52,51,32,45,52,52,46,53,49,54,55,44,45,53,50,46,56,56,48,52,51,32,45,50,56,46,53,57,56,54,44,48,32,45,52,52,46,53,49,54,54,44,49,55,
46,53,51,54,56,56,32,45,52,52,46,53,49,54,54,44,52,56,46,48,50,52,48,54,32,48,44,50,54,46,55,49,48,48,49,32,49,56,46,54,49,54,44,52,49,46,50,55,57,49,49,32,51,54,46,52,50,50,55,44,53,53,46,51,48,56,54,
49,32,118,32,45,48,46,50,54,57,56,32,99,32,49,51,46,50,50,48,49,44,49,48,46,50,53,50,51,51,32,50,53,46,54,51,48,56,44,50,48,46,50,51,52,56,54,32,50,53,46,54,51,48,56,44,51,50,46,57,49,53,51,55,32,48,44,
49,52,46,50,57,57,51,32,45,54,46,50,48,53,51,44,49,57,46,49,53,53,54,55,32,45,49,55,46,53,51,54,57,44,49,57,46,49,53,53,54,55,32,45,51,46,55,55,55,49,44,48,32,45,56,46,51,54,51,55,44,45,48,46,53,51,57,
54,32,45,49,49,46,51,51,49,53,44,45,51,46,53,48,55,51,56,32,45,51,46,55,55,55,50,44,45,51,46,50,51,55,53,56,32,45,54,46,50,48,53,51,44,45,57,46,52,52,50,57,51,32,45,54,46,50,48,53,51,44,45,50,50,46,51,
57,51,50,52,32,118,32,45,51,46,53,48,55,51,56,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,53,56,54,54,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,56,44,45,57,46,55,49,50,55,51,32,104,32,45,
55,46,53,53,52,51,32,99,32,45,53,46,51,57,54,44,48,32,45,57,46,55,49,50,55,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,44,57,46,55,49,50,55,51,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,
101,61,34,102,105,108,108,58,35,57,56,101,97,49,97,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,
32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,49,57,45,55,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,
101,61,34,48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,49,52,48,50,46,56,57,51,53,44,50,50,48,46,52,53,51,55,57,32,118,32,45,54,55,46,57,56,57,49,50,32,99,32,48,44,45,
53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,44,45,57,46,55,49,50,55,51,32,104,32,45,55,46,53,53,52,51,32,99,32,45,53,46,51,57,54,44,48,32,45,57,46,55,
49,50,56,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,56,44,57,46,55,49,50,55,51,32,118,32,49,54,50,46,52,49,56,52,53,32,99,32,48,44,53,46,51,57,53,57,55,32,52,46,51,49,54,56,44,57,46,55,49,50,55,52,32,
57,46,55,49,50,56,44,57,46,55,49,50,55,52,32,104,32,55,46,53,53,52,51,32,99,32,53,46,51,57,54,44,48,32,57,46,55,49,50,55,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,44,45,57,46,55,49,50,55,52,32,86,
32,50,52,55,46,49,54,51,56,32,104,32,50,57,46,57,52,55,54,32,118,32,54,55,46,55,49,57,51,50,32,99,32,48,44,53,46,51,57,53,57,55,32,52,46,51,49,54,56,44,57,46,55,49,50,55,52,32,57,46,55,49,50,55,44,57,
46,55,49,50,55,52,32,104,32,55,46,53,53,52,52,32,99,32,53,46,51,57,54,44,48,32,57,46,55,49,50,55,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,44,45,57,46,55,49,50,55,52,32,86,32,49,53,50,46,52,54,52,
54,55,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,44,45,57,46,55,49,50,55,51,32,104,32,45,55,46,53,53,52,52,32,99,32,45,53,46,51,57,
53,57,44,48,32,45,57,46,55,49,50,55,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,44,57,46,55,49,50,55,51,32,118,32,54,55,46,57,56,57,49,50,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,
61,34,102,105,108,108,58,35,57,56,101,97,49,97,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,
32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,50,49,45,52,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,
34,48,34,32,47,62,60,47,103,62,60,103,10,32,32,32,32,32,32,32,97,114,105,97,45,108,97,98,101,108,61,34,46,34,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,111,110,116,45,115,116,121,108,101,58,
110,111,114,109,97,108,59,102,111,110,116,45,118,97,114,105,97,110,116,58,110,111,114,109,97,108,59,102,111,110,116,45,119,101,105,103,104,116,58,110,111,114,109,97,108,59,102,111,110,116,45,115,116,114,
101,116,99,104,58,110,111,114,109,97,108,59,102,111,110,116,45,115,105,122,101,58,50,54,57,46,55,57,56,48,57,53,55,112,120,59,108,105,110,101,45,104,101,105,103,104,116,58,49,46,50,53,59,102,111,110,116,
45,102,97,109,105,108,121,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,45,105,110,107,115,99,97,112,101,45,102,111,110,116,45,115,112,101,99,105,102,105,99,97,116,105,111,110,58,39,79,115,116,
114,105,99,104,32,83,97,110,115,39,59,108,101,116,116,101,114,45,115,112,97,99,105,110,103,58,48,112,120,59,119,111,114,100,45,115,112,97,99,105,110,103,58,48,112,120,59,100,105,115,112,108,97,121,58,
105,110,108,105,110,101,59,102,105,108,108,58,35,57,54,102,102,50,50,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,58,110,111,110,101,59,115,116,114,111,107,101,45,119,
105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,105,100,61,34,116,101,120,116,52,54,50,55,45,52,45,53,45,48,45,54,34,10,32,32,32,32,32,32,32,116,114,97,110,115,102,111,114,
109,61,34,109,97,116,114,105,120,40,48,46,52,55,54,54,57,57,50,44,48,44,48,44,48,46,52,55,54,54,57,57,49,55,44,45,50,49,49,46,49,55,53,51,51,44,49,54,56,46,55,51,55,55,53,41,34,62,60,112,97,116,104,10,
32,32,32,32,32,32,32,32,32,100,61,34,109,32,49,48,50,50,46,57,51,55,44,51,48,53,46,53,49,53,50,54,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,53,56,54,54,44,45,57,46,55,49,50,55,51,32,45,57,46,
55,49,50,55,44,45,57,46,55,49,50,55,51,32,104,32,45,55,46,56,50,52,50,32,99,32,45,53,46,49,50,54,49,44,48,32,45,57,46,55,49,50,54,57,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,54,57,44,57,46,55,49,50,
55,51,32,118,32,49,48,46,50,53,50,51,50,32,99,32,48,44,53,46,51,57,53,57,55,32,52,46,53,56,54,53,57,44,57,46,55,49,50,55,52,32,57,46,55,49,50,54,57,44,57,46,55,49,50,55,52,32,104,32,55,46,56,50,52,50,
32,99,32,53,46,49,50,54,49,44,48,32,57,46,55,49,50,55,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,44,45,57,46,55,49,50,55,52,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,
108,108,58,35,57,54,102,102,50,50,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,32,
32,105,100,61,34,112,97,116,104,52,53,49,50,45,51,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,
47,62,60,47,103,62,60,47,103,62,60,47,115,118,103,62,0,0};

const char* PinComponent::burstHotWalletlogo_svg = (const char*) resource_PinComponent_burstHotWalletlogo_svg;
const int PinComponent::burstHotWalletlogo_svgSize = 15546;

// JUCER_RESOURCE: burst_logo_white_svg, 3258, "burst_logo_white.svg"
static const unsigned char resource_PinComponent_burst_logo_white_svg[] = { 60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,110,99,111,100,105,110,103,61,34,117,116,102,45,56,
34,63,62,13,10,60,33,45,45,32,71,101,110,101,114,97,116,111,114,58,32,65,100,111,98,101,32,73,108,108,117,115,116,114,97,116,111,114,32,49,52,46,48,46,48,44,32,83,86,71,32,69,120,112,111,114,116,32,80,
108,117,103,45,73,110,32,46,32,83,86,71,32,86,101,114,115,105,111,110,58,32,54,46,48,48,32,66,117,105,108,100,32,52,51,51,54,51,41,32,32,45,45,62,13,10,60,33,68,79,67,84,89,80,69,32,115,118,103,32,80,
85,66,76,73,67,32,34,45,47,47,87,51,67,47,47,68,84,68,32,83,86,71,32,49,46,49,47,47,69,78,34,32,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,71,114,97,112,104,105,99,115,47,83,86,
71,47,49,46,49,47,68,84,68,47,115,118,103,49,49,46,100,116,100,34,62,13,10,60,115,118,103,32,118,101,114,115,105,111,110,61,34,49,46,49,34,32,105,100,61,34,67,97,108,113,117,101,95,49,34,32,120,109,108,
110,115,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,32,120,109,108,110,115,58,120,108,105,110,107,61,34,104,116,116,112,58,47,47,119,119,119,46,
119,51,46,111,114,103,47,49,57,57,57,47,120,108,105,110,107,34,32,120,61,34,48,112,120,34,32,121,61,34,48,112,120,34,13,10,9,32,119,105,100,116,104,61,34,55,48,48,46,52,54,53,112,120,34,32,104,101,105,
103,104,116,61,34,50,49,56,46,57,56,57,112,120,34,32,118,105,101,119,66,111,120,61,34,48,32,48,32,55,48,48,46,52,54,53,32,50,49,56,46,57,56,57,34,32,101,110,97,98,108,101,45,98,97,99,107,103,114,111,117,
110,100,61,34,110,101,119,32,48,32,48,32,55,48,48,46,52,54,53,32,50,49,56,46,57,56,57,34,13,10,9,32,120,109,108,58,115,112,97,99,101,61,34,112,114,101,115,101,114,118,101,34,62,13,10,60,103,62,13,10,9,
60,112,97,116,104,32,102,105,108,108,61,34,35,70,70,70,70,70,70,34,32,100,61,34,77,50,51,48,46,53,53,53,44,51,53,46,53,51,56,99,45,54,46,56,49,57,45,56,46,49,57,55,45,49,57,46,51,52,49,45,49,50,46,49,
56,50,45,51,56,46,50,56,49,45,49,50,46,49,56,50,104,45,53,48,46,56,54,53,76,49,50,56,46,55,57,49,44,57,49,46,52,52,108,45,53,48,46,53,53,55,45,48,46,48,50,53,13,10,9,9,76,55,50,46,53,57,54,44,49,49,55,
46,55,72,49,53,46,54,54,50,108,56,53,46,49,49,55,44,50,55,46,49,56,57,108,53,46,55,56,54,45,50,52,46,54,51,57,104,49,54,46,56,56,54,108,45,49,51,46,57,51,56,44,55,53,46,50,52,104,53,51,46,56,52,52,99,
51,51,46,52,55,50,44,48,44,53,51,46,56,51,50,45,49,52,46,52,48,54,44,53,56,46,56,55,55,45,52,49,46,54,54,51,108,50,46,53,49,55,45,49,51,46,54,50,53,13,10,9,9,99,51,46,51,52,45,49,56,46,48,48,51,45,49,
46,50,53,51,45,50,57,46,57,49,57,45,49,52,46,48,51,50,45,51,54,46,50,53,53,99,49,51,46,48,54,55,45,54,46,50,48,52,44,50,48,46,54,52,55,45,49,54,46,56,57,55,44,50,51,46,54,56,56,45,51,51,46,50,53,51,108,
49,46,49,48,55,45,53,46,57,55,50,13,10,9,9,67,50,51,55,46,56,56,44,53,49,46,57,51,57,44,50,51,54,46,50,53,56,44,52,50,46,51,57,51,44,50,51,48,46,53,53,53,44,51,53,46,53,51,56,122,32,77,49,56,55,46,56,
56,56,44,49,51,55,46,54,51,52,108,45,50,46,55,44,49,52,46,53,54,56,99,45,49,46,57,50,51,44,49,48,46,52,49,56,45,54,46,56,48,50,44,49,52,46,52,55,57,45,49,55,46,52,48,51,44,49,52,46,52,55,57,104,45,49,
53,46,53,56,51,13,10,9,9,108,56,46,54,48,51,45,52,54,46,52,52,57,104,49,50,46,51,55,49,99,55,46,49,48,55,44,48,44,49,49,46,51,57,50,44,49,46,49,55,50,44,49,51,46,52,56,52,44,51,46,54,56,57,67,49,56,56,
46,55,51,52,44,49,50,54,46,52,49,55,44,49,56,57,46,49,51,54,44,49,51,48,46,57,48,49,44,49,56,55,46,56,56,56,44,49,51,55,46,54,51,52,122,32,77,49,57,55,46,56,52,51,44,54,54,46,52,53,13,10,9,9,108,45,49,
46,55,50,53,44,57,46,51,49,50,99,45,50,46,48,51,54,44,49,48,46,57,56,54,45,56,46,49,48,50,44,49,53,46,54,55,52,45,50,48,46,50,56,50,44,49,53,46,54,55,52,104,45,57,46,54,57,55,108,55,46,50,55,55,45,51,
57,46,50,57,54,104,49,51,46,53,53,52,99,52,46,56,52,52,44,48,44,56,46,48,49,53,44,48,46,57,56,44,57,46,54,57,51,44,50,46,57,57,57,13,10,9,9,67,49,57,56,46,52,54,53,44,53,55,46,51,48,54,44,49,57,56,46,
56,53,50,44,54,49,46,48,48,55,44,49,57,55,46,56,52,51,44,54,54,46,52,53,122,34,47,62,13,10,9,60,112,97,116,104,32,102,105,108,108,61,34,35,70,70,70,70,70,70,34,32,100,61,34,77,50,55,49,46,53,50,52,44,
49,57,55,46,54,52,50,99,45,49,55,46,50,53,51,44,48,45,50,57,46,54,54,53,45,52,46,51,57,45,51,54,46,56,57,45,49,51,46,48,52,57,99,45,54,46,52,51,52,45,55,46,55,49,49,45,56,46,52,53,54,45,49,56,46,52,51,
55,45,54,46,48,48,57,45,51,49,46,56,55,56,13,10,9,9,108,50,51,46,53,54,57,45,49,50,57,46,51,49,53,104,51,55,46,50,56,108,45,50,52,46,48,51,44,49,51,49,46,56,54,50,99,45,48,46,56,53,51,44,52,46,54,55,57,
45,48,46,52,48,55,44,56,46,49,48,52,44,49,46,51,50,53,44,49,48,46,49,56,99,49,46,55,53,50,44,50,46,49,44,53,46,49,50,56,44,51,46,49,54,53,44,49,48,46,48,51,53,44,51,46,49,54,53,13,10,9,9,99,49,48,46,49,
54,49,44,48,44,49,53,46,52,57,45,52,46,51,56,55,44,49,55,46,50,56,45,49,52,46,50,50,52,108,50,51,46,56,55,51,45,49,51,48,46,57,56,51,104,51,53,46,53,49,55,108,45,50,51,46,55,50,49,44,49,51,48,46,49,57,
52,67,51,50,52,46,53,55,51,44,49,56,49,46,57,57,57,44,51,48,51,46,56,57,52,44,49,57,55,46,54,52,50,44,50,55,49,46,53,50,52,44,49,57,55,46,54,52,50,13,10,9,9,76,50,55,49,46,53,50,52,44,49,57,55,46,54,52,
50,122,34,47,62,13,10,9,60,112,97,116,104,32,102,105,108,108,61,34,35,70,70,70,70,70,70,34,32,100,61,34,77,52,53,50,46,50,48,54,44,51,53,46,53,54,50,99,45,54,46,56,50,56,45,56,46,49,56,55,45,49,57,46,
51,51,52,45,49,50,46,49,54,55,45,51,56,46,50,51,49,45,49,50,46,49,54,55,72,51,54,51,46,50,108,45,51,49,46,51,53,52,44,49,55,50,46,48,56,55,104,51,55,46,50,55,108,49,50,46,52,49,50,45,54,56,46,48,53,57,
13,10,9,9,104,57,46,49,48,54,99,54,46,55,54,49,44,48,44,49,49,46,49,50,53,44,49,46,50,57,51,44,49,51,46,51,52,50,44,51,46,57,53,49,99,50,46,50,56,53,44,50,46,55,51,57,44,50,46,55,55,57,44,55,46,52,53,
50,44,49,46,53,49,49,44,49,52,46,52,48,56,108,45,52,46,55,57,53,44,50,54,46,50,54,53,13,10,9,9,99,45,50,46,53,50,53,44,49,51,46,56,54,57,45,49,46,56,53,44,49,54,46,56,50,51,45,48,46,56,50,55,44,50,49,
46,50,57,53,108,48,46,52,56,56,44,50,46,49,52,104,51,56,46,50,53,51,108,45,49,46,48,57,56,45,51,46,50,51,57,99,45,49,46,57,52,49,45,53,46,55,50,54,45,49,46,49,53,57,45,49,49,46,50,55,49,44,48,46,50,53,
54,45,49,57,46,48,55,53,108,52,46,55,48,54,45,50,53,46,55,57,53,13,10,9,9,99,50,46,49,52,54,45,49,49,46,55,53,56,44,51,46,48,52,45,50,55,46,55,51,45,49,49,46,55,51,45,51,53,46,57,49,49,99,49,51,46,50,
51,50,45,54,46,50,53,50,44,50,49,46,49,51,54,45,49,55,46,50,57,44,50,52,46,49,45,51,51,46,53,57,50,108,50,46,51,57,52,45,49,51,46,49,50,52,13,10,9,9,67,52,53,57,46,53,54,53,44,53,49,46,57,53,57,44,52,
53,55,46,57,50,49,44,52,50,46,52,49,52,44,52,53,50,46,50,48,54,44,51,53,46,53,54,50,122,32,77,52,49,57,46,54,53,44,54,54,46,52,57,108,45,51,46,48,48,57,44,49,54,46,52,56,54,99,45,49,46,57,57,57,44,49,
48,46,57,55,53,45,56,46,48,51,53,44,49,53,46,54,53,54,45,50,48,46,49,56,52,44,49,53,46,54,53,54,104,45,57,46,54,56,55,13,10,9,9,108,56,46,52,55,49,45,52,54,46,52,52,52,104,49,51,46,53,49,52,99,52,46,56,
51,44,48,44,55,46,57,57,54,44,48,46,57,55,57,44,57,46,54,55,57,44,50,46,57,57,54,67,52,50,48,46,50,52,51,44,53,55,46,51,53,49,44,52,50,48,46,54,52,49,44,54,49,46,48,53,44,52,49,57,46,54,53,44,54,54,46,
52,57,122,34,47,62,13,10,9,60,112,97,116,104,32,102,105,108,108,61,34,35,70,70,70,70,70,70,34,32,100,61,34,77,52,57,48,46,50,53,51,44,49,57,55,46,51,57,54,99,45,49,55,46,50,53,53,44,48,45,50,57,46,54,
54,54,45,52,46,51,57,45,51,54,46,56,56,57,45,49,51,46,48,52,55,99,45,54,46,52,51,51,45,55,46,55,48,57,45,56,46,52,53,50,45,49,56,46,52,51,51,45,54,46,48,48,53,45,51,49,46,56,55,52,13,10,9,9,108,50,46,
50,52,52,45,49,50,46,50,55,54,104,51,53,46,53,49,49,108,45,50,46,55,48,52,44,49,52,46,56,50,52,99,45,48,46,56,53,50,44,52,46,54,56,50,45,48,46,52,48,52,44,56,46,49,48,57,44,49,46,51,50,57,44,49,48,46,
49,56,55,99,49,46,55,53,51,44,50,46,49,48,50,44,53,46,49,50,57,44,51,46,49,54,55,44,49,48,46,48,51,51,44,51,46,49,54,55,13,10,9,9,99,49,48,46,49,54,50,44,48,44,49,53,46,52,57,49,45,52,46,51,57,44,49,55,
46,50,55,55,45,49,52,46,50,51,50,99,49,46,56,52,55,45,49,48,46,49,48,52,45,48,46,55,53,56,45,49,56,46,49,51,50,45,50,48,46,49,49,54,45,51,51,46,57,54,54,99,45,50,51,46,51,52,49,45,49,57,46,50,50,51,45,
51,48,46,54,49,55,45,51,52,46,48,51,49,45,50,54,46,56,53,54,45,53,52,46,54,52,51,13,10,9,9,99,53,46,49,55,56,45,50,56,46,52,48,52,44,50,53,46,54,52,54,45,52,52,46,48,52,55,44,53,55,46,54,51,52,45,52,52,
46,48,52,55,99,49,54,46,57,55,57,44,48,44,50,57,46,50,48,53,44,52,46,51,51,53,44,51,54,46,51,51,57,44,49,50,46,56,56,52,99,54,46,52,51,50,44,55,46,55,48,56,44,56,46,52,52,50,44,49,56,46,52,56,57,44,53,
46,57,55,54,44,51,50,46,48,52,50,13,10,9,9,108,45,49,46,51,50,56,44,55,46,50,54,56,104,45,51,53,46,53,48,56,108,49,46,55,56,45,57,46,56,49,54,99,48,46,57,45,52,46,57,51,55,44,48,46,52,55,51,45,56,46,53,
45,49,46,50,55,50,45,49,48,46,53,57,50,99,45,49,46,54,56,49,45,50,46,48,49,54,45,52,46,55,55,49,45,50,46,57,57,53,45,57,46,52,52,55,45,50,46,57,57,53,13,10,9,9,99,45,57,46,55,53,54,44,48,45,49,52,46,57,
50,49,44,52,46,52,54,49,45,49,54,46,55,52,54,44,49,52,46,52,54,53,99,45,49,46,56,51,57,44,49,48,46,49,48,52,44,48,46,55,54,57,44,49,56,46,49,51,50,44,50,48,46,49,50,54,44,51,51,46,57,54,55,99,50,51,46,
51,51,56,44,49,57,46,50,49,55,44,51,48,46,54,49,52,44,51,52,46,48,50,53,44,50,54,46,56,53,52,44,53,52,46,54,52,51,13,10,9,9,67,53,52,51,46,50,57,55,44,49,56,49,46,55,53,53,44,53,50,50,46,54,49,54,44,49,
57,55,46,51,57,54,44,52,57,48,46,50,53,51,44,49,57,55,46,51,57,54,76,52,57,48,46,50,53,51,44,49,57,55,46,51,57,54,122,34,47,62,13,10,9,60,112,97,116,104,32,102,105,108,108,61,34,35,70,70,70,70,70,70,34,
32,100,61,34,77,54,49,51,46,48,53,51,44,49,57,53,46,52,56,49,104,45,51,55,46,50,55,55,108,50,54,46,49,49,49,45,49,52,51,46,50,57,51,104,45,51,51,46,55,54,57,108,53,46,50,54,45,50,56,46,55,56,57,104,49,
48,52,46,55,57,54,108,45,53,46,50,52,56,44,50,56,46,55,56,57,104,45,51,51,46,55,53,55,13,10,9,9,76,54,49,51,46,48,53,51,44,49,57,53,46,52,56,49,76,54,49,51,46,48,53,51,44,49,57,53,46,52,56,49,122,34,47,
62,13,10,60,47,103,62,13,10,60,47,115,118,103,62,13,10,0,0};

const char* PinComponent::burst_logo_white_svg = (const char*) resource_PinComponent_burst_logo_white_svg;
const int PinComponent::burst_logo_white_svgSize = 3258;


//[EndFile] You can add extra defines here...
//[/EndFile]
