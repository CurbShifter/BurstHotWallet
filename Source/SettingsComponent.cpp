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
#define SERVERLISTURL "https://raw.githubusercontent.com/CurbShifter/BurstHotWallet/master/resources/serverlist.csv"
#define SERVERLIST "\"Burst - team Wallet\",\"https://wallet.burst-team.us:2083/\",\"mainnet\"\n\
					\"Burst-team Wallet 1\",\"https://wallet1.burst-team.us:2083/\",\"mainnet\"\n\
					\"Burst-team Wallet 2\",\"https://wallet2.burst-team.us:2083/\",\"mainnet\"\n\
					\"Burst-team Wallet 3\",\"https://wallet3.burst-team.us:2083/\",\"mainnet\"\n\
					\"Burst-team Wallet 4\",\"https://wallet4.burst-team.us:2083/\",\"mainnet\"\n\
					\"Burst-team Wallet 5\",\"https://wallet5.burst-team.us:2083/\",\"mainnet\"\n\
					\"burst-alliance\",\"https://wallet.burst-alliance.org:8125/\",\"mainnet\"\n\
					\"Cryptoguru\",\"https://wallet.burst.cryptoguru.org:8125\",\"mainnet\"\n\
					\"Poolofd32th wallet 1\",\"https://wallet.poolofd32th.club\",\"mainnet\"\n\
					\"Poolofd32th wallet 2\",\"https://wallet2.poolofd32th.club\",\"mainnet\"\n\
					\"localhost\",\"http://localhost:8125/\",\"localhost\"\n\
					\"getburst [testnet]\",\"http://testnet.getburst.net:6876/\",\"testnet\""

#define POOLLISTURL "https://raw.githubusercontent.com/CurbShifter/BurstHotWallet/master/resources/poollist.csv"
#define POOLLIST "\"BMF50 Marketing Pool\",\"bmf50pool.burstcoin.ro\",\"8080\",\"BURST-S8Z2-TQ7W-ECVP-FM4FP\",\"16711252963\"\n\
					\"CryptoGuru Pool 50/50\",\"50-50-pool.burst.cryptoguru.org\",\"8124\",\"BURST-8KLL-PBYV-6DBC-AM942\",\"31536000\"\n\
					\"CryptoGuru Pool 0-100\",\"0-100-pool.burst.cryptoguru.org\",\"8124\",\"BURST-HKML-NRG6-VBRA-2F8PS\",\"31536000\"\n\
					\"Fastpool.info\",\"fastpool.info\",\"8080\",\"BURST-YMJP-8NNG-6HCJ-29XYJ\",\"80000000\"\n\
					\"pool poolofd32th\",\"pool.poolofd32th.club\",\"8124\",\"BURST-GATX-U4KB-7AWU-H3N8S\",\"2592000\"\n\
					\"VLP Pool 0/100\",\"voiplanparty.com\",\"8124\",\"BURST-MBCG-4ERH-FVH5-2GTXB\",\"31536000\"\n\
					\"xen poolofd32th\",\"xen.poolofd32th.club\",\"8122\",\"BURST-LBQ2-XLPT-S2S8-64ZG5\",\"2592000\"\n\
					\"0-100 burst-team us\",\"0-100.burst-team.us\",\"8080\",\"BURST-YBW4-A3D3-LVUF-F9WVJ\",\"10368000\"\n\
					\"pool burst-team us\",\"pool.burst-team.us\",\"8080\",\"BURST-WRM9-F6JU-NVX5-D7VXS\",\"2592000\"\n\
					\"burstneon.com\",\"burstneon.com\",\"8080\",\"BURST-YXZW-JH7M-QKR9-9PKBN\",\"63072000\"\n\
					\"burstcoin.ro\",\"pool.burstcoin.ro\",\"8080\",\"BURST-GG4B-34Y9-ZXGV-FNTNJ\",\"7889231\"\n\
					\"burstcoin.space\",\"pool.burstcoin.space\",\"8124\",\"BURST-SPAC-EWWF-CRX2-78Z6Z\",\"2592000\"\n\
					\"Burst Minig club\",\"pool.burstmining.club\",\"8124\",\"BURST-RNMB-9FJW-3BJW-F3Z3M\",\"86400\"\n\
					\"BurstPool Cloud\",\"burstpool.cloud\",\"8124\",\"BURST-DYDN-98Z8-YJMY-E2KD4\",\"63072000\"\n\
					\"0-100pool.burstcoin.ro\",\"0-100pool.burstcoin.ro\",\"8880\",\"BURST-NEWP-R7WE-KUH3-3336G\",\"31536000\"\n\
					\"burstcoin.ml\",\"pool.burstcoin.ml\",\"8080\",\"BURST-85W6-5P5V-7VLZ-GZJEF\",\"31536000\"\n\
					\"moverspool.ml\",\"moverspool.ml\",\"8080\",\"BURST-2FMM-EMKQ-9WQR-8DB52\",\"31104000\""

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
    myPassPhraseButton->setButtonText (TRANS("My account"));
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

    addAndMakeVisible (getKeyButton = new TextButton ("getKeyButton"));
    getKeyButton->setTooltip (TRANS("opens default browser"));
    getKeyButton->setButtonText (TRANS("get key"));
    getKeyButton->addListener (this);
    getKeyButton->setColour (TextButton::buttonColourId, Colours::white);
    getKeyButton->setColour (TextButton::buttonOnColourId, Colours::white);
    getKeyButton->setColour (TextButton::textColourOffId, Colours::black);
    getKeyButton->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (nodeComboBox = new ComboBox ("nodeComboBox"));
    nodeComboBox->setTooltip (TRANS("Can be testnet or main net. However it is recommened not to use the your same wallet account on both."));
    nodeComboBox->setEditableText (true);
    nodeComboBox->setJustificationType (Justification::centredLeft);
    nodeComboBox->setTextWhenNothingSelected (TRANS("local or external node address"));
    nodeComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    nodeComboBox->addItem (TRANS("wallet.burst-team.us:2083"), 1);
    nodeComboBox->addItem (TRANS("localhost:8125"), 2);
    nodeComboBox->addItem (TRANS("testnet.getburst.net:6876"), 3);
    nodeComboBox->addListener (this);

    addAndMakeVisible (nodeAddressButton = new TextButton ("nodeAddressButton"));
    nodeAddressButton->setTooltip (TRANS("Pop-up menu with node address options"));
    nodeAddressButton->setButtonText (TRANS("Node address"));
    nodeAddressButton->addListener (this);
    nodeAddressButton->setColour (TextButton::buttonColourId, Colours::white);
    nodeAddressButton->setColour (TextButton::buttonOnColourId, Colours::white);
    nodeAddressButton->setColour (TextButton::textColourOffId, Colours::black);
    nodeAddressButton->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (setRewardRecipientButton = new TextButton ("setRewardRecipientButton"));
    setRewardRecipientButton->setTooltip (TRANS("set the pool mining recipient. Enter an address or alias of the pool to which you are mining to. (using cheap fee)"));
    setRewardRecipientButton->setButtonText (TRANS("set"));
    setRewardRecipientButton->addListener (this);
    setRewardRecipientButton->setColour (TextButton::buttonColourId, Colours::white);
    setRewardRecipientButton->setColour (TextButton::buttonOnColourId, Colours::white);
    setRewardRecipientButton->setColour (TextButton::textColourOffId, Colours::black);
    setRewardRecipientButton->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (poolComboBox = new ComboBox ("poolComboBox"));
    poolComboBox->setTooltip (TRANS("set the pool mining recipient. Enter an address or alias of the pool to which you are mining to. Or your own address for solo."));
    poolComboBox->setEditableText (true);
    poolComboBox->setJustificationType (Justification::centredLeft);
    poolComboBox->setTextWhenNothingSelected (TRANS("address of mining pool"));
    poolComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    poolComboBox->addItem (TRANS("BMF 50 pool BURST-S8Z2-TQ7W-ECVP-FM4FP"), 1);
    poolComboBox->addListener (this);

    addAndMakeVisible (accountNameTextEditor = new TextEditor ("accountNameTextEditor"));
    accountNameTextEditor->setTooltip (TRANS("The public account name. Often viewable on explorers."));
    accountNameTextEditor->setMultiLine (false);
    accountNameTextEditor->setReturnKeyStartsNewLine (false);
    accountNameTextEditor->setReadOnly (false);
    accountNameTextEditor->setScrollbarsShown (false);
    accountNameTextEditor->setCaretVisible (true);
    accountNameTextEditor->setPopupMenuEnabled (true);
    accountNameTextEditor->setText (String());

    addAndMakeVisible (accountDescriptionTextEditor = new TextEditor ("accountDescriptionTextEditor"));
    accountDescriptionTextEditor->setTooltip (TRANS("A brief public description of this account. Often viewable on explorers"));
    accountDescriptionTextEditor->setMultiLine (false);
    accountDescriptionTextEditor->setReturnKeyStartsNewLine (false);
    accountDescriptionTextEditor->setReadOnly (false);
    accountDescriptionTextEditor->setScrollbarsShown (false);
    accountDescriptionTextEditor->setCaretVisible (true);
    accountDescriptionTextEditor->setPopupMenuEnabled (true);
    accountDescriptionTextEditor->setText (String());

    addAndMakeVisible (poolLabel = new Label ("poolLabel",
                                              TRANS("Mining reward recipient")));
    poolLabel->setFont (Font (15.00f, Font::plain));
    poolLabel->setJustificationType (Justification::centredRight);
    poolLabel->setEditable (false, false, false);
    poolLabel->setColour (TextEditor::textColourId, Colours::black);
    poolLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nameLabel = new Label ("nameLabel",
                                              TRANS("Account name")));
    nameLabel->setFont (Font (15.00f, Font::plain));
    nameLabel->setJustificationType (Justification::centredRight);
    nameLabel->setEditable (false, false, false);
    nameLabel->setColour (TextEditor::textColourId, Colours::black);
    nameLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (descriptionLabel = new Label ("descriptionLabel",
                                                     TRANS("Description")));
    descriptionLabel->setTooltip (TRANS("a brief public description of this account"));
    descriptionLabel->setFont (Font (15.00f, Font::plain));
    descriptionLabel->setJustificationType (Justification::centredRight);
    descriptionLabel->setEditable (false, false, false);
    descriptionLabel->setColour (TextEditor::textColourId, Colours::black);
    descriptionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (setAccountButton = new TextButton ("setAccountButton"));
    setAccountButton->setTooltip (TRANS("set the name and description if not empty. (using standard fee)"));
    setAccountButton->setButtonText (TRANS("set account info"));
    setAccountButton->addListener (this);
    setAccountButton->setColour (TextButton::buttonColourId, Colours::white);
    setAccountButton->setColour (TextButton::buttonOnColourId, Colours::white);
    setAccountButton->setColour (TextButton::textColourOffId, Colours::black);
    setAccountButton->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (aliasesComboBox = new ComboBox ("aliasesComboBox"));
    aliasesComboBox->setTooltip (TRANS("Aliases with alphanumeric characters"));
    aliasesComboBox->setEditableText (true);
    aliasesComboBox->setJustificationType (Justification::centredLeft);
    aliasesComboBox->setTextWhenNothingSelected (TRANS("your unique aliases"));
    aliasesComboBox->setTextWhenNoChoicesAvailable (TRANS("empty"));
    aliasesComboBox->addListener (this);

    addAndMakeVisible (aliasesLabel = new Label ("aliasesLabel",
                                                 TRANS("Aliases")));
    aliasesLabel->setFont (Font (15.00f, Font::plain));
    aliasesLabel->setJustificationType (Justification::centredRight);
    aliasesLabel->setEditable (false, false, false);
    aliasesLabel->setColour (TextEditor::textColourId, Colours::black);
    aliasesLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (addAliasButton = new TextButton ("addAliasButton"));
    addAliasButton->setTooltip (TRANS("add an alias if its available (using standard fee)"));
    addAliasButton->setButtonText (TRANS("add"));
    addAliasButton->addListener (this);
    addAliasButton->setColour (TextButton::buttonColourId, Colours::white);
    addAliasButton->setColour (TextButton::buttonOnColourId, Colours::white);
    addAliasButton->setColour (TextButton::textColourOffId, Colours::black);
	addAliasButton->setColour(TextButton::textColourOnId, Colours::black);


	//[UserPreSize]
	{
		nodeComboBox->clear();
		URL url(SERVERLISTURL);
		String serversCSV = url.readEntireTextStream();
		StringArray lines;
		if (serversCSV.isEmpty() || serversCSV.contains("mainnet") == false)
			serversCSV = SERVERLIST;
		lines = StringArray::fromTokens(serversCSV, "\n", "");
		for (int i = 0; i < lines.size(); i++)
		{
			StringArray c = StringArray::fromTokens(lines[i].trim(), ",", "\"");
			if (c.size() > 1)
				nodeComboBox->addItem(c[1].unquoted(), i + 1);
		}
	}
	{
		poolComboBox->clear();
		URL url(POOLLISTURL);
		String poolCSV = url.readEntireTextStream();
		StringArray lines;
		if (poolCSV.isEmpty() || poolCSV.contains("\",\"") == false)
			poolCSV = POOLLIST;
		lines = StringArray::fromTokens(poolCSV, "\n", "");
		for (int i = 0; i < lines.size(); i++)
		{
			StringArray c = StringArray::fromTokens(lines[i].trim(), ",", "\"");
			if (c.size() > 1)
				poolComboBox->addItem(c[0].unquoted() + " - "+ c[3].unquoted(), i + 1);
		}
	}	

	passPhraseTextEditor->setMultiLine(false);
	passPhraseTextEditor->setReturnKeyStartsNewLine(false);
	passPhraseTextEditor->setReadOnly(false);
	passPhraseTextEditor->setScrollbarsShown(false);
	passPhraseTextEditor->setCaretVisible(true);
	passPhraseTextEditor->setPopupMenuEnabled(true);
	passPhraseTextEditor->setPasswordCharacter(0x2022);
	passPhraseTextEditor->addListener(this);
	passPhraseTextEditor->setTextToShowWhenEmpty("My wallet pass phrase", Colours::grey);
	passPhraseTextEditor->setVisible(false);

	cmcTextEditor->setTextToShowWhenEmpty("coinmarketcap.com API key (not affiliated)", Colours::grey);
	cmcTextEditor->addListener(this);
	cmcTextEditor->setVisible(false);
	getKeyButton->setVisible(false);

	accountNameTextEditor->addListener(this);
	accountDescriptionTextEditor->addListener(this);

	currencyType = 0;
	addAliasButton->setEnabled(false);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	EnableControls(true);

	//startTimer(1000 * 60 * 4); // 4 min
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
    getKeyButton = nullptr;
    nodeComboBox = nullptr;
    nodeAddressButton = nullptr;
    setRewardRecipientButton = nullptr;
    poolComboBox = nullptr;
    accountNameTextEditor = nullptr;
    accountDescriptionTextEditor = nullptr;
    poolLabel = nullptr;
    nameLabel = nullptr;
    descriptionLabel = nullptr;
    setAccountButton = nullptr;
    aliasesComboBox = nullptr;
    aliasesLabel = nullptr;
    addAliasButton = nullptr;


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

    passPhraseTextEditor->setBounds (424, 80, 152, 24);
    lockButton->setBounds (40, 392, 120, 24);
    myPassPhraseButton->setBounds (40, 80, 120, 24);
    cmcButton->setBounds (40, 360, 120, 24);
    cmcTextEditor->setBounds (160, 360, 264, 24);
    getKeyButton->setBounds (432, 360, 120, 24);
    nodeComboBox->setBounds (160, 24, 392, 24);
    nodeAddressButton->setBounds (40, 24, 120, 24);
    setRewardRecipientButton->setBounds (432, 208, 120, 24);
    poolComboBox->setBounds (160, 208, 264, 24);
    accountNameTextEditor->setBounds (160, 112, 264, 24);
    accountDescriptionTextEditor->setBounds (160, 144, 264, 24);
    poolLabel->setBounds (40, 208, 118, 24);
    nameLabel->setBounds (40, 112, 118, 24);
    descriptionLabel->setBounds (40, 144, 118, 24);
    setAccountButton->setBounds (432, 144, 120, 24);
    aliasesComboBox->setBounds (160, 176, 264, 24);
    aliasesLabel->setBounds (40, 176, 118, 24);
    addAliasButton->setBounds (432, 176, 120, 24);
    //[UserResized] Add your own custom resize handling here..
	*/
	const int rowH = 30;
	const int pad = 15;
	const int spacer = 5;
	Rectangle<int> r = getBounds().withPosition(0, 0).reduced(pad);

	const int rowsNum = 12;
	Rectangle<int> r_[rowsNum];

	r_[0] = r.withHeight(rowH);
	for (int i = 0; i < rowsNum - 1; i++)
		r_[i+1] = r_[i].translated(0, rowH + spacer);

	/*Rectangle<int> r1 = r.withHeight(rowH);
	Rectangle<int> r2 = r1.translated(0, rowH + spacer);
	Rectangle<int> r3 = r2.translated(0, rowH + spacer);
	Rectangle<int> r4 = r3.translated(0, rowH + spacer);
	Rectangle<int> r5 = r4.translated(0, rowH + spacer);*/

	const int bw = 150;
	const int col3 = 120;
	int rowIdx = 0;
	nodeAddressButton->setBounds(r_[rowIdx].withWidth(bw));
	nodeComboBox->setBounds(r_[rowIdx].withTrimmedLeft(bw + 5));

	rowIdx += 2;

	myPassPhraseButton->setBounds(r_[rowIdx].withWidth(bw));
	passPhraseTextEditor->setBounds(r_[rowIdx].withTrimmedLeft(bw + 5));

	rowIdx++;
	nameLabel->setBounds(r_[rowIdx].withWidth(bw));
	accountNameTextEditor->setBounds(r_[rowIdx].withTrimmedLeft(bw + 5).withTrimmedRight(col3));
	rowIdx++;
	descriptionLabel->setBounds(r_[rowIdx].withWidth(bw));
	accountDescriptionTextEditor->setBounds(r_[rowIdx].withTrimmedLeft(bw + 5).withTrimmedRight(col3));
	setAccountButton->setBounds(r_[rowIdx].withTrimmedLeft(bw + 5 + 5 + accountDescriptionTextEditor->getWidth()));

	rowIdx++;
	aliasesLabel->setBounds(r_[rowIdx].withWidth(bw));
	aliasesComboBox->setBounds(r_[rowIdx].withTrimmedLeft(bw + 5).withTrimmedRight(col3));
	addAliasButton->setBounds(r_[rowIdx].withTrimmedLeft(bw + 5 + 5 + aliasesComboBox->getWidth()));

	rowIdx++;
	poolLabel->setBounds(r_[rowIdx].withWidth(bw));
	poolComboBox->setBounds(r_[rowIdx].withTrimmedLeft(bw + 5).withTrimmedRight(col3));
	setRewardRecipientButton->setBounds(r_[rowIdx].withTrimmedLeft(bw + 5 + 5 + poolComboBox->getWidth()));

	rowIdx+=2;

	cmcButton->setBounds(r_[rowIdx].withWidth(bw));
	cmcTextEditor->setBounds(r_[rowIdx].withTrimmedLeft(bw + 5).withTrimmedRight(col3));
	getKeyButton->setBounds(r_[rowIdx].withTrimmedLeft(bw + 5 + 5 + cmcTextEditor->getWidth()));
//	cpTextEditor->setBounds(r5.withTrimmedLeft(bw + 5));
	rowIdx += 2;

	lockButton->setBounds(r_[rowIdx].withWidth(bw));

#if ALLOW_EXT_REQ != 1
	//websocketButton->setVisible(false);
#endif
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
		contextMenu->addItem(9, "Copy public key to clipboard", true);
		contextMenu->addSeparator();
		contextMenu->addItem(1, "Change my access PIN code", true);
	/*	contextMenu->addItem(5, "Manual edit pass phrase", true, editingPassPhrase);
		contextMenu->addSeparator();
		contextMenu->addItem(3, "Import pass phrase (plain text!)", true);*/
		contextMenu->addItem(2, "Export pass phrase (plain text!)", true);
		contextMenu->addSeparator();
		contextMenu->addItem(6, "Generate new / import account", true);

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

			if (passPhraseTextEditor->isVisible())
				passPhraseTextEditor->setText(GetSecretPhrase(), dontSendNotification);
			else passPhraseTextEditor->setText("");
		}
		else if (result == 6)
		{// "Make new pass phrase"
			NewWallet();
		}
		else if (result == 7)
		{
			String addressRS(burstExt.GetAccountRS());
			SystemClipboard::copyTextToClipboard(addressRS);
			NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Address " + addressRS + "\nis copied to clipboard");
		}
		else if (result == 9)
		{
			interfaceListeners.call(&InterfaceListener::WalletPubKeyToClipboard, 0);
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

	//	if (cmcTextEditor->getText().isNotEmpty())
		{
			contextSubMenu->addItem(10, "BURST", true, currencyType == 0);
			contextSubMenu->addItem(11, "BTC", true, currencyType == 1);
			contextSubMenu->addItem(12, "USD", true, currencyType == 2);
			contextSubMenu->addItem(13, "EUR", true, currencyType == 3);
			contextSubMenu->addItem(14, "GBP", true, currencyType == 4);
		}
		contextMenu->addItem(9, "Prices are only for indication. No rights are given", false, false);

		contextMenu->addSubMenu("Display currency", *contextSubMenu, true);
		contextMenu->addItem(1, "Set coinmarketcap.com API key", true, editing);

		int result = contextMenu->show();
		if (result == 1)
		{
			cmcTextEditor->setVisible(!editing);
			getKeyButton->setVisible(!editing);
		}
		else if (result >= 10)
		{
			SetCurrencyType(result - 10);
		}

		contextMenu = nullptr;
		contextSubMenu = nullptr;
        //[/UserButtonCode_cmcButton]
    }
    else if (buttonThatWasClicked == getKeyButton)
    {
        //[UserButtonCode_getKeyButton] -- add your button handler code here..
		URL url("https://coinmarketcap.com/api/");
		url.launchInDefaultBrowser();
        //[/UserButtonCode_getKeyButton]
    }
    else if (buttonThatWasClicked == nodeAddressButton)
    {
        //[UserButtonCode_nodeAddressButton] -- add your button handler code here..
		ScopedPointer<PopupMenu> contextMenu;
		contextMenu = new PopupMenu;

		String forceSSLOnStr, hopOnStr;
		interfaceListeners.call(&InterfaceListener::GetAppValue, "hopOn", hopOnStr);
		interfaceListeners.call(&InterfaceListener::GetAppValue, "forceSSLOn", forceSSLOnStr);
		bool hopOn = hopOnStr.getIntValue() > 0;
		bool forceSSLOn = forceSSLOnStr.getIntValue() > 0;

		contextMenu->addItem(2, "force https SSL/TSL (excludes nodes without SSL certificates)", true, forceSSLOn);
		contextMenu->addItem(1, "enable node hopping (distribute your precence in the network)", false, hopOn);

		int result = contextMenu->show();
		if (result == 1)
		{
			hopOn = !hopOn; // toggle
			interfaceListeners.call(&InterfaceListener::SetNodeHop, hopOn);
		}
		else if (result == 2)
		{
			forceSSLOn = !forceSSLOn; // toggle
			interfaceListeners.call(&InterfaceListener::SetForceSSL_TSL, forceSSLOn);
		}

		contextMenu = nullptr;
        //[/UserButtonCode_nodeAddressButton]
    }
    else if (buttonThatWasClicked == setRewardRecipientButton)
    {
        //[UserButtonCode_setRewardRecipientButton] -- add your button handler code here..
		String poolSelection = poolComboBox->getText().trim();
		if (poolSelection.length() >= 26)
		{
			poolSelection = poolSelection.substring(poolSelection.length() - 26, poolSelection.length());
			String recipient = burstExt.ensureAccountRS(poolSelection);
			if (NativeMessageBox::showOkCancelBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Set the account reward recipient to " + recipient + " ?\n(cheap fee)"))
			{
				String str = burstExt.setRewardRecipient(recipient, "cheap", "1440");
				if (burstExt.GetJSONvalue(str, "transaction").isNotEmpty())
					NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "New account reward recipient has been sent.\n\nPlease be patient while it is mined and verified. (~30 min)");
				else NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Failed to set the account reward recipient !\n" + burstExt.GetJSONvalue(str, "errorDescription"));
			}
		}
        //[/UserButtonCode_setRewardRecipientButton]
    }
    else if (buttonThatWasClicked == setAccountButton)
    {
        //[UserButtonCode_setAccountButton] -- add your button handler code here..
		String name_ = accountNameTextEditor->getText();
		String description_ = accountDescriptionTextEditor->getText();

		if (NativeMessageBox::showOkCancelBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Set the account name & description info? (cheap fee)\n" + name_ + "\n" + description_ + "\n"))
		{
			String str = burstExt.setAccountInfo(name_, description_, "cheap", "1440");
			if (burstExt.GetJSONvalue(str, "transaction").isNotEmpty())
				NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "New account name & description has been sent. Please be patient while it is mined and verified.");
			else NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Failed to set the account info !\n" + burstExt.GetJSONvalue(str, "errorDescription"));
		}
        //[/UserButtonCode_setAccountButton]
    }
    else if (buttonThatWasClicked == addAliasButton)
    {
        //[UserButtonCode_addAliasButton] -- add your button handler code here..
		String newAlias = aliasesComboBox->getText().trim();
		if (NativeMessageBox::showOkCancelBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Set alias " + newAlias + " ?\n(cheap fee)"))
		{
			String aliasURI = "acct:" + burstExt.GetAccountRS().toLowerCase() + "@burst";
			String str = burstExt.setAlias(newAlias, aliasURI, "cheap", "1440");
			if (burstExt.GetJSONvalue(str, "transaction").isNotEmpty())
				NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Transaction has been sent. Please be patient while it is mined and verified.");
			else NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Failed to set the alias !\n" + burstExt.GetJSONvalue(str, "errorDescription"));
		}
        //[/UserButtonCode_addAliasButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void SettingsComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == nodeComboBox)
    {
        //[UserComboBoxCode_nodeComboBox] -- add your combo box handling code here..
		interfaceListeners.call(&InterfaceListener::SetAppValue, "server", nodeComboBox->getText());
        //[/UserComboBoxCode_nodeComboBox]
    }
    else if (comboBoxThatHasChanged == poolComboBox)
    {
        //[UserComboBoxCode_poolComboBox] -- add your combo box handling code here..
		setRewardRecipientButton->setEnabled(true);
        //[/UserComboBoxCode_poolComboBox]
    }
    else if (comboBoxThatHasChanged == aliasesComboBox)
    {
        //[UserComboBoxCode_aliasesComboBox] -- add your combo box handling code here..
		addAliasButton->setEnabled(aliasesArray.contains(aliasesComboBox->getText()) == false && aliasesComboBox->getText().isNotEmpty());
        //[/UserComboBoxCode_aliasesComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SettingsComponent::SetNode(const String server, const bool allowNonSSL)
{
	burstExt.SetNode(server, allowNonSSL);
	nodeComboBox->setText(server, dontSendNotification);
}

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
	if (accountNameTextEditor == &editor || accountDescriptionTextEditor == &editor)
	{ // enable the set account button if the data changed
		setAccountButton->setEnabled(accountNameTextEditor->getText().compare(name) != 0 || accountDescriptionTextEditor->getText().compare(description) != 0);
	}
}

void SettingsComponent::textEditorReturnKeyPressed(TextEditor &editor) //Called when the user presses the return key.
{
	if (passPhraseTextEditor == &editor)
	{
		interfaceListeners.call(&InterfaceListener::SavePassPhraseWithNewPIN, GetSecretPhrase());
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
void SettingsComponent::textEditorFocusLost(TextEditor &/*editor*/) //Called when the text editor loses focus.
{
}

String SettingsComponent::GetSecretPhrase()
{
	return burstExt.GetSecretPhraseString(); // from here the phrase will be exposed in the device memory
}

void SettingsComponent::SetForceSSL_TSL(const bool forceSSLOn)
{
	burstExt.SetForceSSL_TSL(forceSSLOn);
}

void SettingsComponent::SetNodeHop(const bool hopOn)
{
	burstExt.EnableNodeHop(hopOn ? 7 : 0);
}

void SettingsComponent::SetSecretPhrase(const String passphrase)
{
	burstExt.SetSecretPhrase(passphrase, 0);

	if (passPhraseTextEditor->isVisible())
		passPhraseTextEditor->setText(GetSecretPhrase(), dontSendNotification);

	if (passPhraseTextEditor->getText().length() >= 35)
		passPhraseTextEditor->setColour(TextEditor::backgroundColourId, Colours::white);
	else passPhraseTextEditor->setColour(TextEditor::backgroundColourId, Colours::red);

	if (passphrase.isNotEmpty())
		UpdateAccountData();
	// else todo clear
}

void SettingsComponent::timerCallback()
{
	UpdateAccountData();
}

void SettingsComponent::UpdateAccountData()
{
	String getAccountStr = burstExt.getAccount(burstExt.GetAccountRS());
	var jsonStructure;
	Result r = JSON::parse(getAccountStr, jsonStructure);
	name = jsonStructure["name"];
	description = jsonStructure["description"];

	accountNameTextEditor->setText(name, dontSendNotification);
	accountDescriptionTextEditor->setText(description, dontSendNotification);
	setAccountButton->setEnabled(false);

	aliasesComboBox->clear();
	aliasesArray.clear();
	String aliases = burstExt.getAliases(burstExt.GetAccountRS());
	var aliasesJson;
	Result r2 = JSON::parse(aliases, aliasesJson);
	if (aliasesJson["aliases"].isArray())
	{
		for (int i = 0; i < aliasesJson["aliases"].size(); i++)
		{
			aliasesArray.add(aliasesJson["aliases"][i]["aliasName"]);
		}
		aliasesComboBox->addItemList(aliasesArray, 1);
		aliasesComboBox->setSelectedItemIndex(0);
	}

	const String rewardRecipientJsonStr = burstExt.getRewardRecipient(burstExt.GetAccountRS());
	const String rewardRecipientStr = burstExt.GetJSONvalue(rewardRecipientJsonStr, "rewardRecipient");
	const String rewardRecipientRS = burstExt.ensureAccountRS(rewardRecipientStr);
	if (rewardRecipientRS.isNotEmpty())
	{
		int idx = -1;
		for (int i = 0; i < poolComboBox->getNumItems(); i++)
		{
			if (poolComboBox->getItemText(i).contains(rewardRecipientRS))
				idx = i;
		}
		if (idx >= 0)
			poolComboBox->setSelectedItemIndex(idx, dontSendNotification);
		else if (rewardRecipientRS.isNotEmpty())
			poolComboBox->setText(rewardRecipientRS, dontSendNotification);
		setRewardRecipientButton->setEnabled(false);
	}
}

void SettingsComponent::EnableControls(const bool on)
{
	passPhraseTextEditor->setEnabled(on);
}

void SettingsComponent::ExportWallet()
{
	FileChooser myChooser("Select the location to save your wallet pass phrase...", File::getSpecialLocation(File::userDesktopDirectory), "*.*");
	String addressRS(burstExt.GetAccountRS());
	if (myChooser.browseForDirectory() && addressRS.isNotEmpty())
	{
		File f = myChooser.getResult().getChildFile(addressRS).withFileExtension("txt");
		f.appendText(GetSecretPhrase());

		if (myChooser.getResult().getChildFile(addressRS).withFileExtension("txt").existsAsFile())
			NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "File saved !\n\nSecurly backup the pass phrase file and keep it private !\n" + f.getFullPathName());
		else NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Failed to create file !\n" + f.getFullPathName());
	}
}

void SettingsComponent::ImportWallet()
{
	if (NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, "Import a wallet pass phrase from a file?\nMake sure to BACKUP YOUR CURRENT PASS PHRASE!\nHotWallet only holds 1 account at a time.") == 1)
	{
		FileChooser myChooser("Select the wallet pass phrase file...", File::getSpecialLocation(File::userDesktopDirectory), "*.*");
		if (myChooser.browseForFileToOpen())
		{
			File f = myChooser.getResult();
			StringArray lines;
			f.readLines(lines);
			String passPhrase = lines[0];
		//	String passPhrasePC = lines.size() > 0 ? lines[1] : String::empty;

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
		interfaceListeners.call(&InterfaceListener::SavePassPhraseWithNewPIN, GetSecretPhrase());
	}
}

void SettingsComponent::CreateWallet()
{
	String passPhrase;
	interfaceListeners.call(&InterfaceListener::CreateWallet);
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
	if (NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, "Create new / import wallet pass phrase?\nMake sure you have a BACKUP OF YOUR PASS PHRASE!\nHotWallet only holds 1 account at a time.") == 1)
	{
		CreateWallet();
	}
}
/*
void SettingsComponent::CollectComboBoxNodes()
{
	// goto burst apps team github and read ips from conf file


	burstExt
}
*/
void SettingsComponent::ShowHttpPopup()
{
#if ALLOW_EXT_REQ == 1
	String websocketsStr;
	interfaceListeners.call(&InterfaceListener::GetAppValue, "httpsocket", websocketsStr);
	bool websockets = websocketsStr.getIntValue() > 0;

	ScopedPointer<PopupMenu> contextMenu;
	contextMenu = new PopupMenu;

	contextMenu->addItem(1, "Allow browser requests", true, websockets);
	contextMenu->addItem(2, "Show browser request example page", true);
	int result = contextMenu->show();
	if (result == 1)
	{
		if (!websockets)
		{
			if (NativeMessageBox::showOkCancelBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Allow external pay requests?\nIt will need local networking on port 41137"))
			{
				interfaceListeners.call(&InterfaceListener::SetAppValue, "httpsocket", String(1));
				bool ok = false;
				interfaceListeners.call(&InterfaceListener::OpenHttpSocket, "127.0.0.1", 8080, ok);
			}
		}
		else
		{
			interfaceListeners.call(&InterfaceListener::SetAppValue, "httpsocket", String(0));
			interfaceListeners.call(&InterfaceListener::CloseHttpSocket);
		}
	}
	else if (result == 2)
	{
		URL url("https://curbshifter.github.io/BurstHotWallet/PayButtonDemo.html");
		url.launchInDefaultBrowser();
	}
#endif
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SettingsComponent" componentName=""
                 parentClasses="public TextEditorListener, public Component, public SettingsListener, public Timer"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffdfdfdf"/>
  <TEXTEDITOR name="passPhraseTextEditor" id="f0cbabb6811d2f5" memberName="passPhraseTextEditor"
              virtualName="" explicitFocusOrder="0" pos="424 80 152 24" tooltip="Enter your existing pass phrase here. Or you can create a new wallet here. A red background indicates a phrase shorter than 35 characters, which is not recommended !"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTBUTTON name="lockButton" id="2b10438639a15113" memberName="lockButton"
              virtualName="" explicitFocusOrder="0" pos="40 392 120 24" tooltip="Locks the app now. And clears the pass phrase. You will need to enter the PIN to unlock it again."
              bgColOff="ffffffff" bgColOn="ffffffff" textCol="ff000000" textColOn="ff000000"
              buttonText="Log out" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="myPassPhraseButton" id="a57dbbdc113f5472" memberName="myPassPhraseButton"
              virtualName="" explicitFocusOrder="0" pos="40 80 120 24" tooltip="Pop-up menu with pass phrase options"
              bgColOff="ffffffff" bgColOn="ffffffff" textCol="ff000000" textColOn="ff000000"
              buttonText="My account" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="cmcButton" id="6d710c0347734f90" memberName="cmcButton"
              virtualName="" explicitFocusOrder="0" pos="40 360 120 24" tooltip="Pop-up menu with currency options"
              bgColOff="ffffffff" bgColOn="ffffffff" textCol="ff000000" textColOn="ff000000"
              buttonText="Currency type" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTEDITOR name="cmcTextEditor" id="40e0f00b7b45b6de" memberName="cmcTextEditor"
              virtualName="" explicitFocusOrder="0" pos="160 360 264 24" tooltip="Enter your coinmarketcap.com API key to view the amounts in other currency values."
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTBUTTON name="getKeyButton" id="bfbde25cea42c682" memberName="getKeyButton"
              virtualName="" explicitFocusOrder="0" pos="432 360 120 24" tooltip="opens default browser"
              bgColOff="ffffffff" bgColOn="ffffffff" textCol="ff000000" textColOn="ff000000"
              buttonText="get key" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="nodeComboBox" id="1aa07b18d7c2e0de" memberName="nodeComboBox"
            virtualName="" explicitFocusOrder="0" pos="160 24 392 24" tooltip="Can be testnet or main net. However it is recommened not to use the your same wallet account on both."
            editable="1" layout="33" items="wallet.burst-team.us:2083&#10;localhost:8125&#10;testnet.getburst.net:6876"
            textWhenNonSelected="local or external node address" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="nodeAddressButton" id="215f2fe3e006175a" memberName="nodeAddressButton"
              virtualName="" explicitFocusOrder="0" pos="40 24 120 24" tooltip="Pop-up menu with node address options"
              bgColOff="ffffffff" bgColOn="ffffffff" textCol="ff000000" textColOn="ff000000"
              buttonText="Node address" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="setRewardRecipientButton" id="e77fc513bd6b67c1" memberName="setRewardRecipientButton"
              virtualName="" explicitFocusOrder="0" pos="432 208 120 24" tooltip="set the pool mining recipient. Enter an address or alias of the pool to which you are mining to. (using cheap fee)"
              bgColOff="ffffffff" bgColOn="ffffffff" textCol="ff000000" textColOn="ff000000"
              buttonText="set" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="poolComboBox" id="72c476375a9f41de" memberName="poolComboBox"
            virtualName="" explicitFocusOrder="0" pos="160 208 264 24" tooltip="set the pool mining recipient. Enter an address or alias of the pool to which you are mining to. Or your own address for solo."
            editable="1" layout="33" items="BMF 50 pool BURST-S8Z2-TQ7W-ECVP-FM4FP"
            textWhenNonSelected="address of mining pool" textWhenNoItems="(no choices)"/>
  <TEXTEDITOR name="accountNameTextEditor" id="ce4c2bec32b82234" memberName="accountNameTextEditor"
              virtualName="" explicitFocusOrder="0" pos="160 112 264 24" tooltip="The public account name. Often viewable on explorers."
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="accountDescriptionTextEditor" id="af2bdb775e8462ce" memberName="accountDescriptionTextEditor"
              virtualName="" explicitFocusOrder="0" pos="160 144 264 24" tooltip="A brief public description of this account. Often viewable on explorers"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1"/>
  <LABEL name="poolLabel" id="ae56949c5949a8d1" memberName="poolLabel"
         virtualName="" explicitFocusOrder="0" pos="40 208 118 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Mining reward recipient" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="nameLabel" id="b003f261c26c7d9f" memberName="nameLabel"
         virtualName="" explicitFocusOrder="0" pos="40 112 118 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Account name" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="descriptionLabel" id="d00e126d74f88b88" memberName="descriptionLabel"
         virtualName="" explicitFocusOrder="0" pos="40 144 118 24" tooltip="a brief public description of this account"
         edTextCol="ff000000" edBkgCol="0" labelText="Description" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <TEXTBUTTON name="setAccountButton" id="fead80966fda6de0" memberName="setAccountButton"
              virtualName="" explicitFocusOrder="0" pos="432 144 120 24" tooltip="set the name and description if not empty. (using standard fee)"
              bgColOff="ffffffff" bgColOn="ffffffff" textCol="ff000000" textColOn="ff000000"
              buttonText="set account info" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <COMBOBOX name="aliasesComboBox" id="a5e5442855cb884b" memberName="aliasesComboBox"
            virtualName="" explicitFocusOrder="0" pos="160 176 264 24" tooltip="Aliases with alphanumeric characters"
            editable="1" layout="33" items="" textWhenNonSelected="your unique aliases"
            textWhenNoItems="empty"/>
  <LABEL name="aliasesLabel" id="edc03fc29ce676f2" memberName="aliasesLabel"
         virtualName="" explicitFocusOrder="0" pos="40 176 118 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Aliases" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <TEXTBUTTON name="addAliasButton" id="e83c547edaade8cc" memberName="addAliasButton"
              virtualName="" explicitFocusOrder="0" pos="432 176 120 24" tooltip="add an alias if its available (using standard fee)"
              bgColOff="ffffffff" bgColOn="ffffffff" textCol="ff000000" textColOn="ff000000"
              buttonText="add" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
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
