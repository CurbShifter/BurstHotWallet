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

    addAndMakeVisible (secureHeaderLabel = new Label ("secureHeaderLabel",
                                                      TRANS("Loading transation history\n"
                                                      "\n"
                                                      "If this is a new wallet, copy your address below to receive Burstcoin and start making a transaction history")));
    secureHeaderLabel->setTooltip (TRANS("Note: Exchanges like Bittrex require your public key to be registered on chain to receive funds. You need to make at least 1 transaction recorded on the Burst blockchain."));
    secureHeaderLabel->setFont (Font (22.00f, Font::plain));
    secureHeaderLabel->setJustificationType (Justification::centred);
    secureHeaderLabel->setEditable (false, false, false);
    secureHeaderLabel->setColour (TextEditor::textColourId, Colours::black);
    secureHeaderLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (twitterButton = new TextButton ("twitterButton"));
    twitterButton->setTooltip (TRANS("copy to clipboard"));
    twitterButton->setButtonText (TRANS("copy my address"));
    twitterButton->addListener (this);
    twitterButton->setColour (TextButton::buttonColourId, Colour (0xff77b517));
    twitterButton->setColour (TextButton::buttonOnColourId, Colour (0xff6597ff));

    addAndMakeVisible (transactionsComponent = new TransactionsComponent());
    transactionsComponent->setName ("transactionsComponent");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	secureHeaderLabel->setVisible(false);
	twitterButton->setVisible(false);
    //[/Constructor]
}

HistoryComponent::~HistoryComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    secureHeaderLabel = nullptr;
    twitterButton = nullptr;
    transactionsComponent = nullptr;


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

    //[UserPaint] Add your own custom painting code here..
	*/
	g.fillAll(Colour(0xffe4ecf2));

	if (secureHeaderLabel->isVisible())
	{
		int dim = getHeight() - (twitterButton->getBottom() + 100);
		juce::Rectangle<float> r((getWidth() / 2) - (dim / 2), getHeight() - (75 + dim), dim, dim);
		if (qrDrawable != 0)
		{
			g.setColour(Colours::white);
			g.fillRoundedRectangle(r.expanded(10), 5.f);
			g.setColour(Colours::black);
			qrDrawable->drawWithin(g, r, juce::RectanglePlacement::centred, 1.000f);
		}
	}

    //[/UserPaint]
}

void HistoryComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	/*
    //[/UserPreResize]

    secureHeaderLabel->setBounds (24, 24, 408, 216);
    twitterButton->setBounds (16, 312, 432, 48);
    transactionsComponent->setBounds (32, 488, 424, 128);
    //[UserResized] Add your own custom resize handling here..
	*/
	int secureHeight = getHeight() * 0.3;
	int buttonHeight = 50;// getHeight() * 0.3;
	juce::Rectangle<int> r(getBounds().withZeroOrigin().reduced(30));

	secureHeaderLabel->setBounds(r.withHeight(secureHeight));
	twitterButton->setBounds(r.withSizeKeepingCentre(5 * 80, 80));

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
		SystemClipboard::copyTextToClipboard(addressRS);
		NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "The address copied to clipboard.");
        //[/UserButtonCode_twitterButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void HistoryComponent::ShowSecureAccount(const bool show, const String addressRS, const String pubKey_b64, const bool isPro)
{
	showSecureAccount = show;
	pubKey_b64SecureAccount = pubKey_b64;
	this->addressRS = addressRS;

	qrDrawable = qrCodeGenerator.generateQRpath(addressRS, 100.f);

	transactionsComponent->setVisible(!show);
	secureHeaderLabel->setVisible(show);
	twitterButton->setButtonText(addressRS);
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
  <BACKGROUND backgroundColour="ffe4ecf2"/>
  <LABEL name="secureHeaderLabel" id="16937582d36b0175" memberName="secureHeaderLabel"
         virtualName="" explicitFocusOrder="0" pos="24 24 408 216" tooltip="Note: Exchanges like Bittrex require your public key to be registered on chain to receive funds. You need to make at least 1 transaction recorded on the Burst blockchain."
         edTextCol="ff000000" edBkgCol="0" labelText="Loading transation history&#10;&#10;If this is a new wallet, copy your address below to receive Burstcoin and start making a transaction history"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="22" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="twitterButton" id="6eadaf4887f5fce8" memberName="twitterButton"
              virtualName="" explicitFocusOrder="0" pos="16 312 432 48" tooltip="copy to clipboard"
              bgColOff="ff77b517" bgColOn="ff6597ff" buttonText="copy my address"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="transactionsComponent" id="c229cf6401de4433" memberName="transactionsComponent"
                    virtualName="" explicitFocusOrder="0" pos="32 488 424 128" class="TransactionsComponent"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
