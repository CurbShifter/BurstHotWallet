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

#ifndef __JUCE_HEADER_963CDBB75B5D1790__
#define __JUCE_HEADER_963CDBB75B5D1790__

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
class SettingsComponent  : public TextEditorListener,
                           public Component,
                           public SettingsListener,
                           public ButtonListener,
                           public ComboBoxListener
{
public:
    //==============================================================================
    SettingsComponent ();
    ~SettingsComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void addInterfaceListener(InterfaceListener* const l)      { interfaceListeners.add(l); };
	void removeInterfaceListener(InterfaceListener* const l)   { interfaceListeners.remove(l); };

	void SetNode(const String address) override;

	void textEditorTextChanged(TextEditor &editor); //Called when the user changes the text in some way.
	void textEditorReturnKeyPressed(TextEditor &editor); //Called when the user presses the return key.
	void textEditorEscapeKeyPressed(TextEditor &editor); //Called when the user presses the escape key.
	void textEditorFocusLost(TextEditor &editor); //Called when the text editor loses focus.

	void SetForceSSL_TSL(const bool forceSSLOn) override;
	void SetNodeHop(const bool hopOn) override;
	String GetSecretPhrase();
	void SetSecretPhrase(const String str) override;
	void EnableControls(const bool on) override;

	void ChangePIN();
	void CreateWallet() override;
	void NewWallet() override;
	void ExportWallet() override;
	void ImportWallet() override;

	void SetCMCkey(const String key) override;
	void SetCurrencyType(const String type) override;
	void SetCurrencyType(const int type);

	void ShowHttpPopup();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;

    // Binary resources:
    static const char* brswordlist_txt;
    static const int brswordlist_txtSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ListenerList <InterfaceListener> interfaceListeners;
	//String addressRS;
	int currencyType;
	BurstExt burstExt; // used to securely temp store the pass phrase in mem
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextEditor> passPhraseTextEditor;
    ScopedPointer<TextButton> lockButton;
    ScopedPointer<TextButton> myPassPhraseButton;
    ScopedPointer<TextButton> cmcButton;
    ScopedPointer<TextEditor> cmcTextEditor;
    ScopedPointer<TextButton> getKeyButton;
    ScopedPointer<ComboBox> nodeComboBox;
    ScopedPointer<TextButton> nodeAddressButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_963CDBB75B5D1790__
