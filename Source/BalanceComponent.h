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

#ifndef __JUCE_HEADER_D17F15E9BE0252AA__
#define __JUCE_HEADER_D17F15E9BE0252AA__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "Listeners.h"
#include "BurstExt.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class BalanceComponent  : public Component,
                          public Thread,
                          public Timer,
                          public BalanceComponentListener,
                          public ButtonListener,
                          public ComboBoxListener
{
public:
    //==============================================================================
    BalanceComponent ();
    ~BalanceComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void addInterfaceListener(InterfaceListener* const l)      { interfaceListeners.add(l); };
	void removeInterfaceListener(InterfaceListener* const l)   { interfaceListeners.remove(l); };
	
	void run();
	void timerCallback();

	void InitAccountSelection(const int index) override;
	void SetNode(const String address, const bool allowNonSSL = true) override;
	void SetSecretPhrase(const String str) override;
	void SetForceSSL_TSL(const bool forceSSLOn) override;
	void SetNodeHop(const bool hopOn) override;
	void SetPrice(String currency, double price) override;

	void UpdateBalance();
	void UpdateBalanceRun();
	void AddAssetWhitelist(const StringArray assetIDs);
	String GetAssetName(const String assetID, String &decimals);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;

    // Binary resources:
    static const char* diamond_svg;
    static const int diamond_svgSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ListenerList <InterfaceListener> interfaceListeners;
	CriticalSection burstExtLock;
	BurstExt burstExt; // used to securely temp store the pass phrase in mem

	bool updated;
	String balance;
	String balance_converted;
	String myBurstRS;
	bool hasPubKey;
	String pubKey_b64;
	String currency;
	double price;
	bool isPro;
	String assetID;
	int64 assetIDNumberOfAccounts;
	int64 timerDelay;
	StringArray externalAssetWhitelist;
	StringPairArray assetsBalances;
	StringPairArray assetWhitelistNames;
	StringPairArray assetWhitelistDecimals;

	bool iOwnKhoinoor;
	uint64 khoinoor_priceNQT;

	String NQT2Burst(const String value);
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> balanceLabel;
    ScopedPointer<TextButton> accountButton;
    ScopedPointer<ComboBox> accountComboBox;
    ScopedPointer<Drawable> drawable1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BalanceComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_D17F15E9BE0252AA__
