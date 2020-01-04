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

#ifndef __JUCE_HEADER_D83B56D27656EC18__
#define __JUCE_HEADER_D83B56D27656EC18__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "BurstExt.h"
#include "LookAndFeel.h"
#include "SettingsComponent.h"
#include "SendComponent.h"
#include "HistoryComponent.h"
#include "PinComponent.h"
#include "AboutComponent.h"
#include "ShoutComponent.h"
#include "BalanceComponent.h"
#include "TradeComponent.h"
#include "ChatComponent.h"
#include "Listeners.h"

#include "HttpServer.h"

/* MSVC 2017
needs a mod in boost line 50 of config.hpp

#if defined(__has_cpp_attribute)
becomes:
#if defined(__clang__) && defined(__has_cpp_attribute)

*/

ApplicationProperties& getAppProperties();


#define INTERFACE_UPDATE_MS 1000
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class InterfaceComponent  : public Component,
                            public TextEditorListener,
                            public Timer,
                            public InterfaceListener,
                            public ButtonListener
{
public:
    //==============================================================================
    InterfaceComponent ();
    ~InterfaceComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void run();

	void textEditorTextChanged(TextEditor &editor); //Called when the user changes the text in some way.
	void textEditorReturnKeyPressed(TextEditor &editor); //Called when the user presses the return key.
	void textEditorEscapeKeyPressed(TextEditor &editor); //Called when the user presses the escape key.
	void textEditorFocusLost(TextEditor &editor); //Called when the text editor loses focus.

	void SetupTransaction(const String requestHeader, const String recipient, const String amountNQT, const String feeNQT, const String msg, const bool encrypted) override;


	String Encrypt(String input, String pin);
	String Decrypt(String input, String pin);

//	ApplicationProperties appProp;
//	PropertiesFile::Options options;
	String GetAppValue(const String type);
	void GetAppValue(const String type, String &value) override;
	void SetAppValue(const String type, const String value) override;

	void RemoveWallet() override;
	void CreateWallet() override;
	void SavePassPhraseWithNewPIN(const String passphrase) override;
	void SavePassPhrase(String passphrase, String pin, String address) override;
	void LoadPassPhrase() override;
	void UnloadPassPhrase() override;
	void LoadPassPhraseReturn(String pin) override;

	void SetCMCkey(const String key) override;
	void SetCurrencyType(const String currency) override;
	void SetPrice(String currency, double price) override;

	void WalletPubKeyToClipboard(const int PC_index) override;
#if ALLOW_EXT_REQ == 1
	void OpenHttpSocket(const String host_address, const int port, bool &ok) override;
	void CloseHttpSocket() override;
	bool ProcessHttpSocketMessage(const MemoryBlock& message);
#endif
	StringArray LimitedTokenList(String tokenlist, String newItem, const int maxItems);

	void SystemTrayNotify(const String message, const String tooltip, const bool highlight) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void mouseUp (const MouseEvent& e) override;
    bool keyPressed (const KeyPress& key) override;
    bool keyStateChanged (bool isKeyDown) override;

    // Binary resources:
    static const char* burstHotWalletlogo_svg;
    static const int burstHotWalletlogo_svgSize;
    static const char* burstHotWalletPrologo_svg;
    static const int burstHotWalletPrologo_svgSize;
    static const char* burst_logo_white_svg;
    static const int burst_logo_white_svgSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	void addSettingsListener(SettingsListener* const l)      { settingsListeners.add(l); };
	void removeSettingsListener(SettingsListener* const l)   { settingsListeners.remove(l); };
	ListenerList <SettingsListener> settingsListeners;

	void addPinComponentListener(PinComponentListener* const l)      { pinComponentListeners.add(l); };
	void removePinComponentListener(PinComponentListener* const l)   { pinComponentListeners.remove(l); };
	ListenerList <PinComponentListener> pinComponentListeners;

	void addSendComponentListener(SendComponentListener* const l)      { sendComponentListeners.add(l); };
	void removeSendComponentListener(SendComponentListener* const l)   { sendComponentListeners.remove(l); };
	ListenerList <SendComponentListener> sendComponentListeners;

	void addTransactionsComponentListener(TransactionsComponentListener* const l)      { transactionsComponentListeners.add(l); };
	void removeTransactionsComponentListener(TransactionsComponentListener* const l)   { transactionsComponentListeners.remove(l); };
	ListenerList <TransactionsComponentListener> transactionsComponentListeners;

	void addShoutComponentListener(ShoutComponentListener* const l)      { shoutComponentListeners.add(l); };
	void removeShoutComponentListener(ShoutComponentListener* const l)   { shoutComponentListeners.remove(l); };
	ListenerList <ShoutComponentListener> shoutComponentListeners;

	void addHistoryComponentListener(HistoryComponentListener* const l)      { historyComponentListeners.add(l); };
	void removeHistoryComponentListener(HistoryComponentListener* const l)   { historyComponentListeners.remove(l); };
	ListenerList <HistoryComponentListener> historyComponentListeners;

	void addBalanceComponentListener(BalanceComponentListener* const l)      { balanceComponentListeners.add(l); };
	void removeBalanceComponentListener(BalanceComponentListener* const l)   { balanceComponentListeners.remove(l); };
	ListenerList <BalanceComponentListener> balanceComponentListeners;

	void addTradeComponentListener(TradeComponentListener* const l)      { tradeComponentListeners.add(l); };
	void removeTradeComponentListener(TradeComponentListener* const l)   { tradeComponentListeners.remove(l); };
	ListenerList <TradeComponentListener> tradeComponentListeners;

	void addChatComponentListener(ChatComponentListener* const l)      { chatComponentListeners.add(l); };
	void removeChatComponentListener(ChatComponentListener* const l)   { chatComponentListeners.remove(l); };
	ListenerList <ChatComponentListener> chatComponentListeners;

	String NQT2Burst(const String value);
	String Burst2NQT(const String value);

	void timerCallback();
	void SetView(int nr);

	int accountIndex = 0;
	void GetAccountNames(StringArray &addresses);
	void GetAccountAddresses(StringArray &addresses);
	void GetAccountIndex(int &index) { index = accountIndex; };
	void SetAccountIndex(const int index);

	void CreateVote();
	void CastVote();

	void LoadVote();
	void OpenURL();
	void AddChoice();
	void DelChoice();

	BurstExt burstExt;
	uint64 lastSendDataMs;

	void log(String message);
	ScopedPointer<CELookAndFeel> wizlaf;

	int autoRefreshCounter;
	ScopedPointer<SystemTrayIconComponent> systemTray;
#if ALLOW_EXT_REQ == 1
	ScopedPointer<StreamingSocket> streamingSocket;
	ScopedPointer<MemoryBlock> socketMessageData;
#endif
	bool isPro;
	String assetID;
	int64 assetIDNumberOfAccounts;

	bool setupTX;
	String setupTX_requestHeader;
	String setupTX_recipient;
	String setupTX_amountNQT;
	String setupTX_feeNQT;
	String setupTX_msg;
	bool setupTX_encrypted;

#if BEAST_SERVER == 1
	ScopedPointer<HttpServer> httpServer;
#endif
	void StopHttpServer()
	{
#if BEAST_SERVER == 1
		httpServer = nullptr;
#endif
	}
	void StartHttpServer()
	{
		setupTX = false;
#if BEAST_SERVER == 1
		httpServer = new HttpServer();

		if (httpServer)
			httpServer->addInterfaceListener(this);

		httpServer->startThread();
#endif
	}

	void Broke(const bool show, const String addressRS, const String pubKey_b64, const bool isPro) override;
	void SetAssetsBalances(const StringPairArray assetsBalances) override;

	// calls to burstExt
	void SetNode(const String value);
	void SetForceSSL_TSL(const bool forceSSLOn) override;
	void SetNodeHop(const bool hopOn) override;
	void MakeCoupon(couponArgs args) override;
	void RedeemCoupon(const String couponCode, const String password);

	void SendBurstcoin(const String recipient, const String amount, const String fee, const String msg, const bool encrypted) override;
	void SendAsset(const String recipient, const String assetID, const String amountNQT, const String feeNQT, const String msg, const bool encrypted) override;
	void SendHotWalletLicense(const String recipient) override;
	//void UpdateBalance(String &balance) override;
	void GetAccountDisplayName(const uint64 account, const String accountRS, String &displayName) override;
	void SetupSendView();
	void GetAssetWhitelist(StringArray &assets, StringArray &assetsNames, StringArray &assetsDescription, StringArray &assetsDecimals);
	void UpdateAssetData();
	StringArray assetWhitelist;
	StringArray assetWhitelistNames;
	StringArray assetWhitelistDescription;
	StringArray assetWhitelistDecimals;
	StringPairArray assetsBalances;
	HashMap<String, String> assetMap;

	juce::Rectangle<float> leftTopCorner1;
	juce::Rectangle<float> leftTopCorner2;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> chatButton;
    ScopedPointer<ChatComponent> chatComponent;
    ScopedPointer<TextButton> inventoryButton;
    ScopedPointer<BalanceComponent> balanceComponent;
    ScopedPointer<TextButton> settingsButton;
    ScopedPointer<ShoutComponent> shoutComponent;
    ScopedPointer<SendComponent> sendComponent;
    ScopedPointer<TextButton> historyButton;
    ScopedPointer<TextButton> sendButton;
    ScopedPointer<HistoryComponent> historyComponent;
    ScopedPointer<Label> versionLabel;
    ScopedPointer<TradeComponent> tradeComponent;
    ScopedPointer<PinComponent> pinComponent;
    ScopedPointer<SettingsComponent> settingsComponent;
    ScopedPointer<AboutComponent> aboutComponent;
    ScopedPointer<Drawable> drawable1;
    ScopedPointer<Drawable> drawable2;
    ScopedPointer<Drawable> drawable3;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InterfaceComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_D83B56D27656EC18__
