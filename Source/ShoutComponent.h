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

#ifndef __JUCE_HEADER_7800AAD7EC678F74__
#define __JUCE_HEADER_7800AAD7EC678F74__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "Listeners.h"
#include "BurstExt.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
public SettableTooltipClient
                                                                    //[/Comments]
*/
class ShoutComponent  : public Component,
                        public Thread,
                        public Timer,
                        public ShoutComponentListener,
                        public ButtonListener
{
public:
    //==============================================================================
    ShoutComponent ();
    ~ShoutComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void addInterfaceListener(InterfaceListener* const l)      { interfaceListeners.add(l); };
	void removeInterfaceListener(InterfaceListener* const l)   { interfaceListeners.remove(l); };
	void run();
	void timerCallback();

	void SetNode(const String address, const bool allowNonSSL = true) override;
	void SetForceSSL_TSL(const bool forceSSLOn) override;
	void SetNodeHop(const bool hopOn) override;

	struct shout
	{
		String message;
		String senderRS;
		uint64 alivetime;
		uint64 amountNQT;
		float showtime;
	};
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    bool hitTest (int x, int y) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ListenerList <InterfaceListener> interfaceListeners;
	CriticalSection burstExtLock;
	BurstExt burstExt; // used to securely temp store the pass phrase in mem

	CriticalSection shoutsLock;
	Array<shout> shouts;
	unsigned int timerDelay;
	int totalShowTimeLoop;
	int totalShowTime;
	uint64 totalAmountNQTs;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> textButton;
    ScopedPointer<TextButton> shoutMessageButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShoutComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_7800AAD7EC678F74__
