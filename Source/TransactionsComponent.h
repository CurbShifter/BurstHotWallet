/*
==============================================================================
Copyright (C) 2019  CurbShifter

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

	void SetNode(const String address) override;
	void SetSecretPhrase(const String pp) override;
	void SetForceSSL_TSL(const bool forceSSLOn) override;
	void SetNodeHop(const bool hopOn) override;
	void Refresh() override;

	void ResetPriceTimer();

	void SetCMCkey(const String key) override;
	void SetCurrencyType(const String currency) override;
	void GetCurrency(String &key, String &currency);

	void addInterfaceListener(InterfaceListener* const l)      { listeners.add(l); };
	void removeInterfaceListener(InterfaceListener* const l)   { listeners.remove(l); };
	ListenerList <InterfaceListener> listeners;

	// TableListBoxModel
	int getNumRows() override;
	void paintRowBackground(Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
	void paintCell(Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
	Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
	void cellClicked(int rowNumber, int columnId, const MouseEvent&) override;
	void cellDoubleClicked(int rowNumber, int columnId, const MouseEvent&) override;
	void backgroundClicked(const MouseEvent&) override;
	void sortOrderChanged(int newSortColumnId, bool isForwards) override;
	int getColumnAutoSizeWidth(int columnId) override;
	String getCellTooltip(int rowNumber, int columnId) override;
	void selectedRowsChanged(int lastRowSelected) override;
	void deleteKeyPressed(int lastRowSelected) override;
	void returnKeyPressed(int lastRowSelected) override;
	void listWasScrolled() override;

	int getIndexWhenSorted(const int idx); // als je wil weten wat de index is van de sorted row zelf  idx == sortedRowIndex[i]
	int getIndexOfSorted(const int idx);

	// KeyListener
	bool keyPressed(const KeyPress &key, Component *originatingComponent) override;
	bool keyStateChanged(bool /*isKeyDown*/, Component * /*originatingComponent*/) override;

	// Timer
	void timerCallback() override;
	void run() override;

	struct txDetails
	{
		var value[11];
	};

	TransactionsComponent::txDetails GetCache(int i);
	void SetCache(Array<TransactionsComponent::txDetails> txds);
	int GetCacheSize();
	void ClearCache();

	void GetPrice(String &currency, double &price);
	void SetPrice(String currency, double price);
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
	CriticalSection burstExtLock;
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
	double price;

	String currency_cache;
	double price_cache;
	HashMap<String, String> txMap;

	String NQT2Burst(const String value);
	String Burst2NQT(const String value);


	Array<txDetails> txDetailArrayCache;
	Array<txDetails> txDetailArray;
	txDetails FillTxStruct(String txDetailsStr);
	String GetAccountDisplayName(const String account);
	HashMap<String, String> displayNames;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TransactionsComponent)
};


#endif  // TRANSACTIONSCOMPONENT_H_INCLUDED
