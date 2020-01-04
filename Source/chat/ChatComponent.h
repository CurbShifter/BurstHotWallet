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

#ifndef __JUCE_HEADER_B81C54EA15619A42__
#define __JUCE_HEADER_B81C54EA15619A42__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#ifdef JUCE_WINDOWS
#include "Windows.h" // flash window
#endif
#include "BurstExt.h"
#include "ChatBox.h"
#include "Menu.h"
#include "./../Listeners.h"

#define INTERFACE_UPDATE_MS 1000

enum TransportState
{
	Stopped,
	Starting,
	Playing,
	Pausing,
	Paused,
	Stopping
};
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ChatComponent  : public TextEditorListener,
                       public Timer,
                       public ChatComponentListener,
                       public Component
{
public:
    //==============================================================================
    ChatComponent ();
    ~ChatComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void Init();
	void OpenChannels();


	void textEditorTextChanged(TextEditor &editor); //Called when the user changes the text in some way.
	void textEditorReturnKeyPressed(TextEditor &editor); //Called when the user presses the return key.
	void textEditorEscapeKeyPressed(TextEditor &editor); //Called when the user presses the escape key.
	void textEditorFocusLost(TextEditor &editor); //Called when the text editor loses focus.

	bool CheckOpenChannel();
	void SocketSendMessage(const String port, const String txt, const bool encrypted);
	void SocketSendFile(const String port, const File f, const bool encrypted);

	void SetNode(const String, const bool) override;
	void SetSecretPhrase(const String) override;
	void SetForceSSL_TSL(const bool forceSSLOn) override;
	void SetNodeHop(const bool hopOn) override;
	void SetAssetsBalances(const StringPairArray assetsBalances) override;

	void NewTab(const String recipient, bool isPrivate, bool forceShow) override;
	void RemoveTab(uint64 recipientID, bool isPriv) override;
	void RemoveAllTabs();
	void RemoveTab(int tabIndex);
	void ActivateTab(const int index, const bool forceShow);

	void SaveFileStream(File dir, MemoryBlock hash);
	void NotifyTab(uint64 recipientID, uint64 senderID, bool isPriv, String msg);
	int FindTab(uint64 recipientID, bool isPriv, uint64 &senderID, uint64 &receiverID, bool &isPrivateChannel, String &receiverChannel);

	void OpenCloseSocket(const bool open) override;
	void OpenSocket();
	void CloseSocket();

	void SetForceBlock(const bool stayOnline) override;

	void GetHoldSize(int &holdMultiplier) override;
	void SetHoldSize(const int newHoldMultiplier) override;

	void addInterfaceListener(InterfaceListener* const l) {
		if(menu) menu->addInterfaceListener(l);
		interfaceListeners.add(l); 
	};
	void removeInterfaceListener(InterfaceListener* const l) {
		if (menu) menu->removeInterfaceListener(l);
		interfaceListeners.remove(l);
	};
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    bool keyPressed (const KeyPress& key) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ListenerList <InterfaceListener> interfaceListeners;

	void addMessageListListener(MessageListListener* const l)      { messageListListeners.add(l); };
	void removeMessageListListener(MessageListListener* const l)   { messageListListeners.remove(l); };
	ListenerList <MessageListListener> messageListListeners;

	void addChatBoxListener(ChatBoxListener* const l)      { chatBoxListeners.add(l); };
	void removeChatBoxListener(ChatBoxListener* const l)   { chatBoxListeners.remove(l); };
	ListenerList <ChatBoxListener> chatBoxListeners;

	void addMenuListener(MenuListener* const l)      { menuListeners.add(l); };
	void removeMenuListener(MenuListener* const l)   { menuListeners.remove(l); };
	ListenerList <MenuListener> menuListeners;

	void timerCallback();

	void log(String message);

	void Play_Sound(int nr);

	class CustomTabbedComponent : public TabbedComponent
	{
	public:
		CustomTabbedComponent(ChatComponent *parentComponent, TabbedButtonBar::Orientation orientation) : TabbedComponent(orientation)
		{
			getTabbedButtonBar().setMinimumTabScaleFactor(1.0);
			this->parentComponent = parentComponent;
			contextMenu = new PopupMenu;
			contextMenu->addItem(1, "Close", true);
		};
		~CustomTabbedComponent()
		{
			contextMenu = nullptr;
		};

		void currentTabChanged(int newCurrentTabIndex, const String& newCurrentTabName)
		{
			if (newCurrentTabIndex < 0 || newCurrentTabIndex > getNumTabs() - 1)
				return; // ignore settings and new tab

			TabBarButton *tbb = getTabbedButtonBar().getTabButton(newCurrentTabIndex);
			if (tbb)
			{
				ChatBox *chatBox = (ChatBox*)getTabContentComponent(newCurrentTabIndex);
				if (chatBox)
				{
					bool global = newCurrentTabName.startsWithChar('*');
					tbb->setColour(TabbedButtonBar::ColourIds::tabOutlineColourId, Colours::transparentWhite);
					tbb->setColour(TabbedButtonBar::ColourIds::tabTextColourId, Colours::transparentWhite);
				}
			}
		};

		void popupMenuClickOnTab(int tabIndex, const String &/*tabName*/)
		{
			if (tabIndex > 0 && tabIndex < getNumTabs() - 1)
			{
				int result = contextMenu->show();

				if (result == 0)
				{ // user dismissed the menu without picking anything
				}
				else if (result == 1)
				{
					if (NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "Close this chat?") == 1)
					{
						// remove the listeners !
						ChatBox *chatBox = (ChatBox*)getTabContentComponent(tabIndex);
						parentComponent->removeChatBoxListener(chatBox);

						Viewport *messageViewport = (Viewport *)chatBox->findChildWithID("messageViewport");
						if (messageViewport)
						{
							MessageList *messageList = (MessageList *)messageViewport->getViewedComponent();
							if (messageList)
							{
								parentComponent->removeMessageListListener(messageList);
							}
						}
						removeTab(tabIndex);
						setCurrentTabIndex(tabIndex - 1);
					}
				}
			}
		};
		ScopedPointer<PopupMenu> contextMenu;
		ChatComponent *parentComponent;
	};

	uint32 next_banner_poll_ms;
	int notify;
	StringPairArray assetsBalances;
	Array<ScopedPointer<ChatBox>> chatComponents;
	CriticalSection burstSktLock;
	BurstSocket burstSocket;

	String balance;
	bool burning;
	int slot;
	float pressure;
	uint64 activeMessages;
	uint64 maxActive;

	ScopedPointer<Drawable> drawable1;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Menu> menu;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChatComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_B81C54EA15619A42__
