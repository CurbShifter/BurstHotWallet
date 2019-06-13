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

#ifndef __JUCE_HEADER_2AD4F5BB899E331C__
#define __JUCE_HEADER_2AD4F5BB899E331C__

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
class PinComponent  : public TextEditorListener,
                      public Component,
                      public PinComponentListener,
                      public Thread,
                      public Timer,
                      public ButtonListener
{
public:
    //==============================================================================
    PinComponent ();
    ~PinComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void addInterfaceListener(InterfaceListener* const l)      { interfaceListeners.add(l); };
	void removeInterfaceListener(InterfaceListener* const l)   { interfaceListeners.remove(l); };
	ListenerList <InterfaceListener> interfaceListeners;

	void textEditorTextChanged(TextEditor &editor); //Called when the user changes the text in some way.
	void textEditorReturnKeyPressed(TextEditor &editor); //Called when the user presses the return key.
	void textEditorEscapeKeyPressed(TextEditor &editor); //Called when the user presses the escape key.
	void textEditorFocusLost(TextEditor &editor); //Called when the text editor loses focus.

	void ClearMemory();
	void SavePassPhrase();
	void setViewMode(const int mode, const String passPhrase = String::empty);

	void ExportWallet();
	void CheckPassPhrase();

	String NewPassPhrase();

	void run();
	void ToggleVanityView(const bool togg);
	void timerCallback() override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    bool keyPressed (const KeyPress& key) override;

    // Binary resources:
    static const char* brswordlist_txt;
    static const int brswordlist_txtSize;
    static const char* burstHotWalletlogo_svg;
    static const int burstHotWalletlogo_svgSize;
    static const char* burst_logo_white_svg;
    static const int burst_logo_white_svgSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	bool firstOn;
	bool newOn;
	bool importOn;
	bool savePinOn;
	bool unlockOn;
	bool checkOn;

	BurstKit burstKit;
	BurstKit burstKitVanity;

	bool failedWordCheck;
	int checkIter;

	int vanityItt;
	String passPhraseVanity;
	String vanityWord;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> textButton_1;
    ScopedPointer<Label> unlockHeaderLabel;
    ScopedPointer<TextButton> textButton_2;
    ScopedPointer<TextButton> textButton_3;
    ScopedPointer<TextButton> textButton_4;
    ScopedPointer<TextButton> textButton_5;
    ScopedPointer<TextButton> textButton_6;
    ScopedPointer<TextButton> textButton_7;
    ScopedPointer<TextButton> textButton_8;
    ScopedPointer<TextButton> textButton_9;
    ScopedPointer<TextButton> textButton_0;
    ScopedPointer<TextEditor> pinInputTextEditor;
    ScopedPointer<Label> newWalletLabel;
    ScopedPointer<TextButton> unlockButton;
    ScopedPointer<TextButton> saveButton;
    ScopedPointer<Label> ensurePinLabel;
    ScopedPointer<TextButton> textButton_10;
    ScopedPointer<Label> passPhraseLabel;
    ScopedPointer<Label> importantLabel;
    ScopedPointer<Label> protectHeaderLabel;
    ScopedPointer<Label> addressLabel;
    ScopedPointer<TextButton> refreshButton;
    ScopedPointer<TextButton> importButton;
    ScopedPointer<TextButton> copiedTextButton;
    ScopedPointer<TextEditor> passPhraseTextEditor;
    ScopedPointer<Label> enterPassPhraseLabel;
    ScopedPointer<TextButton> savePassPhraseButton;
    ScopedPointer<Label> enterAddressLabel;
    ScopedPointer<TextButton> newButton;
    ScopedPointer<TextButton> backToStartButton;
    ScopedPointer<TextEditor> checkTextEditor;
    ScopedPointer<Label> checkHeaderLabel;
    ScopedPointer<TextButton> checkButton;
    ScopedPointer<Label> addressHeaderLabel;
    ScopedPointer<Label> passHeaderLabel;
    ScopedPointer<TextButton> copyNewButton;
    ScopedPointer<TextButton> fileSaveButton;
    ScopedPointer<TextEditor> vanityTextEditor;
    ScopedPointer<TextButton> searchButton;
    ScopedPointer<TextButton> searchCancelButton;
    ScopedPointer<Drawable> drawable1;
    ScopedPointer<Drawable> drawable2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PinComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_2AD4F5BB899E331C__
