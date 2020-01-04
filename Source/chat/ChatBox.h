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

#ifndef __JUCE_HEADER_36298F2EF8F6271E__
#define __JUCE_HEADER_36298F2EF8F6271E__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "MessageList.h"
#include "BurstSocket.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ChatBox  : public TextEditorListener,
                 public Component,
                 public InterfaceListener,
                 public ChatBoxListener,
                 public ButtonListener
{
public:
    //==============================================================================
    ChatBox (uint64 senderID, uint64 receiverID, String receiver, bool privateChannel);
    ~ChatBox();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void addListener(ChatComponentListener* const l)      { listeners.add(l); };
	void removeListener(ChatComponentListener* const l)   { listeners.remove(l); };
	ListenerList <ChatComponentListener> listeners;

/*	void addListener(InterfaceListener* const l)      { listeners.add(l); };
	void removeListener(InterfaceListener* const l)   { listeners.remove(l); };
	ListenerList <InterfaceListener> listeners;*/

	void labelTextChanged(Label* labelThatHasChanged); // Called when a Label's text has changed.
	void editorShown(Label*, TextEditor&); // Called when a Label goes into editing mode and displays a TextEditor.
	void editorHidden(Label*, TextEditor&); // Called when a Label is about to delete its TextEditor and exit editing mode.

	//void ReloadChannelItems();
	void PrimeResize(bool &isAtBottom);
	void ScrollToBottom(int bottomPos);
	void SetMaxETx(int in) { maxETx = in; };

	void GetChatProperties(uint64 &senderID,
		uint64 &receiverID,
		bool &isPrivateChannel,
		String &receiverChannel)
	{
		senderID= this->senderID;
		receiverID = this->receiverID;
		isPrivateChannel = this->isPrivateChannel;
		receiverChannel = this->receiverChannel;
	};

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;

    // Binary resources:
    static const char* burstExtensionsLogo_svg;
    static const int burstExtensionsLogo_svgSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ScopedPointer<Drawable> hatnu_1;
	ScopedPointer<Drawable> hatnu_2;
	ScopedPointer<Drawable> logo;
	//void RequestNewTab(bool priv, String name = String::empty);

	void textEditorTextChanged(TextEditor &editor); //Called when the user changes the text in some way.
	void textEditorReturnKeyPressed(TextEditor &editor); //Called when the user presses the return key.
	void textEditorEscapeKeyPressed(TextEditor &editor); //Called when the user presses the escape key.
	void textEditorFocusLost(TextEditor &editor); //Called when the text editor loses focus.

	void SetView(bool selectNew);
	void SendMessage(String msg = String::empty);
	void SendFile(File file);

	uint64 senderID;
	uint64 receiverID;
	bool isPrivateChannel;
	String receiverChannel;

	int maxETx;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> sendButton;
    ScopedPointer<TextEditor> messageEditor;
    ScopedPointer<TextButton> attachmentButton;
    ScopedPointer<Viewport> messageViewport;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChatBox)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_36298F2EF8F6271E__
