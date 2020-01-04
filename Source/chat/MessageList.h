/*
  ==============================================================================

    MessageList.h
    Created: 22 Oct 2018 1:44:15am
    Author:  Jorn

  ==============================================================================
*/

#ifndef MESSAGELIST_H_INCLUDED
#define MESSAGELIST_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "./../Listeners.h"



class MessageList : public Component, public MessageListListener
{
public:
	MessageList();
	~MessageList();

	void paint(Graphics&) override;
	void resized() override;

	void AddPacketToList(BurstSocket::BurstSocketThread::txPacketIn in);
	void AddMessage(BurstSocket::BurstSocketThread::txPacketIn in);

	void SetFilters(uint64 idSender, uint64 idReceiver, bool isPrivate);
	void AddUnconfirmedSendMessage(String msg);

	void addInterfaceListener(InterfaceListener* const l)      { interfaceListeners.add(l); };
	void removeInterfaceListener(InterfaceListener* const l)   { interfaceListeners.remove(l); };

	void addChatListener(ChatComponentListener* const l)      { chatListeners.add(l); };
	void removeChatListener(ChatComponentListener* const l)   { chatListeners.remove(l); };

	void addChatBoxListener(ChatBoxListener* const l)      { listenersChatBox.add(l); };
	void removeChatBoxListener(ChatBoxListener* const l)   { listenersChatBox.remove(l); };

	void mouseDown(const MouseEvent& event);
	void mouseDoubleClick(const MouseEvent& event);

private:
	ListenerList <ChatBoxListener> listenersChatBox;
	ListenerList <InterfaceListener> interfaceListeners;
	ListenerList <ChatComponentListener> chatListeners;
	Array<BurstSocket::BurstSocketThread::txPacketIn> txPackets;
	HashMap<String, String> accountNames;
	uint64 receiverID;
	uint64 senderID;
	bool isPrivate;

#if ENABLE_MESSGE_LOG == 1
	ScopedPointer<FileLogger> log;
#endif
	int linesNum;
	Array<juce::Rectangle<float>> bubbles;

	uint64 GetUINT64(const String uint64Str)
	{
		return *((uint64*)(GetUINT64MemoryBlock(uint64Str).getData()));
	}

	MemoryBlock GetUINT64MemoryBlock(const String uint64Str)
	{
		juce::BigInteger bigInt;
		bigInt.parseString(uint64Str, 10);
		MemoryBlock m(bigInt.toMemoryBlock());
		m.ensureSize(8, true);
		return m;
	}

	GlyphArrangement DrawFittedText(Graphics& g, const String& text, juce::Rectangle<int> area,
		Justification justification,
		const int maximumNumberOfLines,
		const float minimumHorizontalScale);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MessageList)
};


#endif  // MESSAGELIST_H_INCLUDED
