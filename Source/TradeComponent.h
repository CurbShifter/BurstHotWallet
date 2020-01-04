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

#ifndef TradeComponent_H_INCLUDED
#define TradeComponent_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "BurstExt.h"
#include "Listeners.h"
#include "TradeInterfaceComponent.h"

ApplicationProperties& getAppProperties();

//==============================================================================

class TradeComponent    : public Component,
	public TableListBoxModel,
	public KeyListener,
	public TradeComponentListener,
	public Timer,
	public Thread,
	public ButtonListener,
	public SliderListener,
	public ComboBoxListener
{
public:
    TradeComponent();
    ~TradeComponent();

    void paint (Graphics&) override;
    void resized() override;

	void SetNode(const String address, const bool allowNonSSL = true) override;
	void SetSecretPhrase(const String pp) override;
	void SetForceSSL_TSL(const bool forceSSLOn) override;
	void SetNodeHop(const bool hopOn) override;
	void Refresh() override;
	void CancelAskOrder(String orderID) override;
	void CancelBidOrder(String orderID) override;
	void PlaceAskOrder(String orderID, uint64 quantityQNT, uint64 priceNQT) override;
	void PlaceBidOrder(String assetID, uint64 quantityQNT, uint64 priceNQT) override;
	void CreateAsset(String name, String description, uint64 quantityQNT, uint64 decimals) override;


	void addInterfaceListener(InterfaceListener* const l)      { listeners.add(l); };
	void removeInterfaceListener(InterfaceListener* const l)   { listeners.remove(l); };
	ListenerList <InterfaceListener> listeners;

	void addTradeInterfaceComponentListener(TradeInterfaceComponentListener* const l)      { tradeInterfaceComponentListeners.add(l); };
	void removeTradeInterfaceComponentListener(TradeInterfaceComponentListener* const l)   { tradeInterfaceComponentListeners.remove(l); };
	ListenerList <TradeInterfaceComponentListener> tradeInterfaceComponentListeners;

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

	void UpdateAssetPropeties();

	void SetAssetItems(Array<AssetItem> assetItems);
	AssetItem GetAssetItem(int i);
	int GetAssetItemsSize();
	void ClearAssetItems();
	
	void SetSellOrderItems(Array<OrderItem> orderItems);
	Array<OrderItem> GetSellOrderItems();
	void ClearSellOrderItems();

	void SetBuyOrderItems(Array<OrderItem> orderItems);
	Array<OrderItem> GetBuyOrderItems();
	void ClearBuyOrderItems();

	void GetCurrency(String &key, String &currency);
	void GetPrice(String &currency, double &price);
	void SetPrice(String currency, double price);
	String NeatNr(const String balance);
	
	void ClearAssetWhiteList();
	StringArray GetAssetWhiteList();
	String GetAssetName(const String assetID);
	String GetAssetDecimals(const String assetID);
	String GetAssetDescription(const String assetID);
	
	void ShowPopupMenu(int rowNr);

	String ConvertedValue(String balance);
	void SetAssets(const StringArray assetIDs, const StringArray assetsNames, const StringArray assetsDescription, const StringArray assetsDecimals, const StringPairArray assetsBalances) override;
	int GetAssetIndex(const String assetID);
	
	String GetOwnedAssetId(const int idx);
	String GetAssetBalance(const String assetID);
	int GetAssetBalanceSize();
	void ClearAssetBalances();

	void buttonClicked(Button* buttonThatWasClicked) override;
	void sliderValueChanged(Slider* sliderThatWasMoved) override;
	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

private:
	HashMap<String, var> openAskOrders; // map index is order id
	HashMap<String, var> openBidOrders;
	HashMap<String, var> accountCurrentAskOrders; // map index is order id
	HashMap<String, var> accountCurrentBidOrders;
	HashMap<String, Array<String>> askOrders_Asset_PriceSorted; // map index is asset id, val is array of sorted order ids
	HashMap<String, Array<String>> bidOrders_Asset_PriceSorted;

	int GetSelectedRow();
	void SetSelectedRow(int idx);

	String NQT2Burst(const String value, const String decimals = "8");
	String Burst2NQT(const String value);
	String GetAccountDisplayName(const String account);

	TableListBox table;
	bool triggerRefresh;
	Array<int> sortedRowIndex;
	CriticalSection tldLock;
	CriticalSection burstExtLock;
	CriticalSection assetDetailsLock;
	BurstExt burstKit;
	uint64 cachedTimestamp;
	int sortColumnId;
	bool sortIsForwards;
	uint64 numberOfBlocks;
	int autoRefreshCounter;	
	StringPairArray accountDisplayNames;
	String currency;
	double price;
	String currency_cache;
	double price_cache;
	int64 lastTreadStartTime;
	int selectedAssetRowIdx;

	Array<AssetItem> tableAssetItems;
	Array<OrderItem> assetBuyOrderItems;
	Array<OrderItem> assetSellOrderItems;
	HashMap<String, String> displayNames;

	HashMap<String, String> assetMap;
	StringArray assetIDs;
	StringArray assetNames;
	StringArray assetDescriptions;
	StringArray assetDecimals;
	StringPairArray assetsBalances;

	ScopedPointer<TradeInterfaceComponent> tradeInterfaceComponent;
	Font hfont;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TradeComponent)
};


#endif  // TradeComponent_H_INCLUDED
