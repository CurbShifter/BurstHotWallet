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
#include <string>
//[/Headers]

#include "SendComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SendComponent::SendComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (fixedMessageLabel = new Label ("fixedMessageLabel",
                                                      TRANS("fixed message")));
    fixedMessageLabel->setFont (Font (15.00f, Font::plain));
    fixedMessageLabel->setJustificationType (Justification::centredLeft);
    fixedMessageLabel->setEditable (false, false, false);
    fixedMessageLabel->setColour (TextEditor::textColourId, Colours::black);
    fixedMessageLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (totalLabel = new Label ("totalLabel",
                                               TRANS("0. BURST")));
    totalLabel->setFont (Font (18.00f, Font::plain));
    totalLabel->setJustificationType (Justification::centred);
    totalLabel->setEditable (false, false, false);
    totalLabel->setColour (TextEditor::textColourId, Colours::black);
    totalLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sendTextButton = new TextButton ("sendTextButton"));
    sendTextButton->setButtonText (TRANS("send"));
    sendTextButton->addListener (this);
    sendTextButton->setColour (TextButton::buttonColourId, Colour (0xff77b517));
    sendTextButton->setColour (TextButton::buttonOnColourId, Colour (0xff77b517));

    addAndMakeVisible (feeSlider = new Slider ("feeSlider"));
    feeSlider->setTooltip (TRANS("the fee that goes to the miner that adds your transaction to the blockchain"));
    feeSlider->setRange (0.00735, 73.5, 0.00735);
    feeSlider->setSliderStyle (Slider::LinearHorizontal);
    feeSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    feeSlider->setColour (Slider::backgroundColourId, Colour (0x00595959));
    feeSlider->setColour (Slider::thumbColourId, Colour (0xff77b517));
    feeSlider->setColour (Slider::trackColourId, Colours::white);
    feeSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xff77b517));
    feeSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::black);
    feeSlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff77b517));
    feeSlider->addListener (this);

    addAndMakeVisible (messageTextEditor = new TextEditor ("messageTextEditor"));
    messageTextEditor->setMultiLine (true);
    messageTextEditor->setReturnKeyStartsNewLine (false);
    messageTextEditor->setReadOnly (false);
    messageTextEditor->setScrollbarsShown (true);
    messageTextEditor->setCaretVisible (true);
    messageTextEditor->setPopupMenuEnabled (true);
    messageTextEditor->setText (String());

    addAndMakeVisible (encryptToggleButton = new ToggleButton ("encryptToggleButton"));
    encryptToggleButton->setTooltip (TRANS("encrypt to make the message only visible to the recipient"));
    encryptToggleButton->setButtonText (TRANS("encrypt"));
    encryptToggleButton->addListener (this);

    addAndMakeVisible (messageLabel = new Label ("messageLabel",
                                                 TRANS("Message")));
    messageLabel->setFont (Font (15.00f, Font::plain));
    messageLabel->setJustificationType (Justification::centredRight);
    messageLabel->setEditable (false, false, false);
    messageLabel->setColour (TextEditor::textColourId, Colours::black);
    messageLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (recipientLabel = new Label ("recipientLabel",
                                                   TRANS("Recipient")));
    recipientLabel->setFont (Font (15.00f, Font::plain));
    recipientLabel->setJustificationType (Justification::centredRight);
    recipientLabel->setEditable (false, false, false);
    recipientLabel->setColour (TextEditor::textColourId, Colours::black);
    recipientLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (amountLabel = new Label ("amountLabel",
                                                TRANS("Amount")));
    amountLabel->setFont (Font (15.00f, Font::plain));
    amountLabel->setJustificationType (Justification::centredRight);
    amountLabel->setEditable (false, false, false);
    amountLabel->setColour (TextEditor::textColourId, Colours::black);
    amountLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (feeLabel = new Label ("feeLabel",
                                             TRANS("+ Fee in Burstcoin")));
    feeLabel->setFont (Font (15.00f, Font::plain));
    feeLabel->setJustificationType (Justification::centredRight);
    feeLabel->setEditable (false, false, false);
    feeLabel->setColour (TextEditor::textColourId, Colours::black);
    feeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (feeComboBox = new ComboBox ("feeComboBox"));
    feeComboBox->setTooltip (TRANS("the suggested fees that goes to the miner that adds your transaction to the blockchain."));
    feeComboBox->setEditableText (false);
    feeComboBox->setJustificationType (Justification::centredLeft);
    feeComboBox->setTextWhenNothingSelected (TRANS("standard"));
    feeComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    feeComboBox->addItem (TRANS("cheap"), 1);
    feeComboBox->addItem (TRANS("standard"), 2);
    feeComboBox->addItem (TRANS("priority"), 3);
    feeComboBox->addListener (this);

    addAndMakeVisible (recipientComboBox = new ComboBox ("recipientComboBox"));
    recipientComboBox->setEditableText (true);
    recipientComboBox->setJustificationType (Justification::centredLeft);
    recipientComboBox->setTextWhenNothingSelected (TRANS("BURST address, alias, numerical or public key"));
    recipientComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    recipientComboBox->addItem (TRANS("@CurbShifter"), 1);
    recipientComboBox->addListener (this);

    addAndMakeVisible (amountComboBox = new ComboBox ("amountComboBox"));
    amountComboBox->setEditableText (true);
    amountComboBox->setJustificationType (Justification::centredRight);
    amountComboBox->setTextWhenNothingSelected (TRANS("0."));
    amountComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    amountComboBox->addItem (TRANS("0.25"), 1);
    amountComboBox->addItem (TRANS("0.5"), 2);
    amountComboBox->addItem (TRANS("1.0"), 3);
    amountComboBox->addItem (TRANS("10"), 4);
    amountComboBox->addItem (TRANS("100"), 5);
    amountComboBox->addItem (TRANS("1000"), 6);
    amountComboBox->addListener (this);

    addAndMakeVisible (paymentLabel = new Label ("paymentLabel",
                                                 TRANS("Payment request")));
    paymentLabel->setFont (Font (16.00f, Font::plain));
    paymentLabel->setJustificationType (Justification::centredLeft);
    paymentLabel->setEditable (false, false, false);
    paymentLabel->setColour (TextEditor::textColourId, Colours::black);
    paymentLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (costLabel = new Label ("costLabel",
                                              TRANS("Costs")));
    costLabel->setFont (Font (16.00f, Font::plain));
    costLabel->setJustificationType (Justification::centredRight);
    costLabel->setEditable (false, false, false);
    costLabel->setColour (TextEditor::textColourId, Colours::black);
    costLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cancelButton = new TextButton ("cancelButton"));
    cancelButton->setButtonText (TRANS("cancel"));
    cancelButton->addListener (this);
    cancelButton->setColour (TextButton::buttonColourId, Colour (0xffc85c5c));
    cancelButton->setColour (TextButton::buttonOnColourId, Colour (0xff77b517));

    addAndMakeVisible (recipientFixedLabel = new Label ("recipientFixedLabel",
                                                        TRANS("recipient")));
    recipientFixedLabel->setFont (Font (15.00f, Font::plain));
    recipientFixedLabel->setJustificationType (Justification::centredLeft);
    recipientFixedLabel->setEditable (false, false, false);
    recipientFixedLabel->setColour (TextEditor::textColourId, Colours::black);
    recipientFixedLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (passwordTextEditor = new TextEditor ("passwordTextEditor"));
    passwordTextEditor->setTooltip (TRANS("the new coupon password"));
    passwordTextEditor->setMultiLine (false);
    passwordTextEditor->setReturnKeyStartsNewLine (false);
    passwordTextEditor->setReadOnly (false);
    passwordTextEditor->setScrollbarsShown (true);
    passwordTextEditor->setCaretVisible (true);
    passwordTextEditor->setPopupMenuEnabled (true);
    passwordTextEditor->setText (String());

    addAndMakeVisible (couponToggleButton = new ToggleButton ("couponToggleButton"));
    couponToggleButton->setTooltip (TRANS("send the transaction as a coupon to be claimed later"));
    couponToggleButton->setButtonText (TRANS("as coupon"));
    couponToggleButton->addListener (this);

    addAndMakeVisible (minSlider = new Slider ("minSlider"));
    minSlider->setTooltip (TRANS("the minutes when this coupon expires since it\'s made"));
    minSlider->setRange (8, 1440, 4);
    minSlider->setSliderStyle (Slider::IncDecButtons);
    minSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    minSlider->addListener (this);

    addAndMakeVisible (minLabel = new Label ("minLabel",
                                             TRANS("min")));
    minLabel->setTooltip (TRANS("the minutes when this coupon expires since it\'s made"));
    minLabel->setFont (Font (15.00f, Font::plain));
    minLabel->setJustificationType (Justification::centredLeft);
    minLabel->setEditable (false, false, false);
    minLabel->setColour (TextEditor::textColourId, Colours::black);
    minLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (currencyComboBox = new ComboBox ("currencyComboBox"));
    currencyComboBox->setTooltip (TRANS("Use Burst or whitelisted assets"));
    currencyComboBox->setEditableText (false);
    currencyComboBox->setJustificationType (Justification::centredLeft);
    currencyComboBox->setTextWhenNothingSelected (TRANS("BURST"));
    currencyComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    currencyComboBox->addItem (TRANS("BURST"), 1);
    currencyComboBox->addListener (this);


    //[UserPreSize]
	currencyComboBox->setSelectedItemIndex(0);
	//amountComboBox->setInputRestrictions(20, "0.123456789");
	messageTextEditor->setInputRestrictions(999);
//	messageTextEditor->applyFontToAllText(LookAndFeel::getDefaultLookAndFeel().getComboBoxFont());

	passwordTextEditor->setTextToShowWhenEmpty("the coupon password", Colours::darkred);
	passwordTextEditor->setVisible(false);

	minSlider->setVisible(false);
	minLabel->setVisible(false);

	minSlider->setValue(1440, dontSendNotification);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	cheap = FEE_QUANT * 10;
	normal = FEE_QUANT * 30;
	priority = FEE_QUANT * 60;

	SetView(0);
    //[/Constructor]
}

SendComponent::~SendComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    fixedMessageLabel = nullptr;
    totalLabel = nullptr;
    sendTextButton = nullptr;
    feeSlider = nullptr;
    messageTextEditor = nullptr;
    encryptToggleButton = nullptr;
    messageLabel = nullptr;
    recipientLabel = nullptr;
    amountLabel = nullptr;
    feeLabel = nullptr;
    feeComboBox = nullptr;
    recipientComboBox = nullptr;
    amountComboBox = nullptr;
    paymentLabel = nullptr;
    costLabel = nullptr;
    cancelButton = nullptr;
    recipientFixedLabel = nullptr;
    passwordTextEditor = nullptr;
    couponToggleButton = nullptr;
    minSlider = nullptr;
    minLabel = nullptr;
    currencyComboBox = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SendComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xfff0f0f0));

    //[UserPaint] Add your own custom painting code here..

	if (paymentLabel->isVisible())
		g.fillAll(Colour(0x7f77b517));

    //[/UserPaint]
}

void SendComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	/*
    //[/UserPreResize]

    fixedMessageLabel->setBounds (376, 176, 288, 48);
    totalLabel->setBounds (200, 120, 150, 24);
    sendTextButton->setBounds (328, 368, 328, 24);
    feeSlider->setBounds (104, 72, 136, 24);
    messageTextEditor->setBounds (101, 205, 248, 59);
    encryptToggleButton->setBounds (16, 264, 80, 24);
    messageLabel->setBounds (13, 205, 78, 24);
    recipientLabel->setBounds (16, 8, 78, 24);
    amountLabel->setBounds (24, 40, 71, 24);
    feeLabel->setBounds (15, 72, 80, 24);
    feeComboBox->setBounds (248, 72, 96, 24);
    recipientComboBox->setBounds (136, 8, 150, 24);
    amountComboBox->setBounds (136, 40, 150, 24);
    paymentLabel->setBounds (376, 24, 288, 48);
    costLabel->setBounds (376, 112, 288, 56);
    cancelButton->setBounds (24, 368, 296, 24);
    recipientFixedLabel->setBounds (376, 80, 288, 24);
    passwordTextEditor->setBounds (120, 296, 296, 24);
    couponToggleButton->setBounds (16, 296, 96, 24);
    minSlider->setBounds (424, 296, 80, 24);
    minLabel->setBounds (512, 296, 118, 24);
    currencyComboBox->setBounds (288, 40, 72, 24);
    //[UserResized] Add your own custom resize handling here..
	*/
	const float rowH = 28.f;
	juce::Rectangle<float> r = getBounds().withZeroOrigin().reduced((int)(rowH * 3 / 2)).toFloat();

	if (r.getWidth() > 400)
		r = r.withSizeKeepingCentre(400, r.getHeight());

	recipientLabel->setBounds(r.withTrimmedTop(rowH * 0).withHeight(rowH).toNearestInt());
	recipientComboBox->setBounds(r.withTrimmedTop(rowH * 1).withHeight(rowH).toNearestInt());

	amountLabel->setBounds(r.withTrimmedTop(rowH * 2).withHeight(rowH).toNearestInt());
	amountComboBox->setBounds(r.withTrimmedTop(rowH * 3).withHeight(rowH).withWidth(r.getWidth() / 3 * 2).toNearestInt());
	currencyComboBox->setBounds(r.withTrimmedTop(rowH * 3).withHeight(rowH).translated(r.getWidth() / 3 * 2, 0).withWidth(r.getWidth() / 3).toNearestInt());

	feeLabel->setBounds(r.withTrimmedTop(rowH * 4).withHeight(rowH).toNearestInt());
	feeSlider->setBounds(r.withTrimmedTop(rowH * 5).withHeight(rowH).withWidth(r.getWidth() / 3 * 2).toNearestInt());
	feeComboBox->setBounds(r.withTrimmedTop(rowH * 5).withHeight(rowH).translated(r.getWidth() / 3 * 2, 0).withWidth(r.getWidth() / 3).toNearestInt());

	messageLabel->setBounds(r.withTrimmedTop(rowH * 7).withHeight(rowH).toNearestInt());
	messageTextEditor->setBounds(r.withTrimmedTop(rowH * 8).withHeight(r.getHeight() - (rowH * 12)).toNearestInt());
	encryptToggleButton->setBounds(r.withTrimmedTop(r.getHeight() - (rowH * 4)).withHeight(rowH).withWidth(100).toNearestInt());

	couponToggleButton->setBounds(r.withTrimmedTop(r.getHeight() - (rowH * 3)).withHeight(rowH).withTrimmedRight(r.getWidth() - 90).toNearestInt());
	passwordTextEditor->setBounds(r.withTrimmedTop(r.getHeight() - (rowH * 3)).withHeight(rowH).withTrimmedLeft(90).withTrimmedRight(r.getWidth() / 3).toNearestInt().reduced(2));
	minSlider->setBounds(r.withTrimmedTop(r.getHeight() - (rowH * 3)).withHeight(rowH).withTrimmedLeft(r.getWidth() / 3 * 2).withTrimmedRight(r.getWidth() / 12).toNearestInt().reduced(3));
	minLabel->setBounds(r.withTrimmedTop(r.getHeight() - (rowH * 3)).withHeight(rowH).withTrimmedLeft(r.getWidth() / 12 * 11).toNearestInt());

	sendTextButton->setBounds(r.withTrimmedTop(r.getHeight() - (rowH * 2)).withHeight(rowH).withTrimmedLeft(r.getWidth() / 2).toNearestInt());

	totalLabel->setBounds(r.withTrimmedTop(r.getHeight() - (rowH * 1)).withHeight(rowH).toNearestInt()); //(r.withTrimmedTop(rowH * 6).withHeight(rowH).translated(r.getWidth() / 2, 0).withWidth(r.getWidth() / 2).toNearestInt());



	paymentLabel->setBounds(r.withTrimmedTop(rowH * 0).withHeight(rowH * 2).toNearestInt());
	recipientFixedLabel->setBounds(r.withTrimmedTop(rowH * 2).withHeight(rowH).toNearestInt());
	costLabel->setBounds(r.withTrimmedTop(rowH * 3).withHeight(rowH).toNearestInt());
	fixedMessageLabel->setBounds(r.withTrimmedTop(rowH * 6).withHeight(rowH).toNearestInt());

	cancelButton->setBounds(r.withTrimmedTop(r.getHeight() - (rowH * 2)).withHeight(rowH).withWidth(r.getWidth() / 2).toNearestInt());
    //[/UserResized]
}

void SendComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == sendTextButton)
    {
        //[UserButtonCode_sendTextButton] -- add your button handler code here..
		SendBurst();
        //[/UserButtonCode_sendTextButton]
    }
    else if (buttonThatWasClicked == encryptToggleButton)
    {
        //[UserButtonCode_encryptToggleButton] -- add your button handler code here..
        //[/UserButtonCode_encryptToggleButton]
    }
    else if (buttonThatWasClicked == cancelButton)
    {
        //[UserButtonCode_cancelButton] -- add your button handler code here..
		SetView(0);
        //[/UserButtonCode_cancelButton]
    }
    else if (buttonThatWasClicked == couponToggleButton)
    {
        //[UserButtonCode_couponToggleButton] -- add your button handler code here..
		if (couponToggleButton->getToggleState())
			sendTextButton->setButtonText("make coupon");
		else sendTextButton->setButtonText("send");

		passwordTextEditor->setVisible(couponToggleButton->getToggleState());
		minSlider->setVisible(couponToggleButton->getToggleState());
		minLabel->setVisible(couponToggleButton->getToggleState());
        //[/UserButtonCode_couponToggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void SendComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == feeSlider)
    {
        //[UserSliderCode_feeSlider] -- add your slider handling code here..
		uint64 fee = (uint64)(sliderThatWasMoved->getValue() * 100000000L);
		if (fee < normal)
			feeComboBox->setSelectedItemIndex(0, dontSendNotification);
		else if (fee < priority)
			feeComboBox->setSelectedItemIndex(1, dontSendNotification);
		else feeComboBox->setSelectedItemIndex(2, dontSendNotification);

		UpdateTotalLabel(paymentLabel->isVisible() ? costLabel->getText() : amountComboBox->getText(), String(feeSlider->getValue()));
        //[/UserSliderCode_feeSlider]
    }
    else if (sliderThatWasMoved == minSlider)
    {
        //[UserSliderCode_minSlider] -- add your slider handling code here..
        //[/UserSliderCode_minSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void SendComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == feeComboBox)
    {
        //[UserComboBoxCode_feeComboBox] -- add your combo box handling code here..
		if (feeComboBox->getSelectedItemIndex() == 0)
			feeSlider->setValue(cheap / 100000000., dontSendNotification);
		else if (feeComboBox->getSelectedItemIndex() == 1)
			feeSlider->setValue(normal / 100000000., dontSendNotification);
		else if (feeComboBox->getSelectedItemIndex() == 2)
			feeSlider->setValue(priority / 100000000., dontSendNotification);

		UpdateTotalLabel(amountComboBox->getText(), String(feeSlider->getValue()));
        //[/UserComboBoxCode_feeComboBox]
    }
    else if (comboBoxThatHasChanged == recipientComboBox)
    {
        //[UserComboBoxCode_recipientComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_recipientComboBox]
    }
    else if (comboBoxThatHasChanged == amountComboBox)
    {
        //[UserComboBoxCode_amountComboBox] -- add your combo box handling code here..
		UpdateTotalLabel(amountComboBox->getText(), String(feeSlider->getValue()));
        //[/UserComboBoxCode_amountComboBox]
    }
    else if (comboBoxThatHasChanged == currencyComboBox)
    {
        //[UserComboBoxCode_currencyComboBox] -- add your combo box handling code here..
		UpdateTotalLabel(amountComboBox->getText(), String(feeSlider->getValue()));
        //[/UserComboBoxCode_currencyComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SendComponent::SetupTransaction(const String requestHeader, const String recipient, const String amountNQT, const String feeNQT, const String msg, const bool encrypted)
{
	SetView(1);

	recipientComboBox->setText(recipient, dontSendNotification);
	amountComboBox->setText(NQT2Burst(amountNQT), dontSendNotification);
	currencyComboBox->setSelectedItemIndex(0);

	paymentLabel->setText(requestHeader, dontSendNotification);
	recipientFixedLabel->setText("Recipient: " + recipient, dontSendNotification);
	costLabel->setText(NQT2Burst(amountNQT) + " BURST", dontSendNotification);

	String feeStr;
	if (feeNQT.containsOnly("0123456789"))
	{
		feeSlider->setValue(NQT2Burst(feeNQT).getFloatValue(), sendNotification);
	}
	else
	{
		int feeSuggestIdx = 1;// normal = default
		for (int i = 0; i < feeComboBox->getNumItems(); i++)
		{
			if (feeNQT.compare(feeComboBox->getItemText(i)) == 0)
			{
				feeSuggestIdx = i;
			}
		}
		if (feeSuggestIdx == 0)
			feeSlider->setValue(cheap / 100000000., dontSendNotification);
		else if (feeSuggestIdx == 1)
			feeSlider->setValue(normal / 100000000., dontSendNotification);
		else if (feeSuggestIdx == 2)
			feeSlider->setValue(priority / 100000000., dontSendNotification);
		feeComboBox->setSelectedItemIndex(feeSuggestIdx, sendNotification);
	}
	messageTextEditor->setText("", dontSendNotification);
	fixedMessageLabel->setText(msg, dontSendNotification);

	encryptToggleButton->setEnabled(encrypted);
	encryptToggleButton->setToggleState(encrypted, dontSendNotification);

	UpdateTotalLabel(NQT2Burst(amountNQT), String(feeSlider->getValue()));

	this->notifierURL = notifierURL;

}

void SendComponent::SetRecipients(StringArray recipients)
{
	int tindex = recipientComboBox->getSelectedItemIndex();

	recipientComboBox->clear();
	for (int i = 0; i < recipients.size(); i++)
		recipientComboBox->addItem(recipients[i], i+1);

	recipientComboBox->setSelectedItemIndex(tindex);
}

void SendComponent::SetAmounts(StringArray amounts)
{
	int tindex = amountComboBox->getSelectedItemIndex();

	amountComboBox->clear();
	for (int i = 0; i < amounts.size(); i++)
		amountComboBox->addItem(amounts[i], i+1);

	amountComboBox->setSelectedItemIndex(tindex);
}

void SendComponent::SetSuggestedFees(uint64 cheap_in, uint64 normal_in, uint64 priority_in)
{
	int tindex = feeComboBox->getSelectedItemIndex();

	if (cheap_in >= normal_in)
		normal_in = cheap_in + FEE_QUANT;
	if (normal_in >= priority_in)
		priority_in = priority_in + FEE_QUANT;

	if (cheap_in != normal_in || normal_in != priority_in)
	{
		cheap = cheap_in;
		normal = normal_in;
		priority = priority_in;
	}
	else
	{ // default
		cheap = FEE_QUANT * 10;
		normal = FEE_QUANT * 30;
		priority = FEE_QUANT * 60;
	}
	feeSlider->setRange(cheap / 100000000., priority / 100000000., FEE_QUANT / 100000000.);
	feeComboBox->setSelectedItemIndex(tindex);
}

void SendComponent::SetPrice(String currency, double price)
{
	this->currency = currency;
	this->price = price;
}

void SendComponent::SetAssets(const StringArray assetIDs, const StringArray assetsNames, const StringArray assetsDescription, const StringArray assetsDecimals, const StringPairArray assetsBalances)
{
	assetWhitelist = assetIDs;
	assetWhitelistNames = assetsNames;
	assetWhitelistDescription = assetsDescription;
	assetWhitelistDecimals = assetsDescription;

	this->assetsBalances = assetsBalances;

	int idx = currencyComboBox->getSelectedItemIndex();

	currencyComboBox->clear();
	currencyComboBox->addItemList(assetWhitelistNames, 1);

	currencyComboBox->setSelectedItemIndex(idx);
}

String SendComponent::NQT2Burst(const String value)
{
	bool minus = value.startsWithChar('-');
	String neatNr(value.removeCharacters("-").paddedLeft('0', 9));
	neatNr = (neatNr.substring(0, neatNr.length() - 8) + "." + neatNr.substring(neatNr.length() - 8, neatNr.length()).trimCharactersAtEnd("0"));
	return minus ? "-" + neatNr : neatNr;
}

String SendComponent::Burst2NQT(const String value)
{
	int64 amountNQT = 0;
	String amount = value.trim().retainCharacters("0123456789.,");
	int point = amount.indexOfAnyOf(".,");
	if (point < 0)
		amountNQT = amount.retainCharacters("0123456789").getLargeIntValue() * 100000000L;
	else
	{
		amountNQT = amount.substring(0, point).getLargeIntValue() * 100000000L;
		amountNQT += amount.substring(point + 1, amount.length()).retainCharacters("0123456789").paddedRight('0', 8).substring(0, 8).getLargeIntValue();
	}
	return String(amountNQT);
}

void SendComponent::UpdateTotalLabel(const String amount, const String fee)
{
	int64 amountNQT = Burst2NQT(amount).getLargeIntValue();
	int64 feeNQT = Burst2NQT(fee).getLargeIntValue();

	String totalNQT;
	String assetStr;
	if (currencyComboBox->getSelectedItemIndex() > 0)
	{
		totalNQT = String(feeNQT);
		int decimals = assetWhitelistDecimals[currencyComboBox->getSelectedItemIndex()].getLargeIntValue();
		assetStr = String(String(amountNQT / 100000000., decimals) + " " + assetWhitelistNames[currencyComboBox->getSelectedItemIndex()] + " + ");
	}
	else totalNQT = String(amountNQT + feeNQT);

	String balance_t(NQT2Burst(totalNQT) + " BURST");
	String balance_t_ext;

	//if (amountNQT > 0)
	{
		if (currency.compare("BTC") == 0)
		{ // conversion
			uint64 balanceNQT = totalNQT.getLargeIntValue();

			// multiply priceINT by amount of BURST
			uint64 convertedSAT_NQT = /*priceSAT*/price * (balanceNQT / 100000000.);
			double convertedSAT = price * (balanceNQT / 100000000.); // convert the NQT/SAT back

			String convertedBTCstr = std::to_string(convertedSAT);
			convertedBTCstr = convertedBTCstr.upToFirstOccurrenceOf(".", true, true) + convertedBTCstr.fromFirstOccurrenceOf(".", false, true).paddedRight('0', 8).substring(0, 8);
			balance_t_ext = " (" + convertedBTCstr + " BTC)";
		}
		else if (currency.isNotEmpty() && currency.compare("BURST") != 0)
		{ // conversion
			uint64 balanceNQT = totalNQT.getLargeIntValue();

			// multiply priceINT by amount of BURST
			uint64 convertedSAT_NQT = /*priceSAT*/price * balanceNQT;
			double convertedSAT = convertedSAT_NQT / 100000000.; // convert the NQT/SAT back

			String convertedStr(convertedSAT, 2);
			balance_t_ext = (" (" + convertedStr + " " + currency + ")");
		}
	}

	totalLabel->setText("total costs: " + assetStr + balance_t + balance_t_ext, dontSendNotification);
}

void SendComponent::SendBurst()
{
	String recipient = recipientComboBox->getText().trim();
	String amount = Burst2NQT(amountComboBox->getText());
	String fee = Burst2NQT(String(feeSlider->getValue()));
	String message = fixedMessageLabel->getText() + (fixedMessageLabel->getText().isNotEmpty() ? " " : String::empty) + messageTextEditor->getText();
	if (message.length() >= 1000)
		message = message.substring(0, 999);
	bool encrypt = encryptToggleButton->getToggleState();

	if (amountComboBox->getText().compareIgnoreCase("PURGE") == 0)
	{ // max amount !
		if (currencyComboBox->getSelectedItemIndex() == 0) // subtract the fee if the purge is in Burstcoin
			amount = String(assetsBalances["0"].getLargeIntValue() - fee.getLargeIntValue());

		if (NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "[PURGE]\nEmpty the wallet balance?\n" + NQT2Burst(amount) + " " + assetWhitelistNames[currencyComboBox->getSelectedItemIndex()] + " + tx fee") == false)
			return;
	}

	if (currencyComboBox->getSelectedItemIndex() > 0)
	{
		if (couponToggleButton->getToggleState())
		{
			NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Coupons not implemented yet for Assets !");
		}
		else
		{
		//	listeners.call(&InterfaceListener::SendHotWalletLicense, recipient);
			const String assetID = assetWhitelist[currencyComboBox->getSelectedItemIndex()];
			listeners.call(&InterfaceListener::SendAsset, recipient, assetID, amount, fee, message, encrypt);
		}
	}
	else
	{

		if (couponToggleButton->getToggleState())
		{
			/*if (passwordTextEditor->getText().isEmpty())
			{
				if (NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Use a empty coupon password ?!") == false)
					return;
			}*/
			String deadline((int)minSlider->getValue());
			InterfaceListener::couponArgs args;
			args.recipient = recipient;
			args.amountNQT = amount;
			args.feeNQT = fee;
			args.deadline = deadline;
			args.msg = message;
			args.password = passwordTextEditor->getText();
			args.encrypted = encrypt;

			listeners.call(&InterfaceListener::MakeCoupon, args);// recipient, amount, fee, deadline, message, passwordTextEditor->getText(), encrypt);
		}
		else
		{
			listeners.call(&InterfaceListener::SendBurstcoin, recipient, amount, fee, message, encrypt);
		}

		SetView(0);
	}
}

void SendComponent::SetView(int v)
{
	if (v == 0)
	{// reset view
		bool resetAll = fixedMessageLabel->getText().isNotEmpty() || paymentLabel->getText().isNotEmpty();
		fixedMessageLabel->setText("", dontSendNotification);
		paymentLabel->setText("", dontSendNotification);

		if (resetAll)
		{
			recipientComboBox->setText("", dontSendNotification);
			amountComboBox->setText("", dontSendNotification);
			messageTextEditor->setText("", dontSendNotification);
			encryptToggleButton->setToggleState(false, dontSendNotification);
			totalLabel->setText("", dontSendNotification);

			recipientFixedLabel->setText("", dontSendNotification);
			costLabel->setText("", dontSendNotification);
			notifierURL = String::empty;
		}
	}

	recipientLabel->setVisible(v == 0);
	recipientComboBox->setVisible(v == 0);

	amountLabel->setVisible(v == 0);
	amountComboBox->setVisible(v == 0);
	currencyComboBox->setVisible(v == 0);

	fixedMessageLabel->setVisible(v == 1);
	paymentLabel->setVisible(v == 1);
	recipientFixedLabel->setVisible(v == 1);
	costLabel->setVisible(v == 1);
	cancelButton->setVisible(v == 1);

	encryptToggleButton->setEnabled(true);

	repaint();
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SendComponent" componentName=""
                 parentClasses="public Component, public SendComponentListener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="fff0f0f0"/>
  <LABEL name="fixedMessageLabel" id="589ae50bad9367bf" memberName="fixedMessageLabel"
         virtualName="" explicitFocusOrder="0" pos="376 176 288 48" edTextCol="ff000000"
         edBkgCol="0" labelText="fixed message" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="totalLabel" id="5312c992397fcb41" memberName="totalLabel"
         virtualName="" explicitFocusOrder="0" pos="200 120 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0. BURST" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="18"
         bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="sendTextButton" id="6294916aabe7c7c6" memberName="sendTextButton"
              virtualName="" explicitFocusOrder="0" pos="328 368 328 24" bgColOff="ff77b517"
              bgColOn="ff77b517" buttonText="send" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <SLIDER name="feeSlider" id="24c3eaff4e70f1dd" memberName="feeSlider"
          virtualName="" explicitFocusOrder="0" pos="104 72 136 24" tooltip="the fee that goes to the miner that adds your transaction to the blockchain"
          bkgcol="595959" thumbcol="ff77b517" trackcol="ffffffff" rotarysliderfill="ff77b517"
          rotaryslideroutline="ff000000" textboxhighlight="ff77b517" min="0.0073499999999999997627"
          max="73.5" int="0.0073499999999999997627" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <TEXTEDITOR name="messageTextEditor" id="91e625efb4dfd505" memberName="messageTextEditor"
              virtualName="" explicitFocusOrder="0" pos="101 205 248 59" initialText=""
              multiline="1" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="encryptToggleButton" id="e12b5cb5c89d558b" memberName="encryptToggleButton"
                virtualName="" explicitFocusOrder="0" pos="16 264 80 24" tooltip="encrypt to make the message only visible to the recipient"
                buttonText="encrypt" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <LABEL name="messageLabel" id="27525753646d75a1" memberName="messageLabel"
         virtualName="" explicitFocusOrder="0" pos="13 205 78 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Message" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <LABEL name="recipientLabel" id="f4bd535060203a98" memberName="recipientLabel"
         virtualName="" explicitFocusOrder="0" pos="16 8 78 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Recipient" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <LABEL name="amountLabel" id="6df1b7e24a75bc15" memberName="amountLabel"
         virtualName="" explicitFocusOrder="0" pos="24 40 71 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Amount" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <LABEL name="feeLabel" id="eb8589e135b07e36" memberName="feeLabel" virtualName=""
         explicitFocusOrder="0" pos="15 72 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="+ Fee in Burstcoin" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <COMBOBOX name="feeComboBox" id="de6333299e5ba6b6" memberName="feeComboBox"
            virtualName="" explicitFocusOrder="0" pos="248 72 96 24" tooltip="the suggested fees that goes to the miner that adds your transaction to the blockchain."
            editable="0" layout="33" items="cheap&#10;standard&#10;priority"
            textWhenNonSelected="standard" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="recipientComboBox" id="ae82dfdeae76eb8e" memberName="recipientComboBox"
            virtualName="" explicitFocusOrder="0" pos="136 8 150 24" editable="1"
            layout="33" items="@CurbShifter" textWhenNonSelected="BURST address, alias, numerical or public key"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="amountComboBox" id="915c8f63738ec6f2" memberName="amountComboBox"
            virtualName="" explicitFocusOrder="0" pos="136 40 150 24" editable="1"
            layout="34" items="0.25&#10;0.5&#10;1.0&#10;10&#10;100&#10;1000"
            textWhenNonSelected="0." textWhenNoItems="(no choices)"/>
  <LABEL name="paymentLabel" id="ef391b61d67d67f5" memberName="paymentLabel"
         virtualName="" explicitFocusOrder="0" pos="376 24 288 48" edTextCol="ff000000"
         edBkgCol="0" labelText="Payment request" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="0" italic="0" justification="33"/>
  <LABEL name="costLabel" id="aebadc24726ea68e" memberName="costLabel"
         virtualName="" explicitFocusOrder="0" pos="376 112 288 56" edTextCol="ff000000"
         edBkgCol="0" labelText="Costs" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="16"
         bold="0" italic="0" justification="34"/>
  <TEXTBUTTON name="cancelButton" id="fff7bbb1ed04a85f" memberName="cancelButton"
              virtualName="" explicitFocusOrder="0" pos="24 368 296 24" bgColOff="ffc85c5c"
              bgColOn="ff77b517" buttonText="cancel" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="recipientFixedLabel" id="7e9074d7cd45f10f" memberName="recipientFixedLabel"
         virtualName="" explicitFocusOrder="0" pos="376 80 288 24" edTextCol="ff000000"
         edBkgCol="0" labelText="recipient" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="passwordTextEditor" id="d719d6ed5193589b" memberName="passwordTextEditor"
              virtualName="" explicitFocusOrder="0" pos="120 296 296 24" tooltip="the new coupon password"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="1" caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="couponToggleButton" id="cbcb6a7303cb42b3" memberName="couponToggleButton"
                virtualName="" explicitFocusOrder="0" pos="16 296 96 24" tooltip="send the transaction as a coupon to be claimed later"
                buttonText="as coupon" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <SLIDER name="minSlider" id="1d49eed16b20c131" memberName="minSlider"
          virtualName="" explicitFocusOrder="0" pos="424 296 80 24" tooltip="the minutes when this coupon expires since it's made"
          min="8" max="1440" int="4" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="minLabel" id="6689759ad0e9668d" memberName="minLabel" virtualName=""
         explicitFocusOrder="0" pos="512 296 118 24" tooltip="the minutes when this coupon expires since it's made"
         edTextCol="ff000000" edBkgCol="0" labelText="min" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="currencyComboBox" id="7b75468f9920ed54" memberName="currencyComboBox"
            virtualName="" explicitFocusOrder="0" pos="288 40 72 24" tooltip="Use Burst or whitelisted assets"
            editable="0" layout="33" items="BURST" textWhenNonSelected="BURST"
            textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
