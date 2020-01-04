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

#ifndef __JUCE_HEADER_A00B4B2EC4AB43FA__
#define __JUCE_HEADER_A00B4B2EC4AB43FA__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "./../Listeners.h"
#include "Version.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
	,
                         public DragAndDropContainer
                                                                    //[/Comments]
*/
class Menu  : public Component,
              public MenuListener,
              public ButtonListener,
              public ComboBoxListener
{
public:
    //==============================================================================
    Menu ();
    ~Menu();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void addChatListener(ChatComponentListener* const l)      { chatListeners.add(l); };
	void removeChatListener(ChatComponentListener* const l)   { chatListeners.remove(l); };
	ListenerList <ChatComponentListener> chatListeners;

	void addInterfaceListener(InterfaceListener* const l)      { interfaceListeners.add(l); };
	void removeInterfaceListener(InterfaceListener* const l)   { interfaceListeners.remove(l); };
	ListenerList <InterfaceListener> interfaceListeners;

	struct RoomsListBoxModel : public ListBoxModel
	{
		Menu *menu;

		void setParent(Menu *menu);
		// The following methods implement the necessary virtual functions from ListBoxModel,
		// telling the listbox how many rows there are, painting them, etc.
		int getNumRows() override;
		void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
		void listBoxItemClicked(int row, const MouseEvent&) override;
		void listBoxItemDoubleClicked(int row, const MouseEvent&) override;//This can be overridden to react to the user double-clicking on a row.
		void backgroundClicked(const MouseEvent&) override;
		void selectedRowsChanged(int lastRowSelected) override;
		void deleteKeyPressed(int lastRowSelected) override;
		void returnKeyPressed(int lastRowSelected) override;
		void listWasScrolled() override;
		String getTooltipForRow(int row) override;
	/*	MouseCursor getMouseCursorForRow(int row);
		var getDragSourceDescription(const SparseSet<int>& selectedRows) override
		{
			// for our drag description, we'll just make a comma-separated list of the selected row
			// numbers - this will be picked up by the drag target and displayed in its box.
			StringArray rows;

			for (int i = 0; i < selectedRows.size(); ++i)
				rows.add(String(selectedRows[i] + 1));

			return rows.joinIntoString(", ");
		}*/
	};


	void CloseSocket();
	void ToggleSocket();
	void RequestNewTab(bool priv, String name = String::empty);
	void ReloadChannelItems();
	StringArray GetRoomNames();
	String FindActiveTabWithAlias(StringArray aliases);
	
	void AddTab(const String &tabName, uint64 senderID, uint64 receiverID, String receiver, bool privateChannel, const int insertIndex = -1, const bool forceShow = false) override;
	void RemoveTab(const int index) override;
	void TriggerRemoveTab(const int index);

	void ActivateTab(const int index, const bool forceShow) override;
	void NotifyTab(uint64 recipientID, uint64 senderID, bool isPriv, String msg) override;
	void SetStatusText(const String msg, const double progress) override;
	void SetIsOnline(const bool) override;
	void SetAccountRS(const String) override;

	struct tabprops
	{
		String name;
		uint64 senderID;
		uint64 receiverID;
		String receiver;
		bool privateChannel;

		int notify;
	};

	Array<tabprops> getTabs() { return tabs; };
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	RoomsListBoxModel sourceModel;
	String receiverChannel;
	bool isOnline;
	Array<tabprops> tabs;
	String accountRS;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> privateChatButton;
    ScopedPointer<TextButton> publicRoomButton;
    ScopedPointer<ComboBox> channelNameComboBox;
    ScopedPointer<TextButton> slotFeeButton;
    ScopedPointer<ListBox> chatlist;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Menu)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_A00B4B2EC4AB43FA__
