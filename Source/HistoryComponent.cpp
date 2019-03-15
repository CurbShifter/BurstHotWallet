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
#define ACTIVATE_EMAIL "curbshifter@pm.me"
//[/Headers]

#include "HistoryComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
HistoryComponent::HistoryComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (copyTextEditor = new TextEditor ("copyTextEditor"));
    copyTextEditor->setMultiLine (true);
    copyTextEditor->setReturnKeyStartsNewLine (false);
    copyTextEditor->setReadOnly (true);
    copyTextEditor->setScrollbarsShown (true);
    copyTextEditor->setCaretVisible (false);
    copyTextEditor->setPopupMenuEnabled (true);
    copyTextEditor->setColour (TextEditor::textColourId, Colours::black);
    copyTextEditor->setColour (TextEditor::backgroundColourId, Colour (0x50ffffff));
    copyTextEditor->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    copyTextEditor->setText (TRANS("I need to secure my #Burstcoin wallet.  Please send me a #hotwallet.pro license at "));

    addAndMakeVisible (secureHeaderLabel = new Label ("secureHeaderLabel",
                                                      TRANS("Receive a free hotwallet.pro license.\n"
                                                      "and secure your new wallet on the blockchain. \n"
                                                      "\n"
                                                      "Give @BurstExtensions a follow and tweet your request:")));
    secureHeaderLabel->setTooltip (TRANS("This wallet registration allows you to receive funds from exchanges like Bittrex as they require your public key to be registered on chain. Your passphrase stays private and secure. \n"));
    secureHeaderLabel->setFont (Font (18.00f, Font::plain));
    secureHeaderLabel->setJustificationType (Justification::centred);
    secureHeaderLabel->setEditable (false, false, false);
    secureHeaderLabel->setColour (TextEditor::textColourId, Colours::black);
    secureHeaderLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (twitterButton = new TextButton ("twitterButton"));
    twitterButton->setTooltip (TRANS("Trade me a follow and a tweet for a free license :)"));
    twitterButton->setButtonText (TRANS("go to twitter"));
    twitterButton->addListener (this);
    twitterButton->setColour (TextButton::buttonColourId, Colour (0xff4d95ff));
    twitterButton->setColour (TextButton::buttonOnColourId, Colour (0xff6597ff));

    addAndMakeVisible (transactionsComponent = new TransactionsComponent());
    transactionsComponent->setName ("transactionsComponent");

    drawable1 = Drawable::createFromImageData (twitter_svg, twitter_svgSize);

    //[UserPreSize]
	showSecureAccount = false;
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	secureHeaderLabel->setVisible(false);
	copyTextEditor->setVisible(false);
	twitterButton->setVisible(false);
    //[/Constructor]
}

HistoryComponent::~HistoryComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    copyTextEditor = nullptr;
    secureHeaderLabel = nullptr;
    twitterButton = nullptr;
    transactionsComponent = nullptr;
    drawable1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void HistoryComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	/*
    //[/UserPrePaint]

    g.fillAll (Colour (0xffe4ecf2));

    g.setColour (Colours::black);
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, Rectangle<float> (380, 116, 44, 32),
                               RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.000f);

    //[UserPaint] Add your own custom painting code here..
	*/
	g.fillAll(Colour(0xffe4ecf2));

	juce::Rectangle<int> r(getBounds().withZeroOrigin().reduced(60));
	int secureHeight = getHeight() * 0.3;
	g.setColour(Colours::black);
	jassert(drawable1 != 0);
	if (drawable1 != 0)
		drawable1->drawWithin(g, Rectangle<float>(r.withTrimmedTop(secureHeight + 50).withHeight(60).toFloat()),
		RectanglePlacement::xRight | RectanglePlacement::onlyReduceInSize, 1.000f);
    //[/UserPaint]
}

void HistoryComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	/*
    //[/UserPreResize]

    copyTextEditor->setBounds (8, 112, 352, 48);
    secureHeaderLabel->setBounds (16, 8, 408, 96);
    twitterButton->setBounds (8, 168, 440, 48);
    transactionsComponent->setBounds (24, 264, 424, 128);
    //[UserResized] Add your own custom resize handling here..
	*/
	int secureHeight = getHeight() * 0.3;
	int buttonHeight = 50;// getHeight() * 0.3;
	juce::Rectangle<int> r(getBounds().withZeroOrigin().reduced(30));

	secureHeaderLabel->setBounds(r.withHeight(secureHeight));
	copyTextEditor->setBounds(r.withTrimmedTop(secureHeight).withHeight(70));
	twitterButton->setBounds(r.reduced(30).withTrimmedTop(secureHeight + 130).withHeight(buttonHeight));

	//textButton->setBounds(getBounds().withZeroOrigin().withTrimmedTop(secureHeight).reduced(30).withHeight(buttonHeight));

	transactionsComponent->setBounds(getBounds().withZeroOrigin()); // .withTrimmedTop(secureHeight + buttonHeight)
    //[/UserResized]
}

void HistoryComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == twitterButton)
    {
        //[UserButtonCode_twitterButton] -- add your button handler code here..
		SystemClipboard::copyTextToClipboard(copyTextEditor->getText());
		NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "The text has been copied to clipboard. Now tweet it to @BurstExtensions for a license");
		URL url("https://twitter.com/BurstExtensions");
		url.launchInDefaultBrowser();
        //[/UserButtonCode_twitterButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void HistoryComponent::ShowSecureAccount(const bool show, const String pubKey_b64, const bool isPro)
{
	showSecureAccount = show;
	pubKey_b64SecureAccount = pubKey_b64;

	copyTextEditor->setText(TRANS("I need to secure my #Burstcoin wallet.  Please send me a #hotwallet.pro license at " + pubKey_b64SecureAccount));

	transactionsComponent->setVisible(!show);
	secureHeaderLabel->setVisible(show);
	copyTextEditor->setVisible(show);
	twitterButton->setVisible(show);
}
/*
void HistoryComponent::MailRequest()
{
	//- 0 if 'cancel' was pressed
	//- 1 if 'yes' was pressed
	//- 2 if 'no' was pressed
	int r = NativeMessageBox::showYesNoCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, "(Yes) Prepare a email in your mail client?\nOr (No) to copy your public key to clipboard.");
	if (r == 1)
	{
		URL url("mailto:" ACTIVATE_EMAIL "?subject=Secure-pubkey&body=" + pubKey_b64SecureAccount);
		url.launchInDefaultBrowser();
	}
	else if (r == 2)
	{
		SystemClipboard::copyTextToClipboard(pubKey_b64SecureAccount);

		NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Your public key is copied to clipboard.\nemail your public key to " ACTIVATE_EMAIL " for the free licence token. Or have someone send you a transaction.");
	}
}*/
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="HistoryComponent" componentName=""
                 parentClasses="public Component, public HistoryComponentListener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffe4ecf2">
    <IMAGE pos="380 116 44 32" resource="twitter_svg" opacity="1" mode="2"/>
  </BACKGROUND>
  <TEXTEDITOR name="copyTextEditor" id="64fd00d400cfd14a" memberName="copyTextEditor"
              virtualName="" explicitFocusOrder="0" pos="8 112 352 48" textcol="ff000000"
              bkgcol="50ffffff" shadowcol="0" initialText="I need to secure my #Burstcoin wallet.  Please send me a #hotwallet.pro license at "
              multiline="1" retKeyStartsLine="0" readonly="1" scrollbars="1"
              caret="0" popupmenu="1"/>
  <LABEL name="secureHeaderLabel" id="16937582d36b0175" memberName="secureHeaderLabel"
         virtualName="" explicitFocusOrder="0" pos="16 8 408 96" tooltip="This wallet registration allows you to receive funds from exchanges like Bittrex as they require your public key to be registered on chain. Your passphrase stays private and secure. &#10;"
         edTextCol="ff000000" edBkgCol="0" labelText="Receive a free hotwallet.pro license.&#10;and secure your new wallet on the blockchain. &#10;&#10;Give @BurstExtensions a follow and tweet your request:"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="18" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="twitterButton" id="6eadaf4887f5fce8" memberName="twitterButton"
              virtualName="" explicitFocusOrder="0" pos="8 168 440 48" tooltip="Trade me a follow and a tweet for a free license :)"
              bgColOff="ff4d95ff" bgColOn="ff6597ff" buttonText="go to twitter"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="transactionsComponent" id="c229cf6401de4433" memberName="transactionsComponent"
                    virtualName="" explicitFocusOrder="0" pos="24 264 424 128" class="TransactionsComponent"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: twitter_svg, 1416, "img/twitter.svg"
static const unsigned char resource_HistoryComponent_twitter_svg[] = { 60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,110,99,111,100,105,110,103,61,34,119,105,110,100,111,119,
115,45,49,50,53,50,34,63,62,13,10,60,33,45,45,32,71,101,110,101,114,97,116,111,114,58,32,65,100,111,98,101,32,73,108,108,117,115,116,114,97,116,111,114,32,49,56,46,49,46,49,44,32,83,86,71,32,69,120,112,
111,114,116,32,80,108,117,103,45,73,110,32,46,32,83,86,71,32,86,101,114,115,105,111,110,58,32,54,46,48,48,32,66,117,105,108,100,32,48,41,32,32,45,45,62,13,10,60,115,118,103,32,118,101,114,115,105,111,
110,61,34,49,46,49,34,32,105,100,61,34,67,97,112,97,95,49,34,32,120,109,108,110,115,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,32,120,109,108,
110,115,58,120,108,105,110,107,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,49,57,57,57,47,120,108,105,110,107,34,32,120,61,34,48,112,120,34,32,121,61,34,48,112,120,34,32,118,
105,101,119,66,111,120,61,34,48,32,48,32,54,49,50,32,54,49,50,34,32,115,116,121,108,101,61,34,101,110,97,98,108,101,45,98,97,99,107,103,114,111,117,110,100,58,110,101,119,32,48,32,48,32,54,49,50,32,54,
49,50,59,34,32,120,109,108,58,115,112,97,99,101,61,34,112,114,101,115,101,114,118,101,34,62,13,10,60,103,62,13,10,9,60,103,62,13,10,9,9,60,112,97,116,104,32,115,116,121,108,101,61,34,102,105,108,108,58,
35,48,49,48,48,48,50,59,34,32,100,61,34,77,54,49,50,44,49,49,54,46,50,53,56,99,45,50,50,46,53,50,53,44,57,46,57,56,49,45,52,54,46,54,57,52,44,49,54,46,55,53,45,55,50,46,48,56,56,44,49,57,46,55,55,50,99,
50,53,46,57,50,57,45,49,53,46,53,50,55,44,52,53,46,55,55,55,45,52,48,46,49,53,53,44,53,53,46,49,56,52,45,54,57,46,52,49,49,32,32,32,32,99,45,50,52,46,51,50,50,44,49,52,46,51,55,57,45,53,49,46,49,54,57,
44,50,52,46,56,50,45,55,57,46,55,55,53,44,51,48,46,52,56,99,45,50,50,46,57,48,55,45,50,52,46,52,51,55,45,53,53,46,52,57,45,51,57,46,54,53,56,45,57,49,46,54,51,45,51,57,46,54,53,56,99,45,54,57,46,51,51,
52,44,48,45,49,50,53,46,53,53,49,44,53,54,46,50,49,55,45,49,50,53,46,53,53,49,44,49,50,53,46,53,49,51,32,32,32,32,99,48,44,57,46,56,50,56,44,49,46,49,48,57,44,49,57,46,52,50,55,44,51,46,50,53,49,44,50,
56,46,54,48,54,67,49,57,55,46,48,54,53,44,50,48,54,46,51,50,44,49,48,52,46,53,53,54,44,49,53,54,46,51,51,55,44,52,50,46,54,52,49,44,56,48,46,51,56,54,99,45,49,48,46,56,50,51,44,49,56,46,53,49,45,49,54,
46,57,56,44,52,48,46,48,55,56,45,49,54,46,57,56,44,54,51,46,49,48,49,32,32,32,32,99,48,44,52,51,46,53,53,57,44,50,50,46,49,56,49,44,56,49,46,57,57,51,44,53,53,46,56,51,53,44,49,48,52,46,52,55,57,99,45,
50,48,46,53,55,53,45,48,46,54,56,56,45,51,57,46,57,50,54,45,54,46,51,52,56,45,53,54,46,56,54,55,45,49,53,46,55,53,54,118,49,46,53,54,56,99,48,44,54,48,46,56,48,54,44,52,51,46,50,57,49,44,49,49,49,46,53,
53,52,44,49,48,48,46,54,57,51,44,49,50,51,46,49,48,52,32,32,32,32,99,45,49,48,46,53,49,55,44,50,46,56,51,45,50,49,46,54,48,55,44,52,46,51,57,56,45,51,51,46,48,56,44,52,46,51,57,56,99,45,56,46,49,48,55,
44,48,45,49,53,46,57,52,55,45,48,46,56,48,51,45,50,51,46,54,51,52,45,50,46,51,51,51,99,49,53,46,57,56,53,44,52,57,46,57,48,55,44,54,50,46,51,51,54,44,56,54,46,49,57,57,44,49,49,55,46,50,53,51,44,56,55,
46,49,57,52,32,32,32,32,99,45,52,50,46,57,52,55,44,51,51,46,54,53,52,45,57,55,46,48,57,57,44,53,51,46,54,53,53,45,49,53,53,46,57,49,54,44,53,51,46,54,53,53,99,45,49,48,46,49,51,52,44,48,45,50,48,46,49,
49,54,45,48,46,54,49,50,45,50,57,46,57,52,52,45,49,46,55,50,49,99,53,53,46,53,54,55,44,51,53,46,54,56,49,44,49,50,49,46,53,51,54,44,53,54,46,52,56,53,44,49,57,50,46,52,51,56,44,53,54,46,52,56,53,32,32,
32,32,99,50,51,48,46,57,52,56,44,48,44,51,53,55,46,49,56,56,45,49,57,49,46,50,57,49,44,51,53,55,46,49,56,56,45,51,53,55,46,49,56,56,108,45,48,46,52,50,49,45,49,54,46,50,53,51,67,53,55,51,46,56,55,50,44,
49,54,51,46,53,50,54,44,53,57,53,46,50,49,49,44,49,52,49,46,52,50,50,44,54,49,50,44,49,49,54,46,50,53,56,122,34,47,62,13,10,9,60,47,103,62,13,10,60,47,103,62,13,10,60,103,62,13,10,60,47,103,62,13,10,60,
103,62,13,10,60,47,103,62,13,10,60,103,62,13,10,60,47,103,62,13,10,60,103,62,13,10,60,47,103,62,13,10,60,103,62,13,10,60,47,103,62,13,10,60,103,62,13,10,60,47,103,62,13,10,60,103,62,13,10,60,47,103,62,
13,10,60,103,62,13,10,60,47,103,62,13,10,60,103,62,13,10,60,47,103,62,13,10,60,103,62,13,10,60,47,103,62,13,10,60,103,62,13,10,60,47,103,62,13,10,60,103,62,13,10,60,47,103,62,13,10,60,103,62,13,10,60,
47,103,62,13,10,60,103,62,13,10,60,47,103,62,13,10,60,103,62,13,10,60,47,103,62,13,10,60,47,115,118,103,62,0,0};

const char* HistoryComponent::twitter_svg = (const char*) resource_HistoryComponent_twitter_svg;
const int HistoryComponent::twitter_svgSize = 1416;


//[EndFile] You can add extra defines here...
//[/EndFile]
