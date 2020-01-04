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

#ifndef __JUCE_HEADER_93FE9B3A387E4086__
#define __JUCE_HEADER_93FE9B3A387E4086__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "Listeners.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SendComponent  : public Component,
                       public SendComponentListener,
                       public ButtonListener,
                       public SliderListener,
                       public ComboBoxListener
{
public:
    //==============================================================================
    SendComponent ();
    ~SendComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void addInterfaceListener(InterfaceListener* const l)      { listeners.add(l); };
	void removeInterfaceListener(InterfaceListener* const l)   { listeners.remove(l); };
	ListenerList <InterfaceListener> listeners;

	void SetupTransaction(const String requestHeader, const String recipient, const String amountNQT, const String feeNQT, const String msg, const bool encrypted) override;
	void SetRecipients(StringArray recipients) override;
	void SetAmounts(StringArray amounts) override;
	void SetSuggestedFees(uint64 cheap, uint64 normal, uint64 priority) override;
	void SetPrice(String currency, double price) override;
	void SetAssets(const StringArray assetIDs, const StringArray assetsNames, const StringArray assetsDescription, const StringArray assetsDecimals, const StringPairArray assetsBalances) override;

	String NQT2Burst(const String value);
	String Burst2NQT(const String value);
	void UpdateTotalLabel(const String amount, const String fee);
	void SendBurst();
	void SetView(int v);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	uint64 cheap;
	uint64 normal;
	uint64 priority;

	String currency;
	double price;
	String notifierURL;

	StringArray assetWhitelist;
	StringArray assetWhitelistNames;
	StringArray assetWhitelistDescription;
	StringArray assetWhitelistDecimals;

	StringPairArray assetsBalances;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> fixedMessageLabel;
    ScopedPointer<Label> totalLabel;
    ScopedPointer<TextButton> sendTextButton;
    ScopedPointer<Slider> feeSlider;
    ScopedPointer<TextEditor> messageTextEditor;
    ScopedPointer<ToggleButton> encryptToggleButton;
    ScopedPointer<Label> messageLabel;
    ScopedPointer<Label> recipientLabel;
    ScopedPointer<Label> amountLabel;
    ScopedPointer<Label> feeLabel;
    ScopedPointer<ComboBox> feeComboBox;
    ScopedPointer<ComboBox> recipientComboBox;
    ScopedPointer<ComboBox> amountComboBox;
    ScopedPointer<Label> paymentLabel;
    ScopedPointer<Label> costLabel;
    ScopedPointer<TextButton> cancelButton;
    ScopedPointer<Label> recipientFixedLabel;
    ScopedPointer<TextEditor> passwordTextEditor;
    ScopedPointer<ToggleButton> couponToggleButton;
    ScopedPointer<Slider> minSlider;
    ScopedPointer<Label> minLabel;
    ScopedPointer<ComboBox> currencyComboBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SendComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_93FE9B3A387E4086__
