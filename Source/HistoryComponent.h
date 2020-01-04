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

#ifndef __JUCE_HEADER_DA4CDAE989181B92__
#define __JUCE_HEADER_DA4CDAE989181B92__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "TransactionsComponent.h"
#include "./QR-code/JuceQrCodeGenerator.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class HistoryComponent  : public Component,
                          public HistoryComponentListener,
                          public ButtonListener
{
public:
    //==============================================================================
    HistoryComponent ();
    ~HistoryComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	TransactionsComponent *getTransactionComponent() { return transactionsComponent; };
	void ShowSecureAccount(const bool show, const String addressRS, const String pubKey_b64, const bool isPro) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	bool showSecureAccount;
	String pubKey_b64SecureAccount;
	String addressRS;
	JuceQrCodeGenerator qrCodeGenerator;
	ScopedPointer<Drawable> qrDrawable;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> secureHeaderLabel;
    ScopedPointer<TextButton> twitterButton;
    ScopedPointer<TransactionsComponent> transactionsComponent;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HistoryComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_DA4CDAE989181B92__
