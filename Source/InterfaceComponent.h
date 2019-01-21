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
#include "Listeners.h"

#include "websockets\WebSocketServer.h"
#include "websockets\WebSocket.h"

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
                            public ComboBoxListener,
                            public ButtonListener
{
public:
    //==============================================================================
    InterfaceComponent ();
    ~InterfaceComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void textEditorTextChanged(TextEditor &editor); //Called when the user changes the text in some way.
	void textEditorReturnKeyPressed(TextEditor &editor); //Called when the user presses the return key.
	void textEditorEscapeKeyPressed(TextEditor &editor); //Called when the user presses the escape key.
	void textEditorFocusLost(TextEditor &editor); //Called when the text editor loses focus.

	void SetupTransaction(const String requestHeader, const String recipient, const String amountNQT, const String feeNQT, const String msg, const bool encrypted) override;
	void SendBurstcoin(const String recipient, const String amount, const String fee, const String msg, const bool encrypted) override;
	void GetAccountDisplayName(const uint64 account, const String accountRS, String &displayName) override;
	void UpdateBalance(String &balance) override;

	String Encrypt(String input, String pin);
	String Decrypt(String input, String pin);

	ApplicationProperties appProp;
	PropertiesFile::Options options;
	String GetAppValue(const String type);
	void GetAppValue(const String type, String &value) override;
	void SetAppValue(const String type, const String value) override;

	void SavePassPhraseWithNewPIN(const String passphrase) override;
	void SavePassPhrase(String passphrase, String pin) override;
	void LoadPassPhrase() override;
	void UnloadPassPhrase() override;
	void LoadPassPhraseReturn(String pin) override;

	void SetCMCkey(const String key) override;
	void SetCurrencyType(const String currency) override;
	void SetPrice(String currency, String price) override;
   
	void StartWebSocket() override;
	void CloseWebSocket() override;

	void SendWebSocketMessage(String data) override;

	bool OpenWebSocket(String host_address, int port);
	bool ProcessWebSocketMessage(int connectionNr, const MemoryBlock& message);
	//[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void mouseUp (const MouseEvent& e) override;

    // Binary resources:
    static const char* burstHotWalletlogo_svg;
    static const int burstHotWalletlogo_svgSize;


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

	String NQT2Burst(const String value);
	String Burst2NQT(const String value);

	void timerCallback();
	void SetView(int nr);

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
	String currency;
	String price;
	//ScopedPointer<SystemTrayIconComponent> systemTray;

	class InterfaceWebSocket : public WebSocket
	{
	public:
		InterfaceWebSocket(InterfaceComponent& owner_)
			: WebSocket(true),
			owner(owner_)
		{
			static int totalConnections = 0;
			ourNumber = ++totalConnections;
		}
		void connectionMade()
		{
			MemoryBlock message;
			owner.ProcessWebSocketMessage (ourNumber, message);
		}
		void connectionLost()
		{
			ourNumber = ourNumber;
			MemoryBlock message;
			owner.ProcessWebSocketMessage (ourNumber, message);
		}
		void messageReceived(const MemoryBlock& message)
		{
			owner.ProcessWebSocketMessage(ourNumber, message);
		}

	private:
		InterfaceComponent& owner;
		int ourNumber;
	};

	//==============================================================================
	class InterfaceSocketServer : public WebSocketServer
	{
	public:
		InterfaceSocketServer(InterfaceComponent& owner_)
			: owner(owner_)
		{
		}

		WebSocket* createConnectionObject()
		{
			InterfaceWebSocket* newConnection = new InterfaceWebSocket(owner);
			owner.activeConnections.add(newConnection);
			return (WebSocket*)newConnection;
		}

	private:
		InterfaceComponent& owner;
	};


	juce::Array<juce::String> networkmessage;
	OwnedArray <InterfaceWebSocket, CriticalSection> activeConnections;
	ScopedPointer<InterfaceSocketServer> server;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ComboBox> serverComboBox;
    ScopedPointer<Label> balanceLabel;
    ScopedPointer<TextButton> accountButton;
    ScopedPointer<SendComponent> sendComponent;
    ScopedPointer<TextButton> historyButton;
    ScopedPointer<TextButton> sendButton;
    ScopedPointer<HistoryComponent> historyComponent;
    ScopedPointer<Label> versionLabel;
    ScopedPointer<SettingsComponent> settingsComponent;
    ScopedPointer<PinComponent> pinComponent;
    ScopedPointer<AboutComponent> aboutComponent;
    ScopedPointer<Drawable> drawable1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InterfaceComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_D83B56D27656EC18__
