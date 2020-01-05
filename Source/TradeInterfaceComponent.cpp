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

#include "TradeInterfaceComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TradeInterfaceComponent::TradeInterfaceComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (nameTextEditor = new TextEditor ("nameTextEditor"));
    nameTextEditor->setTooltip (TRANS("The name of the asset is NOT unique ! Other assets can have the same name. However each asset gets a unique numbered ID. Like all settings of this new asset, this setting cannot be changed !"));
    nameTextEditor->setMultiLine (false);
    nameTextEditor->setReturnKeyStartsNewLine (false);
    nameTextEditor->setReadOnly (false);
    nameTextEditor->setScrollbarsShown (true);
    nameTextEditor->setCaretVisible (true);
    nameTextEditor->setPopupMenuEnabled (true);
    nameTextEditor->setColour (TextEditor::backgroundColourId, Colour (0x54ffffff));
    nameTextEditor->setColour (TextEditor::shadowColourId, Colour (0x1a000000));
    nameTextEditor->setText (String());

    addAndMakeVisible (descriptionTextEditor = new TextEditor ("descriptionTextEditor"));
    descriptionTextEditor->setTooltip (TRANS("The description text of the asset. Provide info, adding a web link is recommened. Also make sure people can contact you. Like all settings of this new asset, this setting cannot be changed !"));
    descriptionTextEditor->setMultiLine (true);
    descriptionTextEditor->setReturnKeyStartsNewLine (false);
    descriptionTextEditor->setReadOnly (false);
    descriptionTextEditor->setScrollbarsShown (true);
    descriptionTextEditor->setCaretVisible (true);
    descriptionTextEditor->setPopupMenuEnabled (true);
    descriptionTextEditor->setColour (TextEditor::backgroundColourId, Colour (0x66ffffff));
    descriptionTextEditor->setText (String());

    addAndMakeVisible (buyButton = new TextButton ("buyButton"));
    buyButton->setTooltip (TRANS("create buy order (+ tx fee)"));
    buyButton->setButtonText (TRANS("buy"));
    buyButton->addListener (this);
    buyButton->setColour (TextButton::buttonColourId, Colour (0xff77b517));
    buyButton->setColour (TextButton::buttonOnColourId, Colour (0xff98ea1a));

    addAndMakeVisible (sellButton = new TextButton ("sellButton"));
    sellButton->setTooltip (TRANS("create sell order (+ tx fee)"));
    sellButton->setButtonText (TRANS("sell"));
    sellButton->addListener (this);
    sellButton->setColour (TextButton::buttonColourId, Colour (0xffe13a3a));
    sellButton->setColour (TextButton::buttonOnColourId, Colour (0xff9a2626));

    addAndMakeVisible (sellAmountComboBox = new ComboBox ("sellAmountComboBox"));
    sellAmountComboBox->setTooltip (TRANS("quantity"));
    sellAmountComboBox->setEditableText (false);
    sellAmountComboBox->setJustificationType (Justification::centredLeft);
    sellAmountComboBox->setTextWhenNothingSelected (TRANS("1"));
    sellAmountComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    sellAmountComboBox->addListener (this);

    addAndMakeVisible (buyAmountComboBox = new ComboBox ("buyAmountComboBox"));
    buyAmountComboBox->setTooltip (TRANS("quantity"));
    buyAmountComboBox->setEditableText (false);
    buyAmountComboBox->setJustificationType (Justification::centredLeft);
    buyAmountComboBox->setTextWhenNothingSelected (TRANS("1"));
    buyAmountComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    buyAmountComboBox->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("price")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("price")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (balanceNumLabel = new Label ("balanceNumLabel",
                                                    TRANS("0.000")));
    balanceNumLabel->setFont (Font (40.00f, Font::plain));
    balanceNumLabel->setJustificationType (Justification::bottomRight);
    balanceNumLabel->setEditable (false, false, false);
    balanceNumLabel->setColour (Label::textColourId, Colour (0xff1d5481));
    balanceNumLabel->setColour (TextEditor::textColourId, Colour (0xff1d5481));
    balanceNumLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sellPriceComboBox = new ComboBox ("sellPriceComboBox"));
    sellPriceComboBox->setTooltip (TRANS("the sell price in Burstcoin for each asset token"));
    sellPriceComboBox->setEditableText (false);
    sellPriceComboBox->setJustificationType (Justification::centredLeft);
    sellPriceComboBox->setTextWhenNothingSelected (TRANS("0.00000000"));
    sellPriceComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    sellPriceComboBox->addListener (this);

    addAndMakeVisible (buyPriceComboBox = new ComboBox ("buyPriceComboBox"));
    buyPriceComboBox->setTooltip (TRANS("the buy price in Burstcoin for each asset token"));
    buyPriceComboBox->setEditableText (false);
    buyPriceComboBox->setJustificationType (Justification::centredLeft);
    buyPriceComboBox->setTextWhenNothingSelected (TRANS("0.00000000"));
    buyPriceComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    buyPriceComboBox->addListener (this);

    addAndMakeVisible (decimalsSlider = new Slider ("decimalsSlider"));
    decimalsSlider->setTooltip (TRANS("how far devisable each token is. (ie. 2 would give 0.01 as smallest unit)\n"
    "Like all settings of this new asset, this setting cannot be changed !"));
    decimalsSlider->setRange (0, 8, 1);
    decimalsSlider->setSliderStyle (Slider::IncDecButtons);
    decimalsSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    decimalsSlider->addListener (this);

    addAndMakeVisible (decimalslabel = new Label ("decimalslabel",
                                                  TRANS("decimals")));
    decimalslabel->setTooltip (TRANS("how far devisable each token is. (ie. 2 would be 0.01)"));
    decimalslabel->setFont (Font (15.00f, Font::plain));
    decimalslabel->setJustificationType (Justification::centredRight);
    decimalslabel->setEditable (false, false, false);
    decimalslabel->setColour (TextEditor::textColourId, Colours::black);
    decimalslabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (quantityLabel = new Label ("quantityLabel",
                                                  TRANS("quantity")));
    quantityLabel->setTooltip (TRANS("the total amount of tokens this asset has"));
    quantityLabel->setFont (Font (15.00f, Font::plain));
    quantityLabel->setJustificationType (Justification::centredRight);
    quantityLabel->setEditable (false, false, false);
    quantityLabel->setColour (TextEditor::textColourId, Colours::black);
    quantityLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (createButton = new TextButton ("createButton"));
    createButton->setTooltip (TRANS("Once an asset is created it cannot be changed ! (creation fee is 1000 burst)"));
    createButton->setButtonText (TRANS("create asset (cost 1000 BURST)"));
    createButton->addListener (this);
    createButton->setColour (TextButton::buttonColourId, Colour (0xfff0a713));
    createButton->setColour (TextButton::buttonOnColourId, Colour (0xffc48b18));

    addAndMakeVisible (assetMenuButton = new TextButton ("_assetMenuButton"));
    assetMenuButton->setTooltip (TRANS("asset details menu"));
    assetMenuButton->setButtonText (TRANS("Asset ID"));
    assetMenuButton->addListener (this);
    assetMenuButton->setColour (TextButton::buttonColourId, Colour (0x00bbbbff));

    addAndMakeVisible (quantityComboBox = new ComboBox ("quantityComboBox"));
    quantityComboBox->setTooltip (TRANS("the total amount of tokens this asset has. without any decimals. Like all settings of this new asset, this setting cannot be changed !"));
    quantityComboBox->setEditableText (true);
    quantityComboBox->setJustificationType (Justification::centredLeft);
    quantityComboBox->setTextWhenNothingSelected (TRANS("100"));
    quantityComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    quantityComboBox->addItem (TRANS("1"), 1);
    quantityComboBox->addItem (TRANS("100"), 2);
    quantityComboBox->addItem (TRANS("10,000"), 3);
    quantityComboBox->addItem (TRANS("100,000,000,000,000,000"), 4);
    quantityComboBox->addListener (this);

    addAndMakeVisible (buyOrderTableComponent = new OrderTableComponent (1));
    buyOrderTableComponent->setName ("buyOrderTableComponent");

    addAndMakeVisible (sellOrderTableComponent = new OrderTableComponent());
    sellOrderTableComponent->setName ("sellOrderTableComponent");

    addAndMakeVisible (totalBuyLabel = new Label ("totalBuyLabel",
                                                  TRANS("total")));
    totalBuyLabel->setFont (Font (15.00f, Font::plain));
    totalBuyLabel->setJustificationType (Justification::centredLeft);
    totalBuyLabel->setEditable (false, false, false);
    totalBuyLabel->setColour (TextEditor::textColourId, Colours::black);
    totalBuyLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (totalSellLabel = new Label ("totalSellLabel",
                                                   TRANS("total")));
    totalSellLabel->setFont (Font (15.00f, Font::plain));
    totalSellLabel->setJustificationType (Justification::centredLeft);
    totalSellLabel->setEditable (false, false, false);
    totalSellLabel->setColour (TextEditor::textColourId, Colours::black);
    totalSellLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nameLabel = new Label ("nameLabel",
                                              TRANS("name")));
    nameLabel->setFont (Font (22.00f, Font::plain));
    nameLabel->setJustificationType (Justification::topLeft);
    nameLabel->setEditable (false, false, false);
    nameLabel->setColour (Label::textColourId, Colour (0xff323232));
    nameLabel->setColour (TextEditor::textColourId, Colours::black);
    nameLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (descriptionStaticTextEditor = new TextEditor ("descriptionStaticTextEditor"));
    descriptionStaticTextEditor->setMultiLine (true);
    descriptionStaticTextEditor->setReturnKeyStartsNewLine (false);
    descriptionStaticTextEditor->setReadOnly (true);
    descriptionStaticTextEditor->setScrollbarsShown (true);
    descriptionStaticTextEditor->setCaretVisible (false);
    descriptionStaticTextEditor->setPopupMenuEnabled (true);
    descriptionStaticTextEditor->setColour (TextEditor::textColourId, Colour (0xff272727));
    descriptionStaticTextEditor->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));
    descriptionStaticTextEditor->setColour (TextEditor::highlightColourId, Colour (0xff77b517));
    descriptionStaticTextEditor->setColour (TextEditor::outlineColourId, Colour (0x00000000));
    descriptionStaticTextEditor->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    descriptionStaticTextEditor->setText (TRANS("description"));

    addAndMakeVisible (balanceNumLabel2 = new Label ("balanceNumLabel",
                                                     TRANS("0.000")));
    balanceNumLabel2->setFont (Font (22.00f, Font::plain));
    balanceNumLabel2->setJustificationType (Justification::centredLeft);
    balanceNumLabel2->setEditable (false, false, false);
    balanceNumLabel2->setColour (Label::textColourId, Colour (0xff1d5481));
    balanceNumLabel2->setColour (TextEditor::textColourId, Colour (0xff1d5481));
    balanceNumLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (buyTotalComboBox = new ComboBox ("buyTotalComboBox"));
    buyTotalComboBox->setTooltip (TRANS("the total sell price in Burstcoin"));
    buyTotalComboBox->setEditableText (false);
    buyTotalComboBox->setJustificationType (Justification::centredLeft);
    buyTotalComboBox->setTextWhenNothingSelected (TRANS("0.00000000"));
    buyTotalComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    buyTotalComboBox->addListener (this);

    addAndMakeVisible (sellTotalComboBox = new ComboBox ("sellTotalComboBox"));
    sellTotalComboBox->setTooltip (TRANS("the total buy price in Burstcoin"));
    sellTotalComboBox->setEditableText (false);
    sellTotalComboBox->setJustificationType (Justification::centredLeft);
    sellTotalComboBox->setTextWhenNothingSelected (TRANS("0.00000000"));
    sellTotalComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    sellTotalComboBox->addListener (this);

    addAndMakeVisible (quantityLabel2 = new Label (String(),
                                                   TRANS("quantity")));
    quantityLabel2->setFont (Font (15.00f, Font::plain));
    quantityLabel2->setJustificationType (Justification::centredLeft);
    quantityLabel2->setEditable (false, false, false);
    quantityLabel2->setColour (TextEditor::textColourId, Colours::black);
    quantityLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (quantityLabel3 = new Label (String(),
                                                   TRANS("quantity")));
    quantityLabel3->setFont (Font (15.00f, Font::plain));
    quantityLabel3->setJustificationType (Justification::centredLeft);
    quantityLabel3->setEditable (false, false, false);
    quantityLabel3->setColour (TextEditor::textColourId, Colours::black);
    quantityLabel3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (whitelistAssetComboBox = new ComboBox ("whitelistAssetComboBox"));
    whitelistAssetComboBox->setEditableText (true);
    whitelistAssetComboBox->setJustificationType (Justification::centredLeft);
    whitelistAssetComboBox->setTextWhenNothingSelected (TRANS("Asset ID"));
    whitelistAssetComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    whitelistAssetComboBox->addListener (this);

    addAndMakeVisible (whitelistAddTextButton = new TextButton ("whitelistAddTextButton"));
    whitelistAddTextButton->setButtonText (TRANS("add"));
    whitelistAddTextButton->addListener (this);
    whitelistAddTextButton->setColour (TextButton::buttonColourId, Colour (0xff77b517));
    whitelistAddTextButton->setColour (TextButton::buttonOnColourId, Colour (0xff98ea1a));

    addAndMakeVisible (whitelistRemoveTextButton = new TextButton ("whitelistRemoveTextButton"));
    whitelistRemoveTextButton->setButtonText (TRANS("remove"));
    whitelistRemoveTextButton->addListener (this);
    whitelistRemoveTextButton->setColour (TextButton::buttonColourId, Colour (0xffe13a3a));
    whitelistRemoveTextButton->setColour (TextButton::buttonOnColourId, Colours::brown);

    addAndMakeVisible (whitelistLabel = new Label ("whitelistLabel",
                                                   TRANS("Whitelist asset")));
    whitelistLabel->setFont (Font (15.00f, Font::plain));
    whitelistLabel->setJustificationType (Justification::centredLeft);
    whitelistLabel->setEditable (false, false, false);
    whitelistLabel->setColour (TextEditor::textColourId, Colours::black);
    whitelistLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (createLabel = new Label ("createLabel",
                                                TRANS("Create new asset")));
    createLabel->setFont (Font (15.00f, Font::plain));
    createLabel->setJustificationType (Justification::centredLeft);
    createLabel->setEditable (false, false, false);
    createLabel->setColour (TextEditor::textColourId, Colours::black);
    createLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    drawable1 = Drawable::createFromImageData (bursticonblue_svg, bursticonblue_svgSize);

    //[UserPreSize]
	nameTextEditor->setTextToShowWhenEmpty("The new asset name (not unique)", Colours::lightgrey);
	descriptionTextEditor->setTextToShowWhenEmpty("Asset description. Adding website url recommened.", Colours::lightgrey);
	descriptionTextEditor->setInputRestrictions(1000);

	buyOrderTableComponent->addTradeComponentListener(this);
	sellOrderTableComponent->addTradeComponentListener(this);

	balanceNumLabel->setColour(Label::textColourId, Colour(0xff00579d));
	balanceNumLabel->setColour(TextEditor::textColourId, Colour(0xff00579d));
	assetMenuButton->setColour(TextButton::textColourOnId, Colour(0xff00579d));
	assetMenuButton->setColour(TextButton::textColourOffId, Colour(0xff00579d));
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	nameTextEditor->setVisible(false);
	descriptionTextEditor->setVisible(false);
	decimalslabel->setVisible(false);
	decimalsSlider->setVisible(false);
	quantityLabel->setVisible(false);
	quantityComboBox->setVisible(false);
	createButton->setVisible(false);
	balanceNumLabel->setVisible(false);
	balanceNumLabel2->setVisible(false);
	assetMenuButton->setVisible(false);
	nameLabel->setVisible(false);
	descriptionStaticTextEditor->setVisible(false);
	sellAmountComboBox->setVisible(false);
	buyAmountComboBox->setVisible(false);
	label2->setVisible(false);
	label3->setVisible(false);
	sellPriceComboBox->setVisible(false);
	buyPriceComboBox->setVisible(false);
	totalBuyLabel->setVisible(false);
	totalSellLabel->setVisible(false);
	buyButton->setVisible(false);
	sellButton->setVisible(false);
	buyOrderTableComponent->setVisible(false);
	sellOrderTableComponent->setVisible(false);
	whitelistAssetComboBox->setVisible(false);
	whitelistAddTextButton->setVisible(false);
	whitelistRemoveTextButton->setVisible(false);
	whitelistLabel->setVisible(false);
	createLabel->setVisible(false);
	quantityLabel2->setVisible(false);
	quantityLabel3->setVisible(false);
	buyTotalComboBox->setVisible(false);
	sellTotalComboBox->setVisible(false);

	buyButton->setEnabled(false);
	sellButton->setEnabled(false);

	StringArray whitelistedAssets = StringArray::fromTokens(getAppProperties().getUserSettings()->getValue("AssetWhitelist"), ",", "");
	whitelistAssetComboBox->addItemList(whitelistedAssets, 1);
    //[/Constructor]
}

TradeInterfaceComponent::~TradeInterfaceComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    nameTextEditor = nullptr;
    descriptionTextEditor = nullptr;
    buyButton = nullptr;
    sellButton = nullptr;
    sellAmountComboBox = nullptr;
    buyAmountComboBox = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    balanceNumLabel = nullptr;
    sellPriceComboBox = nullptr;
    buyPriceComboBox = nullptr;
    decimalsSlider = nullptr;
    decimalslabel = nullptr;
    quantityLabel = nullptr;
    createButton = nullptr;
    assetMenuButton = nullptr;
    quantityComboBox = nullptr;
    buyOrderTableComponent = nullptr;
    sellOrderTableComponent = nullptr;
    totalBuyLabel = nullptr;
    totalSellLabel = nullptr;
    nameLabel = nullptr;
    descriptionStaticTextEditor = nullptr;
    balanceNumLabel2 = nullptr;
    buyTotalComboBox = nullptr;
    sellTotalComboBox = nullptr;
    quantityLabel2 = nullptr;
    quantityLabel3 = nullptr;
    whitelistAssetComboBox = nullptr;
    whitelistAddTextButton = nullptr;
    whitelistRemoveTextButton = nullptr;
    whitelistLabel = nullptr;
    createLabel = nullptr;
    drawable1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TradeInterfaceComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	/*/
    //[/UserPrePaint]

    g.fillAll (Colour (0xffeef1f4));

    g.setGradientFill (ColourGradient (Colour (0xff8b8b8b),
                                       0.0f, 0.0f,
                                       Colour (0xffe0e0e0),
                                       0.0f, 200.0f,
                                       false));
    g.fillRect (0, 4, 300, 700);

    g.setColour (Colours::black);
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, Rectangle<float> (604, 532, 28, 32),
                               RectanglePlacement::centred, 1.000f);

    //[UserPaint] Add your own custom painting code here..
	*/
	g.setGradientFill(ColourGradient(Colour(0xffe9e9e9),
		0.0f, 0.0f,
		Colour(0xffe0e0e0),
		0.0f, 200.0f,
		false));
	g.fillRect(0, 0, getWidth(), getHeight());

	if (asset.assetID.isNotEmpty())
	{
		g.setColour(Colours::whitesmoke);
		g.fillRoundedRectangle(50, 50, getWidth() - 100, 250, 5.);

		g.setColour(Colours::white);
		g.fillRoundedRectangle(50, 50, getWidth() - 100, 100, 5.);

		if (asset.assetID.getLargeIntValue() > 0)
		{
			g.setColour(Colours::black);
			jassert(drawable1 != 0);
			if (drawable1 != 0)
				drawable1->drawWithin(g, sellPriceComboBox->getBounds().translated(sellPriceComboBox->getWidth(), 0).withWidth(sellPriceComboBox->getHeight()).reduced(2).toFloat(), RectanglePlacement::centred, 1.000f);
			if (drawable1 != 0)
				drawable1->drawWithin(g, buyPriceComboBox->getBounds().translated(buyPriceComboBox->getWidth(), 0).withWidth(buyPriceComboBox->getHeight()).reduced(2).toFloat(), RectanglePlacement::centred, 1.000f);

			if (drawable1 != 0)
				drawable1->drawWithin(g, sellTotalComboBox->getBounds().translated(sellTotalComboBox->getWidth(), 0).withWidth(sellTotalComboBox->getHeight()).reduced(2).toFloat(), RectanglePlacement::centred, 1.000f);
			if (drawable1 != 0)
				drawable1->drawWithin(g, buyTotalComboBox->getBounds().translated(buyTotalComboBox->getWidth(), 0).withWidth(buyTotalComboBox->getHeight()).reduced(2).toFloat(), RectanglePlacement::centred, 1.000f);
		}
	}
	else
	{
		g.setColour(Colours::white);
		g.fillRoundedRectangle(50, 50, getWidth() - 100, 110, 5.);
		g.fillRoundedRectangle(50, 50 + 120, getWidth() - 100, 340, 5.);
	}

	if (asset.assetID.compare("0") == 0)
	{
		int dim = jmin<float>(300, getHeight() - 450 + 50);
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

void TradeInterfaceComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	/*
    //[/UserPreResize]

    nameTextEditor->setBounds (448, 160, 376, 24);
    descriptionTextEditor->setBounds (448, 192, 376, 112);
    buyButton->setBounds (456, 595, 104, 24);
    sellButton->setBounds (680, 597, 112, 24);
    sellAmountComboBox->setBounds (720, 504, 104, 24);
    buyAmountComboBox->setBounds (488, 504, 104, 24);
    label2->setBounds (448, 536, 32, 24);
    label3->setBounds (680, 533, 32, 24);
    balanceNumLabel->setBounds (64, 8, 144, 40);
    sellPriceComboBox->setBounds (712, 533, 112, 24);
    buyPriceComboBox->setBounds (480, 536, 112, 24);
    decimalsSlider->setBounds (560, 352, 144, 24);
    decimalslabel->setBounds (456, 352, 88, 24);
    quantityLabel->setBounds (456, 320, 88, 24);
    createButton->setBounds (456, 384, 374, 32);
    assetMenuButton->setBounds (8, 40, 152, 40);
    quantityComboBox->setBounds (560, 320, 144, 24);
    buyOrderTableComponent->setBounds (448, 632, 152, 224);
    sellOrderTableComponent->setBounds (680, 632, 152, 224);
    totalBuyLabel->setBounds (448, 568, 40, 24);
    totalSellLabel->setBounds (680, 568, 40, 24);
    nameLabel->setBounds (8, 88, 88, 24);
    descriptionStaticTextEditor->setBounds (8, 120, 376, 112);
    balanceNumLabel2->setBounds (216, 8, 208, 40);
    buyTotalComboBox->setBounds (496, 568, 112, 24);
    sellTotalComboBox->setBounds (720, 568, 112, 24);
    quantityLabel2->setBounds (672, 504, 40, 24);
    quantityLabel3->setBounds (440, 504, 40, 24);
    whitelistAssetComboBox->setBounds (448, 48, 150, 24);
    whitelistAddTextButton->setBounds (608, 48, 72, 24);
    whitelistRemoveTextButton->setBounds (688, 48, 72, 24);
    whitelistLabel->setBounds (448, 16, 368, 24);
    createLabel->setBounds (448, 128, 376, 24);
    //[UserResized] Add your own custom resize handling here..
	*/

	int pad = 70;
	int posY = pad;
	int w = (getWidth() - (pad * 2));
	int rowH = 30;

	balanceNumLabel->setBounds(pad, posY, w / 3 * 2, rowH + 20);
	balanceNumLabel2->setBounds(pad + (w / 3 * 2) - 10, posY, w / 3, rowH + 20);
	posY += rowH + 20;

	int posY2 = pad - 10;

	// editors
	whitelistLabel->setBounds(pad, posY2, w, rowH);
	posY2 += rowH + 10;
	whitelistAssetComboBox->setBounds(pad, posY2, w - 160, rowH);
	whitelistAddTextButton->setBounds(pad + w - 160, posY2, 80, rowH);
	whitelistRemoveTextButton->setBounds(pad + w - 80, posY2, 80, rowH);
	posY2 += rowH + 30 + 20;

	createLabel->setBounds(pad, posY2, w, rowH);
	posY2 += rowH + 10;
	nameTextEditor->setBounds(pad, posY2, w, rowH);
	posY2 += 30 + 10;
	quantityLabel->setBounds(pad, posY2, 100, rowH);
	quantityComboBox->setBounds(pad + 100, posY2, w - 200, rowH);
	posY2 += rowH + 10;
	decimalslabel->setBounds(pad, posY2, 100, rowH);
	decimalsSlider->setBounds(pad + 100, posY2, 100, rowH);
	posY2 += rowH + 10;
	descriptionTextEditor->setBounds(pad, posY2, w, 100);
	posY2 += 100 + 20;
	createButton->setBounds(pad, posY2, w, rowH);

	// static
	nameLabel->setBounds(pad + (w / 3*2), posY, w / 3, rowH + 20);
	posY += 30 + 10;
	assetMenuButton->setBounds(pad, posY, w, rowH);
	posY += 30 + 10;
	descriptionStaticTextEditor->setBounds(pad, posY, w, 100);
	posY += 100 + 20;

	const int gap = 50;
	const int rowH2 = 24;
	const int forW = 70;
	pad = 40;
	w = (getWidth() - (pad * 2));

	quantityLabel2->setBounds(pad, posY, forW, rowH2);
	quantityLabel3->setBounds(pad + ((w - gap) / 2) + gap, posY, forW, rowH2);
	buyAmountComboBox->setBounds(pad + forW, posY, ((w - gap) / 2) - forW, rowH2);
	sellAmountComboBox->setBounds(pad + ((w - gap) / 2) + gap + forW, posY, ((w - gap) / 2) - forW, rowH2);
//	buyAmountComboBox->setBounds(pad, posY, (w - gap) / 2, rowH2);
//	sellAmountComboBox->setBounds(pad + ((w - gap) / 2) + gap, posY, (w - gap) / 2, rowH2);
	posY += rowH2 + 2;
	label2->setBounds(pad, posY, forW, rowH2);
	label3->setBounds(pad + ((w - gap) / 2) + gap, posY, forW, rowH2);
	buyPriceComboBox->setBounds(pad + forW, posY, ((w - gap) / 2) - forW, rowH2);
	sellPriceComboBox->setBounds(pad + ((w - gap) / 2) + gap + forW, posY, ((w - gap) / 2) - forW, rowH2);
	posY += rowH2 + 2;

	/*totalBuyLabel->setBounds(pad, posY, forW, rowH2);
	buyTotalComboBox->setBounds(pad + 50, posY, ((w - gap) / 2) - 50, rowH2);
	totalSellLabel->setBounds(pad + ((w - gap) / 2) + gap, posY, ((w - gap) / 2), rowH2);
	sellTotalComboBox->setBounds(pad + ((w - gap) / 2) + gap, posY, ((w - gap) / 2), rowH2);*/
	totalBuyLabel->setBounds(pad, posY, forW, rowH2);
	totalSellLabel->setBounds(pad + ((w - gap) / 2) + gap, posY, forW, rowH2);
	buyTotalComboBox->setBounds(pad + forW, posY, ((w - gap) / 2) - forW, rowH2);
	sellTotalComboBox->setBounds(pad + ((w - gap) / 2) + gap + forW, posY, ((w - gap) / 2) - forW, rowH2);


	posY += rowH2 + 2;
	buyButton->setBounds(pad, posY, ((w - gap) / 2), rowH2);
	sellButton->setBounds(pad + ((w - gap) / 2) + gap, posY, ((w - gap) / 2), rowH2);
	posY += rowH2 + 5;
	buyOrderTableComponent->setBounds(pad, posY, ((w - gap) / 2), getHeight() - posY);
	sellOrderTableComponent->setBounds(pad + ((w - gap) / 2) + gap, posY, ((w - gap) / 2), getHeight() - posY);

    //[/UserResized]
}

void TradeInterfaceComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == buyButton)
    {
        //[UserButtonCode_buyButton] -- add your button handler code here..
		uint64 quantityQNT = toQT(buyAmountComboBox->getText(), String(asset.decimals));
		uint64 priceNQT = toQT(buyPriceComboBox->getText(), String(8 - asset.decimals)); // max decimals of the price is the 8 decimals of burst minus the decimals of the asset

		if (NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, 
			"Place bid order?\nbuy " + 
			NQT2Burst(String(quantityQNT), String(asset.decimals)) + " " + asset.name + "\nfor " +
			NQT2Burst(String(priceNQT), "8") + " Burst each + standard transaction fee"))
			tradeComponentListeners.call(&TradeComponentListener::PlaceBidOrder, asset.assetID, (quantityQNT), (priceNQT));
        //[/UserButtonCode_buyButton]
    }
    else if (buttonThatWasClicked == sellButton)
    {
        //[UserButtonCode_sellButton] -- add your button handler code here..
		uint64 quantityQNT = toQT(sellAmountComboBox->getText(), String(asset.decimals));
		uint64 priceNQT = toQT(sellPriceComboBox->getText(), String(8 - asset.decimals)); // max decimals of the price is the 8 decimals of burst minus the decimals of the asset

		if (NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, 
			"Place ask order?\nsell " + 
			NQT2Burst(String(quantityQNT), String(asset.decimals)) + " " + asset.name + "\nfor " +
			NQT2Burst(String(priceNQT), "8") + " Burst each + standard transaction fee"))
			tradeComponentListeners.call(&TradeComponentListener::PlaceAskOrder, asset.assetID, (quantityQNT), (priceNQT));
        //[/UserButtonCode_sellButton]
    }
    else if (buttonThatWasClicked == createButton)
    {
        //[UserButtonCode_createButton] -- add your button handler code here..
		String name = nameTextEditor->getText();
		String description = descriptionTextEditor->getText();
		uint64 decimals = decimalsSlider->getValue();
		uint64 quantityQNT = toQT(quantityComboBox->getText().retainCharacters("0123456789"), String(decimals));

		String totalStr = NQT2Burst(String(quantityQNT), String(decimals));

		if (userBalanceNQT < 100000000 * 1000)
			NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "You do not have enough Burstcoin !");
		else if (NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, "Create this asset with " + totalStr + " tokens?\ncost: 1000 Burstcoin"))
		{
			tradeComponentListeners.call(&TradeComponentListener::CreateAsset, name, description, quantityQNT, decimals);
		}
        //[/UserButtonCode_createButton]
    }
    else if (buttonThatWasClicked == assetMenuButton)
    {
        //[UserButtonCode_assetMenuButton] -- add your button handler code here..
		ScopedPointer<PopupMenu> contextMenu;
		contextMenu = new PopupMenu;

		String balStr = NQT2Burst(String(asset.balance), String(asset.decimals));

	//	contextMenu->addItem(1, "Copy name " + asset.name, true);
		if (asset.assetID.getLargeIntValue() > 0)
		{
			contextMenu->addItem(6, "Show asset creator in explorer", true);
			contextMenu->addItem(7, "Show asset in explorer", true);
			contextMenu->addSeparator();
			contextMenu->addItem(2, "Copy asset ID " + asset.assetID, true);
			contextMenu->addItem(3, "Copy creator address " + asset.account_RS, true);
			contextMenu->addItem(4, "Copy description", true);
		}
		else
		{
			contextMenu->addItem(99, "3rd party resources", false);
			contextMenu->addItem(105, "Open burst-coin.org", true);
			contextMenu->addItem(106, "Open burstwiki.org", true);

			PopupMenu faucetsMenu;
			faucetsMenu.addItem(113, "burstfaucets.com (Masterlist)");
			faucetsMenu.addItem(114, "burst-alliance.org");
			faucetsMenu.addItem(115, "burst-coin.es");
			faucetsMenu.addItem(116, "burstcoin.cc");
			faucetsMenu.addItem(117, "forums.getburst.net");
			faucetsMenu.addItem(118, "burstpay.net");
			faucetsMenu.addItem(119, "burstcoin.ml");
			faucetsMenu.addItem(112, "burst-account-activator");

			PopupMenu exchangesMenu;
			exchangesMenu.addItem(120, "bittrex.com");
			exchangesMenu.addItem(121, "eterbase.exchange");
			exchangesMenu.addItem(122, "upbit.com");
			exchangesMenu.addItem(123, "stex.com");
			exchangesMenu.addItem(124, "livecoin.net");
			exchangesMenu.addItem(125, "xchange.me");
			exchangesMenu.addItem(126, "qbtc.ink");

			PopupMenu explorersMenu;
			explorersMenu.addItem(130, "burstcoin.network");
			explorersMenu.addItem(131, "burst.devtrue.net");
			explorersMenu.addItem(132, "cryptoguru.org");
			explorersMenu.addItem(133, "burstcoin.ro");

			PopupMenu gamesMenu;
			gamesMenu.addItem(140, "blockplay.io");
			gamesMenu.addItem(141, "lotto.burstcoin.ro");

			contextMenu->addSubMenu("Exchanges", exchangesMenu);
			contextMenu->addSubMenu("Faucets", faucetsMenu);
			contextMenu->addSubMenu("Explorers", explorersMenu);
			contextMenu->addSubMenu("Games", gamesMenu);
		}
		contextMenu->addSeparator();

		contextMenu->addItem(101, "Copy my address", true);
		contextMenu->addItem(102, "Copy my public key", true);
		if (asset.balance > 0)
			contextMenu->addItem(5, "Copy my balance " + balStr, true);
		if (asset.assetID.getLargeIntValue() > 0)
		{
			contextMenu->addSeparator();
			contextMenu->addItem(8, "Number of accounts " + String(asset.numberOfAccounts), false);
			contextMenu->addItem(9, "Number of transfers " + String(asset.numberOfTransfers), false);
			contextMenu->addItem(10, "Number of trades " + String(asset.numberOfTrades), false);
			contextMenu->addSeparator();
			contextMenu->addItem(11, "Number of tokens " + NQT2Burst(String(asset.quantityQNT), String(asset.decimals)), false);
			contextMenu->addItem(12, "Number of decimals " + String(asset.decimals), false);
		}

		// ACTIONS
		int result = contextMenu->show();
		if (result == 1)
			SystemClipboard::copyTextToClipboard(asset.name);
		else if (result == 2)
			SystemClipboard::copyTextToClipboard(asset.assetID);
		else if (result == 3)
			SystemClipboard::copyTextToClipboard(asset.account_RS);
		else if (result == 4)
			SystemClipboard::copyTextToClipboard(asset.description);
		else if (result == 5)
			SystemClipboard::copyTextToClipboard(balStr);
		else if (result == 6)
		{
			bool isOnTestnet = false;
			URL u("https://" + String(isOnTestnet ? "testnet." : "") + "explorer.burstcoin.network/?action=account&account=" + asset.account_ID);
			u.launchInDefaultBrowser();
		}
		else if (result == 7)
			URL("https://explorer.burstcoin.network/?action=assets&id=" + asset.assetID).launchInDefaultBrowser();

		else if (result == 101)
			SystemClipboard::copyTextToClipboard(accountRS);
		else if (result == 102)
			SystemClipboard::copyTextToClipboard(accountPubkey);

		else if (result == 105)
			URL("https://burst-coin.org").launchInDefaultBrowser();
		else if (result == 106)
			URL("https://burstwiki.org/en/").launchInDefaultBrowser();


		else if (result == 112)
		{
			URL u("https://burst-account-activator.ohager.now.sh/");
			u.launchInDefaultBrowser();
		}
		else if (result == 113)
			URL("https://burstfaucets.com/").launchInDefaultBrowser();
		else if (result == 114)
			URL("http://faucet.burst-alliance.org/").launchInDefaultBrowser();
 		else if (result == 115)
			URL("https://burst-coin.es/faucet").launchInDefaultBrowser();
 		else if (result == 116)
			URL("http://burstcoin.cc:3333/").launchInDefaultBrowser();
 		else if (result == 117)
			URL("https://forums.getburst.net/c/new-members-introductions/getting-started-initial-burstcoin-requests").launchInDefaultBrowser();
 		else if (result == 118)
			URL("https://faucet.burstpay.net/").launchInDefaultBrowser();
 		else if (result == 119)
			URL("http://faucet.burstcoin.ml/").launchInDefaultBrowser();

		else if (result == 120)
			URL("https://bittrex.com/Market/Index?MarketName=BTC-burst").launchInDefaultBrowser();
		else if (result == 121)
			URL("https://eterbase.exchange/invite/d1jNPDkj").launchInDefaultBrowser();
		else if (result == 122)
			URL("https://upbit.com/exchange?code=CRIX.UPBIT.BTC-BURST").launchInDefaultBrowser();
		else if (result == 123)
			URL("https://app.stex.com/").launchInDefaultBrowser();
		else if (result == 124)
			URL("https://www.livecoin.net/").launchInDefaultBrowser();
		else if (result == 125)
			URL("https://xchange.me/").launchInDefaultBrowser();
		else if (result == 126)
			URL("https://www.qbtc.ink/trade?symbol=BURST_CNYT").launchInDefaultBrowser();

		else if (result == 130)
			URL("https://explorer.burstcoin.network/").launchInDefaultBrowser();
		else if (result == 131)
			URL("https://explorer.burst.devtrue.net/").launchInDefaultBrowser();
		else if (result == 132)
			URL("https://explore.burst.cryptoguru.org/").launchInDefaultBrowser();
		else if (result == 133)
			URL("https://explore.burstcoin.ro/").launchInDefaultBrowser();

		else if (result == 140)
			URL("https://www.blockplay.io/").launchInDefaultBrowser();
		else if (result == 141)
			URL("https://lotto.burstcoin.ro/").launchInDefaultBrowser();
        //[/UserButtonCode_assetMenuButton]
    }
    else if (buttonThatWasClicked == whitelistAddTextButton)
    {
        //[UserButtonCode_whitelistAddTextButton] -- add your button handler code here..
		if (whitelistAssetComboBox->getText().isNotEmpty())
		{
			StringArray whitelistedAssets = StringArray::fromTokens(getAppProperties().getUserSettings()->getValue("AssetWhitelist"), ",", "");
			whitelistedAssets.add(whitelistAssetComboBox->getText().trim().retainCharacters("0123456789"));
			whitelistedAssets.removeDuplicates(true);
			getAppProperties().getUserSettings()->setValue("AssetWhitelist", whitelistedAssets.joinIntoString(","));
			tradeComponentListeners.call(&TradeComponentListener::Refresh);
			whitelistAssetComboBox->addItem(whitelistAssetComboBox->getText(), whitelistAssetComboBox->getNumItems() + 1);

			tradeComponentListeners.call(&TradeComponentListener::Refresh);
		}
        //[/UserButtonCode_whitelistAddTextButton]
    }
    else if (buttonThatWasClicked == whitelistRemoveTextButton)
    {
        //[UserButtonCode_whitelistRemoveTextButton] -- add your button handler code here..
		if (whitelistAssetComboBox->getText().isNotEmpty())
		{
			StringArray whitelistedAssets = StringArray::fromTokens(getAppProperties().getUserSettings()->getValue("AssetWhitelist"), ",", "");
			whitelistedAssets.removeString(whitelistAssetComboBox->getText());
			getAppProperties().getUserSettings()->setValue("AssetWhitelist", whitelistedAssets.joinIntoString(","));
			tradeComponentListeners.call(&TradeComponentListener::Refresh);
			whitelistAssetComboBox->clear();
			whitelistAssetComboBox->addItemList(whitelistedAssets, 1);

			tradeComponentListeners.call(&TradeComponentListener::Refresh);
		}
        //[/UserButtonCode_whitelistRemoveTextButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void TradeInterfaceComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == sellAmountComboBox)
    {
        //[UserComboBoxCode_sellAmountComboBox] -- add your combo box handling code here..
		//tradeComponentListeners.call(&TradeComponentListener::UpdateBuySellPrice, buyAmountComboBox->getText(), sellAmountComboBox->getText());
		UpdateTotalSellLabel();
        //[/UserComboBoxCode_sellAmountComboBox]
    }
    else if (comboBoxThatHasChanged == buyAmountComboBox)
    {
        //[UserComboBoxCode_buyAmountComboBox] -- add your combo box handling code here..
		//tradeComponentListeners.call(&TradeComponentListener::UpdateBuySellPrice, buyAmountComboBox->getText(), sellAmountComboBox->getText());
		UpdateTotalBuyLabel();
        //[/UserComboBoxCode_buyAmountComboBox]
    }
    else if (comboBoxThatHasChanged == sellPriceComboBox)
    {
        //[UserComboBoxCode_sellPriceComboBox] -- add your combo box handling code here..
		UpdateTotalSellLabel();
        //[/UserComboBoxCode_sellPriceComboBox]
    }
    else if (comboBoxThatHasChanged == buyPriceComboBox)
    {
        //[UserComboBoxCode_buyPriceComboBox] -- add your combo box handling code here..
		UpdateTotalBuyLabel();
        //[/UserComboBoxCode_buyPriceComboBox]
    }
    else if (comboBoxThatHasChanged == quantityComboBox)
    {
        //[UserComboBoxCode_quantityComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_quantityComboBox]
    }
    else if (comboBoxThatHasChanged == buyTotalComboBox)
    {
        //[UserComboBoxCode_buyTotalComboBox] -- add your combo box handling code here..
		UpdateTotalBuyLabel(true);
        //[/UserComboBoxCode_buyTotalComboBox]
    }
    else if (comboBoxThatHasChanged == sellTotalComboBox)
    {
        //[UserComboBoxCode_sellTotalComboBox] -- add your combo box handling code here..
		UpdateTotalSellLabel(true);
        //[/UserComboBoxCode_sellTotalComboBox]
    }
    else if (comboBoxThatHasChanged == whitelistAssetComboBox)
    {
        //[UserComboBoxCode_whitelistAssetComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_whitelistAssetComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void TradeInterfaceComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == decimalsSlider)
    {
        //[UserSliderCode_decimalsSlider] -- add your slider handling code here..
        //[/UserSliderCode_decimalsSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TradeInterfaceComponent::NewAsset()
{
	asset.assetID = "";

	whitelistAssetComboBox->setVisible(true);
	whitelistAddTextButton->setVisible(true);
	whitelistRemoveTextButton->setVisible(true);
	whitelistLabel->setVisible(true);
	createLabel->setVisible(true);
	nameTextEditor->setVisible(true);
	descriptionTextEditor->setVisible(true);
	decimalslabel->setVisible(true);
	decimalsSlider->setVisible(true);
	quantityLabel->setVisible(true);
	quantityComboBox->setVisible(true);
	createButton->setVisible(true);

	balanceNumLabel->setVisible(false);
	balanceNumLabel2->setVisible(false);
	assetMenuButton->setVisible(false);
	nameLabel->setVisible(false);
	descriptionStaticTextEditor->setVisible(false);
	sellAmountComboBox->setVisible(false);
	buyAmountComboBox->setVisible(false);
	label2->setVisible(false);
	label3->setVisible(false);
	sellPriceComboBox->setVisible(false);
	buyPriceComboBox->setVisible(false);
	totalBuyLabel->setVisible(false);
	totalSellLabel->setVisible(false);
	buyButton->setVisible(false);
	sellButton->setVisible(false);
	buyOrderTableComponent->setVisible(false);
	sellOrderTableComponent->setVisible(false);
	buyTotalComboBox->setVisible(false);
	sellTotalComboBox->setVisible(false);
	quantityLabel2->setVisible(false);
	quantityLabel3->setVisible(false);

	repaint();
}

void TradeInterfaceComponent::SetBuyOrderItems(Array<OrderItem> buyOrders)
{
	buyOrderTableComponent->SetOrders(buyOrders);
}

void TradeInterfaceComponent::SetSellOrderItems(Array<OrderItem> sellOrders)
{
	sellOrderTableComponent->SetOrders(sellOrders);
}

void TradeInterfaceComponent::SetOrder(OrderItem orders)
{
	String quantityStr = NQT2Burst(String(orders.quantityQNT), String(asset.decimals));
	String priceStr = NQT2Burst(String(orders.priceNQT), String(8 - asset.decimals));

	if (orders.type.compareIgnoreCase("bid"))
	{
		buyAmountComboBox->setText(quantityStr, dontSendNotification);
		buyPriceComboBox->setText(priceStr, dontSendNotification);
		UpdateTotalBuyLabel();
	}
	else if (orders.type.compareIgnoreCase("ask"))
	{
		sellAmountComboBox->setText(quantityStr, dontSendNotification);
		sellPriceComboBox->setText(priceStr, dontSendNotification);
		UpdateTotalSellLabel();
	}
}

void TradeInterfaceComponent::UpdateTotalBuyLabel(const bool useTotal)
{
	uint64 totalPriceNQT = 0;
	if (useTotal)
	{
		uint64 totalQNT = toQT(buyTotalComboBox->getText(), String(8));
		uint64 priceNQT = toQT(buyPriceComboBox->getText(), String(8));

		uint64 scaler = pow(10, asset.decimals);
		uint64 quantityQNT = (totalQNT * scaler) / (jmax<uint64>(1, priceNQT));
		String quantityStr = NQT2Burst(String(quantityQNT), String(asset.decimals));

		String priceStr = NQT2Burst(String(priceNQT), String(8));

		totalPriceNQT = priceNQT * quantityQNT / scaler;
		String totalPriceStr = NQT2Burst(String(totalPriceNQT), String(8));

		buyAmountComboBox->setText(quantityStr, dontSendNotification);
		buyPriceComboBox->setText(priceStr, dontSendNotification);
		buyTotalComboBox->setText(totalPriceStr, dontSendNotification);
	}
	else
	{
		uint64 scaler = pow(10, asset.decimals);
		uint64 quantityQNT = toQT(buyAmountComboBox->getText(), String(asset.decimals));
		uint64 priceNQT = toQT(buyPriceComboBox->getText(), String(8));

		String quantityStr = NQT2Burst(String(quantityQNT), String(asset.decimals));

		String priceStr = NQT2Burst(String(priceNQT), String(8));

		totalPriceNQT = priceNQT * quantityQNT / scaler;
		String totalPriceStr = NQT2Burst(String(totalPriceNQT), String(8));

		buyAmountComboBox->setText(quantityStr, dontSendNotification);
		buyPriceComboBox->setText(priceStr, dontSendNotification);
		buyTotalComboBox->setText(totalPriceStr, dontSendNotification);
	}
	// enable the buy button if user has enough burst
	uint64 txFee = FEE_QUANT * 3;
	buyButton->setEnabled((userBalanceNQT >= (txFee + totalPriceNQT)) && totalPriceNQT > 0);
}

void TradeInterfaceComponent::UpdateTotalSellLabel(const bool useTotal)
{
	uint64 totalPriceNQT = 0;
	uint64 quantityQNT = 0;
	if (useTotal)
	{
		uint64 totalQNT = toQT(sellTotalComboBox->getText(), String(8));
		uint64 priceNQT = toQT(sellPriceComboBox->getText(), String(8));

		uint64 scaler = pow(10, asset.decimals);
		quantityQNT = (totalQNT * scaler) / (jmax<uint64>(1, priceNQT));
		String quantityStr = NQT2Burst(String(quantityQNT), String(asset.decimals));

		totalPriceNQT = priceNQT * quantityQNT / scaler;
		String totalPriceStr = NQT2Burst(String(totalPriceNQT), String(8));

		String priceStr = NQT2Burst(String(priceNQT), String(8));

		sellAmountComboBox->setText(quantityStr, dontSendNotification);
		sellPriceComboBox->setText(priceStr, dontSendNotification);
		sellTotalComboBox->setText(totalPriceStr, dontSendNotification);
	}
	else
	{
		uint64 scaler = pow(10, asset.decimals);
		quantityQNT = toQT(sellAmountComboBox->getText(), String(asset.decimals));
		uint64 priceNQT = toQT(sellPriceComboBox->getText(), String(8));

		totalPriceNQT = priceNQT * quantityQNT / scaler;
		String totalPriceStr = NQT2Burst(String(totalPriceNQT), String(8));

		String quantityStr = NQT2Burst(String(quantityQNT), String(asset.decimals));

		String priceStr = NQT2Burst(String(priceNQT), String(8));

		sellAmountComboBox->setText(quantityStr, dontSendNotification);
		sellPriceComboBox->setText(priceStr, dontSendNotification);
		sellTotalComboBox->setText(totalPriceStr, dontSendNotification);
	}
	// enable the sell button if user has enough tokens, and burst for tx fee
	uint64 txFee = FEE_QUANT * 3;
	sellButton->setEnabled((userBalanceNQT > txFee) && quantityQNT <= asset.balance);
}

void TradeInterfaceComponent::SetAssetBurstNQT(const uint64 balanceNQT)
{
	userBalanceNQT = balanceNQT;
}

void TradeInterfaceComponent::SetAssetData(const AssetItem asset)
{
	if (this->asset.assetID != asset.assetID)
	{
		buyAmountComboBox->setText(String::empty, dontSendNotification);
		buyPriceComboBox->setText(String::empty, dontSendNotification);
		buyTotalComboBox->setText(String::empty, dontSendNotification);
		sellAmountComboBox->setText(String::empty, dontSendNotification);
		sellPriceComboBox->setText(String::empty, dontSendNotification);
		sellTotalComboBox->setText(String::empty, dontSendNotification);
	}

	this->asset = asset;

	whitelistAssetComboBox->setVisible(false);
	whitelistAddTextButton->setVisible(false);
	whitelistRemoveTextButton->setVisible(false);
	whitelistLabel->setVisible(false);
	createLabel->setVisible(false);
	nameTextEditor->setVisible(false);
	descriptionTextEditor->setVisible(false);
	decimalslabel->setVisible(false);
	decimalsSlider->setVisible(false);
	quantityLabel->setVisible(false);
	quantityComboBox->setVisible(false);
	createButton->setVisible(false);

	balanceNumLabel->setVisible(true);
	balanceNumLabel2->setVisible(true);
	assetMenuButton->setVisible(true);
	nameLabel->setVisible(true);
	descriptionStaticTextEditor->setVisible(true);

	bool showTradeDesk = (asset.assetID.getLargeIntValue() > 0);

	sellAmountComboBox->setVisible(showTradeDesk);
	buyAmountComboBox->setVisible(showTradeDesk);
	label2->setVisible(showTradeDesk);
	label3->setVisible(showTradeDesk);
	sellPriceComboBox->setVisible(showTradeDesk);
	buyPriceComboBox->setVisible(showTradeDesk);
	totalBuyLabel->setVisible(showTradeDesk);
	totalSellLabel->setVisible(showTradeDesk);
	buyButton->setVisible(showTradeDesk);
	sellButton->setVisible(showTradeDesk);
	buyOrderTableComponent->setVisible(showTradeDesk);
	sellOrderTableComponent->setVisible(showTradeDesk);
	buyTotalComboBox->setVisible(showTradeDesk);
	sellTotalComboBox->setVisible(showTradeDesk);
	quantityLabel2->setVisible(showTradeDesk);
	quantityLabel3->setVisible(showTradeDesk);


	buyAmountComboBox->setEditableText(true);
	buyPriceComboBox->setEditableText(true);
	buyTotalComboBox->setEditableText(true);
	sellAmountComboBox->setEditableText(true);
	sellPriceComboBox->setEditableText(true);
	sellTotalComboBox->setEditableText(true);



	String quantityStr = NQT2Burst(String(asset.quantityQNT), String(asset.decimals));
	String balStr = NQT2Burst(String(asset.balance), String(asset.decimals));
	String bal2 = balStr.fromFirstOccurrenceOf(".", false, true);
	if (bal2.isEmpty())
		bal2 = "-";
	balanceNumLabel->setText(balStr.upToFirstOccurrenceOf(".", true, true), dontSendNotification);
	balanceNumLabel2->setText(bal2, dontSendNotification);
	assetMenuButton->setButtonText(asset.assetID.getLargeIntValue() != 0 ? "Asset ID " + asset.assetID : accountRS);
	nameLabel->setText(asset.name, dontSendNotification);
	descriptionStaticTextEditor->setText(asset.description);

	buyOrderTableComponent->SetDecimals(asset.decimals);
	sellOrderTableComponent->SetDecimals(asset.decimals);

	repaint();
}

uint64 TradeInterfaceComponent::GetUINT64(const String uint64Str)
{
	return *((uint64*)(GetUINT64MemoryBlock(uint64Str).getData()));
}

MemoryBlock TradeInterfaceComponent::GetUINT64MemoryBlock(const String uint64Str)
{ // drop the use of BigInteger. but String only returns signed version of int 64 (max size should be 2^64)
	juce::BigInteger bigInt;
	bigInt.parseString(uint64Str, 10);
	MemoryBlock m(bigInt.toMemoryBlock());
	m.ensureSize(8, true);
	return m;
}

void TradeInterfaceComponent::SetRecommendedSellAndBuyPrice(const String buyPrice, const String sellPrice)
{
	buyPriceComboBox->setText(buyPrice);
	sellPriceComboBox->setText(sellPrice);
}

String TradeInterfaceComponent::NQT2Burst(const String value, const String decimals)
{
	int dec = decimals.getIntValue();
	bool minus = value.startsWithChar('-');
	String neatNr(value.removeCharacters("-").paddedLeft('0', dec + 1));
	neatNr = (neatNr.substring(0, neatNr.length() - dec) + "." + neatNr.substring(neatNr.length() - dec, neatNr.length()).trimCharactersAtEnd("0"));
	return minus ? "-" + neatNr : neatNr;
}

String TradeInterfaceComponent::Burst2NQT(const String value, const String decimals)
{
	return String(toQT(value, decimals));
}

uint64 TradeInterfaceComponent::toQT(const String value, const String decimals)
{
	int64 amountNQT = 0;
	String amount = value.trim().retainCharacters("0123456789.,");
	uint64 scaler = pow(10, decimals.trim().getIntValue());
	int point = amount.indexOfAnyOf(".,");
	if (point < 0)
		amountNQT = amount.retainCharacters("0123456789").getLargeIntValue() * scaler;
	else
	{
		amountNQT = amount.substring(0, point).getLargeIntValue() * scaler;
		amountNQT += amount.substring(point + 1, amount.length()).retainCharacters("0123456789").paddedRight('0', decimals.getIntValue()).substring(0, decimals.getIntValue()).getLargeIntValue();
	}
	return (amountNQT);
}

Colour TradeInterfaceComponent::GetAssetColor(float iTime)
{
	float r = abs(sin(iTime + 12.) + sin(iTime*0.7 + 71.124)*0.5);
	float g = abs(sin(iTime) + sin(iTime*0.8 + 41.)*0.5);
	float b = abs(sin(iTime + 61.) + sin(iTime*0.8 + 831.32)*0.5);
	return Colour(r * 0xff, g * 0xff, b * 0xff);
}

// Step2: Every time you want a color from the current color scheme, call the following function, while providing it with two random seeds which range between 0 to 1, and three Key colors.
//Color TradeInterfaceComponent::SampleFromColorScheme(float r1, float r2, Colour _Color1, Colour _Color2, Colour _Color3)
//{
	//return (1. — sqrt(r1))*_Color1 + (sqrt(r1)*(1. — r2))*_Color2 + (r2*sqrt(r1)) * _Color3.;
//}

void TradeInterfaceComponent::CancelAskOrder(String orderID)
{
	if (NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, "Cancel your ask order?\n+ standard transaction fee\nOrder ID: " + orderID))
		tradeComponentListeners.call(&TradeComponentListener::CancelAskOrder, orderID);
}

void TradeInterfaceComponent::CancelBidOrder(String orderID)
{
	if (NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, "Cancel your bid order?\n+ standard transaction fee\nOrder ID: " + orderID))
		tradeComponentListeners.call(&TradeComponentListener::CancelBidOrder, orderID);
}

TradeInterfaceComponent::OrderTableComponent::OrderTableComponent(const bool isBuyOrders)
{
	this->isBuyOrders = isBuyOrders;

	int defWidth = 70;
	int minWidth = 70;
	table.getHeader().addColumn("Quantity", 1, defWidth, minWidth, -1, TableHeaderComponent::visible);
	table.getHeader().addColumn("Price", 2, defWidth, minWidth, -1, TableHeaderComponent::visible);
	table.setHeaderHeight(25);
	table.setRowHeight(30);
	table.setModel(this);
	//table.addKeyListener(this);
	table.setMultipleSelectionEnabled(false);
	table.getVerticalScrollBar()->setAutoHide(true);
	table.setColour(TableListBox::ColourIds::backgroundColourId, Colour(0xfffcfcfc));
	table.getHeader().setSortColumnId(1, false);
	addAndMakeVisible(table);
	table.autoSizeAllColumns();
};
TradeInterfaceComponent::OrderTableComponent::~OrderTableComponent()
{
};
void TradeInterfaceComponent::OrderTableComponent::paint(Graphics& g)
{
	g.fillAll(Colours::white);
}

void TradeInterfaceComponent::OrderTableComponent::resized()
{
	table.setBoundsInset(BorderSize<int>(0, 0, 0, 0));
	table.autoSizeAllColumns();
}

int TradeInterfaceComponent::OrderTableComponent::getNumRows()
{
	return orders.size();
}

void TradeInterfaceComponent::OrderTableComponent::paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected)
{
	if (orders[rowNumber].orderID.isEmpty())
		g.fillAll(Colours::lightgrey.brighter());
	else g.fillAll(Colours::white);

	if (rowIsSelected)
	{
		g.setColour(Colours::lightgrey.withAlpha(0.5f));
		g.fillRoundedRectangle(0.f, 0.f, width, height, 5.f);
	}
}

void TradeInterfaceComponent::OrderTableComponent::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
	float alpha = orders[rowNumber].orderID.isEmpty() ? 0.5f : 1.f;

	if (orders[rowNumber].cancelled)
		g.setColour(Colours::darkred.withAlpha(alpha));
	else if (orders[rowNumber].accountRS.compareIgnoreCase(accountRS) == 0)
		g.setColour(Colours::darkgreen.withAlpha(alpha));
	else g.setColour(Colours::black.withAlpha(alpha));

	if (columnId == 1)
		g.drawText(NQT2Burst(orders[rowNumber].quantityQNT, dec), 5, 0, (width) - 10, height, Justification::right);
	else if (columnId == 2)
		g.drawText(NQT2Burst(orders[rowNumber].priceNQT, 8 - dec), 5, 0, (width) - 10, height, Justification::left);

	if (orders[rowNumber].cancelled)
	{
		const float dashes[2] = { 4.f, 4.f };
		g.drawDashedLine(juce::Line<float>(0.f, height / 2.f, width, height / 2.f), &dashes[0], 2);
	}
}

Component* TradeInterfaceComponent::OrderTableComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
	return nullptr;
}

void TradeInterfaceComponent::OrderTableComponent::cellClicked(int rowNumber, int columnId, const MouseEvent &ev)
{
	if (ev.mods.isRightButtonDown())
	{
		PopupMenu m;
		int idx = 1;
		m.addItem(idx++, "Copy Order ID", orders[rowNumber].orderID.isNotEmpty());
		m.addItem(idx++, "Setup order", (orders[rowNumber].accountRS.compareIgnoreCase(accountRS) != 0));
		if (orders[rowNumber].orderID.isNotEmpty() && orders[rowNumber].accountRS.compareIgnoreCase(accountRS) == 0)
		{
			m.addSeparator();
			m.addItem(idx++, "Cancel order", orders[rowNumber].cancelled == false);
		}
		const int result = m.show();

		if (result == 1)
		{
			SystemClipboard::copyTextToClipboard(orders[rowNumber].orderID);
		}
		else if (result == 2)
		{
			tradeInterfaceComponentListeners.call(&TradeInterfaceComponentListener::SetOrder, orders[rowNumber]);
		}
		else if (result == 3)
		{
			if (orders[rowNumber].type.compareIgnoreCase("ask") == 0)
				tradeInterfaceComponentListeners.call(&TradeInterfaceComponentListener::CancelAskOrder, orders[rowNumber].orderID);
			else if (orders[rowNumber].type.compareIgnoreCase("bid") == 0)
				tradeInterfaceComponentListeners.call(&TradeInterfaceComponentListener::CancelBidOrder, orders[rowNumber].orderID);
		}
	}
}

void TradeInterfaceComponent::OrderTableComponent::cellDoubleClicked(int rowNumber, int columnId, const MouseEvent&)
{
	if (orders[rowNumber].accountRS.compareIgnoreCase(accountRS) != 0)
		tradeInterfaceComponentListeners.call(&TradeInterfaceComponentListener::SetOrder, orders[rowNumber]);
};
void TradeInterfaceComponent::OrderTableComponent::backgroundClicked(const MouseEvent&)
{
};
void TradeInterfaceComponent::OrderTableComponent::sortOrderChanged(int newSortColumnId, bool isForwards)
{
};
int TradeInterfaceComponent::OrderTableComponent::getColumnAutoSizeWidth(int /*columnId*/)
{
	return (getWidth() - (table.getVerticalScrollBar() ? table.getVerticalScrollBar()->getWidth() : 1)) / jmax<int>(1, table.getHeader().getNumColumns(true));
};
String TradeInterfaceComponent::OrderTableComponent::getCellTooltip(int rowNumber, int columnId)
{
	String totalPriceStr = NQT2Burst(orders[rowNumber].priceNQT * orders[rowNumber].quantityQNT, 8);
	return "total: " + totalPriceStr + " Burstcoin";
};
void TradeInterfaceComponent::OrderTableComponent::selectedRowsChanged(int lastRowSelected)
{
};
void TradeInterfaceComponent::OrderTableComponent::deleteKeyPressed(int /*lastRowSelected*/)
{
};
void TradeInterfaceComponent::OrderTableComponent::returnKeyPressed(int /*lastRowSelected*/)
{
};
void TradeInterfaceComponent::OrderTableComponent::listWasScrolled()
{
};

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TradeInterfaceComponent"
                 componentName="" parentClasses="public Component, public TradeInterfaceComponentListener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffeef1f4">
    <RECT pos="0 4 300 700" fill="linear: 0 0, 0 200, 0=ff8b8b8b, 1=ffe0e0e0"
          hasStroke="0"/>
    <IMAGE pos="604 532 28 32" resource="bursticonblue_svg" opacity="1"
           mode="1"/>
  </BACKGROUND>
  <TEXTEDITOR name="nameTextEditor" id="31190c55a43f9c1d" memberName="nameTextEditor"
              virtualName="" explicitFocusOrder="0" pos="448 160 376 24" tooltip="The name of the asset is NOT unique ! Other assets can have the same name. However each asset gets a unique numbered ID. Like all settings of this new asset, this setting cannot be changed !"
              bkgcol="54ffffff" shadowcol="1a000000" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="descriptionTextEditor" id="db27613c820c3053" memberName="descriptionTextEditor"
              virtualName="" explicitFocusOrder="0" pos="448 192 376 112" tooltip="The description text of the asset. Provide info, adding a web link is recommened. Also make sure people can contact you. Like all settings of this new asset, this setting cannot be changed !"
              bkgcol="66ffffff" initialText="" multiline="1" retKeyStartsLine="0"
              readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTBUTTON name="buyButton" id="698b316f360117bc" memberName="buyButton"
              virtualName="" explicitFocusOrder="0" pos="456 595 104 24" tooltip="create buy order (+ tx fee)"
              bgColOff="ff77b517" bgColOn="ff98ea1a" buttonText="buy" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="sellButton" id="21f203b85c9213c5" memberName="sellButton"
              virtualName="" explicitFocusOrder="0" pos="680 597 112 24" tooltip="create sell order (+ tx fee)"
              bgColOff="ffe13a3a" bgColOn="ff9a2626" buttonText="sell" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="sellAmountComboBox" id="a68f6533b9945dd2" memberName="sellAmountComboBox"
            virtualName="" explicitFocusOrder="0" pos="720 504 104 24" tooltip="quantity"
            editable="0" layout="33" items="" textWhenNonSelected="1" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="buyAmountComboBox" id="58ef3f195c7ffce6" memberName="buyAmountComboBox"
            virtualName="" explicitFocusOrder="0" pos="488 504 104 24" tooltip="quantity"
            editable="0" layout="33" items="" textWhenNonSelected="1" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="21c394d7482a96be" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="448 536 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="price" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="8ebfea4579aa7cf5" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="680 533 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="price" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="balanceNumLabel" id="5746ea1921eb531e" memberName="balanceNumLabel"
         virtualName="" explicitFocusOrder="0" pos="64 8 144 40" textCol="ff1d5481"
         edTextCol="ff1d5481" edBkgCol="0" labelText="0.000" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="40" bold="0" italic="0" justification="18"/>
  <COMBOBOX name="sellPriceComboBox" id="2f91a4d80c3d0a2c" memberName="sellPriceComboBox"
            virtualName="" explicitFocusOrder="0" pos="712 533 112 24" tooltip="the sell price in Burstcoin for each asset token"
            editable="0" layout="33" items="" textWhenNonSelected="0.00000000"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="buyPriceComboBox" id="24a7719f0297e2f7" memberName="buyPriceComboBox"
            virtualName="" explicitFocusOrder="0" pos="480 536 112 24" tooltip="the buy price in Burstcoin for each asset token"
            editable="0" layout="33" items="" textWhenNonSelected="0.00000000"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="decimalsSlider" id="aa6a73dfd0b9626b" memberName="decimalsSlider"
          virtualName="" explicitFocusOrder="0" pos="560 352 144 24" tooltip="how far devisable each token is. (ie. 2 would give 0.01 as smallest unit)&#10;Like all settings of this new asset, this setting cannot be changed !"
          min="0" max="8" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="decimalslabel" id="ab96c71b449353cc" memberName="decimalslabel"
         virtualName="" explicitFocusOrder="0" pos="456 352 88 24" tooltip="how far devisable each token is. (ie. 2 would be 0.01)"
         edTextCol="ff000000" edBkgCol="0" labelText="decimals" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="quantityLabel" id="afedbc07e29a57f1" memberName="quantityLabel"
         virtualName="" explicitFocusOrder="0" pos="456 320 88 24" tooltip="the total amount of tokens this asset has"
         edTextCol="ff000000" edBkgCol="0" labelText="quantity" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <TEXTBUTTON name="createButton" id="9bff21642c414843" memberName="createButton"
              virtualName="" explicitFocusOrder="0" pos="456 384 374 32" tooltip="Once an asset is created it cannot be changed ! (creation fee is 1000 burst)"
              bgColOff="fff0a713" bgColOn="ffc48b18" buttonText="create asset (cost 1000 BURST)"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="_assetMenuButton" id="92cfd026c94e840c" memberName="assetMenuButton"
              virtualName="" explicitFocusOrder="0" pos="8 40 152 40" tooltip="asset details menu"
              bgColOff="bbbbff" buttonText="Asset ID" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <COMBOBOX name="quantityComboBox" id="975ef40aebd5264f" memberName="quantityComboBox"
            virtualName="" explicitFocusOrder="0" pos="560 320 144 24" tooltip="the total amount of tokens this asset has. without any decimals. Like all settings of this new asset, this setting cannot be changed !"
            editable="1" layout="33" items="1&#10;100&#10;10,000&#10;100,000,000,000,000,000"
            textWhenNonSelected="100" textWhenNoItems="(no choices)"/>
  <GENERICCOMPONENT name="buyOrderTableComponent" id="e673ea6824cf6e1f" memberName="buyOrderTableComponent"
                    virtualName="" explicitFocusOrder="0" pos="448 632 152 224" class="OrderTableComponent"
                    params="1"/>
  <GENERICCOMPONENT name="sellOrderTableComponent" id="89957b1c2337edb0" memberName="sellOrderTableComponent"
                    virtualName="" explicitFocusOrder="0" pos="680 632 152 224" class="OrderTableComponent"
                    params=""/>
  <LABEL name="totalBuyLabel" id="a9d9a0638b068a33" memberName="totalBuyLabel"
         virtualName="" explicitFocusOrder="0" pos="448 568 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="total" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="totalSellLabel" id="802f4dbd5c3559e2" memberName="totalSellLabel"
         virtualName="" explicitFocusOrder="0" pos="680 568 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="total" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="nameLabel" id="d18bd4f243abbbfb" memberName="nameLabel"
         virtualName="" explicitFocusOrder="0" pos="8 88 88 24" textCol="ff323232"
         edTextCol="ff000000" edBkgCol="0" labelText="name" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="22" bold="0" italic="0" justification="9"/>
  <TEXTEDITOR name="descriptionStaticTextEditor" id="14bd98e2bf4e8093" memberName="descriptionStaticTextEditor"
              virtualName="" explicitFocusOrder="0" pos="8 120 376 112" textcol="ff272727"
              bkgcol="ffffff" hilitecol="ff77b517" outlinecol="0" shadowcol="0"
              initialText="description" multiline="1" retKeyStartsLine="0"
              readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <LABEL name="balanceNumLabel" id="70d948bb2944c4e7" memberName="balanceNumLabel2"
         virtualName="" explicitFocusOrder="0" pos="216 8 208 40" textCol="ff1d5481"
         edTextCol="ff1d5481" edBkgCol="0" labelText="0.000" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="22" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="buyTotalComboBox" id="708186ee47df0559" memberName="buyTotalComboBox"
            virtualName="" explicitFocusOrder="0" pos="496 568 112 24" tooltip="the total sell price in Burstcoin"
            editable="0" layout="33" items="" textWhenNonSelected="0.00000000"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="sellTotalComboBox" id="5d9ee59b46ab4c8d" memberName="sellTotalComboBox"
            virtualName="" explicitFocusOrder="0" pos="720 568 112 24" tooltip="the total buy price in Burstcoin"
            editable="0" layout="33" items="" textWhenNonSelected="0.00000000"
            textWhenNoItems="(no choices)"/>
  <LABEL name="" id="cf07383c9dee08ef" memberName="quantityLabel2" virtualName=""
         explicitFocusOrder="0" pos="672 504 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="quantity" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="" id="bf32c0e40bac032b" memberName="quantityLabel3" virtualName=""
         explicitFocusOrder="0" pos="440 504 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="quantity" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="whitelistAssetComboBox" id="9711cd67465b101b" memberName="whitelistAssetComboBox"
            virtualName="" explicitFocusOrder="0" pos="448 48 150 24" editable="1"
            layout="33" items="" textWhenNonSelected="Asset ID" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="whitelistAddTextButton" id="5cbe3f9e0b0d3979" memberName="whitelistAddTextButton"
              virtualName="" explicitFocusOrder="0" pos="608 48 72 24" bgColOff="ff77b517"
              bgColOn="ff98ea1a" buttonText="add" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="whitelistRemoveTextButton" id="28b6682a0d4a87c0" memberName="whitelistRemoveTextButton"
              virtualName="" explicitFocusOrder="0" pos="688 48 72 24" bgColOff="ffe13a3a"
              bgColOn="ffa52a2a" buttonText="remove" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="whitelistLabel" id="f8be835efd9c1710" memberName="whitelistLabel"
         virtualName="" explicitFocusOrder="0" pos="448 16 368 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Whitelist asset" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="createLabel" id="27841d3145e6e9e7" memberName="createLabel"
         virtualName="" explicitFocusOrder="0" pos="448 128 376 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Create new asset" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: burst_logo_white_svg, 3258, "img/burst_logo_white.svg"
static const unsigned char resource_TradeInterfaceComponent_burst_logo_white_svg[] = { 60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,110,99,111,100,105,110,103,61,34,117,116,
102,45,56,34,63,62,13,10,60,33,45,45,32,71,101,110,101,114,97,116,111,114,58,32,65,100,111,98,101,32,73,108,108,117,115,116,114,97,116,111,114,32,49,52,46,48,46,48,44,32,83,86,71,32,69,120,112,111,114,
116,32,80,108,117,103,45,73,110,32,46,32,83,86,71,32,86,101,114,115,105,111,110,58,32,54,46,48,48,32,66,117,105,108,100,32,52,51,51,54,51,41,32,32,45,45,62,13,10,60,33,68,79,67,84,89,80,69,32,115,118,
103,32,80,85,66,76,73,67,32,34,45,47,47,87,51,67,47,47,68,84,68,32,83,86,71,32,49,46,49,47,47,69,78,34,32,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,71,114,97,112,104,105,99,115,
47,83,86,71,47,49,46,49,47,68,84,68,47,115,118,103,49,49,46,100,116,100,34,62,13,10,60,115,118,103,32,118,101,114,115,105,111,110,61,34,49,46,49,34,32,105,100,61,34,67,97,108,113,117,101,95,49,34,32,120,
109,108,110,115,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,32,120,109,108,110,115,58,120,108,105,110,107,61,34,104,116,116,112,58,47,47,119,119,
119,46,119,51,46,111,114,103,47,49,57,57,57,47,120,108,105,110,107,34,32,120,61,34,48,112,120,34,32,121,61,34,48,112,120,34,13,10,9,32,119,105,100,116,104,61,34,55,48,48,46,52,54,53,112,120,34,32,104,
101,105,103,104,116,61,34,50,49,56,46,57,56,57,112,120,34,32,118,105,101,119,66,111,120,61,34,48,32,48,32,55,48,48,46,52,54,53,32,50,49,56,46,57,56,57,34,32,101,110,97,98,108,101,45,98,97,99,107,103,114,
111,117,110,100,61,34,110,101,119,32,48,32,48,32,55,48,48,46,52,54,53,32,50,49,56,46,57,56,57,34,13,10,9,32,120,109,108,58,115,112,97,99,101,61,34,112,114,101,115,101,114,118,101,34,62,13,10,60,103,62,
13,10,9,60,112,97,116,104,32,102,105,108,108,61,34,35,70,70,70,70,70,70,34,32,100,61,34,77,50,51,48,46,53,53,53,44,51,53,46,53,51,56,99,45,54,46,56,49,57,45,56,46,49,57,55,45,49,57,46,51,52,49,45,49,50,
46,49,56,50,45,51,56,46,50,56,49,45,49,50,46,49,56,50,104,45,53,48,46,56,54,53,76,49,50,56,46,55,57,49,44,57,49,46,52,52,108,45,53,48,46,53,53,55,45,48,46,48,50,53,13,10,9,9,76,55,50,46,53,57,54,44,49,
49,55,46,55,72,49,53,46,54,54,50,108,56,53,46,49,49,55,44,50,55,46,49,56,57,108,53,46,55,56,54,45,50,52,46,54,51,57,104,49,54,46,56,56,54,108,45,49,51,46,57,51,56,44,55,53,46,50,52,104,53,51,46,56,52,
52,99,51,51,46,52,55,50,44,48,44,53,51,46,56,51,50,45,49,52,46,52,48,54,44,53,56,46,56,55,55,45,52,49,46,54,54,51,108,50,46,53,49,55,45,49,51,46,54,50,53,13,10,9,9,99,51,46,51,52,45,49,56,46,48,48,51,
45,49,46,50,53,51,45,50,57,46,57,49,57,45,49,52,46,48,51,50,45,51,54,46,50,53,53,99,49,51,46,48,54,55,45,54,46,50,48,52,44,50,48,46,54,52,55,45,49,54,46,56,57,55,44,50,51,46,54,56,56,45,51,51,46,50,53,
51,108,49,46,49,48,55,45,53,46,57,55,50,13,10,9,9,67,50,51,55,46,56,56,44,53,49,46,57,51,57,44,50,51,54,46,50,53,56,44,52,50,46,51,57,51,44,50,51,48,46,53,53,53,44,51,53,46,53,51,56,122,32,77,49,56,55,
46,56,56,56,44,49,51,55,46,54,51,52,108,45,50,46,55,44,49,52,46,53,54,56,99,45,49,46,57,50,51,44,49,48,46,52,49,56,45,54,46,56,48,50,44,49,52,46,52,55,57,45,49,55,46,52,48,51,44,49,52,46,52,55,57,104,
45,49,53,46,53,56,51,13,10,9,9,108,56,46,54,48,51,45,52,54,46,52,52,57,104,49,50,46,51,55,49,99,55,46,49,48,55,44,48,44,49,49,46,51,57,50,44,49,46,49,55,50,44,49,51,46,52,56,52,44,51,46,54,56,57,67,49,
56,56,46,55,51,52,44,49,50,54,46,52,49,55,44,49,56,57,46,49,51,54,44,49,51,48,46,57,48,49,44,49,56,55,46,56,56,56,44,49,51,55,46,54,51,52,122,32,77,49,57,55,46,56,52,51,44,54,54,46,52,53,13,10,9,9,108,
45,49,46,55,50,53,44,57,46,51,49,50,99,45,50,46,48,51,54,44,49,48,46,57,56,54,45,56,46,49,48,50,44,49,53,46,54,55,52,45,50,48,46,50,56,50,44,49,53,46,54,55,52,104,45,57,46,54,57,55,108,55,46,50,55,55,
45,51,57,46,50,57,54,104,49,51,46,53,53,52,99,52,46,56,52,52,44,48,44,56,46,48,49,53,44,48,46,57,56,44,57,46,54,57,51,44,50,46,57,57,57,13,10,9,9,67,49,57,56,46,52,54,53,44,53,55,46,51,48,54,44,49,57,
56,46,56,53,50,44,54,49,46,48,48,55,44,49,57,55,46,56,52,51,44,54,54,46,52,53,122,34,47,62,13,10,9,60,112,97,116,104,32,102,105,108,108,61,34,35,70,70,70,70,70,70,34,32,100,61,34,77,50,55,49,46,53,50,
52,44,49,57,55,46,54,52,50,99,45,49,55,46,50,53,51,44,48,45,50,57,46,54,54,53,45,52,46,51,57,45,51,54,46,56,57,45,49,51,46,48,52,57,99,45,54,46,52,51,52,45,55,46,55,49,49,45,56,46,52,53,54,45,49,56,46,
52,51,55,45,54,46,48,48,57,45,51,49,46,56,55,56,13,10,9,9,108,50,51,46,53,54,57,45,49,50,57,46,51,49,53,104,51,55,46,50,56,108,45,50,52,46,48,51,44,49,51,49,46,56,54,50,99,45,48,46,56,53,51,44,52,46,54,
55,57,45,48,46,52,48,55,44,56,46,49,48,52,44,49,46,51,50,53,44,49,48,46,49,56,99,49,46,55,53,50,44,50,46,49,44,53,46,49,50,56,44,51,46,49,54,53,44,49,48,46,48,51,53,44,51,46,49,54,53,13,10,9,9,99,49,48,
46,49,54,49,44,48,44,49,53,46,52,57,45,52,46,51,56,55,44,49,55,46,50,56,45,49,52,46,50,50,52,108,50,51,46,56,55,51,45,49,51,48,46,57,56,51,104,51,53,46,53,49,55,108,45,50,51,46,55,50,49,44,49,51,48,46,
49,57,52,67,51,50,52,46,53,55,51,44,49,56,49,46,57,57,57,44,51,48,51,46,56,57,52,44,49,57,55,46,54,52,50,44,50,55,49,46,53,50,52,44,49,57,55,46,54,52,50,13,10,9,9,76,50,55,49,46,53,50,52,44,49,57,55,46,
54,52,50,122,34,47,62,13,10,9,60,112,97,116,104,32,102,105,108,108,61,34,35,70,70,70,70,70,70,34,32,100,61,34,77,52,53,50,46,50,48,54,44,51,53,46,53,54,50,99,45,54,46,56,50,56,45,56,46,49,56,55,45,49,
57,46,51,51,52,45,49,50,46,49,54,55,45,51,56,46,50,51,49,45,49,50,46,49,54,55,72,51,54,51,46,50,108,45,51,49,46,51,53,52,44,49,55,50,46,48,56,55,104,51,55,46,50,55,108,49,50,46,52,49,50,45,54,56,46,48,
53,57,13,10,9,9,104,57,46,49,48,54,99,54,46,55,54,49,44,48,44,49,49,46,49,50,53,44,49,46,50,57,51,44,49,51,46,51,52,50,44,51,46,57,53,49,99,50,46,50,56,53,44,50,46,55,51,57,44,50,46,55,55,57,44,55,46,
52,53,50,44,49,46,53,49,49,44,49,52,46,52,48,56,108,45,52,46,55,57,53,44,50,54,46,50,54,53,13,10,9,9,99,45,50,46,53,50,53,44,49,51,46,56,54,57,45,49,46,56,53,44,49,54,46,56,50,51,45,48,46,56,50,55,44,
50,49,46,50,57,53,108,48,46,52,56,56,44,50,46,49,52,104,51,56,46,50,53,51,108,45,49,46,48,57,56,45,51,46,50,51,57,99,45,49,46,57,52,49,45,53,46,55,50,54,45,49,46,49,53,57,45,49,49,46,50,55,49,44,48,46,
50,53,54,45,49,57,46,48,55,53,108,52,46,55,48,54,45,50,53,46,55,57,53,13,10,9,9,99,50,46,49,52,54,45,49,49,46,55,53,56,44,51,46,48,52,45,50,55,46,55,51,45,49,49,46,55,51,45,51,53,46,57,49,49,99,49,51,
46,50,51,50,45,54,46,50,53,50,44,50,49,46,49,51,54,45,49,55,46,50,57,44,50,52,46,49,45,51,51,46,53,57,50,108,50,46,51,57,52,45,49,51,46,49,50,52,13,10,9,9,67,52,53,57,46,53,54,53,44,53,49,46,57,53,57,
44,52,53,55,46,57,50,49,44,52,50,46,52,49,52,44,52,53,50,46,50,48,54,44,51,53,46,53,54,50,122,32,77,52,49,57,46,54,53,44,54,54,46,52,57,108,45,51,46,48,48,57,44,49,54,46,52,56,54,99,45,49,46,57,57,57,
44,49,48,46,57,55,53,45,56,46,48,51,53,44,49,53,46,54,53,54,45,50,48,46,49,56,52,44,49,53,46,54,53,54,104,45,57,46,54,56,55,13,10,9,9,108,56,46,52,55,49,45,52,54,46,52,52,52,104,49,51,46,53,49,52,99,52,
46,56,51,44,48,44,55,46,57,57,54,44,48,46,57,55,57,44,57,46,54,55,57,44,50,46,57,57,54,67,52,50,48,46,50,52,51,44,53,55,46,51,53,49,44,52,50,48,46,54,52,49,44,54,49,46,48,53,44,52,49,57,46,54,53,44,54,
54,46,52,57,122,34,47,62,13,10,9,60,112,97,116,104,32,102,105,108,108,61,34,35,70,70,70,70,70,70,34,32,100,61,34,77,52,57,48,46,50,53,51,44,49,57,55,46,51,57,54,99,45,49,55,46,50,53,53,44,48,45,50,57,
46,54,54,54,45,52,46,51,57,45,51,54,46,56,56,57,45,49,51,46,48,52,55,99,45,54,46,52,51,51,45,55,46,55,48,57,45,56,46,52,53,50,45,49,56,46,52,51,51,45,54,46,48,48,53,45,51,49,46,56,55,52,13,10,9,9,108,
50,46,50,52,52,45,49,50,46,50,55,54,104,51,53,46,53,49,49,108,45,50,46,55,48,52,44,49,52,46,56,50,52,99,45,48,46,56,53,50,44,52,46,54,56,50,45,48,46,52,48,52,44,56,46,49,48,57,44,49,46,51,50,57,44,49,
48,46,49,56,55,99,49,46,55,53,51,44,50,46,49,48,50,44,53,46,49,50,57,44,51,46,49,54,55,44,49,48,46,48,51,51,44,51,46,49,54,55,13,10,9,9,99,49,48,46,49,54,50,44,48,44,49,53,46,52,57,49,45,52,46,51,57,44,
49,55,46,50,55,55,45,49,52,46,50,51,50,99,49,46,56,52,55,45,49,48,46,49,48,52,45,48,46,55,53,56,45,49,56,46,49,51,50,45,50,48,46,49,49,54,45,51,51,46,57,54,54,99,45,50,51,46,51,52,49,45,49,57,46,50,50,
51,45,51,48,46,54,49,55,45,51,52,46,48,51,49,45,50,54,46,56,53,54,45,53,52,46,54,52,51,13,10,9,9,99,53,46,49,55,56,45,50,56,46,52,48,52,44,50,53,46,54,52,54,45,52,52,46,48,52,55,44,53,55,46,54,51,52,45,
52,52,46,48,52,55,99,49,54,46,57,55,57,44,48,44,50,57,46,50,48,53,44,52,46,51,51,53,44,51,54,46,51,51,57,44,49,50,46,56,56,52,99,54,46,52,51,50,44,55,46,55,48,56,44,56,46,52,52,50,44,49,56,46,52,56,57,
44,53,46,57,55,54,44,51,50,46,48,52,50,13,10,9,9,108,45,49,46,51,50,56,44,55,46,50,54,56,104,45,51,53,46,53,48,56,108,49,46,55,56,45,57,46,56,49,54,99,48,46,57,45,52,46,57,51,55,44,48,46,52,55,51,45,56,
46,53,45,49,46,50,55,50,45,49,48,46,53,57,50,99,45,49,46,54,56,49,45,50,46,48,49,54,45,52,46,55,55,49,45,50,46,57,57,53,45,57,46,52,52,55,45,50,46,57,57,53,13,10,9,9,99,45,57,46,55,53,54,44,48,45,49,52,
46,57,50,49,44,52,46,52,54,49,45,49,54,46,55,52,54,44,49,52,46,52,54,53,99,45,49,46,56,51,57,44,49,48,46,49,48,52,44,48,46,55,54,57,44,49,56,46,49,51,50,44,50,48,46,49,50,54,44,51,51,46,57,54,55,99,50,
51,46,51,51,56,44,49,57,46,50,49,55,44,51,48,46,54,49,52,44,51,52,46,48,50,53,44,50,54,46,56,53,52,44,53,52,46,54,52,51,13,10,9,9,67,53,52,51,46,50,57,55,44,49,56,49,46,55,53,53,44,53,50,50,46,54,49,54,
44,49,57,55,46,51,57,54,44,52,57,48,46,50,53,51,44,49,57,55,46,51,57,54,76,52,57,48,46,50,53,51,44,49,57,55,46,51,57,54,122,34,47,62,13,10,9,60,112,97,116,104,32,102,105,108,108,61,34,35,70,70,70,70,70,
70,34,32,100,61,34,77,54,49,51,46,48,53,51,44,49,57,53,46,52,56,49,104,45,51,55,46,50,55,55,108,50,54,46,49,49,49,45,49,52,51,46,50,57,51,104,45,51,51,46,55,54,57,108,53,46,50,54,45,50,56,46,55,56,57,
104,49,48,52,46,55,57,54,108,45,53,46,50,52,56,44,50,56,46,55,56,57,104,45,51,51,46,55,53,55,13,10,9,9,76,54,49,51,46,48,53,51,44,49,57,53,46,52,56,49,76,54,49,51,46,48,53,51,44,49,57,53,46,52,56,49,122,
34,47,62,13,10,60,47,103,62,13,10,60,47,115,118,103,62,13,10,0,0};

const char* TradeInterfaceComponent::burst_logo_white_svg = (const char*) resource_TradeInterfaceComponent_burst_logo_white_svg;
const int TradeInterfaceComponent::burst_logo_white_svgSize = 3258;

// JUCER_RESOURCE: bursticonblue_svg, 1273, "img/burst-icon-blue.svg"
static const unsigned char resource_TradeInterfaceComponent_bursticonblue_svg[] = { 60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,110,99,111,100,105,110,103,61,34,117,116,102,
45,56,34,63,62,13,10,60,33,45,45,32,71,101,110,101,114,97,116,111,114,58,32,65,100,111,98,101,32,73,108,108,117,115,116,114,97,116,111,114,32,49,52,46,48,46,48,44,32,83,86,71,32,69,120,112,111,114,116,
32,80,108,117,103,45,73,110,32,46,32,83,86,71,32,86,101,114,115,105,111,110,58,32,54,46,48,48,32,66,117,105,108,100,32,52,51,51,54,51,41,32,32,45,45,62,13,10,60,33,68,79,67,84,89,80,69,32,115,118,103,
32,80,85,66,76,73,67,32,34,45,47,47,87,51,67,47,47,68,84,68,32,83,86,71,32,49,46,49,47,47,69,78,34,32,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,71,114,97,112,104,105,99,115,47,
83,86,71,47,49,46,49,47,68,84,68,47,115,118,103,49,49,46,100,116,100,34,62,13,10,60,115,118,103,32,118,101,114,115,105,111,110,61,34,49,46,49,34,32,105,100,61,34,67,97,108,113,117,101,95,49,34,32,120,
109,108,110,115,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,32,120,109,108,110,115,58,120,108,105,110,107,61,34,104,116,116,112,58,47,47,119,119,
119,46,119,51,46,111,114,103,47,49,57,57,57,47,120,108,105,110,107,34,32,120,61,34,48,112,120,34,32,121,61,34,48,112,120,34,13,10,9,32,119,105,100,116,104,61,34,51,53,51,112,120,34,32,104,101,105,103,
104,116,61,34,51,52,50,112,120,34,32,118,105,101,119,66,111,120,61,34,48,32,48,32,51,53,51,32,51,52,50,34,32,101,110,97,98,108,101,45,98,97,99,107,103,114,111,117,110,100,61,34,110,101,119,32,48,32,48,
32,51,53,51,32,51,52,50,34,32,120,109,108,58,115,112,97,99,101,61,34,112,114,101,115,101,114,118,101,34,62,13,10,60,103,62,13,10,9,60,99,105,114,99,108,101,32,102,105,108,108,61,34,35,48,48,53,55,57,68,
34,32,99,120,61,34,49,55,54,46,53,34,32,99,121,61,34,49,55,49,34,32,114,61,34,49,51,55,46,50,51,55,34,47,62,13,10,9,60,103,62,13,10,9,9,60,112,97,116,104,32,102,105,108,108,61,34,35,70,70,70,70,70,70,
34,32,100,61,34,77,49,49,56,46,57,50,57,44,49,56,48,46,48,51,50,108,45,54,46,48,54,57,44,50,53,46,56,48,50,108,45,55,51,46,49,49,52,45,50,51,46,50,55,54,72,56,54,46,53,53,108,54,46,48,55,50,45,50,56,46,
51,50,56,108,52,54,46,54,50,50,44,48,46,48,51,50,108,49,51,46,53,57,57,45,55,51,46,51,56,54,104,53,50,46,54,50,57,13,10,9,9,9,99,51,54,46,49,52,52,44,48,44,52,57,46,49,53,50,44,49,51,46,54,53,44,52,51,
46,57,57,56,44,52,49,46,52,53,56,108,45,49,46,49,57,44,54,46,52,51,56,99,45,51,46,52,52,44,49,56,46,53,51,57,45,49,50,46,53,54,50,44,51,48,46,49,50,50,45,50,57,46,49,56,56,44,51,54,46,48,52,51,108,45,
48,46,48,57,56,44,48,46,53,49,56,13,10,9,9,9,99,49,55,46,54,49,44,53,46,57,50,49,44,50,50,46,52,50,50,44,49,57,46,51,49,51,44,49,56,46,56,57,49,44,51,56,46,51,54,54,108,45,50,46,55,49,57,44,49,52,46,54,
55,53,99,45,53,46,49,53,52,44,50,55,46,56,49,49,45,50,53,46,57,57,54,44,52,50,46,55,52,54,45,54,48,46,56,55,44,52,50,46,55,52,54,104,45,53,52,46,56,53,49,108,49,53,46,48,50,54,45,56,49,46,48,56,56,72,
49,49,56,46,57,50,57,13,10,9,9,9,122,32,77,49,54,57,46,51,52,57,44,49,56,48,46,48,49,50,108,45,49,48,46,50,53,54,44,53,53,46,51,53,55,104,49,57,46,57,55,53,99,49,49,46,55,51,49,44,48,44,49,56,46,56,56,
49,45,52,46,51,55,56,44,50,49,46,51,54,45,49,55,46,55,54,55,108,50,46,57,49,50,45,49,53,46,55,48,57,13,10,9,9,9,99,51,46,48,57,57,45,49,54,46,55,51,50,45,50,46,54,48,52,45,50,49,46,56,56,51,45,49,56,46,
52,53,55,45,50,49,46,56,56,51,76,49,54,57,46,51,52,57,44,49,56,48,46,48,49,50,76,49,54,57,46,51,52,57,44,49,56,48,46,48,49,50,122,32,77,49,56,50,46,57,52,55,44,49,48,54,46,54,50,55,108,45,56,46,56,50,
54,44,52,55,46,54,51,54,104,49,51,46,54,51,50,13,10,9,9,9,99,49,50,46,57,57,54,44,48,44,50,49,46,55,55,56,45,52,46,54,51,54,44,50,52,46,52,53,49,45,49,57,46,48,53,53,108,49,46,56,54,50,45,49,48,46,48,
52,50,99,50,46,51,56,54,45,49,50,46,56,55,50,45,49,46,57,53,51,45,49,56,46,53,51,56,45,49,52,46,51,49,55,45,49,56,46,53,51,56,76,49,56,50,46,57,52,55,44,49,48,54,46,54,50,55,76,49,56,50,46,57,52,55,44,
49,48,54,46,54,50,55,122,34,47,62,13,10,9,60,47,103,62,13,10,60,47,103,62,13,10,60,47,115,118,103,62,13,10,0,0};

const char* TradeInterfaceComponent::bursticonblue_svg = (const char*) resource_TradeInterfaceComponent_bursticonblue_svg;
const int TradeInterfaceComponent::bursticonblue_svgSize = 1273;


//[EndFile] You can add extra defines here...
//[/EndFile]
