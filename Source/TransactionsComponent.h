/*
  ==============================================================================

    TransactionsComponent.h
    Created: 5 Jan 2019 11:12:58am
    Author:  Jorn

  ==============================================================================
*/

#ifndef TRANSACTIONSCOMPONENT_H_INCLUDED
#define TRANSACTIONSCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "BurstExt.h"
#include "Listeners.h"

//==============================================================================
/*
*/
class TransactionsComponent    : public Component,
	public TableListBoxModel,
	public KeyListener,
	public TransactionsComponentListener,
	public Timer,
	public Thread
{
public:
    TransactionsComponent();
    ~TransactionsComponent();

    void paint (Graphics&) override;
    void resized() override;

	void SetNode(String address);
	void SetSecretPhrase(String pp);
	void Refresh();

	void SetCMCkey(const String key);
	void SetCurrencyType(const String currency);
	void GetCurrency(String &key, String &currency);

	void addInterfaceListener(InterfaceListener* const l)      { listeners.add(l); };
	void removeInterfaceListener(InterfaceListener* const l)   { listeners.remove(l); };
	ListenerList <InterfaceListener> listeners;

	// TableListBoxModel
	int getNumRows();
	void paintRowBackground(Graphics&, int rowNumber, int width, int height, bool rowIsSelected);
	void paintCell(Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected);
	Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate);
	void cellClicked(int rowNumber, int columnId, const MouseEvent&);
	void cellDoubleClicked(int rowNumber, int columnId, const MouseEvent&);
	void backgroundClicked(const MouseEvent&);
	void sortOrderChanged(int newSortColumnId, bool isForwards);
	int getColumnAutoSizeWidth(int columnId);
	String getCellTooltip(int rowNumber, int columnId);
	void selectedRowsChanged(int lastRowSelected);
	void deleteKeyPressed(int lastRowSelected);
	void returnKeyPressed(int lastRowSelected);
	void listWasScrolled();

	int getIndexWhenSorted(const int idx); // als je wil weten wat de index is van de sorted row zelf  idx == sortedRowIndex[i]
	int getIndexOfSorted(const int idx);

	// KeyListener
	bool keyPressed(const KeyPress &key, Component *originatingComponent);
	bool keyStateChanged(bool /*isKeyDown*/, Component * /*originatingComponent*/);

	// Timer
	void timerCallback();
	void run();

	struct txDetails
	{
		var value[11];
	};

	TransactionsComponent::txDetails TransactionsComponent::GetCache(int i);
	void SetCache(Array<TransactionsComponent::txDetails> txds);
	int GetCacheSize();
	void ClearCache();

	void GetPrice(String &currency, String &price);
	void SetPrice(String currency, String price);
	String NeatNr(const String balance);
	
	void ExportCSV();
	void ShowPopupMenu(int rowNr);

	String ConvertedValue(String balance);

private:
	TableListBox table;
	bool triggerRefresh;
	ScopedPointer<FileLogger> txlog;
	Array<int> sortedRowIndex;
	CriticalSection tldLock;
	BurstExt burstKit;
	uint64 cachedTimestamp;
	int sortColumnId;
	bool sortIsForwards;
	uint64 numberOfBlocks;
	int autoRefreshCounter;
	
	String cmcAPIkey;
	String currencyType;
	int64 latestCMCtimestamp;
	String currentCurrencyType;

	String currency;
	String price;

	String currency_cache;
	String price_cache;


	Array<txDetails> txDetailArrayCache;
	Array<txDetails> txDetailArray;
	txDetails FillTxStruct(String txDetailsStr);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TransactionsComponent)
};


#endif  // TRANSACTIONSCOMPONENT_H_INCLUDED
