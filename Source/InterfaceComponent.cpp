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

#include "InterfaceComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "Logger.h"
#include "SettingsComponent.h"
#include "BurstLib-source.cpp"
#include "Version.h"

void InterfaceComponent::log(String message)
{
	ToLog(message);
}
//[/MiscUserDefs]

//==============================================================================
InterfaceComponent::InterfaceComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (serverComboBox = new ComboBox ("serverComboBox"));
    serverComboBox->setTooltip (TRANS("The wallet address. running a local node is recommended !"));
    serverComboBox->setEditableText (true);
    serverComboBox->setJustificationType (Justification::centredLeft);
    serverComboBox->setTextWhenNothingSelected (TRANS("http://localhost:8125/"));
    serverComboBox->setTextWhenNoChoicesAvailable (TRANS("enter a node address"));
    serverComboBox->addItem (TRANS("https://wallet.burst-team.us:2083/"), 1);
    serverComboBox->addItem (TRANS("http://localhost:8125/"), 2);
    serverComboBox->addItem (TRANS("http://3.16.150.48:6876/"), 3);
    serverComboBox->addListener (this);

    addAndMakeVisible (balanceLabel = new Label ("balanceLabel",
                                                 TRANS("EMPTY WALLET")));
    balanceLabel->setTooltip (TRANS("balance"));
    balanceLabel->setFont (Font (18.00f, Font::plain));
    balanceLabel->setJustificationType (Justification::centred);
    balanceLabel->setEditable (false, false, false);
    balanceLabel->setColour (Label::textColourId, Colours::white);
    balanceLabel->setColour (TextEditor::textColourId, Colours::black);
    balanceLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (accountButton = new TextButton ("accountButton"));
    accountButton->setTooltip (TRANS("show account options"));
    accountButton->setButtonText (TRANS("BURST-XXXX-XXXX-XXXX-XXXXX"));
    accountButton->addListener (this);
    accountButton->setColour (TextButton::buttonColourId, Colour (0x0077b517));
    accountButton->setColour (TextButton::buttonOnColourId, Colour (0xff77b517));
    accountButton->setColour (TextButton::textColourOffId, Colours::white);

    addAndMakeVisible (sendComponent = new SendComponent());
    sendComponent->setName ("sendComponent");

    addAndMakeVisible (historyButton = new TextButton ("historyButton"));
    historyButton->setButtonText (TRANS("history"));
    historyButton->addListener (this);
    historyButton->setColour (TextButton::buttonColourId, Colour (0xff77b517));
    historyButton->setColour (TextButton::buttonOnColourId, Colour (0xff77b517));

    addAndMakeVisible (sendButton = new TextButton ("sendButton"));
    sendButton->setButtonText (TRANS("send Burst"));
    sendButton->addListener (this);
    sendButton->setColour (TextButton::buttonColourId, Colour (0xff77b517));
    sendButton->setColour (TextButton::buttonOnColourId, Colour (0xff77b517));

    addAndMakeVisible (historyComponent = new HistoryComponent());
    historyComponent->setName ("historyComponent");

    addAndMakeVisible (versionLabel = new Label ("versionLabel",
                                                 TRANS("v0.1")));
    versionLabel->setFont (Font (12.00f, Font::plain));
    versionLabel->setJustificationType (Justification::centredRight);
    versionLabel->setEditable (false, false, false);
    versionLabel->setColour (Label::textColourId, Colours::white);
    versionLabel->setColour (TextEditor::textColourId, Colours::black);
    versionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (settingsComponent = new SettingsComponent());
    settingsComponent->setName ("settingsComponent");

    addAndMakeVisible (pinComponent = new PinComponent());
    pinComponent->setName ("pinComponent");

    addAndMakeVisible (aboutComponent = new AboutComponent());
    aboutComponent->setName ("aboutComponent");

    drawable1 = Drawable::createFromImageData (burstHotWalletlogo_svg, burstHotWalletlogo_svgSize);

    //[UserPreSize]
	sendComponent->setVisible(false);
    //[/UserPreSize]

    setSize (450, 650);


    //[Constructor] You can add your own custom stuff here..

	lastSendDataMs = 0;

	options.commonToAllUsers = false;
	options.applicationName = ProjectInfo::projectName;
	options.folderName = "CryptoExtensions";
	options.filenameSuffix = "settings";
	options.osxLibrarySubFolder = "Application Support";
	options.storageFormat = PropertiesFile::storeAsXML;
	appProp.setStorageParameters(options);

	if (settingsComponent)
	{
		addAndMakeVisible(settingsComponent);
		addSettingsListener(settingsComponent);
		settingsComponent->addInterfaceListener(this);
		settingsComponent->setVisible(false);
	}

	if (pinComponent)
	{
		pinComponent->setVisible(false);
		addPinComponentListener(pinComponent);
		pinComponent->addInterfaceListener(this);
	}

	if (aboutComponent)
	{
		aboutComponent->addInterfaceListener(this);
	}

	if (historyComponent)
	{
		historyComponent->getTransactionComponent()->addInterfaceListener(this);
		addTransactionsComponentListener(historyComponent->getTransactionComponent());
	}

	if (sendComponent)
	{
		sendComponent->addInterfaceListener(this);
		addSendComponentListener(sendComponent);
	}

	String server;
	GetAppValue("server", server);
	if (server.isEmpty())
	{
		server = "https://wallet.burst-team.us:2083/";
	}
	burstExt.SetNode(server);
	transactionsComponentListeners.call(&TransactionsComponentListener::SetNode, server);
	serverComboBox->setText(server, dontSendNotification);

	wizlaf = new CELookAndFeel();
	Typeface::Ptr typefacePtr = Typeface::createSystemTypefaceFor(BinaryData::NotoSansRegular_ttf, BinaryData::NotoSansRegular_ttfSize);
	Font f(typefacePtr);
	wizlaf->setFont(f);
	wizlaf->setColour(TreeView::selectedItemBackgroundColourId, Colour(0xff83acf0));
	wizlaf->setColour(TextEditor::highlightColourId, Colour(0xff83acf0));
	wizlaf->setColour(TextEditor::highlightedTextColourId, Colour(0xff141305));
	wizlaf->setColour(TextEditor::backgroundColourId, Colour(0xfff6f6f6));
	wizlaf->setColour(TextEditor::textColourId, Colours::black);
	wizlaf->setColour(TextEditor::focusedOutlineColourId, Colour(0xfface1ef));
	wizlaf->setColour(TextEditor::shadowColourId, Colour(0xffbbbbbb));
	wizlaf->setColour(ListBox::outlineColourId, Colour(0xffe4e4e4));
	wizlaf->setColour(ListBox::backgroundColourId, Colour(0xbefdfdfd));
	wizlaf->setColour(Label::textColourId, Colour(0xffffffff));
	wizlaf->setColour(juce::TextButton::buttonOnColourId, Colour(0xfface1ef));
	wizlaf->setColour(juce::TextButton::buttonColourId, Colour(0xff88bbc8));
	wizlaf->setColour(juce::TextButton::textColourOnId, Colour(0xffffffff));
	wizlaf->setColour(juce::TextButton::textColourOffId, Colour(0xffffffff));
	wizlaf->setColour(juce::TextButton::buttonOnColourId, Colour(0xfface1ef));
	wizlaf->setColour(ProgressBar::foregroundColourId, Colour(0xfface1ef));
	LookAndFeel::setDefaultLookAndFeel(wizlaf);
	wizlaf->Init();

	StringArray amounts = StringArray::fromTokens(GetAppValue("amounts"), ";", "");
	while (amounts.size() < 10)
		amounts.add(String((amounts.size() + 1) * 10));
	SetAppValue("amounts", amounts.joinIntoString(";"));

	String currencyType_t = GetAppValue("CurrencyType");
	String cMCAPIkey = GetAppValue("CMCAPIkey");
	transactionsComponentListeners.call(&TransactionsComponentListener::SetCMCkey, cMCAPIkey);
	transactionsComponentListeners.call(&TransactionsComponentListener::SetCurrencyType, currencyType_t);
	settingsListeners.call(&SettingsListener::SetCMCkey, cMCAPIkey);
	settingsListeners.call(&SettingsListener::SetCurrencyType, currencyType_t);
	
	String passPhrase;
	GetAppValue("passPhraseEnc", passPhrase);
	if (passPhrase.isEmpty()) // quick check if there is a pasword. if not make a new wallet
		settingsListeners.call(&SettingsListener::CreateWallet);
	else LoadPassPhrase();

	autoRefreshCounter = 0;

	versionLabel->setText("v0.1." PROJECT_SVNRevision " (" + String(burstExt.GetBurstKitVersionNumber()) + ")", dontSendNotification);

	startTimer(INTERFACE_UPDATE_MS);
    //[/Constructor]
}

InterfaceComponent::~InterfaceComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    serverComboBox = nullptr;
    balanceLabel = nullptr;
    accountButton = nullptr;
    sendComponent = nullptr;
    historyButton = nullptr;
    sendButton = nullptr;
    historyComponent = nullptr;
    versionLabel = nullptr;
    settingsComponent = nullptr;
    pinComponent = nullptr;
    aboutComponent = nullptr;
    drawable1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
	//systemTray = nullptr;
    //[/Destructor]
}

//==============================================================================
void InterfaceComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	/*
    //[/UserPrePaint]

    g.fillAll (Colour (0xff343434));

    g.setColour (Colours::black);
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, Rectangle<float> (12, 12, 128, 32),
                               RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.000f);

    //[UserPaint] Add your own custom painting code here..
	*/
	g.fillAll(Colour(0xff535353));

	g.setColour(Colours::black);
	jassert(drawable1 != 0);
	if (drawable1 != 0)
		drawable1->drawWithin(g, juce::Rectangle<float>(10, 5, 100, 45),
		RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.000f);
    //[/UserPaint]
}

void InterfaceComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	/*
    //[/UserPreResize]

    serverComboBox->setBounds (160, 8, 232, 24);
    balanceLabel->setBounds (120, 80, 272, 24);
    accountButton->setBounds (120, 40, 272, 32);
    sendComponent->setBounds (0, 176, 168, 424);
    historyButton->setBounds (210, 128, 180, 24);
    sendButton->setBounds (10, 128, 180, 24);
    historyComponent->setBounds (232, 176, 168, 424);
    versionLabel->setBounds (416, 8, 64, 24);
    settingsComponent->setBounds (408, 176, 168, 424);
    pinComponent->setBounds (224, 624, 168, 179);
    aboutComponent->setBounds (24, 624, 168, 179);
    //[UserResized] Add your own custom resize handling here..
	*/
	juce::Rectangle<float> r = getBounds().toFloat();

	const int rowH = 30;
	const int topH = rowH * 4;
	const int w = r.getWidth();

	settingsComponent->setBounds(r.withTrimmedTop(topH).toNearestInt());
	sendComponent->setBounds(r.withTrimmedTop(topH).toNearestInt());
	historyComponent->setBounds(r.withTrimmedTop(topH).toNearestInt());

	if (pinComponent) pinComponent->setBounds(r.toNearestInt());
	aboutComponent->setBounds(r.toNearestInt());

	serverComboBox->setBounds(r.withHeight(rowH).withTrimmedLeft(120).withTrimmedRight(70).reduced(3).toNearestInt());
	versionLabel->setBounds(r.withHeight(rowH).withX(serverComboBox->getRight()).withWidth(70).reduced(3).toNearestInt());

	accountButton->setBounds(0, rowH * 1.8, w / 2, rowH);
	balanceLabel->setBounds(w / 2, rowH * 1.8, w / 2, rowH);

	historyButton->setBounds(0, rowH * 3, w / 2, rowH);
	sendButton->setBounds(w / 2, rowH * 3, w / 2, rowH);
    //[/UserResized]
}

void InterfaceComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == serverComboBox)
    {
        //[UserComboBoxCode_serverComboBox] -- add your combo box handling code here..
		SetAppValue("server", serverComboBox->getText());
        //[/UserComboBoxCode_serverComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void InterfaceComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == accountButton)
    {
        //[UserButtonCode_accountButton] -- add your button handler code here..
		SetView(-1);
        //[/UserButtonCode_accountButton]
    }
    else if (buttonThatWasClicked == historyButton)
    {
        //[UserButtonCode_historyButton] -- add your button handler code here..
		SetView(1);
        //[/UserButtonCode_historyButton]
    }
    else if (buttonThatWasClicked == sendButton)
    {
        //[UserButtonCode_sendButton] -- add your button handler code here..
		SetView(2);

		String feeStr = burstExt.suggestFee();
		uint64 cheap = burstExt.GetJSONvalue(feeStr, "cheap").getLargeIntValue();
		uint64 standard = burstExt.GetJSONvalue(feeStr, "standard").getLargeIntValue();
		uint64 priority = burstExt.GetJSONvalue(feeStr, "priority").getLargeIntValue();
		sendComponentListeners.call(&SendComponentListener::SetSuggestedFees, cheap, standard, priority);


		StringArray recipients = StringArray::fromTokens(GetAppValue("contacts"), ";", "");
		sendComponentListeners.call(&SendComponentListener::SetRecipients, recipients);

		StringArray amounts = StringArray::fromTokens(GetAppValue("amounts"), ";", "");
		sendComponentListeners.call(&SendComponentListener::SetAmounts, amounts);
        //[/UserButtonCode_sendButton]
    }

    //[UserbuttonClicked_Post]
	//aboutComponent->setVisible(aboutComponent->isVisible() == false);
    //[/UserbuttonClicked_Post]
}

void InterfaceComponent::mouseUp (const MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
	if (juce::Rectangle<int>(10, 5, 100, 50).contains(e.getPosition())) // clicked logo
		aboutComponent->setVisible(aboutComponent->isVisible() == false);
    //[/UserCode_mouseUp]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void InterfaceComponent::textEditorTextChanged(TextEditor &) //Called when the user changes the text in some way.
{
}
void InterfaceComponent::textEditorReturnKeyPressed(TextEditor &) //Called when the user presses the return key.
{
}
void InterfaceComponent::textEditorEscapeKeyPressed(TextEditor &/*editor*/) //Called when the user presses the escape key.
{
}
void InterfaceComponent::textEditorFocusLost(TextEditor &) //Called when the text editor loses focus.
{
}

void InterfaceComponent::SetupTransaction(const String recipient, const String amountNQT, const String feeNQT, const String msg, const bool encrypted)
{
	sendComponentListeners.call(&SendComponentListener::SetupTransaction, recipient, amountNQT, feeNQT, msg, encrypted);
	SetView(2);
}

void InterfaceComponent::SendBurstcoin(const String recipient, const String amountNQT, const String feeNQT, const String msg, const bool encrypted)
{
	String errorStr;
	// check arguments, addrss/alias amount and fee
	String dispName;
	GetAccountDisplayName(0, recipient, dispName);

	String balance;
	UpdateBalance(balance);

	if (amountNQT.getLargeIntValue() <= 0)
		errorStr = "Incorrect amount ! use numeric values. Like 123.45";
	else if (feeNQT.getLargeIntValue() <= 0)
		errorStr = "Incorrect fee !";
	else if (amountNQT.getLargeIntValue() + feeNQT.getLargeIntValue() > balance.getLargeIntValue())
		errorStr = "Your balance is too low for this transaction !";
	else if (dispName.isEmpty() || dispName.compare("BURST-2222-2222-2222-22222") == 0)
		errorStr = "Incorrect recipient address, Use a BURST-XXXX-XXXX-XXXX-XXXXX address, numeric ID or an existing alias.";

	if (errorStr.isNotEmpty())
		NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, errorStr);
	else
	{
		if (dispName.containsChar(';'))
			dispName = dispName.upToFirstOccurrenceOf(";", false, true);
		if (dispName.compare(recipient) != 0)
			dispName = dispName + " (" + recipient + ")"; // add RS to text

		if (NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, "Send " + NQT2Burst(amountNQT) + " Burstcoin\nto " + dispName + " ?"))
		{
			String resp = burstExt.sendMoneyWithMessage(recipient, amountNQT, feeNQT, "1440", msg, encrypted, "", true);
			String transactionID = burstExt.GetJSONvalue(resp, "transaction");
			if (transactionID.isNotEmpty())
			{
				StringArray recipients = StringArray::fromTokens(GetAppValue("contacts"), ";", "");
				if (recipients.contains(recipient) == false)
					recipients.insert(0, recipient);
				while (recipients.size() > 10)
					recipients.remove(recipients.size() - 1);
				SetAppValue("contacts", recipients.joinIntoString(";"));
				sendComponentListeners.call(&SendComponentListener::SetRecipients, recipients);

				StringArray amounts = StringArray::fromTokens(GetAppValue("amounts"), ";", "");
				if (amounts.contains(NQT2Burst(amountNQT)) == false)
					amounts.insert(0, NQT2Burst(amountNQT));
				while (amounts.size() > 10)
					amounts.remove(amounts.size() - 1);
				SetAppValue("amounts", amounts.joinIntoString(";"));
				sendComponentListeners.call(&SendComponentListener::SetAmounts, amounts);

				NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Transaction send successfully !");
			}
			else NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "An ERROR occurred transaction has not been send\n\n" + resp.replace(",", ",\n"));
		}
	}
}

void InterfaceComponent::UpdateBalance(String &balance)
{
	// check / update balance
	String myBurstRS = burstExt.GetAccountRS();
	String balanceJSON = burstExt.getBalance(myBurstRS);
	balance = burstExt.GetJSONvalue(balanceJSON, "balanceNQT");
	settingsListeners.call(&SettingsListener::SetBurstRS, myBurstRS);
	accountButton->setButtonText(myBurstRS);

	String balance_t;
	if (balance.length() > 8)
		balance_t = (balance.substring(0, balance.length() - 8) + "." + balance.substring(balance.length() - 8, balance.length()).trimCharactersAtEnd("0") + " BURST");
	else if (balance.length() > 0)
		balance_t = (balance + " NQT");
	else balance_t = ("EMPTY WALLET");

	balanceLabel->setTooltip(balance_t);

	if (currency.isEmpty() || currency.compare("BURST") == 0)
	{
		balanceLabel->setText(balance_t, dontSendNotification);
	}
	else if (currency.compare("BTC") == 0)
	{ // coin market cap conversion
		String priceINT = price.upToFirstOccurrenceOf(".", false, true) + price.fromFirstOccurrenceOf(".", false, true).substring(0, 8); // convert to integer / 0.000001043106736701768 -> 104
		uint64 priceSAT = priceINT.getLargeIntValue();
		uint64 balanceNQT = balance.getLargeIntValue();

		// multiply priceINT by amount of BURST
		uint64 convertedSAT_NQT = priceSAT * balanceNQT;
		uint64 convertedSAT = convertedSAT_NQT / 100000000; // convert the NQT/SAT back

		String convertedSATstr(convertedSAT);
		String convertedBTCstr = convertedSATstr.length() > 8 ? convertedSATstr.substring(0, 8) : "0";
		convertedBTCstr += ".";
		convertedBTCstr += convertedSATstr.getLastCharacters(8).paddedLeft('0', 8);

		balanceLabel->setText(convertedBTCstr + " BTC in BURST", dontSendNotification);
	}
	else
	{ // coin market cap conversion
		String priceINT = price.upToFirstOccurrenceOf(".", false, true) + price.fromFirstOccurrenceOf(".", false, true).substring(0, 8); // convert to integer / 0.000001043106736701768 -> 104
		uint64 priceSAT = priceINT.getLargeIntValue();
		uint64 balanceNQT = balance.getLargeIntValue();

		// multiply priceINT by amount of BURST
		uint64 convertedSAT_NQT = priceSAT * balanceNQT;
		uint64 convertedSAT = convertedSAT_NQT / 100000000; // convert the NQT/SAT back

		String convertedSATstr(convertedSAT);
		convertedSATstr = convertedSATstr.paddedLeft('0', 9);
		String convertedStr = convertedSATstr.substring(0, convertedSATstr.length() - 8) + "." + convertedSATstr.substring(convertedSATstr.length() - 8, convertedSATstr.length() - 6);

		balanceLabel->setText(convertedStr + " " + currency + " in BURST", dontSendNotification);
	}
}

void InterfaceComponent::GetAccountDisplayName(const uint64 account, const String accountRS, String &displayName)
{
	if (accountRS.isEmpty())
	{
		const String rs = burstExt.ensureAccountRS(String(account));
		displayName = burstExt.getAccountAliases(rs);
		if (displayName.isEmpty())
			displayName = rs;
	}
	else
	{
		const String rs = burstExt.ensureAccountRS(String(accountRS));
		displayName = burstExt.getAccountAliases(rs);
		if (displayName.isEmpty())
			displayName = rs;
	}
}

// save pass phrase ------------------------------------
void InterfaceComponent::SavePassPhraseWithNewPIN(const String passPhrase)
{
	// show PIN dialog
	pinComponent->setMode(passPhrase);
	pinComponent->setVisible(true);
	// ask for new PIN
	// function end
	// PIN  dialog calls SavePassPhrase with new PIN code
}

void InterfaceComponent::SavePassPhrase(String passphrase, String pin)
{ // called from PIN dialog
	pinComponent->setVisible(false);
	if (passphrase.isNotEmpty())
	{
		// reload burstExt account
		burstExt.SetSecretPhrase(passphrase);
		transactionsComponentListeners.call(&TransactionsComponentListener::SetSecretPhrase, passphrase);
		String balance;
		UpdateBalance(balance);

		String encryptedPassPhrase = Encrypt("PIN" + passphrase, pin).replace("\"", "&quot;");
		SetAppValue("passPhraseEnc", encryptedPassPhrase);
	}
	else SetAppValue("passPhraseEnc", "");
}

// read pass phrase ------------------------------------
void InterfaceComponent::UnloadPassPhrase()
{
	String emptypassphrase;
	burstExt.SetSecretPhrase(emptypassphrase);
	transactionsComponentListeners.call(&TransactionsComponentListener::SetSecretPhrase, "");
	String balance;
	UpdateBalance(balance);

	// do a listener call with returnListenerCall
	settingsListeners.call(&SettingsListener::SetSecretPhrase, emptypassphrase);

	LoadPassPhrase();
}

void InterfaceComponent::LoadPassPhrase()
{
	// show PIN dialog "enter your PIN to load the wallet pass phrase"
	pinComponent->setMode();
	pinComponent->setVisible(true);
	// PIN dialog calls LoadPassPhraseReturn(String pin)
}

void InterfaceComponent::LoadPassPhraseReturn(String pin)
{ // called from PIN dialog
	String passPhraseEnc = GetAppValue("passPhraseEnc");
	if (passPhraseEnc.isNotEmpty())
	{
		String passphrase = Decrypt(passPhraseEnc, pin);
		if (passphrase.startsWith("PIN"))
		{
			passphrase = passphrase.substring(3);

			pinComponent->setVisible(false);
			// reload burstExt account
			burstExt.SetSecretPhrase(passphrase);
			transactionsComponentListeners.call(&TransactionsComponentListener::SetSecretPhrase, passphrase);
			String balance;
			UpdateBalance(balance);

			// do a listener call with returnListenerCall
			settingsListeners.call(&SettingsListener::SetSecretPhrase, passphrase);

			SetView(1);
		}
	}
}

// -----------------------------------------------------
void InterfaceComponent::GetAppValue(const String type, String &value)
{
	value = GetAppValue(type);
}

String InterfaceComponent::GetAppValue(const String type)
{
	String ret;
	PropertiesFile* props2 = appProp.getUserSettings();
	if (props2)
		ret = props2->getValue(type);
	return ret.replace("&quot;", "\"");
}

void InterfaceComponent::SetAppValue(const String type, const String value)
{
	PropertiesFile* props2 = appProp.getUserSettings();
	if (props2)
	{
		if (type.compare("server") == 0)
		{
			burstExt.SetNode(value);
			transactionsComponentListeners.call(&TransactionsComponentListener::SetNode, value);
			String constants = burstExt.getConstants();
			if (constants.isEmpty())
				NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Node address seems invalid !");
			props2->setValue(type, value.replace("\"", "&quot;"));
		}
		else props2->setValue(type, value.replace("\"", "&quot;"));
	}
	appProp.closeFiles();
}

String InterfaceComponent::Encrypt(String input, String pin)
{
	if (input.isEmpty())
		return String::empty;

	MemoryBlock memoryBlock;
	memoryBlock.loadFromHexString(String::toHexString(input.toUTF8(), (int)input.getNumBytesAsUTF8()));

	SHA256 sha256(pin.toUTF8());
	sha256.toHexString();
	String encryptionKey(sha256.toHexString());

	BlowFish blowFish(encryptionKey.toUTF8(), (int)encryptionKey.getNumBytesAsUTF8());
	blowFish.encrypt(memoryBlock);

	return memoryBlock.toBase64Encoding();
}

String InterfaceComponent::Decrypt(String input, String pin)
{
	if (input.isEmpty())
		return String::empty;

	MemoryBlock memoryBlock;
	memoryBlock.fromBase64Encoding(input);

	SHA256 sha256(pin.toUTF8());
	sha256.toHexString();
	String encryptionKey(sha256.toHexString());

	BlowFish blowFish(encryptionKey.toUTF8(), (int)encryptionKey.getNumBytesAsUTF8());
	blowFish.decrypt(memoryBlock);

	return memoryBlock.toString();
}

void InterfaceComponent::SetView(int nr)
{
	if (settingsComponent)
		settingsComponent->setVisible(nr == -1);

	historyComponent->setVisible(nr == 1);
	if (nr == 1)
		transactionsComponentListeners.call(&TransactionsComponentListener::Refresh);

	sendComponent->setVisible(nr == 2);

	accountButton->setColour(TextButton::ColourIds::buttonColourId, accountButton->findColour(TextButton::ColourIds::buttonColourId).withAlpha(nr == -1 ? 1.0f : 0.0f));
	historyButton->setColour(TextButton::ColourIds::buttonColourId, historyButton->findColour(TextButton::ColourIds::buttonColourId).withAlpha(nr == 1 ? 1.0f : 0.0f));
	sendButton->setColour(TextButton::ColourIds::buttonColourId, sendButton->findColour(TextButton::ColourIds::buttonColourId).withAlpha(nr == 2 ? 1.0f : 0.0f));

	repaint();
}

String InterfaceComponent::NQT2Burst(const String value)
{
	bool minus = value.startsWithChar('-');
	String neatNr(value.removeCharacters("-").paddedLeft('0', 9));
	neatNr = (neatNr.substring(0, neatNr.length() - 8) + "." + neatNr.substring(neatNr.length() - 8, neatNr.length()).trimCharactersAtEnd("0"));
	return minus ? "-" + neatNr : neatNr;
}

String InterfaceComponent::Burst2NQT(const String value)
{
	int64 amountNQT = 0;
	String amount = value.trim().retainCharacters("0123456789.,");
	int point = amount.indexOfAnyOf(".,");
	if (point < 0)
		amountNQT = amount.retainCharacters("0123456789").getLargeIntValue() * 100000000L;
	else
	{
		amountNQT = amount.substring(0, point).getLargeIntValue() * 100000000L;
		amountNQT += amount.substring(point + 1, amount.length()).retainCharacters("0123456789").paddedRight('0', 8).getLargeIntValue();
	}
	return String(amountNQT);
}

void InterfaceComponent::timerCallback()
{
	if (pinComponent->isVisible() == false)
	{
		{
		//	systemTray->showInfoBubble(ProjectInfo::projectName, "New message(s)");
			//systemTray->setIconTooltip("");
		//	systemTray->setHighlighted(true);
		}
	}

	if (autoRefreshCounter++ > ((1 * 60 * 1000) / jmax<int>(1, Timer::getTimerInterval())))
	{
		autoRefreshCounter = 0;
		String bal;
		UpdateBalance(bal);
	}
}

void InterfaceComponent::SetPrice(String currency, String price)
{
	this->currency = currency;
	this->price = price;

	String bal;
	UpdateBalance(bal);

	sendComponentListeners.call(&SendComponentListener::SetPrice, currency, price);
}

void InterfaceComponent::SetCMCkey(const String key)
{
	SetAppValue("CMCAPIkey", key);
	transactionsComponentListeners.call(&TransactionsComponentListener::SetCMCkey, key);
}

void InterfaceComponent::SetCurrencyType(const String currency)
{
	SetAppValue("CurrencyType", currency);
	transactionsComponentListeners.call(&TransactionsComponentListener::SetCurrencyType, currency);
	transactionsComponentListeners.call(&TransactionsComponentListener::Refresh);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="InterfaceComponent" componentName=""
                 parentClasses="public Component, public TextEditorListener, public Timer, public InterfaceListener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="450"
                 initialHeight="650">
  <METHODS>
    <METHOD name="mouseUp (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff343434">
    <IMAGE pos="12 12 128 32" resource="burstHotWalletlogo_svg" opacity="1"
           mode="2"/>
  </BACKGROUND>
  <COMBOBOX name="serverComboBox" id="98ba1d24bcdc2daa" memberName="serverComboBox"
            virtualName="" explicitFocusOrder="0" pos="160 8 232 24" tooltip="The wallet address. running a local node is recommended !"
            editable="1" layout="33" items="https://wallet.burst-team.us:2083/&#10;http://localhost:8125/&#10;http://3.16.150.48:6876/"
            textWhenNonSelected="http://localhost:8125/" textWhenNoItems="enter a node address"/>
  <LABEL name="balanceLabel" id="21cd31dd3925091c" memberName="balanceLabel"
         virtualName="" explicitFocusOrder="0" pos="120 80 272 24" tooltip="balance"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="EMPTY WALLET"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="18" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="accountButton" id="ae4f12654e0537ec" memberName="accountButton"
              virtualName="" explicitFocusOrder="0" pos="120 40 272 32" tooltip="show account options"
              bgColOff="77b517" bgColOn="ff77b517" textCol="ffffffff" buttonText="BURST-XXXX-XXXX-XXXX-XXXXX"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="sendComponent" id="581fb820cd30f666" memberName="sendComponent"
                    virtualName="" explicitFocusOrder="0" pos="0 176 168 424" class="SendComponent"
                    params=""/>
  <TEXTBUTTON name="historyButton" id="c0a926ef92b2eeb8" memberName="historyButton"
              virtualName="" explicitFocusOrder="0" pos="210 128 180 24" bgColOff="ff77b517"
              bgColOn="ff77b517" buttonText="history" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="sendButton" id="411c767fae4dc759" memberName="sendButton"
              virtualName="" explicitFocusOrder="0" pos="10 128 180 24" bgColOff="ff77b517"
              bgColOn="ff77b517" buttonText="send Burst" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="historyComponent" id="78be139897394c8f" memberName="historyComponent"
                    virtualName="" explicitFocusOrder="0" pos="232 176 168 424" class="HistoryComponent"
                    params=""/>
  <LABEL name="versionLabel" id="eebdf42a75f7e3d7" memberName="versionLabel"
         virtualName="" explicitFocusOrder="0" pos="416 8 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="v0.1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <GENERICCOMPONENT name="settingsComponent" id="205c6171ce3a77a7" memberName="settingsComponent"
                    virtualName="" explicitFocusOrder="0" pos="408 176 168 424" class="SettingsComponent"
                    params=""/>
  <GENERICCOMPONENT name="pinComponent" id="33c6370b679be6dc" memberName="pinComponent"
                    virtualName="" explicitFocusOrder="0" pos="224 624 168 179" class="PinComponent"
                    params=""/>
  <GENERICCOMPONENT name="aboutComponent" id="ab42d58ceea79f04" memberName="aboutComponent"
                    virtualName="" explicitFocusOrder="0" pos="24 624 168 179" class="AboutComponent"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: burstHotWalletlogo_svg, 15551, "BurstHotWallet-logo.svg"
static const unsigned char resource_InterfaceComponent_burstHotWalletlogo_svg[] = { 60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,110,99,111,100,105,110,103,61,34,85,84,70,
45,56,34,32,115,116,97,110,100,97,108,111,110,101,61,34,110,111,34,63,62,10,60,33,45,45,32,71,101,110,101,114,97,116,111,114,58,32,65,100,111,98,101,32,73,108,108,117,115,116,114,97,116,111,114,32,49,
56,46,49,46,49,44,32,83,86,71,32,69,120,112,111,114,116,32,80,108,117,103,45,73,110,32,46,32,83,86,71,32,86,101,114,115,105,111,110,58,32,54,46,48,48,32,66,117,105,108,100,32,48,41,32,32,45,45,62,10,10,
60,115,118,103,10,32,32,32,120,109,108,110,115,58,100,99,61,34,104,116,116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,101,108,101,109,101,110,116,115,47,49,46,49,47,34,10,32,32,32,120,109,
108,110,115,58,99,99,61,34,104,116,116,112,58,47,47,99,114,101,97,116,105,118,101,99,111,109,109,111,110,115,46,111,114,103,47,110,115,35,34,10,32,32,32,120,109,108,110,115,58,114,100,102,61,34,104,116,
116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,49,57,57,57,47,48,50,47,50,50,45,114,100,102,45,115,121,110,116,97,120,45,110,115,35,34,10,32,32,32,120,109,108,110,115,58,115,118,103,61,34,104,
116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,10,32,32,32,120,109,108,110,115,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,
48,48,47,115,118,103,34,10,32,32,32,120,109,108,110,115,58,115,111,100,105,112,111,100,105,61,34,104,116,116,112,58,47,47,115,111,100,105,112,111,100,105,46,115,111,117,114,99,101,102,111,114,103,101,
46,110,101,116,47,68,84,68,47,115,111,100,105,112,111,100,105,45,48,46,100,116,100,34,10,32,32,32,120,109,108,110,115,58,105,110,107,115,99,97,112,101,61,34,104,116,116,112,58,47,47,119,119,119,46,105,
110,107,115,99,97,112,101,46,111,114,103,47,110,97,109,101,115,112,97,99,101,115,47,105,110,107,115,99,97,112,101,34,10,32,32,32,118,101,114,115,105,111,110,61,34,49,46,49,34,10,32,32,32,105,100,61,34,
67,97,112,97,95,49,34,10,32,32,32,120,61,34,48,112,120,34,10,32,32,32,121,61,34,48,112,120,34,10,32,32,32,118,105,101,119,66,111,120,61,34,48,32,48,32,53,57,57,46,57,57,57,57,55,32,51,53,57,46,57,57,57,
57,57,34,10,32,32,32,120,109,108,58,115,112,97,99,101,61,34,112,114,101,115,101,114,118,101,34,10,32,32,32,115,111,100,105,112,111,100,105,58,100,111,99,110,97,109,101,61,34,66,117,114,115,116,72,111,
116,87,97,108,108,101,116,45,108,111,103,111,46,115,118,103,34,10,32,32,32,105,110,107,115,99,97,112,101,58,118,101,114,115,105,111,110,61,34,48,46,57,50,46,49,32,114,49,53,51,55,49,34,10,32,32,32,119,
105,100,116,104,61,34,54,48,48,34,10,32,32,32,104,101,105,103,104,116,61,34,51,54,48,34,10,32,32,32,105,110,107,115,99,97,112,101,58,101,120,112,111,114,116,45,102,105,108,101,110,97,109,101,61,34,69,
58,92,67,43,43,92,66,117,114,115,116,92,66,117,114,115,116,72,111,116,87,97,108,108,101,116,92,66,117,114,115,116,72,111,116,87,97,108,108,101,116,46,103,105,116,92,116,114,117,110,107,92,83,111,117,114,
99,101,92,66,117,114,115,116,72,111,116,87,97,108,108,101,116,45,108,111,103,111,45,98,105,103,46,112,110,103,34,10,32,32,32,105,110,107,115,99,97,112,101,58,101,120,112,111,114,116,45,120,100,112,105,
61,34,54,53,46,52,53,52,53,52,52,34,10,32,32,32,105,110,107,115,99,97,112,101,58,101,120,112,111,114,116,45,121,100,112,105,61,34,54,53,46,52,53,52,53,52,52,34,62,60,109,101,116,97,100,97,116,97,10,32,
32,32,32,32,105,100,61,34,109,101,116,97,100,97,116,97,52,49,34,62,60,114,100,102,58,82,68,70,62,60,99,99,58,87,111,114,107,10,32,32,32,32,32,32,32,32,32,114,100,102,58,97,98,111,117,116,61,34,34,62,60,
100,99,58,102,111,114,109,97,116,62,105,109,97,103,101,47,115,118,103,43,120,109,108,60,47,100,99,58,102,111,114,109,97,116,62,60,100,99,58,116,121,112,101,10,32,32,32,32,32,32,32,32,32,32,32,114,100,
102,58,114,101,115,111,117,114,99,101,61,34,104,116,116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,100,99,109,105,116,121,112,101,47,83,116,105,108,108,73,109,97,103,101,34,32,47,62,60,100,
99,58,116,105,116,108,101,62,60,47,100,99,58,116,105,116,108,101,62,60,47,99,99,58,87,111,114,107,62,60,47,114,100,102,58,82,68,70,62,60,47,109,101,116,97,100,97,116,97,62,60,100,101,102,115,10,32,32,
32,32,32,105,100,61,34,100,101,102,115,51,57,34,32,47,62,60,115,111,100,105,112,111,100,105,58,110,97,109,101,100,118,105,101,119,10,32,32,32,32,32,112,97,103,101,99,111,108,111,114,61,34,35,102,102,102,
102,102,102,34,10,32,32,32,32,32,98,111,114,100,101,114,99,111,108,111,114,61,34,35,54,54,54,54,54,54,34,10,32,32,32,32,32,98,111,114,100,101,114,111,112,97,99,105,116,121,61,34,49,34,10,32,32,32,32,32,
111,98,106,101,99,116,116,111,108,101,114,97,110,99,101,61,34,49,48,34,10,32,32,32,32,32,103,114,105,100,116,111,108,101,114,97,110,99,101,61,34,49,48,34,10,32,32,32,32,32,103,117,105,100,101,116,111,
108,101,114,97,110,99,101,61,34,49,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,112,97,103,101,111,112,97,99,105,116,121,61,34,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,112,
97,103,101,115,104,97,100,111,119,61,34,50,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,119,105,100,116,104,61,34,49,49,49,49,34,10,32,32,32,32,32,105,110,107,115,99,
97,112,101,58,119,105,110,100,111,119,45,104,101,105,103,104,116,61,34,56,53,57,34,10,32,32,32,32,32,105,100,61,34,110,97,109,101,100,118,105,101,119,51,55,34,10,32,32,32,32,32,115,104,111,119,103,114,
105,100,61,34,102,97,108,115,101,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,122,111,111,109,61,34,48,46,55,53,50,50,57,57,49,49,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,120,
61,34,50,57,50,46,55,51,55,56,51,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,121,61,34,50,49,49,46,57,56,55,55,51,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,
119,45,120,61,34,49,54,56,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,121,61,34,53,57,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,
45,109,97,120,105,109,105,122,101,100,61,34,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,117,114,114,101,110,116,45,108,97,121,101,114,61,34,108,97,121,101,114,53,34,10,32,32,32,32,32,105,
110,107,115,99,97,112,101,58,112,97,103,101,99,104,101,99,107,101,114,98,111,97,114,100,61,34,102,97,108,115,101,34,10,32,32,32,32,32,115,104,111,119,98,111,114,100,101,114,61,34,116,114,117,101,34,10,
32,32,32,32,32,98,111,114,100,101,114,108,97,121,101,114,61,34,102,97,108,115,101,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,115,104,111,119,112,97,103,101,115,104,97,100,111,119,61,34,116,
114,117,101,34,32,47,62,60,103,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,103,114,111,117,112,109,111,100,101,61,34,108,97,121,101,114,34,10,32,32,32,32,32,105,100,61,34,108,97,121,101,114,49,
34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,108,97,98,101,108,61,34,76,97,121,101,114,32,50,34,10,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,
34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,49,52,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,54,34,10,32,32,32,32,32,116,
114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,56,34,10,32,32,32,32,32,116,114,
97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,49,48,34,10,32,32,32,32,32,116,114,97,
110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,49,50,34,10,32,32,32,32,32,116,114,97,110,
115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,49,52,34,10,32,32,32,32,32,116,114,97,110,115,
102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,49,54,34,10,32,32,32,32,32,116,114,97,110,115,102,
111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,49,56,34,10,32,32,32,32,32,116,114,97,110,115,102,111,
114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,50,48,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,
109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,50,50,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,
61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,50,52,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,
34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,50,54,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,
116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,50,56,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,
114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,51,48,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,
97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,51,50,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,
110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,51,52,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,
115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,97,114,105,97,45,108,97,98,101,108,61,34,66,85,82,78,69,82,32,77,79,68,69,34,10,32,32,32,32,32,115,116,
121,108,101,61,34,102,111,110,116,45,115,116,121,108,101,58,110,111,114,109,97,108,59,102,111,110,116,45,118,97,114,105,97,110,116,58,110,111,114,109,97,108,59,102,111,110,116,45,119,101,105,103,104,116,
58,110,111,114,109,97,108,59,102,111,110,116,45,115,116,114,101,116,99,104,58,110,111,114,109,97,108,59,102,111,110,116,45,115,105,122,101,58,49,49,49,46,52,51,51,49,51,53,57,57,112,120,59,108,105,110,
101,45,104,101,105,103,104,116,58,49,46,50,53,59,102,111,110,116,45,102,97,109,105,108,121,58,39,66,101,98,97,115,32,78,101,117,101,39,59,45,105,110,107,115,99,97,112,101,45,102,111,110,116,45,115,112,
101,99,105,102,105,99,97,116,105,111,110,58,39,66,101,98,97,115,32,78,101,117,101,39,59,108,101,116,116,101,114,45,115,112,97,99,105,110,103,58,48,112,120,59,119,111,114,100,45,115,112,97,99,105,110,103,
58,48,112,120,59,102,105,108,108,58,35,48,48,48,48,48,48,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,58,110,111,110,101,59,115,116,114,111,107,101,45,119,105,100,116,
104,58,50,46,55,56,53,56,50,56,51,53,34,10,32,32,32,32,32,105,100,61,34,116,101,120,116,52,53,50,48,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,
44,45,51,52,48,41,34,32,47,62,60,103,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,103,114,111,117,112,109,111,100,101,61,34,108,97,121,101,114,34,10,32,32,32,32,32,105,100,61,34,108,97,121,101,114,
50,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,108,97,98,101,108,61,34,76,97,121,101,114,32,49,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,
40,48,44,45,51,52,48,41,34,10,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,34,32,47,62,60,103,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,103,114,
111,117,112,109,111,100,101,61,34,108,97,121,101,114,34,10,32,32,32,32,32,105,100,61,34,108,97,121,101,114,53,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,108,97,98,101,108,61,34,76,97,121,101,
114,32,52,34,10,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,
101,40,48,44,45,49,52,41,34,62,60,103,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,34,10,32,32,32,32,32,32,32,116,114,97,110,115,102,111,114,
109,61,34,109,97,116,114,105,120,40,48,46,57,54,55,56,54,48,55,52,44,48,44,48,44,48,46,57,54,55,56,54,48,55,52,44,53,53,51,46,49,54,56,51,54,44,45,49,48,48,55,46,53,53,50,52,41,34,10,32,32,32,32,32,32,
32,105,100,61,34,103,52,53,54,55,45,56,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,59,111,112,97,99,105,116,121,
58,49,59,102,105,108,108,58,35,57,56,101,97,49,97,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,102,105,108,108,45,114,117,108,101,58,110,111,110,122,101,114,111,59,115,116,114,111,107,101,
58,35,48,48,48,48,48,48,59,115,116,114,111,107,101,45,119,105,100,116,104,58,50,48,46,49,54,52,53,50,53,57,57,59,115,116,114,111,107,101,45,108,105,110,101,99,97,112,58,98,117,116,116,59,115,116,114,111,
107,101,45,108,105,110,101,106,111,105,110,58,109,105,116,101,114,59,115,116,114,111,107,101,45,109,105,116,101,114,108,105,109,105,116,58,52,59,115,116,114,111,107,101,45,100,97,115,104,97,114,114,97,
121,58,110,111,110,101,59,115,116,114,111,107,101,45,100,97,115,104,111,102,102,115,101,116,58,48,59,115,116,114,111,107,101,45,111,112,97,99,105,116,121,58,49,59,112,97,105,110,116,45,111,114,100,101,
114,58,102,105,108,108,32,109,97,114,107,101,114,115,32,115,116,114,111,107,101,34,10,32,32,32,32,32,32,32,100,61,34,77,32,49,49,55,46,56,57,57,51,55,44,53,49,46,51,54,51,54,48,49,32,72,32,53,55,55,46,
57,49,55,55,49,32,86,32,50,50,56,46,56,50,56,50,55,32,99,32,48,44,48,32,48,46,55,50,57,49,54,44,49,49,46,54,57,57,52,55,32,45,57,46,48,48,57,53,53,44,50,49,46,52,49,53,57,54,32,45,57,46,55,51,56,55,49,
44,57,46,55,49,54,52,57,32,45,50,57,46,55,49,50,51,52,44,49,48,46,50,48,56,49,53,32,45,50,57,46,55,49,50,51,52,44,49,48,46,50,48,56,49,53,32,108,32,45,49,46,49,55,56,44,45,56,52,46,52,55,54,56,32,99,32,
45,48,46,48,55,52,55,44,54,54,46,50,56,57,52,32,48,46,48,57,53,56,44,53,53,46,53,51,53,55,57,32,45,48,46,48,55,57,55,44,49,50,49,46,56,50,52,57,57,32,76,32,50,50,46,48,56,50,55,57,50,44,50,57,54,46,50,
54,51,51,55,32,50,50,46,48,56,50,51,48,56,44,57,54,46,56,53,50,56,50,56,32,90,34,10,32,32,32,32,32,32,32,105,100,61,34,114,101,99,116,52,54,50,51,45,57,45,52,45,57,45,52,34,10,32,32,32,32,32,32,32,105,
110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,10,32,32,32,32,32,32,32,115,111,100,105,112,111,100,105,58,110,111,100,101,116,121,112,101,
115,61,34,99,99,99,122,99,99,99,99,99,99,34,32,47,62,60,114,101,99,116,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,59,111,112,97,99,105,116,
121,58,49,59,102,105,108,108,58,35,48,50,48,50,48,50,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,102,105,108,108,45,114,117,108,101,58,110,111,110,122,101,114,111,59,115,116,114,111,107,101,
58,110,111,110,101,59,115,116,114,111,107,101,45,119,105,100,116,104,58,50,56,46,56,52,55,55,48,53,56,52,59,115,116,114,111,107,101,45,108,105,110,101,99,97,112,58,98,117,116,116,59,115,116,114,111,107,
101,45,108,105,110,101,106,111,105,110,58,109,105,116,101,114,59,115,116,114,111,107,101,45,109,105,116,101,114,108,105,109,105,116,58,52,59,115,116,114,111,107,101,45,100,97,115,104,97,114,114,97,121,
58,110,111,110,101,59,115,116,114,111,107,101,45,100,97,115,104,111,102,102,115,101,116,58,48,59,115,116,114,111,107,101,45,111,112,97,99,105,116,121,58,49,59,112,97,105,110,116,45,111,114,100,101,114,
58,109,97,114,107,101,114,115,32,115,116,114,111,107,101,32,102,105,108,108,34,10,32,32,32,32,32,32,32,105,100,61,34,114,101,99,116,52,54,50,51,45,57,45,52,34,10,32,32,32,32,32,32,32,119,105,100,116,104,
61,34,52,57,57,46,53,56,53,55,50,34,10,32,32,32,32,32,32,32,104,101,105,103,104,116,61,34,50,53,56,46,56,48,49,48,51,34,10,32,32,32,32,32,32,32,120,61,34,49,50,46,48,48,48,48,51,49,34,10,32,32,32,32,32,
32,32,121,61,34,57,50,46,55,51,53,50,57,56,34,10,32,32,32,32,32,32,32,114,120,61,34,52,54,46,51,51,52,56,51,57,34,10,32,32,32,32,32,32,32,114,121,61,34,52,54,46,51,51,52,56,51,57,34,32,47,62,60,103,10,
32,32,32,32,32,32,32,97,114,105,97,45,108,97,98,101,108,61,34,72,79,84,87,65,76,76,69,84,34,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,111,110,116,45,115,116,121,108,101,58,110,111,114,109,
97,108,59,102,111,110,116,45,118,97,114,105,97,110,116,58,110,111,114,109,97,108,59,102,111,110,116,45,119,101,105,103,104,116,58,110,111,114,109,97,108,59,102,111,110,116,45,115,116,114,101,116,99,104,
58,110,111,114,109,97,108,59,102,111,110,116,45,115,105,122,101,58,50,54,57,46,55,57,56,48,57,53,55,112,120,59,108,105,110,101,45,104,101,105,103,104,116,58,49,46,50,53,59,102,111,110,116,45,102,97,109,
105,108,121,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,45,105,110,107,115,99,97,112,101,45,102,111,110,116,45,115,112,101,99,105,102,105,99,97,116,105,111,110,58,39,79,115,116,114,105,99,104,
32,83,97,110,115,39,59,108,101,116,116,101,114,45,115,112,97,99,105,110,103,58,48,112,120,59,119,111,114,100,45,115,112,97,99,105,110,103,58,48,112,120,59,100,105,115,112,108,97,121,58,105,110,108,105,
110,101,59,102,105,108,108,58,35,102,102,102,102,102,102,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,58,110,111,110,101,59,115,116,114,111,107,101,45,119,105,100,116,
104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,105,100,61,34,116,101,120,116,52,54,50,55,45,48,45,57,34,10,32,32,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,109,97,116,114,
105,120,40,48,46,52,55,54,54,57,57,50,44,48,44,48,44,48,46,52,55,54,54,57,57,49,55,44,49,53,46,50,57,54,56,55,44,53,54,46,53,49,48,53,56,49,41,34,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,
61,34,109,32,56,50,46,56,51,50,51,57,44,50,50,49,46,51,53,54,48,52,32,118,32,45,54,55,46,57,56,57,49,50,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,54,57,44,45,57,46,55,49,50,55,51,
32,45,57,46,55,49,50,55,51,49,44,45,57,46,55,49,50,55,51,32,104,32,45,55,46,53,53,52,51,52,55,32,99,32,45,53,46,51,57,53,57,54,50,44,48,32,45,57,46,55,49,50,55,51,49,44,52,46,51,49,54,55,55,32,45,57,46,
55,49,50,55,51,49,44,57,46,55,49,50,55,51,32,118,32,49,54,50,46,52,49,56,52,54,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,54,57,44,57,46,55,49,50,55,51,32,57,46,55,49,50,55,51,49,44,57,46,
55,49,50,55,51,32,104,32,55,46,53,53,52,51,52,55,32,99,32,53,46,51,57,53,57,54,50,44,48,32,57,46,55,49,50,55,51,49,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,49,44,45,57,46,55,49,50,55,51,32,118,
32,45,54,55,46,55,49,57,51,51,32,104,32,50,57,46,57,52,55,53,57,32,118,32,54,55,46,55,49,57,51,51,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,55,44,57,46,55,49,50,55,51,32,57,46,55,49,50,
55,51,44,57,46,55,49,50,55,51,32,104,32,55,46,53,53,52,51,53,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,
86,32,49,53,51,46,51,54,54,57,50,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,104,32,45,55,46,53,
53,52,51,53,32,99,32,45,53,46,51,57,53,57,54,44,48,32,45,57,46,55,49,50,55,51,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,51,44,57,46,55,49,50,55,51,32,118,32,54,55,46,57,56,57,49,50,32,122,34,10,
32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,
32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,50,52,45,55,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,
34,48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,49,54,50,46,50,57,54,51,54,44,50,55,50,46,54,49,55,54,56,32,99,32,48,44,50,49,46,51,49,52,48,53,32,53,46,57,51,53,53,
54,44,51,51,46,55,50,52,55,54,32,49,52,46,50,57,57,51,44,52,50,46,48,56,56,53,32,56,46,57,48,51,51,52,44,56,46,54,51,51,53,52,32,50,48,46,50,51,52,56,54,44,49,48,46,55,57,49,57,51,32,50,57,46,57,52,55,
53,57,44,49,48,46,55,57,49,57,51,32,57,46,57,56,50,53,51,44,48,32,50,49,46,51,49,52,48,53,44,45,50,46,49,53,56,51,57,32,51,48,46,50,49,55,51,56,44,45,49,48,46,55,57,49,57,51,32,56,46,51,54,51,55,53,44,
45,56,46,51,54,51,55,52,32,49,52,46,48,50,57,53,49,44,45,50,48,46,55,55,52,52,53,32,49,52,46,48,50,57,53,49,44,45,52,50,46,48,56,56,53,32,118,32,45,55,54,46,51,53,50,56,54,32,99,32,48,44,45,51,52,46,50,
54,52,51,54,32,45,49,52,46,53,54,57,49,44,45,53,50,46,54,49,48,54,51,32,45,52,52,46,50,52,54,56,57,44,45,53,50,46,54,49,48,54,51,32,45,50,57,46,52,48,55,57,57,44,48,32,45,52,52,46,50,52,54,56,57,44,49,
56,46,54,49,54,48,55,32,45,52,52,46,50,52,54,56,57,44,53,50,46,54,49,48,54,51,32,122,32,109,32,50,54,46,57,55,57,56,49,44,45,55,54,46,51,53,50,56,54,32,99,32,48,44,45,49,55,46,53,51,54,56,56,32,53,46,
51,57,53,57,54,44,45,50,53,46,57,48,48,54,50,32,49,55,46,50,54,55,48,56,44,45,50,53,46,57,48,48,54,50,32,49,49,46,54,48,49,51,50,44,48,32,49,55,46,50,54,55,48,56,44,55,46,56,50,52,49,53,32,49,55,46,50,
54,55,48,56,44,50,53,46,57,48,48,54,50,32,118,32,55,54,46,51,53,50,56,54,32,99,32,48,44,49,56,46,51,52,54,50,55,32,45,53,46,57,51,53,53,54,44,50,54,46,49,55,48,52,50,32,45,49,55,46,50,54,55,48,56,44,50,
54,46,49,55,48,52,50,32,45,49,49,46,54,48,49,51,50,44,48,32,45,49,55,46,50,54,55,48,56,44,45,56,46,51,54,51,55,52,32,45,49,55,46,50,54,55,48,56,44,45,50,54,46,49,55,48,52,50,32,122,34,10,32,32,32,32,32,
32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,32,32,
105,100,61,34,112,97,116,104,52,53,50,54,45,49,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,47,
62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,50,55,48,46,56,50,50,54,52,44,49,54,48,46,54,53,49,52,55,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,55,44,57,46,55,49,
50,55,51,32,57,46,55,49,50,55,52,44,57,46,55,49,50,55,51,32,104,32,50,49,46,56,53,51,54,52,32,118,32,49,52,53,46,49,53,49,51,56,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,55,44,57,46,55,
49,50,55,51,32,57,46,55,49,50,55,51,44,57,46,55,49,50,55,51,32,104,32,55,46,50,56,52,53,53,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,
44,45,57,46,55,49,50,55,51,32,86,32,49,55,48,46,51,54,52,50,32,104,32,50,50,46,49,50,51,52,53,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,
51,44,45,57,46,55,49,50,55,51,32,118,32,45,55,46,53,53,52,51,53,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,51,44,45,57,46,55,49,
50,55,51,32,104,32,45,55,48,46,54,56,55,49,32,99,32,45,53,46,51,57,53,57,55,44,48,32,45,57,46,55,49,50,55,52,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,52,44,57,46,55,49,50,55,51,32,122,34,10,32,
32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,
32,32,32,32,105,100,61,34,112,97,116,104,52,53,50,56,45,51,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,
48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,52,53,55,46,48,56,56,55,50,44,49,53,49,46,52,55,56,51,52,32,99,32,45,48,46,56,48,57,52,44,45,52,46,51,49,54,55,55,32,45,
53,46,49,50,54,49,54,44,45,55,46,56,50,52,49,53,32,45,57,46,52,52,50,57,51,44,45,55,46,56,50,52,49,53,32,104,32,45,53,46,57,51,53,53,54,32,99,32,45,52,46,51,49,54,55,55,44,48,32,45,56,46,54,51,51,53,52,
44,51,46,53,48,55,51,56,32,45,57,46,52,52,50,57,52,44,55,46,56,50,52,49,53,32,108,32,45,49,52,46,48,50,57,53,44,56,50,46,48,49,56,54,50,32,45,49,50,46,52,49,48,55,49,44,45,56,49,46,55,52,56,56,51,32,99,
32,45,48,46,56,48,57,51,57,44,45,52,46,53,56,54,53,54,32,45,53,46,49,50,54,49,54,44,45,56,46,48,57,51,57,52,32,45,57,46,55,49,50,55,51,44,45,56,46,48,57,51,57,52,32,104,32,45,55,46,56,50,52,49,53,32,99,
32,45,54,46,50,48,53,51,53,44,48,32,45,49,48,46,50,53,50,51,50,44,53,46,49,50,54,49,55,32,45,57,46,52,52,50,57,51,44,49,49,46,48,54,49,55,50,32,108,32,50,54,46,52,52,48,50,49,44,49,54,50,46,54,56,56,50,
54,32,99,32,48,46,56,48,57,52,44,52,46,51,49,54,55,54,32,52,46,56,53,54,51,55,44,56,46,48,57,51,57,52,32,57,46,52,52,50,57,52,44,56,46,48,57,51,57,52,32,104,32,53,46,57,51,53,53,54,32,99,32,52,46,51,49,
54,55,55,44,48,32,56,46,54,51,51,53,52,44,45,51,46,53,48,55,51,56,32,57,46,52,52,50,57,51,44,45,55,46,56,50,52,49,53,32,108,32,49,52,46,53,54,57,49,44,45,56,54,46,48,54,53,53,57,32,49,52,46,50,57,57,51,
44,56,54,46,48,54,53,53,57,32,99,32,48,46,56,48,57,51,57,44,52,46,51,49,54,55,55,32,53,46,49,50,54,49,54,44,55,46,56,50,52,49,53,32,57,46,52,52,50,57,51,44,55,46,56,50,52,49,53,32,104,32,54,46,50,48,53,
51,54,32,99,32,52,46,53,56,54,53,54,44,48,32,56,46,57,48,51,51,51,44,45,51,46,55,55,55,49,56,32,57,46,55,49,50,55,51,44,45,56,46,48,57,51,57,52,32,108,32,50,53,46,57,48,48,54,49,44,45,49,54,50,46,54,56,
56,50,54,32,99,32,48,46,56,48,57,52,44,45,53,46,57,51,53,53,53,32,45,51,46,55,55,55,49,55,44,45,49,49,46,48,54,49,55,50,32,45,57,46,55,49,50,55,51,44,45,49,49,46,48,54,49,55,50,32,104,32,45,55,46,56,50,
52,49,52,32,99,32,45,52,46,53,56,54,53,55,44,48,32,45,57,46,49,55,51,49,52,44,51,46,53,48,55,51,56,32,45,57,46,55,49,50,55,51,44,56,46,48,57,51,57,52,32,108,32,45,49,50,46,49,52,48,57,50,44,56,49,46,50,
48,57,50,51,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,
54,56,34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,51,48,45,50,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,
118,97,116,117,114,101,61,34,48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,53,55,54,46,48,57,48,55,53,44,51,49,55,46,57,52,51,55,54,32,99,32,49,46,48,55,57,49,57,44,52,
46,48,52,54,57,55,32,53,46,51,57,53,57,54,44,55,46,53,53,52,51,53,32,57,46,52,52,50,57,51,44,55,46,53,53,52,51,53,32,104,32,55,46,56,50,52,49,53,32,99,32,54,46,52,55,53,49,53,44,48,32,49,48,46,55,57,49,
57,50,44,45,53,46,54,54,53,55,54,32,57,46,52,52,50,57,51,44,45,49,49,46,56,55,49,49,50,32,76,32,53,54,53,46,53,54,56,54,51,44,49,53,49,46,50,48,56,53,52,32,99,32,45,48,46,56,48,57,52,44,45,52,46,48,52,
54,57,55,32,45,53,46,51,57,53,57,55,44,45,55,46,53,53,52,51,53,32,45,57,46,52,52,50,57,52,44,45,55,46,53,53,52,51,53,32,104,32,45,53,46,57,51,53,53,54,32,99,32,45,52,46,48,52,54,57,55,44,48,32,45,56,46,
51,54,51,55,52,44,51,46,53,48,55,51,56,32,45,57,46,52,52,50,57,51,44,55,46,53,53,52,51,53,32,108,32,45,50,52,46,53,53,49,54,51,44,49,48,53,46,52,57,49,48,53,32,45,49,50,46,57,53,48,51,44,53,55,46,49,57,
55,50,32,99,32,45,49,46,51,52,57,44,54,46,50,48,53,51,54,32,50,46,57,54,55,55,55,44,49,49,46,54,48,49,51,50,32,57,46,52,52,50,57,51,44,49,49,46,54,48,49,51,50,32,104,32,55,46,56,50,52,49,52,32,99,32,52,
46,48,52,54,57,55,44,48,32,56,46,51,54,51,55,52,44,45,51,46,53,48,55,51,56,32,57,46,52,52,50,57,52,44,45,55,46,53,53,52,51,53,32,108,32,57,46,52,52,50,57,51,44,45,52,50,46,48,56,56,53,32,104,32,50,55,
46,53,49,57,52,49,32,122,32,77,32,53,53,51,46,49,53,55,57,49,44,50,48,53,46,57,55,55,53,53,32,99,32,53,46,49,50,54,49,55,44,50,50,46,57,51,50,56,52,32,52,46,53,56,54,53,55,44,51,48,46,50,49,55,51,57,32,
55,46,53,53,52,51,53,44,52,51,46,49,54,55,55,32,104,32,45,49,53,46,49,48,56,54,57,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,
116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,51,50,45,53,34,10,32,32,32,32,32,32,32,32,32,105,110,107,
115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,54,57,54,46,56,48,48,49,
50,44,51,48,56,46,53,48,48,56,51,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,52,44,45,57,46,55,49,50,55,51,32,72,32,54,52,54,46,
56,56,55,52,55,32,86,32,49,53,51,46,51,54,54,57,50,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,52,52,50,57,52,44,45,57,46,55,49,50,55,51,32,
104,32,45,55,46,56,50,52,49,52,32,99,32,45,53,46,51,57,53,57,54,44,48,32,45,57,46,55,49,50,55,51,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,51,44,57,46,55,49,50,55,51,32,118,32,49,54,50,46,52,49,
56,52,54,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,55,44,57,46,55,49,50,55,51,32,57,46,55,49,50,55,51,44,57,46,55,49,50,55,51,32,104,32,53,55,46,52,54,54,57,57,32,99,32,53,46,51,57,53,57,
55,44,48,32,57,46,55,49,50,55,52,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,52,44,45,57,46,55,49,50,55,51,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,
102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,51,52,45,50,34,10,32,32,32,32,
32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,
32,55,56,55,46,52,51,53,52,51,44,51,48,56,46,53,48,48,56,51,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,51,44,45,57,46,55,49,50,
55,51,32,72,32,55,51,55,46,53,50,50,55,56,32,86,32,49,53,51,46,51,54,54,57,50,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,52,52,50,57,51,44,
45,57,46,55,49,50,55,51,32,104,32,45,55,46,56,50,52,49,52,32,99,32,45,53,46,51,57,53,57,55,44,48,32,45,57,46,55,49,50,55,52,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,52,44,57,46,55,49,50,55,51,32,
118,32,49,54,50,46,52,49,56,52,54,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,55,44,57,46,55,49,50,55,51,32,57,46,55,49,50,55,52,44,57,46,55,49,50,55,51,32,104,32,53,55,46,52,54,54,57,57,
32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,
34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,
51,54,45,57,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,47,62,60,112,97,116,104,10,32,32,32,
32,32,32,32,32,32,100,61,34,109,32,56,49,50,46,53,48,57,55,53,44,49,52,51,46,54,53,52,49,57,32,99,32,45,53,46,51,57,53,57,54,44,48,32,45,57,46,55,49,50,55,51,44,52,46,51,49,54,55,55,32,45,57,46,55,49,
50,55,51,44,57,46,55,49,50,55,51,32,118,32,49,54,50,46,52,49,56,52,54,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,55,44,57,46,55,49,50,55,51,32,57,46,55,49,50,55,51,44,57,46,55,49,50,55,51,
32,104,32,53,56,46,50,55,54,51,57,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,118,32,45,55,46,50,56,52,
53,53,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,104,32,45,52,49,46,50,55,57,49,49,32,118,32,
45,53,48,46,57,57,49,56,52,32,104,32,51,51,46,57,57,52,53,54,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,52,32,
118,32,45,55,46,50,56,52,53,52,32,99,32,48,44,45,53,46,51,57,53,57,55,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,52,32,45,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,52,32,72,32,56,50,57,46,53,
48,55,48,51,32,86,32,49,55,48,46,51,54,52,50,32,104,32,52,49,46,50,55,57,49,49,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,51,44,45,57,46,
55,49,50,55,51,32,118,32,45,55,46,50,56,52,53,53,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,122,
34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,
32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,51,56,45,52,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,
101,61,34,48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,56,57,55,46,51,54,53,52,57,44,49,54,48,46,54,53,49,52,55,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,
55,55,44,57,46,55,49,50,55,51,32,57,46,55,49,50,55,51,44,57,46,55,49,50,55,51,32,104,32,50,49,46,56,53,51,54,53,32,118,32,49,52,53,46,49,53,49,51,56,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,
54,55,55,44,57,46,55,49,50,55,51,32,57,46,55,49,50,55,51,44,57,46,55,49,50,55,51,32,104,32,55,46,50,56,52,53,53,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,32,
57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,86,32,49,55,48,46,51,54,52,50,32,104,32,50,50,46,49,50,51,52,52,32,99,32,53,46,51,57,53,57,54,44,48,32,57,46,55,49,50,55,51,44,45,52,46,51,49,54,55,55,
32,57,46,55,49,50,55,51,44,45,57,46,55,49,50,55,51,32,118,32,45,55,46,53,53,52,51,53,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,
51,44,45,57,46,55,49,50,55,51,32,104,32,45,55,48,46,54,56,55,49,32,99,32,45,53,46,51,57,53,57,54,44,48,32,45,57,46,55,49,50,55,51,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,51,44,57,46,55,49,50,55,
51,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,
10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,52,48,45,48,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,
117,114,101,61,34,48,34,32,47,62,60,47,103,62,60,103,10,32,32,32,32,32,32,32,97,114,105,97,45,108,97,98,101,108,61,34,67,65,83,72,34,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,111,110,116,45,
115,116,121,108,101,58,110,111,114,109,97,108,59,102,111,110,116,45,118,97,114,105,97,110,116,58,110,111,114,109,97,108,59,102,111,110,116,45,119,101,105,103,104,116,58,110,111,114,109,97,108,59,102,111,
110,116,45,115,116,114,101,116,99,104,58,110,111,114,109,97,108,59,102,111,110,116,45,115,105,122,101,58,50,54,57,46,55,57,56,48,57,53,55,112,120,59,108,105,110,101,45,104,101,105,103,104,116,58,49,46,
50,53,59,102,111,110,116,45,102,97,109,105,108,121,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,45,105,110,107,115,99,97,112,101,45,102,111,110,116,45,115,112,101,99,105,102,105,99,97,116,105,
111,110,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,108,101,116,116,101,114,45,115,112,97,99,105,110,103,58,48,112,120,59,119,111,114,100,45,115,112,97,99,105,110,103,58,48,112,120,59,100,105,
115,112,108,97,121,58,105,110,108,105,110,101,59,102,105,108,108,58,35,57,56,101,97,49,97,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,58,110,111,110,101,59,115,116,
114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,105,100,61,34,116,101,120,116,52,54,50,55,45,52,45,50,45,56,34,10,32,32,32,32,32,32,32,116,114,97,110,
115,102,111,114,109,61,34,109,97,116,114,105,120,40,48,46,52,55,54,54,57,57,50,44,48,44,48,44,48,46,52,55,54,54,57,57,49,55,44,45,50,49,49,46,49,55,53,51,51,44,49,54,56,46,55,51,55,55,53,41,34,62,60,112,
97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,49,48,52,56,46,54,54,53,53,44,50,55,49,46,55,49,53,52,51,32,99,32,48,44,50,49,46,51,49,52,48,53,32,53,46,57,51,53,54,44,51,51,46,55,50,52,55,54,
32,49,52,46,50,57,57,51,44,52,50,46,48,56,56,53,32,56,46,57,48,51,51,44,56,46,54,51,51,53,52,32,49,57,46,57,54,53,49,44,49,48,46,55,57,49,57,51,32,51,48,46,50,49,55,52,44,49,48,46,55,57,49,57,51,32,57,
46,55,49,50,55,44,48,32,50,49,46,48,52,52,50,44,45,50,46,49,53,56,51,57,32,50,57,46,57,52,55,54,44,45,49,48,46,55,57,49,57,51,32,56,46,51,54,51,55,44,45,56,46,51,54,51,55,52,32,49,52,46,48,50,57,53,44,
45,50,48,46,55,55,52,52,53,32,49,52,46,48,50,57,53,44,45,52,50,46,48,56,56,53,32,118,32,45,51,46,55,55,55,49,55,32,99,32,48,44,45,53,46,51,57,53,57,55,32,45,52,46,51,49,54,56,44,45,57,46,55,49,50,55,52,
32,45,57,46,52,52,51,44,45,57,46,55,49,50,55,52,32,104,32,45,55,46,56,50,52,49,32,99,32,45,53,46,51,57,54,44,48,32,45,57,46,55,49,50,55,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,44,57,46,55,49,50,
55,52,32,118,32,51,46,55,55,55,49,55,32,99,32,48,44,57,46,55,49,50,55,51,32,45,49,46,51,52,57,44,49,54,46,57,57,55,50,56,32,45,52,46,53,56,54,54,44,50,49,46,51,49,52,48,53,32,45,50,46,52,50,56,50,44,50,
46,54,57,55,57,56,32,45,55,46,50,56,52,53,44,52,46,56,53,54,51,54,32,45,49,50,46,52,49,48,55,44,52,46,56,53,54,51,54,32,45,49,49,46,54,48,49,51,44,48,32,45,49,55,46,50,54,55,49,44,45,56,46,48,57,51,57,
52,32,45,49,55,46,50,54,55,49,44,45,50,54,46,49,55,48,52,49,32,118,32,45,55,54,46,51,53,50,56,54,32,99,32,48,44,45,49,56,46,48,55,54,52,55,32,53,46,57,51,53,54,44,45,50,53,46,57,48,48,54,50,32,49,55,46,
50,54,55,49,44,45,50,53,46,57,48,48,54,50,32,49,49,46,48,54,49,55,44,48,32,49,54,46,57,57,55,51,44,55,46,56,50,52,49,53,32,49,54,46,57,57,55,51,44,50,53,46,57,48,48,54,50,32,118,32,51,46,55,55,55,49,55,
32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,55,44,57,46,55,49,50,55,51,32,57,46,55,49,50,55,44,57,46,55,49,50,55,51,32,104,32,55,46,56,50,52,49,32,99,32,53,46,49,50,54,50,44,48,32,57,46,52,52,
51,44,45,52,46,51,49,54,55,55,32,57,46,52,52,51,44,45,57,46,55,49,50,55,51,32,118,32,45,51,46,55,55,55,49,55,32,99,32,48,44,45,50,48,46,53,48,52,54,54,32,45,53,46,54,54,53,56,44,45,51,51,46,57,57,52,53,
54,32,45,49,52,46,50,57,57,51,44,45,52,50,46,48,56,56,53,49,32,45,56,46,57,48,51,52,44,45,56,46,48,57,51,57,52,32,45,49,57,46,54,57,53,51,44,45,49,48,46,53,50,50,49,50,32,45,50,57,46,54,55,55,56,44,45,
49,48,46,53,50,50,49,50,32,45,49,48,46,50,53,50,51,44,48,32,45,50,49,46,48,52,52,51,44,50,46,52,50,56,49,56,32,45,50,57,46,57,52,55,54,44,49,48,46,53,50,50,49,50,32,45,56,46,54,51,51,53,44,56,46,48,57,
51,57,53,32,45,49,52,46,53,54,57,49,44,50,49,46,53,56,51,56,53,32,45,49,52,46,53,54,57,49,44,52,50,46,48,56,56,53,49,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,
35,57,56,101,97,49,97,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,32,32,105,100,
61,34,112,97,116,104,52,53,49,53,45,50,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,47,62,60,
112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,49,50,50,57,46,48,51,52,44,51,49,55,46,48,52,49,53,49,32,99,32,49,46,48,55,57,50,44,52,46,48,52,54,57,55,32,53,46,51,57,53,57,44,55,46,53,
53,52,51,53,32,57,46,52,52,50,57,44,55,46,53,53,52,51,53,32,104,32,55,46,56,50,52,49,32,99,32,54,46,52,55,53,50,44,48,32,49,48,46,55,57,50,44,45,53,46,54,54,53,55,54,32,57,46,52,52,51,44,45,49,49,46,56,
55,49,49,50,32,108,32,45,51,55,46,50,51,50,50,44,45,49,54,50,46,52,49,56,52,53,32,99,32,45,48,46,56,48,57,52,44,45,52,46,48,52,54,57,56,32,45,53,46,51,57,53,57,44,45,55,46,53,53,52,51,53,32,45,57,46,52,
52,50,57,44,45,55,46,53,53,52,51,53,32,104,32,45,53,46,57,51,53,54,32,99,32,45,52,46,48,52,54,57,44,48,32,45,56,46,51,54,51,55,44,51,46,53,48,55,51,55,32,45,57,46,52,52,50,57,44,55,46,53,53,52,51,53,32,
108,32,45,50,52,46,53,53,49,54,44,49,48,53,46,52,57,49,48,53,32,45,49,50,46,57,53,48,51,44,53,55,46,49,57,55,50,32,99,32,45,49,46,51,52,57,44,54,46,50,48,53,51,53,32,50,46,57,54,55,56,44,49,49,46,54,48,
49,51,50,32,57,46,52,52,50,57,44,49,49,46,54,48,49,51,50,32,104,32,55,46,56,50,52,50,32,99,32,52,46,48,52,54,57,44,48,32,56,46,51,54,51,55,44,45,51,46,53,48,55,51,56,32,57,46,52,52,50,57,44,45,55,46,53,
53,52,51,53,32,108,32,57,46,52,52,50,57,44,45,52,50,46,48,56,56,53,32,104,32,50,55,46,53,49,57,52,32,122,32,77,32,49,50,48,54,46,49,48,49,49,44,50,48,53,46,48,55,53,51,32,99,32,53,46,49,50,54,50,44,50,
50,46,57,51,50,56,52,32,52,46,53,56,54,54,44,51,48,46,50,49,55,51,57,32,55,46,53,53,52,52,44,52,51,46,49,54,55,54,57,32,104,32,45,49,53,46,49,48,56,55,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,
108,101,61,34,102,105,108,108,58,35,57,56,101,97,49,97,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,
32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,49,55,45,51,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,
114,101,61,34,48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,49,50,54,56,46,52,49,54,49,44,50,55,49,46,55,49,53,52,51,32,99,32,48,44,51,53,46,51,52,51,53,53,32,49,52,46,
56,51,56,56,44,53,50,46,54,49,48,54,51,32,52,52,46,53,49,54,54,44,53,50,46,54,49,48,54,51,32,50,56,46,53,57,56,54,44,48,32,52,52,46,53,49,54,55,44,45,49,54,46,49,56,55,56,57,32,52,52,46,53,49,54,55,44,
45,52,54,46,52,48,53,50,55,32,48,44,45,50,54,46,49,55,48,52,50,32,45,49,56,46,48,55,54,52,44,45,51,57,46,57,51,48,49,50,32,45,51,53,46,56,56,51,49,44,45,53,51,46,54,56,57,56,51,32,104,32,48,46,50,54,57,
56,32,99,32,45,49,51,46,50,50,48,49,44,45,49,48,46,50,53,50,51,50,32,45,50,54,46,52,52,48,50,44,45,50,48,46,55,55,52,52,53,32,45,50,54,46,52,52,48,50,44,45,51,52,46,53,51,52,49,53,32,48,44,45,49,52,46,
48,50,57,53,32,54,46,50,48,53,51,44,45,50,48,46,50,51,52,56,54,32,49,55,46,53,51,54,56,44,45,50,48,46,50,51,52,56,54,32,49,49,46,56,55,49,50,44,48,32,49,55,46,53,51,54,57,44,56,46,48,57,51,57,52,32,49,
55,46,53,51,54,57,44,50,53,46,57,48,48,54,50,32,118,32,51,46,55,55,55,49,55,32,99,32,48,44,53,46,51,57,53,57,54,32,52,46,51,49,54,56,44,57,46,55,49,50,55,51,32,57,46,55,49,50,55,44,57,46,55,49,50,55,51,
32,104,32,55,46,53,53,52,52,32,99,32,53,46,51,57,54,44,48,32,57,46,55,49,50,55,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,44,45,57,46,55,49,50,55,51,32,118,32,45,51,46,55,55,55,49,55,32,99,32,48,
44,45,51,52,46,50,54,52,51,54,32,45,49,53,46,51,55,56,53,44,45,53,50,46,56,56,48,52,51,32,45,52,52,46,53,49,54,55,44,45,53,50,46,56,56,48,52,51,32,45,50,56,46,53,57,56,54,44,48,32,45,52,52,46,53,49,54,
54,44,49,55,46,53,51,54,56,56,32,45,52,52,46,53,49,54,54,44,52,56,46,48,50,52,48,54,32,48,44,50,54,46,55,49,48,48,49,32,49,56,46,54,49,54,44,52,49,46,50,55,57,49,49,32,51,54,46,52,50,50,55,44,53,53,46,
51,48,56,54,49,32,118,32,45,48,46,50,54,57,56,32,99,32,49,51,46,50,50,48,49,44,49,48,46,50,53,50,51,51,32,50,53,46,54,51,48,56,44,50,48,46,50,51,52,56,54,32,50,53,46,54,51,48,56,44,51,50,46,57,49,53,51,
55,32,48,44,49,52,46,50,57,57,51,32,45,54,46,50,48,53,51,44,49,57,46,49,53,53,54,55,32,45,49,55,46,53,51,54,57,44,49,57,46,49,53,53,54,55,32,45,51,46,55,55,55,49,44,48,32,45,56,46,51,54,51,55,44,45,48,
46,53,51,57,54,32,45,49,49,46,51,51,49,53,44,45,51,46,53,48,55,51,56,32,45,51,46,55,55,55,50,44,45,51,46,50,51,55,53,56,32,45,54,46,50,48,53,51,44,45,57,46,52,52,50,57,51,32,45,54,46,50,48,53,51,44,45,
50,50,46,51,57,51,50,52,32,118,32,45,51,46,53,48,55,51,56,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,53,56,54,54,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,56,44,45,57,46,55,49,50,55,51,32,
104,32,45,55,46,53,53,52,51,32,99,32,45,53,46,51,57,54,44,48,32,45,57,46,55,49,50,55,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,44,57,46,55,49,50,55,51,32,122,34,10,32,32,32,32,32,32,32,32,32,115,
116,121,108,101,61,34,102,105,108,108,58,35,57,56,101,97,49,97,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,
34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,49,57,45,55,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,
116,117,114,101,61,34,48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,49,52,48,50,46,56,57,51,53,44,50,50,48,46,52,53,51,55,57,32,118,32,45,54,55,46,57,56,57,49,50,32,99,
32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,44,45,57,46,55,49,50,55,51,32,104,32,45,55,46,53,53,52,51,32,99,32,45,53,46,51,57,54,44,48,32,
45,57,46,55,49,50,56,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,56,44,57,46,55,49,50,55,51,32,118,32,49,54,50,46,52,49,56,52,53,32,99,32,48,44,53,46,51,57,53,57,55,32,52,46,51,49,54,56,44,57,46,55,49,
50,55,52,32,57,46,55,49,50,56,44,57,46,55,49,50,55,52,32,104,32,55,46,53,53,52,51,32,99,32,53,46,51,57,54,44,48,32,57,46,55,49,50,55,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,44,45,57,46,55,49,50,
55,52,32,86,32,50,52,55,46,49,54,51,56,32,104,32,50,57,46,57,52,55,54,32,118,32,54,55,46,55,49,57,51,50,32,99,32,48,44,53,46,51,57,53,57,55,32,52,46,51,49,54,56,44,57,46,55,49,50,55,52,32,57,46,55,49,
50,55,44,57,46,55,49,50,55,52,32,104,32,55,46,53,53,52,52,32,99,32,53,46,51,57,54,44,48,32,57,46,55,49,50,55,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,44,45,57,46,55,49,50,55,52,32,86,32,49,53,50,
46,52,54,52,54,55,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,51,49,54,55,44,45,57,46,55,49,50,55,51,32,45,57,46,55,49,50,55,44,45,57,46,55,49,50,55,51,32,104,32,45,55,46,53,53,52,52,32,99,32,45,
53,46,51,57,53,57,44,48,32,45,57,46,55,49,50,55,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,55,44,57,46,55,49,50,55,51,32,118,32,54,55,46,57,56,57,49,50,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,
121,108,101,61,34,102,105,108,108,58,35,57,56,101,97,49,97,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,
32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,50,49,45,52,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,
114,101,61,34,48,34,32,47,62,60,47,103,62,60,103,10,32,32,32,32,32,32,32,97,114,105,97,45,108,97,98,101,108,61,34,46,34,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,111,110,116,45,115,116,121,
108,101,58,110,111,114,109,97,108,59,102,111,110,116,45,118,97,114,105,97,110,116,58,110,111,114,109,97,108,59,102,111,110,116,45,119,101,105,103,104,116,58,110,111,114,109,97,108,59,102,111,110,116,45,
115,116,114,101,116,99,104,58,110,111,114,109,97,108,59,102,111,110,116,45,115,105,122,101,58,50,54,57,46,55,57,56,48,57,53,55,112,120,59,108,105,110,101,45,104,101,105,103,104,116,58,49,46,50,53,59,102,
111,110,116,45,102,97,109,105,108,121,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,45,105,110,107,115,99,97,112,101,45,102,111,110,116,45,115,112,101,99,105,102,105,99,97,116,105,111,110,58,
39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,108,101,116,116,101,114,45,115,112,97,99,105,110,103,58,48,112,120,59,119,111,114,100,45,115,112,97,99,105,110,103,58,48,112,120,59,100,105,115,112,
108,97,121,58,105,110,108,105,110,101,59,102,105,108,108,58,35,57,54,102,102,50,50,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,58,110,111,110,101,59,115,116,114,111,
107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,32,32,32,105,100,61,34,116,101,120,116,52,54,50,55,45,52,45,53,45,48,45,54,34,10,32,32,32,32,32,32,32,116,114,97,110,115,
102,111,114,109,61,34,109,97,116,114,105,120,40,48,46,52,55,54,54,57,57,50,44,48,44,48,44,48,46,52,55,54,54,57,57,49,55,44,45,50,49,49,46,49,55,53,51,51,44,49,54,56,46,55,51,55,55,53,41,34,62,60,112,97,
116,104,10,32,32,32,32,32,32,32,32,32,100,61,34,109,32,49,48,50,50,46,57,51,55,44,51,48,53,46,53,49,53,50,54,32,99,32,48,44,45,53,46,51,57,53,57,54,32,45,52,46,53,56,54,54,44,45,57,46,55,49,50,55,51,32,
45,57,46,55,49,50,55,44,45,57,46,55,49,50,55,51,32,104,32,45,55,46,56,50,52,50,32,99,32,45,53,46,49,50,54,49,44,48,32,45,57,46,55,49,50,54,57,44,52,46,51,49,54,55,55,32,45,57,46,55,49,50,54,57,44,57,46,
55,49,50,55,51,32,118,32,49,48,46,50,53,50,51,50,32,99,32,48,44,53,46,51,57,53,57,55,32,52,46,53,56,54,53,57,44,57,46,55,49,50,55,52,32,57,46,55,49,50,54,57,44,57,46,55,49,50,55,52,32,104,32,55,46,56,
50,52,50,32,99,32,53,46,49,50,54,49,44,48,32,57,46,55,49,50,55,44,45,52,46,51,49,54,55,55,32,57,46,55,49,50,55,44,45,57,46,55,49,50,55,52,32,122,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,
34,102,105,108,108,58,35,57,54,102,102,50,50,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,54,46,55,52,52,57,53,50,54,56,34,10,32,32,32,32,
32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,49,50,45,51,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,
34,48,34,32,47,62,60,47,103,62,60,47,103,62,60,47,115,118,103,62,0,0};

const char* InterfaceComponent::burstHotWalletlogo_svg = (const char*) resource_InterfaceComponent_burstHotWalletlogo_svg;
const int InterfaceComponent::burstHotWalletlogo_svgSize = 15551;


//[EndFile] You can add extra defines here...
//[/EndFile]
