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
#include "BurstLib-source.cpp"
#include "Logger.h"
#include "Version.h"

#define REQ_PORT 41137

void InterfaceComponent::log(String message)
{
	ToLog(message);
}
//[/MiscUserDefs]

//==============================================================================
InterfaceComponent::InterfaceComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
	//  : Thread("InterfaceComponent")
    //[/Constructor_pre]

    addAndMakeVisible (balanceComponent = new BalanceComponent());
    balanceComponent->setName ("balanceComponent");

    addAndMakeVisible (settingsButton = new TextButton ("settingsButton"));
    settingsButton->setTooltip (TRANS("show settings"));
    settingsButton->setButtonText (TRANS("cog"));
    settingsButton->addListener (this);
    settingsButton->setColour (TextButton::buttonColourId, Colour (0xff84cb16));
    settingsButton->setColour (TextButton::buttonOnColourId, Colour (0xff84cb16));
    settingsButton->setColour (TextButton::textColourOffId, Colours::white);

    addAndMakeVisible (shoutComponent = new ShoutComponent());
    shoutComponent->setName ("shoutComponent");

    addAndMakeVisible (sendComponent = new SendComponent());
    sendComponent->setName ("sendComponent");

    addAndMakeVisible (historyButton = new TextButton ("historyButton"));
    historyButton->setButtonText (TRANS("history"));
    historyButton->addListener (this);
    historyButton->setColour (TextButton::buttonColourId, Colour (0xff84cb16));
    historyButton->setColour (TextButton::buttonOnColourId, Colour (0xff84cb16));

    addAndMakeVisible (sendButton = new TextButton ("sendButton"));
    sendButton->setButtonText (TRANS("send"));
    sendButton->addListener (this);
    sendButton->setColour (TextButton::buttonColourId, Colour (0xff84cb16));
    sendButton->setColour (TextButton::buttonOnColourId, Colour (0xff84cb16));

    addAndMakeVisible (historyComponent = new HistoryComponent());
    historyComponent->setName ("historyComponent");

    addAndMakeVisible (versionLabel = new Label ("versionLabel",
                                                 TRANS("v0.1")));
    versionLabel->setFont (Font (11.00f, Font::plain));
    versionLabel->setJustificationType (Justification::topLeft);
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
    drawable2 = Drawable::createFromImageData (burstHotWalletPrologo_svg, burstHotWalletPrologo_svgSize);
    drawable3 = Drawable::createFromImageData (burst_logo_white_svg, burst_logo_white_svgSize);

    //[UserPreSize]
	sendComponent->setVisible(false);
	isPro = false;
	autoRefreshCounter = 0;

    //[/UserPreSize]

    setSize (450, 700);


    //[Constructor] You can add your own custom stuff here..
	leftTopCorner1 = juce::Rectangle<float>(0, 0, 100, 50).reduced(5);
	leftTopCorner2 = juce::Rectangle<float>(100, 0, 80, 50).reduced(6);

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
		addHistoryComponentListener(historyComponent);
		addTransactionsComponentListener(historyComponent->getTransactionComponent());
	}

	if (shoutComponent)
	{
		shoutComponent->addInterfaceListener(this);
		addShoutComponentListener(shoutComponent);
	}

	if (sendComponent)
	{
		sendComponent->addInterfaceListener(this);
		addSendComponentListener(sendComponent);
	}

	if (balanceComponent)
	{
		balanceComponent->addInterfaceListener(this);
		addBalanceComponentListener(balanceComponent);
	}

	String forceSSLOnStr;
	GetAppValue("forceSSLOn", forceSSLOnStr);

	bool forceSSLOn = forceSSLOnStr.getIntValue() > 0;
	burstExt.SetForceSSL_TSL(forceSSLOn);
	transactionsComponentListeners.call(&TransactionsComponentListener::SetForceSSL_TSL, forceSSLOn);
	shoutComponentListeners.call(&ShoutComponentListener::SetForceSSL_TSL, forceSSLOn);
	settingsListeners.call(&SettingsListener::SetForceSSL_TSL, forceSSLOn);
	balanceComponentListeners.call(&BalanceComponentListener::SetForceSSL_TSL, forceSSLOn);

	String node_server;
	GetAppValue("server", node_server);
	if (node_server.isEmpty())
	{
		node_server = US_NET;// "https://wallet1.burst-team.us:2083/";
	}
	burstExt.SetNode(node_server);
	node_server = burstExt.GetNode();

	transactionsComponentListeners.call(&TransactionsComponentListener::SetNode, node_server, false);
	shoutComponentListeners.call(&ShoutComponentListener::SetNode, node_server, false);
	settingsListeners.call(&SettingsListener::SetNode, node_server, false);
	balanceComponentListeners.call(&BalanceComponentListener::SetNode, node_server, false);

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

	versionLabel->setText("v0.3." PROJECT_SVNRevision " (" + String(burstExt.GetBurstKitVersionNumber()) + ")", dontSendNotification);

#if ALLOW_EXT_REQ == 1
	String httpsocketStr;
	GetAppValue("httpsocket", httpsocketStr);
	if (httpsocketStr.getIntValue() > 0)
	{
		bool ok = false;
		OpenHttpSocket("127.0.0.1", REQ_PORT, ok);
	}
#endif

	String hopOnStr;
	GetAppValue("hopOn", hopOnStr);

	bool hopOn = hopOnStr.getIntValue() > 0;
	burstExt.EnableNodeHop(hopOn ? 7 : 0);
	transactionsComponentListeners.call(&TransactionsComponentListener::SetNodeHop, hopOn);
	shoutComponentListeners.call(&ShoutComponentListener::SetNodeHop, hopOn);
	settingsListeners.call(&SettingsListener::SetNodeHop, hopOn);
	balanceComponentListeners.call(&BalanceComponentListener::SetNodeHop, hopOn);

	//systemTray->showInfoBubble(ProjectInfo::projectName, "hi");
	//systemTray->setIconTooltip("");
	//systemTray->setHighlighted(true);
	StartHttpServer();

	startTimer(INTERFACE_UPDATE_MS);
    //[/Constructor]
}

InterfaceComponent::~InterfaceComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
#if ALLOW_EXT_REQ == 1
	CloseHttpSocket();
	streamingSocket = nullptr;
#endif
	StopHttpServer();

    //[/Destructor_pre]

    balanceComponent = nullptr;
    settingsButton = nullptr;
    shoutComponent = nullptr;
    sendComponent = nullptr;
    historyButton = nullptr;
    sendButton = nullptr;
    historyComponent = nullptr;
    versionLabel = nullptr;
    settingsComponent = nullptr;
    pinComponent = nullptr;
    aboutComponent = nullptr;
    drawable1 = nullptr;
    drawable2 = nullptr;
    drawable3 = nullptr;


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
        drawable1->drawWithin (g, Rectangle<float> (44, 244, 128, 32),
                               RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.000f);

    g.setColour (Colours::black);
    jassert (drawable2 != 0);
    if (drawable2 != 0)
        drawable2->drawWithin (g, Rectangle<float> (44, 292, 128, 32),
                               RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.000f);

    g.setGradientFill (ColourGradient (Colour (0xff004578),
                                       624.0f, 528.0f,
                                       Colour (0xff00432f),
                                       100.0f, 100.0f,
                                       true));
    g.fillRect (4, 4, 636, 524);

    g.setColour (Colours::black);
    jassert (drawable3 != 0);
    if (drawable3 != 0)
        drawable3->drawWithin (g, Rectangle<float> (12, 12, 64, 24),
                               RectanglePlacement::centred, 1.000f);

    //[UserPaint] Add your own custom painting code here..
	*/
	g.fillAll(Colour(0xff535353));

	g.setGradientFill(ColourGradient(Colour(0xff004578),
		getWidth() - 100.f, getHeight() / 2,
		Colour(0xff00432f),
		100.0f, 100.0f,
		true));
	g.fillRect(0, 0, getWidth(), getHeight());

	g.setColour(Colours::black);


	// BURST
	jassert(drawable3 != 0);
	if (drawable3 != 0)
		drawable3->drawWithin(g, leftTopCorner1,
		RectanglePlacement::centred, 1.000f);

	// LOGO
	if (isPro == false)
	{
		jassert(drawable1 != 0);
		if (drawable1 != 0)
			drawable1->drawWithin(g, leftTopCorner2,
			RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.000f);
	}
	else
	{
		jassert(drawable2 != 0);
		if (drawable2 != 0)
			drawable2->drawWithin(g, leftTopCorner2,
			RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.000f);
	}
    //[/UserPaint]
}

void InterfaceComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	/*
    //[/UserPreResize]

    balanceComponent->setBounds (136, 24, 416, 24);
    settingsButton->setBounds (576, 8, 56, 56);
    shoutComponent->setBounds (120, 496, 416, 24);
    sendComponent->setBounds (120, 72, 168, 224);
    historyButton->setBounds (0, 72, 110, 24);
    sendButton->setBounds (0, 96, 112, 24);
    historyComponent->setBounds (296, 72, 168, 224);
    versionLabel->setBounds (48, 40, 64, 24);
    settingsComponent->setBounds (472, 72, 168, 224);
    pinComponent->setBounds (296, 304, 168, 179);
    aboutComponent->setBounds (120, 304, 168, 179);
    //[UserResized] Add your own custom resize handling here..
	*/
	juce::Rectangle<float> r = getBounds().toFloat();

	const float rowH = 35.f;
	const float topH = rowH * 4.f;
	const float rowH2 = 35.f;
	const int w = (int)r.getWidth();
	
	if (pinComponent) pinComponent->setBounds(r.toNearestInt());
	aboutComponent->setBounds(r.toNearestInt());
	
	versionLabel->setBounds(juce::Rectangle<int>(20, 50, leftTopCorner2.getRight() - 20, 20));
	
	balanceComponent->setBounds(juce::Rectangle<int>(versionLabel->getRight(), 0, w - versionLabel->getRight() - (2 * rowH), (int)rowH * 2).reduced(3));

	settingsButton->setBounds(juce::Rectangle<int>(w - (2 * rowH), 0, (2 * rowH), (2 * rowH)).reduced(15));

	historyButton->setBounds(0, balanceComponent->getBottom(), w / 2, (int)rowH);
	sendButton->setBounds(w / 2, balanceComponent->getBottom(), w / 2, (int)rowH);

	settingsComponent->setBounds(r.withTrimmedTop(sendButton->getBottom()).withTrimmedBottom(rowH2).toNearestInt());
	sendComponent->setBounds(r.withTrimmedTop(sendButton->getBottom()).withTrimmedBottom(rowH2).toNearestInt());
	historyComponent->setBounds(r.withTrimmedTop(sendButton->getBottom()).withTrimmedBottom(rowH2).toNearestInt());

	shoutComponent->setBounds(r.withTrimmedTop(r.getHeight() - rowH2).toNearestInt());
    //[/UserResized]
}

void InterfaceComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == settingsButton)
    {
        //[UserButtonCode_settingsButton] -- add your button handler code here..
		SetView(-1);
        //[/UserButtonCode_settingsButton]
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

		SetupSendView();
        //[/UserButtonCode_sendButton]
    }

    //[UserbuttonClicked_Post]
	//aboutComponent->setVisible(aboutComponent->isVisible() == false);
    //[/UserbuttonClicked_Post]
}

void InterfaceComponent::mouseUp (const MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
	if (leftTopCorner1.toNearestInt().contains(e.getPosition()) || leftTopCorner2.toNearestInt().contains(e.getPosition())) // clicked logo
		aboutComponent->setVisible(aboutComponent->isVisible() == false);
    //[/UserCode_mouseUp]
}

bool InterfaceComponent::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}

bool InterfaceComponent::keyStateChanged (bool isKeyDown)
{
    //[UserCode_keyStateChanged] -- Add your code here...
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyStateChanged]
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

void InterfaceComponent::SetupTransaction(const String requestHeader, const String recipient, const String amountNQT, const String feeNQT, const String msg, const bool encrypted)
{ // async
	setupTX = true;
	setupTX_requestHeader = requestHeader;
	setupTX_recipient = recipient;
	setupTX_amountNQT = amountNQT;
	setupTX_feeNQT = feeNQT;
	setupTX_msg = msg;
	setupTX_encrypted = encrypted;
}


void InterfaceComponent::SavePassPhraseWithNewPIN(const String passPhrase)
{ // save pass phrase
	// show PIN dialog
	pinComponent->setViewMode(4, passPhrase);
	pinComponent->setVisible(true);
	// ask for new PIN
	// PIN  dialog calls SavePassPhrase with new PIN code
}

void InterfaceComponent::LoadPassPhrase()
{
	// show PIN dialog "enter your PIN to load the wallet pass phrase"
	pinComponent->setViewMode(5);
	pinComponent->setVisible(true);
	// PIN dialog calls LoadPassPhraseReturn(String pin)
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

	settingsButton->setColour(TextButton::ColourIds::buttonColourId, settingsButton->findColour(TextButton::ColourIds::buttonColourId).withAlpha(nr == -1 ? 1.0f : 0.0f));
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
		amountNQT += amount.substring(point + 1, amount.length()).retainCharacters("0123456789").paddedRight('0', 8).substring(0, 8).getLargeIntValue();
	}
	return String(amountNQT);
}

void InterfaceComponent::SetPrice(String currency_, double price_)
{
	balanceComponentListeners.call(&BalanceComponentListener::SetPrice, currency_, price_);
	balanceComponentListeners.call(&BalanceComponentListener::UpdateBalance);

	sendComponentListeners.call(&SendComponentListener::SetPrice, currency_, price_);
}

void InterfaceComponent::SetCMCkey(const String key)
{
	SetAppValue("CMCAPIkey", key);
	transactionsComponentListeners.call(&TransactionsComponentListener::SetCMCkey, key);
}

void InterfaceComponent::SetCurrencyType(const String currency_)
{
	SetAppValue("CurrencyType", currency_);
	transactionsComponentListeners.call(&TransactionsComponentListener::SetCurrencyType, currency_);
	transactionsComponentListeners.call(&TransactionsComponentListener::Refresh);
}


StringArray InterfaceComponent::LimitedTokenList(String tokenlist, String newItem, const int maxItems)
{
	StringArray list = StringArray::fromTokens(tokenlist, ";", "");
	if (list.contains(newItem) == false)
		list.insert(0, newItem);
	if (list.size() - maxItems > 0)
		list.removeRange(0, list.size() - maxItems);

	return list;
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
			SetNode(value);
		}
		props2->setValue(type, value.replace("\"", "&quot;"));
	}
	appProp.closeFiles();
}

// read pass phrase ------------------------------------
void InterfaceComponent::UnloadPassPhrase()
{
	burstExt.SetSecretPhrase(String::empty, 0);
	transactionsComponentListeners.call(&TransactionsComponentListener::SetSecretPhrase, String::empty);
	settingsListeners.call(&SettingsListener::SetSecretPhrase, String::empty);
	balanceComponentListeners.call(&BalanceComponentListener::SetSecretPhrase, String::empty);

	LoadPassPhrase();
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
			burstExt.SetSecretPhrase(passphrase, 0);

			transactionsComponentListeners.call(&TransactionsComponentListener::SetSecretPhrase, passphrase);
			balanceComponentListeners.call(&BalanceComponentListener::SetSecretPhrase, passphrase);
			settingsListeners.call(&SettingsListener::SetSecretPhrase, passphrase);

			balanceComponentListeners.call(&BalanceComponentListener::UpdateBalance);
			SetView(1);
		}
	}
}

void InterfaceComponent::timerCallback()
{
#if ALLOW_EXT_REQ == 1
	if (streamingSocket && streamingSocket->waitUntilReady(true, 100) == 1)
	{
		if (socketMessageData == nullptr)
			socketMessageData = new MemoryBlock(1024);

		int bytesRead = streamingSocket->read(static_cast <char*> (socketMessageData->getData()), 1024, false);

		ProcessHttpSocketMessage(*socketMessageData);

		juce::StreamingSocket* connection = streamingSocket->waitForNextConnection();
		char response[] = "HTTP/1.1 200 OK\r\n"
			"Connection: close\r\n"
			"Access-Control-Allow-Origin: *\r\n"
			"Content-Type: text/plain; charset=UTF-8\r\n\r\n"
			"<xml></xml>"
			;
		int bytesWritten = connection->write(response, strlen(response));
		connection->close();
	}
#endif
	if (setupTX)
	{
		setupTX = false;
		sendComponentListeners.call(&SendComponentListener::SetupTransaction, setupTX_requestHeader, setupTX_recipient, setupTX_amountNQT, setupTX_feeNQT, setupTX_msg, setupTX_encrypted);
		SetView(2);
	}
	if (autoRefreshCounter++ > ((1 * 60 * 1000) / jmax<int>(1, Timer::getTimerInterval())))
	{
		autoRefreshCounter = 0;
		balanceComponentListeners.call(&BalanceComponentListener::UpdateBalance);
	}
}

// burstExt blocking calls ============================================================================================
void InterfaceComponent::SetNode(const String address)
{
	burstExt.SetNode(address);
	String checkedAddress = burstExt.GetNode();

	String v;
	if (checkedAddress.isNotEmpty())
		v = burstExt.getMyInfo();

	if (v.isEmpty())
	{
		NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Node address seems invalid !");
	}
	else
	{
		transactionsComponentListeners.call(&TransactionsComponentListener::SetNode, checkedAddress, false);
		shoutComponentListeners.call(&ShoutComponentListener::SetNode, checkedAddress, false);
		settingsListeners.call(&SettingsListener::SetNode, checkedAddress, false);
		balanceComponentListeners.call(&BalanceComponentListener::SetNode, checkedAddress, false);
	}
}

void InterfaceComponent::SetForceSSL_TSL(const bool forceSSLOn)
{
	SetAppValue("forceSSLOn", String(forceSSLOn ? 1 : 0));

	burstExt.SetForceSSL_TSL(forceSSLOn);
	transactionsComponentListeners.call(&TransactionsComponentListener::SetForceSSL_TSL, forceSSLOn);
	shoutComponentListeners.call(&ShoutComponentListener::SetForceSSL_TSL, forceSSLOn);
	settingsListeners.call(&SettingsListener::SetForceSSL_TSL, forceSSLOn);
	balanceComponentListeners.call(&BalanceComponentListener::SetForceSSL_TSL, forceSSLOn);
}

void InterfaceComponent::SetNodeHop(const bool hopOn)
{
	SetAppValue("hopOn", String(hopOn ? 1 : 0));

	burstExt.EnableNodeHop(hopOn ? 7 : 0);
	transactionsComponentListeners.call(&TransactionsComponentListener::SetNodeHop, hopOn);
	shoutComponentListeners.call(&ShoutComponentListener::SetNodeHop, hopOn);
	settingsListeners.call(&SettingsListener::SetNodeHop, hopOn);
	balanceComponentListeners.call(&BalanceComponentListener::SetNodeHop, hopOn);
}

void InterfaceComponent::MakeCoupon(couponArgs args)
{
	String errorStr;
	// check arguments, addrss/alias amount and fee
	String dispName;
	GetAccountDisplayName(0, args.recipient, dispName);

	String balance = String(burstExt.GetBalance(0));

	if (dispName.isEmpty() || dispName.compare("BURST-2222-2222-2222-22222") == 0)
		errorStr = "Incorrect recipient address, Use a BURST-XXXX-XXXX-XXXX-XXXXX address, numeric ID or an existing alias.";
	else if (args.amountNQT.getLargeIntValue() <= 0)
		errorStr = "Incorrect amount ! use numeric values. Like 123.45";
	else if (args.feeNQT.getLargeIntValue() <= 0)
		errorStr = "Incorrect fee !";
	else if (args.amountNQT.getLargeIntValue() + args.feeNQT.getLargeIntValue() > balance.getLargeIntValue())
	{
		errorStr = "Your balance (" + String(balance.getLargeIntValue()) + ") is too low for this transaction !";
	}
	else if (args.password.isEmpty())
		errorStr = "the coupon password cannot be empty !";

	if (errorStr.isNotEmpty())
		NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, errorStr);
	else
	{
		if (dispName.containsChar(';'))
			dispName = dispName.upToFirstOccurrenceOf(";", false, true);
		if (dispName.compare(args.recipient) != 0)
			dispName = dispName + " (" + args.recipient + ")"; // add RS to text

		if (NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, "Make coupon for " + NQT2Burst(args.amountNQT) + " Burstcoin\nto " + dispName + " ?"))
		{
			String txSignedHex = burstExt.sendMoneyWithMessage(args.recipient, args.amountNQT, args.feeNQT, args.deadline, args.msg, args.encrypted, "", false);
			if (txSignedHex.isNotEmpty())
			{
				String coupon = burstExt.CreateCoupon(txSignedHex, args.password);
				//String transactionID = burstExt.GetJSONvalue(txSignedHex, "transaction");
				if (coupon.isNotEmpty())
				{
					String couponLink = ("https://curbshifter.github.io/BurstHotWallet/RedeemCoupon.html?coupon=" + coupon);
					juce::SystemClipboard::copyTextToClipboard(couponLink);

					StringArray recipients = LimitedTokenList(GetAppValue("contacts"), args.recipient, 10);
					SetAppValue("contacts", recipients.joinIntoString(";"));
					sendComponentListeners.call(&SendComponentListener::SetRecipients, recipients);

					StringArray amounts = LimitedTokenList(GetAppValue("amounts"), NQT2Burst(args.amountNQT), 10);
					SetAppValue("amounts", amounts.joinIntoString(";"));
					sendComponentListeners.call(&SendComponentListener::SetAmounts, amounts);

					NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "The coupon has been copied to clipboard.\nYou can now paste it (with ctrl/cmd + v)");
				}
				else NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "An ERROR occurred coupon has not been made\n\n" + txSignedHex.replace(",", ",\n"));
			}
		}
	}
}

void InterfaceComponent::RedeemCoupon(const String couponCode, const String password)
{
	burstExt.RedeemCoupon(couponCode, password);
}

void InterfaceComponent::SendHotWalletLicense(const String recipient)
{
	String dispName;
	GetAccountDisplayName(0, recipient, dispName);
	if (NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, "Send license to " + dispName + " ?"))
	{
		String assetID;
		if (assetID.isEmpty())
		{ // find the HotWallet asset
			String assetsByCurb = burstExt.getAssetsByIssuer(burstExt.ensureAccountID("HotWallet"));
			var assetsByCurbJson;
			Result r = JSON::parse(assetsByCurb, assetsByCurbJson);
			if (assetsByCurbJson["assets"].isArray() && assetsByCurbJson["assets"][0].isArray())
			{
				for (int i = 0; i < assetsByCurbJson["assets"][0].size(); i++)
				{
					if (assetsByCurbJson["assets"][0][i]["name"].toString().compareIgnoreCase("HotWallet") == 0)
					{
						assetID = assetsByCurbJson["assets"][0][i]["asset"].toString();
						assetIDNumberOfAccounts = (int64)assetsByCurbJson["assets"][0][i]["numberOfAccounts"];
					}
				}
			}
		}

		String transferAssetResp = burstExt.transferAsset(recipient, assetID, "1", "normal", "1440", true, 0);
		String transactionID = burstExt.GetJSONvalue(transferAssetResp, "transaction");
		if (transactionID.isNotEmpty())
			NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "License sent" + transactionID);
		else NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Send license FAILED !");
	}
}

void InterfaceComponent::SendAsset(const String recipient, const String assetID, const String amountNQT, const String feeNQT, const String msg, const bool encrypted)
{
	String errorStr;
	String dispName;
	GetAccountDisplayName(0, recipient, dispName);

	String balance = String(burstExt.GetBalance(0));
	uint64 balanceAsset = (burstExt.GetAssetBalance(assetID, 0));
	int whitelistIdx = assetWhitelist.indexOf(assetID);
	int dec = assetWhitelistDecimals[whitelistIdx].getLargeIntValue();

	// asset can have less decimals than the default 8. convert if needed
	uint64 amountNQT_Asset = amountNQT.getLargeIntValue() / (uint64)(pow(10., 8 - dec));


	if (dispName.isEmpty() || dispName.compare("BURST-2222-2222-2222-22222") == 0)
		errorStr = "Incorrect recipient address, Use a BURST-XXXX-XXXX-XXXX-XXXXX address, numeric ID or an existing alias.";
	else if (amountNQT_Asset <= 0)
		errorStr = "Incorrect amount ! use numeric values. Like 123.45";
	else if (feeNQT.getLargeIntValue() <= 0)
		errorStr = "Incorrect fee !";
	else if (feeNQT.getLargeIntValue() > balance.getLargeIntValue())
		errorStr = "Your balance is too low to make this transaction ! (check BURST fee)";
	else if (amountNQT_Asset > balanceAsset)
	{
		errorStr = "Your balance (" + String(balanceAsset / pow(10., dec), dec) + ") is too low to make this transaction !";
	}

	if (errorStr.isNotEmpty())
		NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, errorStr);
	else
	{
		if (dispName.containsChar(';'))
			dispName = dispName.upToFirstOccurrenceOf(";", false, true);
		if (dispName.compare(recipient) != 0)
			dispName = dispName + " (" + recipient + ")"; // add RS to text

		if (NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, ProjectInfo::projectName, "Send " + String(amountNQT_Asset / (pow(10., dec)), dec) + " " + assetWhitelistNames[whitelistIdx] + " to " + dispName + " ?"))
		{
			String transferAssetResp = burstExt.transferAsset(recipient, assetID, String(amountNQT_Asset), feeNQT, "1440", msg, encrypted, "", true, 0);
			String transactionID = burstExt.GetJSONvalue(transferAssetResp, "transaction");
			if (transactionID.isNotEmpty())
				NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Asset sent!\ntransaction id: " + transactionID);
			else NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Send asset FAILED ! Cannot create transaction.");
		}
	}
}

void InterfaceComponent::SendBurstcoin(const String recipient, const String amountNQT, const String feeNQT, const String msg, const bool encrypted)
{
	String errorStr;
	// check arguments, addrss/alias amount and fee
	String dispName;
	GetAccountDisplayName(0, recipient, dispName);

	String balance = String(burstExt.GetBalance(0));
	if (dispName.isEmpty() || dispName.compare("BURST-2222-2222-2222-22222") == 0)
		errorStr = "Incorrect recipient address, Use a BURST-XXXX-XXXX-XXXX-XXXXX address, numeric ID or an existing alias.";
	else if (amountNQT.getLargeIntValue() <= 0 && amountNQT.compare("0") != 0)
		errorStr = "Incorrect amount ! use numeric values. Like 123.45";
	else if (feeNQT.getLargeIntValue() <= 0)
		errorStr = "Incorrect fee !";
	else if (amountNQT.getLargeIntValue() + feeNQT.getLargeIntValue() > balance.getLargeIntValue())
		errorStr = "Your balance is too low for this transaction !";

	if (errorStr.isNotEmpty())
		NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, errorStr);
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
				StringArray recipients = LimitedTokenList(GetAppValue("contacts"), recipient, 10);
				SetAppValue("contacts", recipients.joinIntoString(";"));
				sendComponentListeners.call(&SendComponentListener::SetRecipients, recipients);

				StringArray amounts = LimitedTokenList(GetAppValue("amounts"), NQT2Burst(amountNQT), 10);
				SetAppValue("amounts", amounts.joinIntoString(";"));
				sendComponentListeners.call(&SendComponentListener::SetAmounts, amounts);

				NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Transaction send successfully !");
			}
			else NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "An ERROR occurred transaction has not been send\n\n" + resp.replace(",", ",\n"));
		}
	}
}

void InterfaceComponent::SetAssetsBalances(const StringPairArray assetsBalances)
{
	this->assetsBalances = assetsBalances;

	UpdateAssetData();
}

void InterfaceComponent::Broke(const bool show, const String pubKey_b64, const bool isPro)
{ // show the secure account option, if the wallet is empty and has no pubkey
	this->isPro = isPro;
	historyComponentListeners.call(&HistoryComponentListener::ShowSecureAccount, show, pubKey_b64, isPro);
	repaint();
}

void InterfaceComponent::GetAccountDisplayName(const uint64 account, const String accountRS, String &displayName)
{
	if(accountRS.isEmpty())
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

void InterfaceComponent::CreateWallet()
{
	pinComponent->setViewMode(1);
	pinComponent->setVisible(true);
}

void InterfaceComponent::SavePassPhrase(String passphrase, String pin)
{ // called from PIN dialog
	pinComponent->setVisible(false);
	if (passphrase.isNotEmpty())
	{
		// reload burstExt account
		burstExt.SetSecretPhrase(passphrase, 0);
		transactionsComponentListeners.call(&TransactionsComponentListener::SetSecretPhrase, passphrase);
		settingsListeners.call(&SettingsListener::SetSecretPhrase, passphrase);
		balanceComponentListeners.call(&BalanceComponentListener::SetSecretPhrase, passphrase);

		String encryptedPassPhrase = Encrypt("PIN" + passphrase, pin).replace("\"", "&quot;");
		SetAppValue("passPhraseEnc", encryptedPassPhrase);
	}
	else SetAppValue("passPhraseEnc", "");

	balanceComponentListeners.call(&BalanceComponentListener::UpdateBalance);

	SetView(1);
}

void InterfaceComponent::WalletPubKeyToClipboard(const int index)
{
	String pubKey_hex, pubKey_b64;
	String reedSolomon;
	String addressID;
	burstExt.GetWallet(index, pubKey_hex, pubKey_b64, reedSolomon, addressID);
	juce::SystemClipboard::copyTextToClipboard(pubKey_b64);

	NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Public key:\n" + pubKey_b64 + "\nis copied to clipboard");
}

void InterfaceComponent::SetupSendView()
{
	String feeStr = burstExt.suggestFee();
	uint64 cheap = burstExt.GetJSONvalue(feeStr, "cheap").getLargeIntValue();
	uint64 standard = burstExt.GetJSONvalue(feeStr, "standard").getLargeIntValue();
	uint64 priority = burstExt.GetJSONvalue(feeStr, "priority").getLargeIntValue();
	sendComponentListeners.call(&SendComponentListener::SetSuggestedFees, cheap, standard, priority);

	StringArray recipients = StringArray::fromTokens(GetAppValue("contacts"), ";", "");
	sendComponentListeners.call(&SendComponentListener::SetRecipients, recipients);

	StringArray amounts = StringArray::fromTokens(GetAppValue("amounts"), ";", "");
	sendComponentListeners.call(&SendComponentListener::SetAmounts, amounts);
}

void InterfaceComponent::UpdateAssetData()
{
	StringArray assets;
	StringArray assetsNames;
	StringArray assetsDescription;
	StringArray assetsDecimals;
	GetAssetWhitelist(assets, assetsNames, assetsDescription, assetsDecimals);
	sendComponentListeners.call(&SendComponentListener::SetAssets, assets, assetsNames, assetsDescription, assetsDecimals, assetsBalances);
	transactionsComponentListeners.call(&TransactionsComponentListener::SetAssets, assets, assetsNames, assetsDescription, assetsDecimals, assetsBalances);
}

void InterfaceComponent::GetAssetWhitelist(StringArray &assets, StringArray &assetsNames, StringArray &assetsDescription, StringArray &assetsDecimals)
{
	if (assetWhitelist.size() <= 0)
	{
		assets = assetsBalances.getAllKeys();
		assets.sortNatural();
		assets.move(assets.indexOf("0"), 0); // put Burst up front

		for (int i = 0; i < assets.size(); i++)
		{
			if (assets[i].compare("0") == 0)
			{
				assetsNames.add("BURST");
				assetsDescription.add("Burstcoin");
				assetsDecimals.add("8");
			}
			else
			{
				String assetStr = burstExt.getAsset(assets[i]);
				var assetJson;
				Result r = JSON::parse(assetStr, assetJson);

				assetsNames.add(assetJson["name"].toString());
				assetsDescription.add(assetJson["description"].toString());
				assetsDecimals.add(assetJson["decimals"].toString());
			}
		}

		assetWhitelist = assets;
		assetWhitelistNames = assetsNames;
		assetWhitelistDescription = assetsDescription;
		assetWhitelistDecimals = assetsDecimals;
	}
	else
	{
		assets = assetWhitelist;
		assetsNames = assetWhitelistNames;
		assetsDescription = assetWhitelistDescription;
		assetsDecimals = assetWhitelistDecimals;
	}
}

/*********************************************************************************/
#if ALLOW_EXT_REQ == 1
// implement this using secure websockets (boost+beast)
void InterfaceComponent::OpenHttpSocket(const String host_address, const int port, bool &ok)
{
	CloseHttpSocket();

	if (streamingSocket == nullptr)
	{
		streamingSocket = new juce::StreamingSocket();
		ok = streamingSocket->createListener(port, host_address);
	}
}

void InterfaceComponent::CloseHttpSocket()
{
	if (streamingSocket)
		streamingSocket->close();
}

bool InterfaceComponent::ProcessHttpSocketMessage(const MemoryBlock& message)
{
	if (message.getSize() > 0)
	{
		if (CharPointer_UTF8::isValidString((const char* const)message.getData(), message.getSize()) == false)
			return false;
		const String dataStr = message.toString();

		var jsonStructure;
		Result r = JSON::parse(dataStr, jsonStructure);
		if (r.wasOk())
		{
			const String requestHeader = jsonStructure.getProperty("requestHeader", String::empty);
			const String recipient = jsonStructure.getProperty("recipient", String::empty);
			const String amountNQT = jsonStructure.getProperty("amountNQT", String::empty);
			const String feeNQT = jsonStructure.getProperty("feeNQT", String::empty);
			const String msg = jsonStructure.getProperty("msg", String::empty);
			const bool encrypted = jsonStructure.getProperty("encrypted", false);

			SetupTransaction(requestHeader, recipient, amountNQT, feeNQT, msg, encrypted);

#ifdef JUCE_WINDOWS
			FLASHWINFO fwi;
			fwi.cbSize = sizeof(fwi);
			fwi.hwnd = static_cast<HWND>(getWindowHandle());
			fwi.dwFlags = FLASHW_TIMERNOFG | FLASHW_TRAY; // FLASHW_ALL
			fwi.uCount = 10;
			fwi.dwTimeout = 0;
			FlashWindowEx(&fwi);
#elif JUCE_MAC
			MacOSUserNotification notifier;
			notifier.Send(ProjectInfo::projectName, msg.toUTF8());
#endif

			return true;
		}
	}
	return false;
}
#endif

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
                 initialHeight="700">
  <METHODS>
    <METHOD name="mouseUp (const MouseEvent&amp; e)"/>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
    <METHOD name="keyStateChanged (bool isKeyDown)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff343434">
    <IMAGE pos="44 244 128 32" resource="burstHotWalletlogo_svg" opacity="1"
           mode="2"/>
    <IMAGE pos="44 292 128 32" resource="burstHotWalletPrologo_svg" opacity="1"
           mode="2"/>
    <RECT pos="4 4 636 524" fill=" radial: 624 528, 100 100, 0=ff004578, 1=ff00432f"
          hasStroke="0"/>
    <IMAGE pos="12 12 64 24" resource="burst_logo_white_svg" opacity="1"
           mode="1"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="balanceComponent" id="dccea979d2f05486" memberName="balanceComponent"
                    virtualName="" explicitFocusOrder="0" pos="136 24 416 24" class="BalanceComponent"
                    params=""/>
  <TEXTBUTTON name="settingsButton" id="3c0d9880abeb454a" memberName="settingsButton"
              virtualName="" explicitFocusOrder="0" pos="576 8 56 56" tooltip="show settings"
              bgColOff="ff84cb16" bgColOn="ff84cb16" textCol="ffffffff" buttonText="cog"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="shoutComponent" id="b8cc02c9a4d4d2c2" memberName="shoutComponent"
                    virtualName="" explicitFocusOrder="0" pos="120 496 416 24" class="ShoutComponent"
                    params=""/>
  <GENERICCOMPONENT name="sendComponent" id="581fb820cd30f666" memberName="sendComponent"
                    virtualName="" explicitFocusOrder="0" pos="120 72 168 224" class="SendComponent"
                    params=""/>
  <TEXTBUTTON name="historyButton" id="c0a926ef92b2eeb8" memberName="historyButton"
              virtualName="" explicitFocusOrder="0" pos="0 72 110 24" bgColOff="ff84cb16"
              bgColOn="ff84cb16" buttonText="history" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="sendButton" id="411c767fae4dc759" memberName="sendButton"
              virtualName="" explicitFocusOrder="0" pos="0 96 112 24" bgColOff="ff84cb16"
              bgColOn="ff84cb16" buttonText="send" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <GENERICCOMPONENT name="historyComponent" id="78be139897394c8f" memberName="historyComponent"
                    virtualName="" explicitFocusOrder="0" pos="296 72 168 224" class="HistoryComponent"
                    params=""/>
  <LABEL name="versionLabel" id="eebdf42a75f7e3d7" memberName="versionLabel"
         virtualName="" explicitFocusOrder="0" pos="48 40 64 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="v0.1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="11" bold="0" italic="0" justification="9"/>
  <GENERICCOMPONENT name="settingsComponent" id="205c6171ce3a77a7" memberName="settingsComponent"
                    virtualName="" explicitFocusOrder="0" pos="472 72 168 224" class="SettingsComponent"
                    params=""/>
  <GENERICCOMPONENT name="pinComponent" id="33c6370b679be6dc" memberName="pinComponent"
                    virtualName="" explicitFocusOrder="0" pos="296 304 168 179" class="PinComponent"
                    params=""/>
  <GENERICCOMPONENT name="aboutComponent" id="ab42d58ceea79f04" memberName="aboutComponent"
                    virtualName="" explicitFocusOrder="0" pos="120 304 168 179" class="AboutComponent"
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

// JUCER_RESOURCE: burstHotWalletPrologo_svg, 14333, "BurstHotWalletPro-logo.svg"
static const unsigned char resource_InterfaceComponent_burstHotWalletPrologo_svg[] = { 60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,110,99,111,100,105,110,103,61,34,85,84,
70,45,56,34,32,115,116,97,110,100,97,108,111,110,101,61,34,110,111,34,63,62,10,60,33,45,45,32,71,101,110,101,114,97,116,111,114,58,32,65,100,111,98,101,32,73,108,108,117,115,116,114,97,116,111,114,32,
49,56,46,49,46,49,44,32,83,86,71,32,69,120,112,111,114,116,32,80,108,117,103,45,73,110,32,46,32,83,86,71,32,86,101,114,115,105,111,110,58,32,54,46,48,48,32,66,117,105,108,100,32,48,41,32,32,45,45,62,10,
10,60,115,118,103,10,32,32,32,120,109,108,110,115,58,100,99,61,34,104,116,116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,101,108,101,109,101,110,116,115,47,49,46,49,47,34,10,32,32,32,120,
109,108,110,115,58,99,99,61,34,104,116,116,112,58,47,47,99,114,101,97,116,105,118,101,99,111,109,109,111,110,115,46,111,114,103,47,110,115,35,34,10,32,32,32,120,109,108,110,115,58,114,100,102,61,34,104,
116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,49,57,57,57,47,48,50,47,50,50,45,114,100,102,45,115,121,110,116,97,120,45,110,115,35,34,10,32,32,32,120,109,108,110,115,58,115,118,103,61,34,
104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,10,32,32,32,120,109,108,110,115,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,
48,48,48,47,115,118,103,34,10,32,32,32,120,109,108,110,115,58,115,111,100,105,112,111,100,105,61,34,104,116,116,112,58,47,47,115,111,100,105,112,111,100,105,46,115,111,117,114,99,101,102,111,114,103,101,
46,110,101,116,47,68,84,68,47,115,111,100,105,112,111,100,105,45,48,46,100,116,100,34,10,32,32,32,120,109,108,110,115,58,105,110,107,115,99,97,112,101,61,34,104,116,116,112,58,47,47,119,119,119,46,105,
110,107,115,99,97,112,101,46,111,114,103,47,110,97,109,101,115,112,97,99,101,115,47,105,110,107,115,99,97,112,101,34,10,32,32,32,118,101,114,115,105,111,110,61,34,49,46,49,34,10,32,32,32,105,100,61,34,
67,97,112,97,95,49,34,10,32,32,32,120,61,34,48,112,120,34,10,32,32,32,121,61,34,48,112,120,34,10,32,32,32,118,105,101,119,66,111,120,61,34,48,32,48,32,53,57,57,46,57,57,57,57,55,32,51,53,57,46,57,57,57,
57,57,34,10,32,32,32,120,109,108,58,115,112,97,99,101,61,34,112,114,101,115,101,114,118,101,34,10,32,32,32,115,111,100,105,112,111,100,105,58,100,111,99,110,97,109,101,61,34,66,117,114,115,116,72,111,
116,87,97,108,108,101,116,80,114,111,45,108,111,103,111,46,115,118,103,34,10,32,32,32,105,110,107,115,99,97,112,101,58,118,101,114,115,105,111,110,61,34,48,46,57,50,46,49,32,114,49,53,51,55,49,34,10,32,
32,32,119,105,100,116,104,61,34,54,48,48,34,10,32,32,32,104,101,105,103,104,116,61,34,51,54,48,34,10,32,32,32,105,110,107,115,99,97,112,101,58,101,120,112,111,114,116,45,102,105,108,101,110,97,109,101,
61,34,69,58,92,67,43,43,92,66,117,114,115,116,92,66,117,114,115,116,72,111,116,87,97,108,108,101,116,92,66,117,114,115,116,72,111,116,87,97,108,108,101,116,46,103,105,116,92,116,114,117,110,107,92,83,
111,117,114,99,101,92,66,117,114,115,116,72,111,116,87,97,108,108,101,116,45,108,111,103,111,45,98,105,103,46,112,110,103,34,10,32,32,32,105,110,107,115,99,97,112,101,58,101,120,112,111,114,116,45,120,
100,112,105,61,34,54,53,46,52,53,52,53,52,52,34,10,32,32,32,105,110,107,115,99,97,112,101,58,101,120,112,111,114,116,45,121,100,112,105,61,34,54,53,46,52,53,52,53,52,52,34,62,60,109,101,116,97,100,97,
116,97,10,32,32,32,32,32,105,100,61,34,109,101,116,97,100,97,116,97,52,49,34,62,60,114,100,102,58,82,68,70,62,60,99,99,58,87,111,114,107,10,32,32,32,32,32,32,32,32,32,114,100,102,58,97,98,111,117,116,
61,34,34,62,60,100,99,58,102,111,114,109,97,116,62,105,109,97,103,101,47,115,118,103,43,120,109,108,60,47,100,99,58,102,111,114,109,97,116,62,60,100,99,58,116,121,112,101,10,32,32,32,32,32,32,32,32,32,
32,32,114,100,102,58,114,101,115,111,117,114,99,101,61,34,104,116,116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,100,99,109,105,116,121,112,101,47,83,116,105,108,108,73,109,97,103,101,34,
32,47,62,60,100,99,58,116,105,116,108,101,62,60,47,100,99,58,116,105,116,108,101,62,60,47,99,99,58,87,111,114,107,62,60,47,114,100,102,58,82,68,70,62,60,47,109,101,116,97,100,97,116,97,62,60,100,101,102,
115,10,32,32,32,32,32,105,100,61,34,100,101,102,115,51,57,34,32,47,62,60,115,111,100,105,112,111,100,105,58,110,97,109,101,100,118,105,101,119,10,32,32,32,32,32,112,97,103,101,99,111,108,111,114,61,34,
35,102,102,102,102,102,102,34,10,32,32,32,32,32,98,111,114,100,101,114,99,111,108,111,114,61,34,35,54,54,54,54,54,54,34,10,32,32,32,32,32,98,111,114,100,101,114,111,112,97,99,105,116,121,61,34,49,34,10,
32,32,32,32,32,111,98,106,101,99,116,116,111,108,101,114,97,110,99,101,61,34,49,48,34,10,32,32,32,32,32,103,114,105,100,116,111,108,101,114,97,110,99,101,61,34,49,48,34,10,32,32,32,32,32,103,117,105,100,
101,116,111,108,101,114,97,110,99,101,61,34,49,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,112,97,103,101,111,112,97,99,105,116,121,61,34,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,
101,58,112,97,103,101,115,104,97,100,111,119,61,34,50,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,119,105,100,116,104,61,34,49,49,49,49,34,10,32,32,32,32,32,105,110,
107,115,99,97,112,101,58,119,105,110,100,111,119,45,104,101,105,103,104,116,61,34,56,53,57,34,10,32,32,32,32,32,105,100,61,34,110,97,109,101,100,118,105,101,119,51,55,34,10,32,32,32,32,32,115,104,111,
119,103,114,105,100,61,34,102,97,108,115,101,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,122,111,111,109,61,34,48,46,55,53,50,50,57,57,49,49,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,
58,99,120,61,34,50,52,57,46,51,48,48,53,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,121,61,34,50,49,49,46,57,56,55,55,51,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,
100,111,119,45,120,61,34,49,54,56,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,121,61,34,53,57,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,
111,119,45,109,97,120,105,109,105,122,101,100,61,34,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,117,114,114,101,110,116,45,108,97,121,101,114,61,34,108,97,121,101,114,53,34,10,32,32,32,
32,32,105,110,107,115,99,97,112,101,58,112,97,103,101,99,104,101,99,107,101,114,98,111,97,114,100,61,34,102,97,108,115,101,34,10,32,32,32,32,32,115,104,111,119,98,111,114,100,101,114,61,34,116,114,117,
101,34,10,32,32,32,32,32,98,111,114,100,101,114,108,97,121,101,114,61,34,102,97,108,115,101,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,115,104,111,119,112,97,103,101,115,104,97,100,111,119,
61,34,116,114,117,101,34,32,47,62,60,103,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,103,114,111,117,112,109,111,100,101,61,34,108,97,121,101,114,34,10,32,32,32,32,32,105,100,61,34,108,97,121,101,
114,49,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,108,97,98,101,108,61,34,76,97,121,101,114,32,50,34,10,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,
110,101,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,49,52,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,54,34,10,32,32,32,32,
32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,56,34,10,32,32,32,32,32,116,
114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,49,48,34,10,32,32,32,32,32,116,114,
97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,49,50,34,10,32,32,32,32,32,116,114,97,
110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,49,52,34,10,32,32,32,32,32,116,114,97,110,
115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,49,54,34,10,32,32,32,32,32,116,114,97,110,115,
102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,49,56,34,10,32,32,32,32,32,116,114,97,110,115,102,
111,114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,50,48,34,10,32,32,32,32,32,116,114,97,110,115,102,111,
114,109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,50,50,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,
109,61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,50,52,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,
61,34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,50,54,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,
34,116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,50,56,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,
116,114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,51,48,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,
114,97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,51,50,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,
97,110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,105,100,61,34,103,51,52,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,
110,115,108,97,116,101,40,48,44,45,50,53,49,46,57,57,57,48,51,41,34,32,47,62,60,103,10,32,32,32,32,32,97,114,105,97,45,108,97,98,101,108,61,34,66,85,82,78,69,82,32,77,79,68,69,34,10,32,32,32,32,32,115,
116,121,108,101,61,34,102,111,110,116,45,115,116,121,108,101,58,110,111,114,109,97,108,59,102,111,110,116,45,118,97,114,105,97,110,116,58,110,111,114,109,97,108,59,102,111,110,116,45,119,101,105,103,104,
116,58,110,111,114,109,97,108,59,102,111,110,116,45,115,116,114,101,116,99,104,58,110,111,114,109,97,108,59,102,111,110,116,45,115,105,122,101,58,49,49,49,46,52,51,51,49,51,53,57,57,112,120,59,108,105,
110,101,45,104,101,105,103,104,116,58,49,46,50,53,59,102,111,110,116,45,102,97,109,105,108,121,58,39,66,101,98,97,115,32,78,101,117,101,39,59,45,105,110,107,115,99,97,112,101,45,102,111,110,116,45,115,
112,101,99,105,102,105,99,97,116,105,111,110,58,39,66,101,98,97,115,32,78,101,117,101,39,59,108,101,116,116,101,114,45,115,112,97,99,105,110,103,58,48,112,120,59,119,111,114,100,45,115,112,97,99,105,110,
103,58,48,112,120,59,102,105,108,108,58,35,48,48,48,48,48,48,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,58,110,111,110,101,59,115,116,114,111,107,101,45,119,105,100,
116,104,58,50,46,55,56,53,56,50,56,51,53,34,10,32,32,32,32,32,105,100,61,34,116,101,120,116,52,53,50,48,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,116,101,
40,48,44,45,51,52,48,41,34,32,47,62,60,103,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,103,114,111,117,112,109,111,100,101,61,34,108,97,121,101,114,34,10,32,32,32,32,32,105,100,61,34,108,97,121,
101,114,50,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,108,97,98,101,108,61,34,76,97,121,101,114,32,49,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,108,97,
116,101,40,48,44,45,51,52,48,41,34,10,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,34,32,47,62,60,103,10,32,32,32,32,32,105,110,107,115,99,97,112,101,
58,103,114,111,117,112,109,111,100,101,61,34,108,97,121,101,114,34,10,32,32,32,32,32,105,100,61,34,108,97,121,101,114,53,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,108,97,98,101,108,61,34,76,
97,121,101,114,32,52,34,10,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,116,114,97,110,115,
108,97,116,101,40,48,44,45,49,52,41,34,62,60,103,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,34,10,32,32,32,32,32,32,32,116,114,97,110,115,102,
111,114,109,61,34,109,97,116,114,105,120,40,48,46,57,54,55,56,54,48,55,52,44,48,44,48,44,48,46,57,54,55,56,54,48,55,52,44,53,53,51,46,49,54,56,51,54,44,45,49,48,48,55,46,53,53,50,52,41,34,10,32,32,32,
32,32,32,32,105,100,61,34,103,52,53,54,55,45,56,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,59,111,112,97,99,105,
116,121,58,49,59,102,105,108,108,58,35,102,102,101,48,50,52,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,102,105,108,108,45,114,117,108,101,58,110,111,110,122,101,114,111,59,115,116,114,111,
107,101,58,35,48,48,48,48,48,48,59,115,116,114,111,107,101,45,119,105,100,116,104,58,50,48,46,49,54,53,59,115,116,114,111,107,101,45,108,105,110,101,99,97,112,58,98,117,116,116,59,115,116,114,111,107,
101,45,108,105,110,101,106,111,105,110,58,109,105,116,101,114,59,115,116,114,111,107,101,45,109,105,116,101,114,108,105,109,105,116,58,52,59,115,116,114,111,107,101,45,100,97,115,104,97,114,114,97,121,
58,110,111,110,101,59,115,116,114,111,107,101,45,100,97,115,104,111,102,102,115,101,116,58,48,59,115,116,114,111,107,101,45,111,112,97,99,105,116,121,58,49,59,112,97,105,110,116,45,111,114,100,101,114,
58,102,105,108,108,32,109,97,114,107,101,114,115,32,115,116,114,111,107,101,34,10,32,32,32,32,32,32,32,100,61,34,77,32,49,49,55,46,56,57,57,51,55,44,53,49,46,51,54,51,54,48,49,32,72,32,53,55,55,46,57,
49,55,55,49,32,86,32,50,50,56,46,56,50,56,50,55,32,99,32,48,44,48,32,48,46,55,50,57,49,54,44,49,49,46,54,57,57,52,55,32,45,57,46,48,48,57,53,53,44,50,49,46,52,49,53,57,54,32,45,57,46,55,51,56,55,49,44,
57,46,55,49,54,52,57,32,45,50,57,46,55,49,50,51,52,44,49,48,46,50,48,56,49,53,32,45,50,57,46,55,49,50,51,52,44,49,48,46,50,48,56,49,53,32,108,32,45,49,46,49,55,56,44,45,56,52,46,52,55,54,56,32,99,32,45,
48,46,48,55,52,55,44,54,54,46,50,56,57,52,32,48,46,48,57,53,56,44,53,53,46,53,51,53,55,57,32,45,48,46,48,55,57,55,44,49,50,49,46,56,50,52,57,57,32,76,32,50,50,46,48,56,50,55,57,50,44,50,57,54,46,50,54,
51,51,55,32,50,50,46,48,56,50,51,48,56,44,57,54,46,56,53,50,56,50,56,32,90,34,10,32,32,32,32,32,32,32,105,100,61,34,114,101,99,116,52,54,50,51,45,57,45,52,45,57,45,52,34,10,32,32,32,32,32,32,32,105,110,
107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,10,32,32,32,32,32,32,32,115,111,100,105,112,111,100,105,58,110,111,100,101,116,121,112,101,115,
61,34,99,99,99,122,99,99,99,99,99,99,34,32,47,62,60,114,101,99,116,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,100,105,115,112,108,97,121,58,105,110,108,105,110,101,59,111,112,97,99,105,116,121,
58,49,59,102,105,108,108,58,35,48,50,48,50,48,50,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,102,105,108,108,45,114,117,108,101,58,110,111,110,122,101,114,111,59,115,116,114,111,107,101,58,
110,111,110,101,59,115,116,114,111,107,101,45,119,105,100,116,104,58,50,56,46,56,52,55,55,48,53,56,52,59,115,116,114,111,107,101,45,108,105,110,101,99,97,112,58,98,117,116,116,59,115,116,114,111,107,101,
45,108,105,110,101,106,111,105,110,58,109,105,116,101,114,59,115,116,114,111,107,101,45,109,105,116,101,114,108,105,109,105,116,58,52,59,115,116,114,111,107,101,45,100,97,115,104,97,114,114,97,121,58,
110,111,110,101,59,115,116,114,111,107,101,45,100,97,115,104,111,102,102,115,101,116,58,48,59,115,116,114,111,107,101,45,111,112,97,99,105,116,121,58,49,59,112,97,105,110,116,45,111,114,100,101,114,58,
109,97,114,107,101,114,115,32,115,116,114,111,107,101,32,102,105,108,108,34,10,32,32,32,32,32,32,32,105,100,61,34,114,101,99,116,52,54,50,51,45,57,45,52,34,10,32,32,32,32,32,32,32,119,105,100,116,104,
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
117,114,101,61,34,48,34,32,47,62,60,103,10,32,32,32,32,32,32,32,32,32,97,114,105,97,45,108,97,98,101,108,61,34,46,80,82,79,34,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,111,110,116,45,
115,116,121,108,101,58,110,111,114,109,97,108,59,102,111,110,116,45,118,97,114,105,97,110,116,58,110,111,114,109,97,108,59,102,111,110,116,45,119,101,105,103,104,116,58,110,111,114,109,97,108,59,102,111,
110,116,45,115,116,114,101,116,99,104,58,110,111,114,109,97,108,59,102,111,110,116,45,115,105,122,101,58,50,55,56,46,48,55,48,48,57,56,56,56,112,120,59,108,105,110,101,45,104,101,105,103,104,116,58,49,
46,50,53,59,102,111,110,116,45,102,97,109,105,108,121,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,45,105,110,107,115,99,97,112,101,45,102,111,110,116,45,115,112,101,99,105,102,105,99,97,116,
105,111,110,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,108,101,116,116,101,114,45,115,112,97,99,105,110,103,58,48,112,120,59,119,111,114,100,45,115,112,97,99,105,110,103,58,48,112,120,59,102,
105,108,108,58,35,102,102,101,48,50,52,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,58,110,111,110,101,59,115,116,114,111,107,101,45,119,105,100,116,104,58,52,54,46,
56,56,57,50,51,54,52,53,34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,116,101,120,116,52,53,50,50,34,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,32,32,100,61,34,109,32,54,50,56,46,56,57,55,52,
51,44,53,52,50,46,50,54,53,56,57,32,99,32,48,44,45,53,46,53,54,49,52,32,45,52,46,55,50,55,49,57,44,45,49,48,46,48,49,48,53,50,32,45,49,48,46,48,49,48,53,50,44,45,49,48,46,48,49,48,53,50,32,104,32,45,56,
46,48,54,52,48,51,32,99,32,45,53,46,50,56,51,51,51,44,48,32,45,49,48,46,48,49,48,53,51,44,52,46,52,52,57,49,50,32,45,49,48,46,48,49,48,53,51,44,49,48,46,48,49,48,53,50,32,118,32,49,48,46,53,54,54,54,55,
32,99,32,48,44,53,46,53,54,49,52,32,52,46,55,50,55,50,44,49,48,46,48,49,48,53,50,32,49,48,46,48,49,48,53,51,44,49,48,46,48,49,48,53,50,32,104,32,56,46,48,54,52,48,51,32,99,32,53,46,50,56,51,51,51,44,48,
32,49,48,46,48,49,48,53,50,44,45,52,46,52,52,57,49,50,32,49,48,46,48,49,48,53,50,44,45,49,48,46,48,49,48,53,50,32,122,34,10,32,32,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,111,110,116,45,
115,116,121,108,101,58,110,111,114,109,97,108,59,102,111,110,116,45,118,97,114,105,97,110,116,58,110,111,114,109,97,108,59,102,111,110,116,45,119,101,105,103,104,116,58,110,111,114,109,97,108,59,102,111,
110,116,45,115,116,114,101,116,99,104,58,110,111,114,109,97,108,59,102,111,110,116,45,102,97,109,105,108,121,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,45,105,110,107,115,99,97,112,101,45,
102,111,110,116,45,115,112,101,99,105,102,105,99,97,116,105,111,110,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,102,105,108,108,58,35,102,102,101,48,50,52,59,102,105,108,108,45,111,112,97,99,
105,116,121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,52,54,46,56,56,57,50,51,54,52,53,34,10,32,32,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,50,56,34,10,32,32,32,32,
32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,32,32,
100,61,34,109,32,55,48,56,46,50,55,57,53,57,44,52,56,50,46,55,53,56,56,57,32,99,32,51,51,46,57,50,52,53,53,44,48,32,52,56,46,57,52,48,51,52,44,45,49,55,46,55,57,54,52,57,32,52,56,46,57,52,48,51,52,44,
45,53,51,46,54,54,55,53,51,32,48,44,45,51,53,46,56,55,49,48,52,32,45,49,53,46,48,49,53,55,57,44,45,53,51,46,54,54,55,53,51,32,45,52,56,46,57,52,48,51,52,44,45,53,51,46,54,54,55,53,51,32,104,32,45,51,48,
46,48,51,49,53,55,32,99,32,45,53,46,53,54,49,52,44,48,32,45,49,48,46,48,49,48,53,51,44,52,46,52,52,57,49,50,32,45,49,48,46,48,49,48,53,51,44,49,48,46,48,49,48,53,51,32,118,32,49,54,55,46,51,57,56,50,32,
99,32,48,44,53,46,53,54,49,52,32,52,46,52,52,57,49,51,44,49,48,46,48,49,48,53,50,32,49,48,46,48,49,48,53,51,44,49,48,46,48,49,48,53,50,32,104,32,55,46,55,56,53,57,54,32,99,32,53,46,50,56,51,51,51,44,48,
32,57,46,55,51,50,52,53,44,45,52,46,52,52,57,49,50,32,57,46,55,51,50,52,53,44,45,49,48,46,48,49,48,53,50,32,118,32,45,55,48,46,48,55,51,54,55,32,122,32,109,32,48,44,45,55,57,46,56,48,54,49,50,32,99,32,
49,53,46,48,49,53,55,56,44,48,32,50,49,46,49,51,51,51,51,44,55,46,53,48,55,56,57,32,50,49,46,49,51,51,51,51,44,50,54,46,49,51,56,53,57,32,48,44,49,56,46,48,55,52,53,54,32,45,54,46,49,49,55,53,53,44,50,
54,46,49,51,56,53,57,32,45,50,49,46,49,51,51,51,51,44,50,54,46,49,51,56,53,57,32,104,32,45,49,50,46,53,49,51,49,54,32,118,32,45,53,50,46,50,55,55,49,56,32,122,34,10,32,32,32,32,32,32,32,32,32,32,32,115,
116,121,108,101,61,34,102,111,110,116,45,115,116,121,108,101,58,110,111,114,109,97,108,59,102,111,110,116,45,118,97,114,105,97,110,116,58,110,111,114,109,97,108,59,102,111,110,116,45,119,101,105,103,104,
116,58,110,111,114,109,97,108,59,102,111,110,116,45,115,116,114,101,116,99,104,58,110,111,114,109,97,108,59,102,111,110,116,45,102,97,109,105,108,121,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,
59,45,105,110,107,115,99,97,112,101,45,102,111,110,116,45,115,112,101,99,105,102,105,99,97,116,105,111,110,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,102,105,108,108,58,35,102,102,101,48,50,
52,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,52,54,46,56,56,57,50,51,54,52,53,34,10,32,32,32,32,32,32,32,32,32,32,32,105,100,61,34,112,
97,116,104,52,53,51,48,34,32,47,62,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,32,32,100,61,34,109,32,56,54,54,46,49,49,57,49,51,44,53,48,54,46,49,49,54,55,56,32,99,32,48,44,45,49,52,46,52,53,57,54,
53,32,45,51,46,56,57,50,57,56,44,45,50,53,46,56,54,48,53,50,32,45,49,49,46,57,53,55,48,49,44,45,51,52,46,52,56,48,54,57,32,48,46,56,51,52,50,49,44,45,48,46,56,51,52,50,49,32,49,46,51,57,48,51,53,44,45,
49,46,51,57,48,51,53,32,50,46,50,50,52,53,54,44,45,50,46,50,50,52,53,54,32,56,46,54,50,48,49,55,44,45,56,46,54,50,48,49,56,32,49,49,46,54,55,56,57,52,44,45,50,50,46,53,50,51,54,56,32,49,49,46,54,55,56,
57,52,44,45,51,57,46,55,54,52,48,51,32,48,44,45,51,55,46,50,54,49,51,57,32,45,49,49,46,57,53,55,48,49,44,45,53,52,46,53,48,49,55,52,32,45,52,54,46,49,53,57,54,51,44,45,53,52,46,53,48,49,55,52,32,104,32,
45,51,53,46,48,51,54,56,52,32,99,32,45,53,46,53,54,49,52,44,48,32,45,49,48,46,48,49,48,53,50,44,52,46,52,52,57,49,50,32,45,49,48,46,48,49,48,53,50,44,49,48,46,48,49,48,53,51,32,118,32,49,54,55,46,51,57,
56,49,57,32,99,32,48,44,53,46,53,54,49,52,49,32,52,46,52,52,57,49,50,44,49,48,46,48,49,48,53,51,32,49,48,46,48,49,48,53,50,44,49,48,46,48,49,48,53,51,32,104,32,55,46,55,56,53,57,55,32,99,32,53,46,50,56,
51,51,51,44,48,32,57,46,55,51,50,52,53,44,45,52,46,52,52,57,49,50,32,57,46,55,51,50,52,53,44,45,49,48,46,48,49,48,53,51,32,118,32,45,54,56,46,49,50,55,49,55,32,104,32,49,50,46,53,49,51,49,53,32,99,32,
49,51,46,54,50,53,52,52,44,48,32,50,49,46,52,49,49,52,44,55,46,55,56,53,57,54,32,50,49,46,52,49,49,52,44,50,49,46,54,56,57,52,55,32,118,32,52,54,46,52,51,55,55,32,99,32,48,44,53,46,53,54,49,52,49,32,52,
46,52,52,57,49,50,44,49,48,46,48,49,48,53,51,32,49,48,46,48,49,48,53,51,44,49,48,46,48,49,48,53,51,32,104,32,55,46,55,56,53,57,54,32,99,32,53,46,53,54,49,52,44,48,32,49,48,46,48,49,48,53,50,44,45,52,46,
52,52,57,49,50,32,49,48,46,48,49,48,53,50,44,45,49,48,46,48,49,48,53,51,32,122,32,77,32,56,48,52,46,51,56,55,53,55,44,52,48,50,46,57,53,50,55,55,32,104,32,49,55,46,53,49,56,52,50,32,99,32,49,52,46,52,
53,57,54,52,44,48,32,49,56,46,54,51,48,54,57,44,55,46,55,56,53,57,54,32,49,56,46,54,51,48,54,57,44,50,54,46,54,57,52,55,51,32,48,44,49,56,46,57,48,56,55,55,32,45,56,46,48,54,52,48,51,44,50,54,46,54,57,
52,55,51,32,45,50,51,46,54,51,53,57,54,44,50,54,46,54,57,52,55,51,32,104,32,45,49,50,46,53,49,51,49,53,32,122,34,10,32,32,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,111,110,116,45,115,116,
121,108,101,58,110,111,114,109,97,108,59,102,111,110,116,45,118,97,114,105,97,110,116,58,110,111,114,109,97,108,59,102,111,110,116,45,119,101,105,103,104,116,58,110,111,114,109,97,108,59,102,111,110,116,
45,115,116,114,101,116,99,104,58,110,111,114,109,97,108,59,102,111,110,116,45,102,97,109,105,108,121,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,45,105,110,107,115,99,97,112,101,45,102,111,
110,116,45,115,112,101,99,105,102,105,99,97,116,105,111,110,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,102,105,108,108,58,35,102,102,101,48,50,52,59,102,105,108,108,45,111,112,97,99,105,116,
121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,52,54,46,56,56,57,50,51,54,52,53,34,10,32,32,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,51,50,34,32,47,62,60,112,97,116,
104,10,32,32,32,32,32,32,32,32,32,32,32,100,61,34,109,32,56,56,55,46,51,55,52,49,49,44,53,48,56,46,51,52,49,51,52,32,99,32,48,44,50,49,46,57,54,55,53,52,32,54,46,49,49,55,53,52,44,51,52,46,55,53,56,55,
54,32,49,52,46,55,51,55,55,49,44,52,51,46,51,55,56,57,51,32,57,46,49,55,54,51,50,44,56,46,56,57,56,50,53,32,50,48,46,56,53,53,50,54,44,49,49,46,49,50,50,56,49,32,51,48,46,56,54,53,55,57,44,49,49,46,49,
50,50,56,49,32,49,48,46,50,56,56,53,57,44,48,32,50,49,46,57,54,55,53,51,44,45,50,46,50,50,52,53,54,32,51,49,46,49,52,51,56,53,44,45,49,49,46,49,50,50,56,49,32,56,46,54,50,48,49,55,44,45,56,46,54,50,48,
49,55,32,49,52,46,52,53,57,54,52,44,45,50,49,46,52,49,49,51,57,32,49,52,46,52,53,57,54,52,44,45,52,51,46,51,55,56,57,51,32,86,32,52,50,57,46,54,52,55,53,32,99,32,48,44,45,51,53,46,51,49,52,57,32,45,49,
53,46,48,49,53,55,56,44,45,53,52,46,50,50,51,54,55,32,45,52,53,46,54,48,51,52,57,44,45,53,52,46,50,50,51,54,55,32,45,51,48,46,51,48,57,54,53,44,48,32,45,52,53,46,54,48,51,53,44,49,57,46,49,56,54,56,52,
32,45,52,53,46,54,48,51,53,44,53,52,46,50,50,51,54,55,32,122,32,109,32,50,55,46,56,48,55,48,49,44,45,55,56,46,54,57,51,56,52,32,99,32,48,44,45,49,56,46,48,55,52,53,54,32,53,46,53,54,49,52,44,45,50,54,
46,54,57,52,55,51,32,49,55,46,55,57,54,52,57,44,45,50,54,46,54,57,52,55,51,32,49,49,46,57,53,55,48,49,44,48,32,49,55,46,55,57,54,52,56,44,56,46,48,54,52,48,51,32,49,55,46,55,57,54,52,56,44,50,54,46,54,
57,52,55,51,32,118,32,55,56,46,54,57,51,56,52,32,99,32,48,44,49,56,46,57,48,56,55,55,32,45,54,46,49,49,55,53,52,44,50,54,46,57,55,50,56,32,45,49,55,46,55,57,54,52,56,44,50,54,46,57,55,50,56,32,45,49,49,
46,57,53,55,48,50,44,48,32,45,49,55,46,55,57,54,52,57,44,45,56,46,54,50,48,49,55,32,45,49,55,46,55,57,54,52,57,44,45,50,54,46,57,55,50,56,32,122,34,10,32,32,32,32,32,32,32,32,32,32,32,115,116,121,108,
101,61,34,102,111,110,116,45,115,116,121,108,101,58,110,111,114,109,97,108,59,102,111,110,116,45,118,97,114,105,97,110,116,58,110,111,114,109,97,108,59,102,111,110,116,45,119,101,105,103,104,116,58,110,
111,114,109,97,108,59,102,111,110,116,45,115,116,114,101,116,99,104,58,110,111,114,109,97,108,59,102,111,110,116,45,102,97,109,105,108,121,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,45,105,
110,107,115,99,97,112,101,45,102,111,110,116,45,115,112,101,99,105,102,105,99,97,116,105,111,110,58,39,79,115,116,114,105,99,104,32,83,97,110,115,39,59,102,105,108,108,58,35,102,102,101,48,50,52,59,102,
105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,52,54,46,56,56,57,50,51,54,52,53,34,10,32,32,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,
52,53,51,52,34,32,47,62,60,47,103,62,60,47,103,62,60,47,103,62,60,47,115,118,103,62,0,0};

const char* InterfaceComponent::burstHotWalletPrologo_svg = (const char*) resource_InterfaceComponent_burstHotWalletPrologo_svg;
const int InterfaceComponent::burstHotWalletPrologo_svgSize = 14333;

// JUCER_RESOURCE: burst_logo_white_svg, 3258, "img/burst_logo_white.svg"
static const unsigned char resource_InterfaceComponent_burst_logo_white_svg[] = { 60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,110,99,111,100,105,110,103,61,34,117,116,102,
45,56,34,63,62,13,10,60,33,45,45,32,71,101,110,101,114,97,116,111,114,58,32,65,100,111,98,101,32,73,108,108,117,115,116,114,97,116,111,114,32,49,52,46,48,46,48,44,32,83,86,71,32,69,120,112,111,114,116,
32,80,108,117,103,45,73,110,32,46,32,83,86,71,32,86,101,114,115,105,111,110,58,32,54,46,48,48,32,66,117,105,108,100,32,52,51,51,54,51,41,32,32,45,45,62,13,10,60,33,68,79,67,84,89,80,69,32,115,118,103,
32,80,85,66,76,73,67,32,34,45,47,47,87,51,67,47,47,68,84,68,32,83,86,71,32,49,46,49,47,47,69,78,34,32,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,71,114,97,112,104,105,99,115,47,
83,86,71,47,49,46,49,47,68,84,68,47,115,118,103,49,49,46,100,116,100,34,62,13,10,60,115,118,103,32,118,101,114,115,105,111,110,61,34,49,46,49,34,32,105,100,61,34,67,97,108,113,117,101,95,49,34,32,120,
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

const char* InterfaceComponent::burst_logo_white_svg = (const char*) resource_InterfaceComponent_burst_logo_white_svg;
const int InterfaceComponent::burst_logo_white_svgSize = 3258;


//[EndFile] You can add extra defines here...
//[/EndFile]
