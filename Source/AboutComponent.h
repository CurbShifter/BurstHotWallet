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

#ifndef __JUCE_HEADER_6F5BC92BB0597534__
#define __JUCE_HEADER_6F5BC92BB0597534__

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
class AboutComponent  : public Component,
                        public ButtonListener
{
public:
    //==============================================================================
    AboutComponent ();
    ~AboutComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void addInterfaceListener(InterfaceListener* const l)      { listeners.add(l); };
	void removeInterfaceListener(InterfaceListener* const l)   { listeners.remove(l); };
	ListenerList <InterfaceListener> listeners;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void mouseUp (const MouseEvent& e) override;

    // Binary resources:
    static const char* burstHotWalletlogo_svg;
    static const int burstHotWalletlogo_svgSize;
    static const char* cryptoExtensionsLogo_svg;
    static const int cryptoExtensionsLogo_svgSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> licenseLabel;
    ScopedPointer<TextButton> textButton;
    ScopedPointer<TextButton> proButton;
    ScopedPointer<TextButton> textButton2;
    ScopedPointer<Drawable> drawable1;
    ScopedPointer<Drawable> drawable2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AboutComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_6F5BC92BB0597534__
