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
                      public ButtonListener,
                      public ComboBoxListener
{
public:
    //==============================================================================
    PinComponent ();
    ~PinComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void addInterfaceListener(InterfaceListener* const l)      { interfaceListeners.add(l); };
	void removeInterfaceListener(InterfaceListener* const l)   { interfaceListeners.remove(l); };

	void textEditorTextChanged(TextEditor &editor); //Called when the user changes the text in some way.
	void textEditorReturnKeyPressed(TextEditor &editor); //Called when the user presses the return key.
	void textEditorEscapeKeyPressed(TextEditor &editor); //Called when the user presses the escape key.
	void textEditorFocusLost(TextEditor &editor); //Called when the text editor loses focus.

	void SavePassPhrase();
	void setMode(String passPhrase = String::empty);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    bool keyPressed (const KeyPress& key) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ListenerList <InterfaceListener> interfaceListeners;
	String passPhrase;
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
    ScopedPointer<Label> saveHeaderLabel;
    ScopedPointer<TextButton> unlockButton;
    ScopedPointer<TextButton> saveButton;
    ScopedPointer<Label> saveHeaderLabel2;
    ScopedPointer<ComboBox> accountsComboBox;
    ScopedPointer<TextButton> textButton_10;
    ScopedPointer<TextButton> newAccountButton;
    ScopedPointer<TextButton> delAccountButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PinComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_2AD4F5BB899E331C__
