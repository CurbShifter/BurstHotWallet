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

#include "../JuceLibraryCode/JuceHeader.h"
#include "TradeComponent.h"

//==============================================================================
TradeComponent::TradeComponent() : Thread("Transactions")
{
	Typeface::Ptr typefacePtr = Typeface::createSystemTypefaceFor(BinaryData::NotoSansRegular_ttf, BinaryData::NotoSansRegular_ttfSize);
	hfont = Font(typefacePtr);

	addAndMakeVisible(tradeInterfaceComponent = new TradeInterfaceComponent());
	tradeInterfaceComponent->addTradeComponentListener(this);	
	addTradeInterfaceComponentListener(tradeInterfaceComponent);

	cachedTimestamp = 0;
	triggerRefresh = false;
	autoRefreshCounter = 0;
	sortColumnId = 1;
	sortIsForwards = false;
	lastTreadStartTime = 0;
	selectedAssetRowIdx = 0;

	int defWidth = 70;
	int minWidth = 70;
	int idx = 1;
	table.getHeader().addColumn("Asset", idx++, defWidth, minWidth, -1, TableHeaderComponent::visible);
	table.setHeaderHeight(0);
	table.setRowHeight(30);
	table.setModel(this);
	table.addKeyListener(this);
	table.setMultipleSelectionEnabled(false);
	table.getVerticalScrollBar()->setAutoHide(true);
	table.setColour(TableListBox::ColourIds::backgroundColourId, Colour(0xfffcfcfc));
	table.getHeader().setSortColumnId(1, false);
	addAndMakeVisible(table);
	table.autoSizeAllColumns();
	sortOrderChanged(sortColumnId, sortIsForwards);
	
	Refresh();
	startTimer(100);
}

TradeComponent::~TradeComponent()
{
	stopTimer();
	stopThread(20000);

	askOrders_Asset_PriceSorted.clear();
	bidOrders_Asset_PriceSorted.clear();
}

int TradeComponent::getColumnAutoSizeWidth(int columnId)
{
	return table.getWidth() - 20;
}

void TradeComponent::paint(Graphics& g)
{
    g.fillAll (Colours::white);   // clear the background
}

void TradeComponent::resized()
{
	int propBarHeight = 120;
	table.setBoundsInset(BorderSize<int>(0, 0, 0, getWidth() - 200));
	table.autoSizeAllColumns();

	tradeInterfaceComponent->setBounds(200, 0, getWidth() - 200, getHeight());
}

// --------------------------------------------------------------------------------------------------------
int TradeComponent::getNumRows()
{
	return GetAssetItemsSize() + 2;
}

void TradeComponent::paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected)
{
	g.setGradientFill(ColourGradient(Colours::white, width - 100, 0, Colours::whitesmoke, width-20, 0, false));
	g.fillAll();

	if (rowIsSelected)
	{
		g.setColour(Colours::lightgrey.withAlpha(0.5f));
		g.fillRoundedRectangle(0.f, 0.f, width, height, 5.f);
	}
	/*	
	if (isThreadRunning())
	{
		g.fillAll(Colours::lightgrey.withAlpha(0.5f));
		g.setColour(Colours::black);
		g.drawText("Loading...", Rectangle<int>(10, 2, width-10, height-2), Justification::left, false);
	}*/
}

void TradeComponent::paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
	if (GetAssetItemsSize() + 2 <= rowNumber)
		return;

	g.setColour(Colours::black.brighter(0.1));

	if (columnId == 1)
	{
		if (rowNumber == 0)
		{
			g.setColour(Colour(0xff00579d));
			g.setFont(rowIsSelected ? 20.f : 18.f);
			g.drawText("Burstcoin", 0, 0, width - 10, height, Justification::right);

		}
		else if (rowNumber == GetAssetItemsSize() + 1)
		{
			g.setFont(rowIsSelected ? 32.f : 28.f);
			g.drawText("+", 0, 0, width - 10, height, Justification::right);
		}
		else
		{
			const AssetItem assetItem = GetAssetItem(getIndexOfSorted(rowNumber - 1));
			if (assetsBalances.getValue(assetItem.assetID, "0").getLargeIntValue() > 0)
				g.setColour(Colours::darkgrey);
			else g.setColour(Colours::lightgrey); 

			g.setFont(rowIsSelected ? 18.f : 16.f);
			g.drawText(assetItem.name, 0, 0, width - 10, height, Justification::right);
		}
	}
}

Component* TradeComponent::refreshComponentForCell(int /*rowNumber*/, int /*columnId*/, bool /*isRowSelected*/, Component* /*existingComponentToUpdate*/)
{
	return nullptr;
}

void TradeComponent::cellClicked(int rowNumber, int /*columnId*/, const MouseEvent &e)
{
//	if (e.mods.isRightButtonDown())
//		ShowPopupMenu(rowNumber);
}

void TradeComponent::cellDoubleClicked(int rowNumber, int /*columnId*/, const MouseEvent&)
{
//	ShowPopupMenu(rowNumber);
}

void TradeComponent::backgroundClicked(const MouseEvent &e)
{
//	if (e.mods.isRightButtonDown())
//		ShowPopupMenu(-1);
	table.updateContent();
	repaint();
}

void TradeComponent::sortOrderChanged(int newSortColumnId, bool isForwards)
{
	const ScopedLock lock(tldLock);
	const int s = GetAssetItemsSize();

//	if (s == sortedRowIndex.size() && sortColumnId == newSortColumnId && sortIsForwards == isForwards)
//		return;

	sortColumnId = newSortColumnId;
	sortIsForwards = isForwards;

	sortedRowIndex.clearQuick();
	for (int idx = 0; idx < s; idx++)
		sortedRowIndex.add(idx);
}

int TradeComponent::getIndexWhenSorted(const int idx)
{
	const ScopedLock lock(tldLock);

	const int s = GetAssetItemsSize();
	if (sortedRowIndex.size() != s) // check to update the sort
		sortOrderChanged(sortColumnId, sortIsForwards);

	int r = -1;
	for (int i = 0; i < sortedRowIndex.size(); i++)
	{ // find idx
		if (idx == sortedRowIndex[i])
			r = i;
	}
	return r;
}

int TradeComponent::getIndexOfSorted(const int idx)
{
	const ScopedLock lock(tldLock);

	const int s = GetAssetItemsSize();
	if (sortedRowIndex.size() != s) // check to update the sort
		sortOrderChanged(sortColumnId, sortIsForwards);

	if (idx < sortedRowIndex.size() && idx >= 0)
		return sortedRowIndex[idx];
	else if (idx == sortedRowIndex.size())
		return idx;
	else return -1;
}

String TradeComponent::getCellTooltip(int rowNumber, int columnId)
{
	if (rowNumber == 0)
		return NQT2Burst(GetAssetBalance("0"), String(8)) + " Burstcoin";

	const AssetItem tradeDetails = GetAssetItem(getIndexOfSorted(rowNumber - 1));
	if (tradeDetails.name.isNotEmpty())
	{
		const String balanceStr = NQT2Burst(GetAssetBalance(tradeDetails.assetID), String(tradeDetails.decimals));
		return balanceStr + " " + tradeDetails.name;
	}
	return String::empty;
}

void TradeComponent::selectedRowsChanged(int lastRowSelected)
{
	SetSelectedRow(lastRowSelected);

	//if (lastRowSelected >= getNumRows() - 1)
	//	ClearAssetItems();

	Refresh();
}

void TradeComponent::deleteKeyPressed(int /*lastRowSelected*/)
{
}

void TradeComponent::returnKeyPressed(int /*lastRowSelected*/)
{
}

void TradeComponent::listWasScrolled()
{
}

bool TradeComponent::keyPressed(const KeyPress &/*key*/, Component * /*originatingComponent*/)
{
	return false;
}

bool TradeComponent::keyStateChanged(bool /*isKeyDown*/, Component * /*originatingComponent*/)
{
	return false;
}

void TradeComponent::buttonClicked(Button* buttonThatWasClicked)
{
}

void TradeComponent::sliderValueChanged(Slider* sliderThatWasMoved)
{
}

void TradeComponent::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
}

// --------------------------------------------------------------------------------------------------------
void TradeComponent::SetNode(String server, const bool allowNonSSL)
{
	const ScopedLock lock(burstExtLock);
	burstKit.SetNode(server, allowNonSSL);

	ClearAssetItems();
	Refresh();
}

void TradeComponent::SetSecretPhrase(String pp)
{
	const ScopedLock lock(burstExtLock);
	burstKit.SetSecretPhrase(pp, 0);
	
	tradeInterfaceComponent->SetUserBurstAddress(burstKit.GetAccountRS(), burstKit.GetAccountPublicKey());

	ClearAssetBalances();
	ClearAssetWhiteList();
	ClearAssetItems();

	SetSelectedRow(0);

	table.updateContent();
	repaint();
	UpdateAssetPropeties();

	Refresh();
}

void TradeComponent::SetForceSSL_TSL(const bool forceSSLOn)
{
	const ScopedLock lock(burstExtLock);
	burstKit.SetForceSSL_TSL(forceSSLOn);
}

void TradeComponent::SetNodeHop(const bool hopOn)
{
	const ScopedLock lock(burstExtLock);
	burstKit.EnableNodeHop(hopOn ? 7 : 0);
}

void TradeComponent::GetCurrency(String &key, String &currency)
{
	const ScopedLock lock(tldLock);
	//	key = cmcAPIkey;
	//	currency = currencyType;
}

void TradeComponent::CreateAsset(String name, String description, uint64 quantityQNT, uint64 decimals)
{
	String issueAsset = burstKit.issueAsset(name, description, String(quantityQNT), String(decimals), "100000000000", "1440", true, 0);
	String transactionID = burstKit.GetJSONvalue(issueAsset, "transaction");
	if (transactionID.isNotEmpty())
		NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Success !\nAsset will be created when this transaction is mined !");
	else
	{
		String errorDescription = burstKit.GetJSONvalue(issueAsset, "errorDescription");
		NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "failed ! please try again\n" + errorDescription);
	}
}

String TradeComponent::GetAccountDisplayName(const String account)
{
	if (displayNames.contains(account) == false) // a simple app lifetime cache
	{
		String displayName;

		const String rs = burstKit.convertToReedSolomon(String(account));
		displayName = burstKit.getAccountAliases(rs, true);
		if (displayName.isEmpty())
			displayName = rs;

		displayNames.set(account, displayName);

		return displayName;
	}
	else return displayNames[account];
}

void TradeComponent::ClearAssetWhiteList()
{
	const ScopedLock lock(assetDetailsLock);
	assetIDs.clear();
}

StringArray TradeComponent::GetAssetWhiteList()
{
	const ScopedLock lock(assetDetailsLock);
	return assetIDs;
}

String TradeComponent::GetAssetName(const String assetID)
{
	const ScopedLock lock(assetDetailsLock);

	const int idx = assetIDs.indexOf(assetID);
	if (idx >= 0)
		return assetNames[idx];
	else
	{ // lookup expensive
		String assetStr = burstKit.getAsset(assetID);
		var assetJson;
		Result r = JSON::parse(assetStr, assetJson);

		assetIDs.add(assetID);
		assetNames.add(assetJson["name"].toString());
		assetDescriptions.add(assetJson["description"].toString());
		assetDecimals.add(assetJson["decimals"].toString());

		return assetJson["name"].toString();
	}
}

String TradeComponent::GetAssetDescription(const String assetID)
{
	const ScopedLock lock(assetDetailsLock);

	const int idx = GetAssetIndex(assetID);
	return idx >= 0 ? assetDescriptions[idx] : "0";
}

String TradeComponent::GetAssetDecimals(const String assetID)
{
	const ScopedLock lock(assetDetailsLock);

	const int idx = GetAssetIndex(assetID);
	return idx >= 0 ? assetDecimals[idx] : "0";
}

String TradeComponent::NeatNr(const String balance)
{
	bool minus = balance.startsWithChar('-');
	String neatNr(balance.removeCharacters("-").paddedLeft('0', 9));
	neatNr = (neatNr.substring(0, neatNr.length() - 8) + "." + neatNr.substring(neatNr.length() - 8, neatNr.length()).trimCharactersAtEnd("0"));
	if (neatNr.compare("0.") != 0)
		return minus ? "-" + neatNr : neatNr;
	else return String::empty;
}

void TradeComponent::ShowPopupMenu(int rowNr)
{
	PopupMenu m;
	m.addItem(1, "Copy contact");
	const int result = m.show();

	AssetItem tradeDetails;
	if (rowNr >= 0)
		tradeDetails = GetAssetItem(getIndexOfSorted(rowNr));

	if (result == 1)
	{
		SystemClipboard::copyTextToClipboard(tradeDetails.account_RS);
	}
}

String TradeComponent::ConvertedValue(String balance)
{
	String r;
	if (currency.isEmpty() || currency.compare("BURST") == 0)
	{
		if (balance.length() > 8)
			r = (balance.substring(0, balance.length() - 8) + "." + balance.substring(balance.length() - 8, balance.length()).trimCharactersAtEnd("0") + " BURST");
		else if (balance.length() > 0)
			r = (balance + " NQT");
	}
	else
	{ // market conversion
		double conv = price * (balance.getLargeIntValue() / 100000000.);
		String convertedStr = std::to_string(conv);
		r = convertedStr.upToFirstOccurrenceOf(".", true, true) +
			convertedStr.fromFirstOccurrenceOf(".", false, true).paddedRight('0', 8).substring(0, (conv > 1. ? 2 : 8)) + " " + currency + "/BURST";
	}
	return r;
}

String TradeComponent::NQT2Burst(const String value, const String decimals)
{
	int dec = decimals.getIntValue();
	bool minus = value.startsWithChar('-');
	String neatNr(value.removeCharacters("-").paddedLeft('0', dec + 1));
	neatNr = (neatNr.substring(0, neatNr.length() - dec) + "." + neatNr.substring(neatNr.length() - dec, neatNr.length()).trimCharactersAtEnd("0"));
	return minus ? "-" + neatNr : neatNr;
}

String TradeComponent::Burst2NQT(const String value)
{
	int64 amountNQT = 0;
	String amount = value.trim().retainCharacters("0123456789.,");
	int point = amount.indexOfAnyOf(".,");
	if (point < 0)
		amountNQT = amount.retainCharacters("0123456789").getLargeIntValue() * 100000000L;
	else
	{
		amountNQT = amount.substring(0, point).getLargeIntValue() * 100000000L;
		amountNQT += amount.substring(point + 1, amount.length()).retainCharacters("0123456789").paddedRight('0', 8).substring(0, 8).getLargeIntValue();
	}
	return String(amountNQT);
}

int TradeComponent::GetAssetIndex(const String assetID)
{
	const ScopedLock lock(assetDetailsLock);

	return assetIDs.indexOf(assetID);
}

String TradeComponent::GetAssetBalance(const String assetID)
{
	const ScopedLock lock(assetDetailsLock);
	return assetsBalances[assetID];
}

String TradeComponent::GetOwnedAssetId(const int idx)
{
	const ScopedLock lock(assetDetailsLock);
	return assetsBalances.getAllKeys()[idx];
}

int TradeComponent::GetAssetBalanceSize()
{
	const ScopedLock lock(assetDetailsLock);
	return assetsBalances.size();
}

void TradeComponent::ClearAssetBalances()
{
	const ScopedLock lock(assetDetailsLock);
	assetsBalances.clear();
}

void TradeComponent::SetAssets(const StringArray assetIDs, const StringArray assetsNames, const StringArray assetsDescription, const StringArray assetsDecimals, const StringPairArray assetsBalances)
{
	const ScopedLock lock(assetDetailsLock);

	if (assetIDs.size() > assetIDs.size())
	{ // if we used to have more data than given now. then keep the trailing data. (update the front)
		this->assetIDs.removeRange(0, assetIDs.size());
		StringArray assetIDs_t = assetIDs;
		assetIDs_t.addArray(assetIDs);
		this->assetIDs = assetIDs_t;

		assetNames.removeRange(0, assetsNames.size());
		StringArray assetNames_t = assetsNames;
		assetNames_t.addArray(assetNames);
		assetNames = assetNames_t;

		assetDescriptions.removeRange(0, assetsDescription.size());
		StringArray assetDescription_t = assetsDescription;
		assetDescription_t.addArray(assetDescriptions);
		assetDescriptions = assetDescription_t;

		assetDecimals.removeRange(0, assetsDecimals.size());
		StringArray assetDecimals_t = assetsDecimals;
		assetDecimals_t.addArray(assetDecimals);
		assetDecimals = assetDecimals_t;
	}
	else
	{
		this->assetIDs = assetIDs;
		assetNames = assetsNames;
		assetDescriptions = assetsDescription;
		assetDecimals = assetsDecimals;
	}

	if (this->assetsBalances.size() <= 0) // trigger a refresh once. the first time this function is called
		Refresh();

	this->assetsBalances = assetsBalances;
}

void TradeComponent::timerCallback()
{
	if (isThreadRunning())
		triggerRefresh = true;
	else if (triggerRefresh)
	{
		triggerRefresh = false;

		table.updateContent();
		repaint();
		UpdateAssetPropeties();

		if (table.getSelectedRow(0) < 0)
			table.selectRow(0);
	}
	else if (Time::currentTimeMillis() - lastTreadStartTime > 60 * 1000) // start refresh thread each min
		Refresh();
}

void TradeComponent::Refresh()
{
	lastTreadStartTime = Time::currentTimeMillis();
	startThread(); // trigger data refresh
	triggerRefresh = true;
}

void TradeComponent::PlaceAskOrder(String assetID, uint64 quantityQNT, uint64 priceNQT)
{
	String placeOrderResult = burstKit.placeAskOrder(assetID, String(quantityQNT), String(priceNQT), "standard", "1440", String::empty, false, true, 0);
	String transactionID = burstKit.GetJSONvalue(placeOrderResult, "transaction");
	if (transactionID.isNotEmpty())
	{
		NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Order is being placed, wait for this transaction to be mined.");
		Refresh();
	}
	else
	{
		String errorDescription = burstKit.GetJSONvalue(placeOrderResult, "errorDescription");
		NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "failed ! please try again\n" + errorDescription);
	}
}

void TradeComponent::PlaceBidOrder(String assetID, uint64 quantityQNT, uint64 priceNQT)
{
	String placeOrderResult = burstKit.placeBidOrder(assetID, String(quantityQNT), String(priceNQT), "standard", "1440", String::empty, false, true, 0);
	String transactionID = burstKit.GetJSONvalue(placeOrderResult, "transaction");
	if (transactionID.isNotEmpty())
	{
		NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Order is being placed, wait for this transaction to be mined.");
		Refresh();
	}
	else
	{
		String errorDescription = burstKit.GetJSONvalue(placeOrderResult, "errorDescription");
		NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "failed ! please try again\n" + errorDescription);
	}
}

void TradeComponent::CancelAskOrder(String orderID)
{
	String cancelOrderResult = burstKit.cancelAskOrder(orderID, "standard", "1440", true, 0);
	String transactionID = burstKit.GetJSONvalue(cancelOrderResult, "transaction");
	if (transactionID.isNotEmpty())
	{
		NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Order being canceled, wait for this cancel transaction to be mined !");
		Refresh();
	}
	else
	{
		String errorDescription = burstKit.GetJSONvalue(cancelOrderResult, "errorDescription");
		NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "failed ! please try again\n" + errorDescription);
	}
}

void TradeComponent::CancelBidOrder(String orderID)
{
	String cancelOrderResult = burstKit.cancelBidOrder(orderID, "standard", "1440", true, 0);
	String transactionID = burstKit.GetJSONvalue(cancelOrderResult, "transaction");
	if (transactionID.isNotEmpty())
	{
		NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Order being canceled, wait for this cancel transaction to be mined !");
		Refresh();
	}
	else
	{
		String errorDescription = burstKit.GetJSONvalue(cancelOrderResult, "errorDescription");
		NativeMessageBox::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "failed ! please try again\n" + errorDescription);
	}
}

void TradeComponent::UpdateAssetPropeties()
{
	const int selectedRowIdx = table.getSelectedRow();
	if (selectedRowIdx == 0)
	{
		AssetItem ai;
		ai.assetID = "0";
		ai.balance = GetAssetBalance("0").getLargeIntValue();
		ai.name = "Burstcoin";
		ai.decimals = 8;
		ai.description = "public key: " + burstKit.GetAccountPublicKey();
		ai.quantityQNT = 215881280000000000;
		tradeInterfaceComponentListeners.call(&TradeInterfaceComponentListener::SetAssetData, ai);

		Array<OrderItem> r;
		tradeInterfaceComponentListeners.call(&TradeInterfaceComponentListener::SetBuyOrderItems, r);
		tradeInterfaceComponentListeners.call(&TradeInterfaceComponentListener::SetSellOrderItems, r);
	}
	else if (selectedRowIdx == GetAssetItemsSize() + 1)
	{
		tradeInterfaceComponentListeners.call(&TradeInterfaceComponentListener::NewAsset);
	}
	else if (selectedRowIdx > 0)
	{
		AssetItem ai = GetAssetItem(selectedRowIdx - 1);
		ai.balance = GetAssetBalance(ai.assetID).getLargeIntValue();
		tradeInterfaceComponentListeners.call(&TradeInterfaceComponentListener::SetAssetData, ai);

		tradeInterfaceComponentListeners.call(&TradeInterfaceComponentListener::SetBuyOrderItems, GetBuyOrderItems());
		tradeInterfaceComponentListeners.call(&TradeInterfaceComponentListener::SetSellOrderItems, GetSellOrderItems());
	}

	tradeInterfaceComponentListeners.call(&TradeInterfaceComponentListener::SetAssetBurstNQT, GetAssetBalance("0").getLargeIntValue());
}

int TradeComponent::GetSelectedRow()
{
	const ScopedLock lock(tldLock);
	return selectedAssetRowIdx;
}

void TradeComponent::SetSelectedRow(int idx)
{
	const ScopedLock lock(tldLock);
	selectedAssetRowIdx = idx;
}

// Thread
AssetItem TradeComponent::GetAssetItem(int i)
{
	const ScopedLock lock(tldLock);
	return tableAssetItems[i];
}

int TradeComponent::GetAssetItemsSize()
{
	const ScopedTryLock lock(tldLock);
	return lock.isLocked() ? tableAssetItems.size() : 0;
}

void TradeComponent::SetAssetItems(Array<AssetItem> assetItems)
{
	const ScopedLock lock(tldLock);
	tableAssetItems.swapWith(assetItems);
}

void TradeComponent::ClearAssetItems()
{
	const ScopedLock lock(tldLock);
	tableAssetItems.clear();
}

void TradeComponent::SetPrice(String currency, double price)
{
	const ScopedLock lock(tldLock);
	this->currency = currency;
	this->price = price;
}

void TradeComponent::GetPrice(String &currency, double &price)
{
	const ScopedLock lock(tldLock);
	currency = this->currency;
	price = this->price;
}

void TradeComponent::SetBuyOrderItems(Array<OrderItem> orderItems)
{
	const ScopedLock lock(tldLock);
	assetBuyOrderItems.swapWith(orderItems);
}

void TradeComponent::ClearBuyOrderItems()
{
	const ScopedLock lock(tldLock);
	assetBuyOrderItems.clear();
}

Array<OrderItem> TradeComponent::GetBuyOrderItems()
{
	const ScopedLock lock(tldLock);
	return assetBuyOrderItems;
}

void TradeComponent::SetSellOrderItems(Array<OrderItem> orderItems)
{
	const ScopedLock lock(tldLock);
	assetSellOrderItems.swapWith(orderItems);
}

void TradeComponent::ClearSellOrderItems()
{
	const ScopedLock lock(tldLock);
	assetSellOrderItems.clear();
}

Array<OrderItem> TradeComponent::GetSellOrderItems()
{
	const ScopedLock lock(tldLock);
	return assetSellOrderItems;
}

void TradeComponent::run()
{
	StringArray assetIds = GetAssetWhiteList(); // add the assetIds that user owns, but maybe has no active trade
	assetIds.removeDuplicates(true);

	int range = 100;
	// the selected asset will show the current sell and buy price.
	// find orderbook of current asset. to be used to find the matching buy/sell price for a direct market order fullfillment	
	// get all assets to list them in the table
	int totalOwnedAsset = GetAssetBalanceSize();
	StringArray whitelistedAssets = StringArray::fromTokens(getAppProperties().getUserSettings()->getValue("AssetWhitelist"), ",", "");

	if (GetAssetItemsSize() <= whitelistedAssets.size() + (totalOwnedAsset - 1))
	{ // add whitelisted assets
		Array<AssetItem> assetItems;
		for (int oai = 0; oai < whitelistedAssets.size() + (totalOwnedAsset - 1); oai++)
		{
			String ownedAssetID;
			if (oai < whitelistedAssets.size())
				ownedAssetID = whitelistedAssets[oai];				
			else if (whitelistedAssets.contains(GetOwnedAssetId(1 + oai - whitelistedAssets.size())) == false)
				ownedAssetID = GetOwnedAssetId(1 + oai - whitelistedAssets.size());
			
			String assetStr;
			if (assetMap.contains(ownedAssetID) == false)
				assetStr = burstKit.getAsset(ownedAssetID);
			else assetStr = assetMap[ownedAssetID];
			assetMap.set(ownedAssetID, assetStr);

			var assetJSON;
			if (JSON::parse(assetStr, assetJSON).wasOk() && !threadShouldExit())
			{
				AssetItem assetItem;
				assetItem.assetID = assetJSON["asset"].toString();
				assetItem.account_RS = assetJSON["accountRS"].toString();
				assetItem.account_ID = assetJSON["account"].toString();

				assetItem.name = assetJSON["name"].toString();
				assetItem.description = assetJSON["description"].toString();

				assetItem.decimals = assetJSON["decimals"].toString().getLargeIntValue();
				assetItem.quantityQNT = assetJSON["quantityQNT"].toString().getLargeIntValue();

				assetItem.numberOfTrades = assetJSON["numberOfTrades"].toString().getLargeIntValue();
				assetItem.numberOfTransfers = assetJSON["numberOfTransfers"].toString().getLargeIntValue();
				assetItem.numberOfAccounts = assetJSON["numberOfAccounts"].toString().getLargeIntValue();

				assetItem.balance = GetAssetBalance(assetItem.assetID).getLargeIntValue();
				
				if (assetItem.assetID.getLargeIntValue() > 0)
					assetItems.add(assetItem);
			}
		}

		if (!threadShouldExit())
		{
			assetItems.sort();
			SetAssetItems(assetItems);
			sortOrderChanged(sortColumnId, sortIsForwards);
		}
	}


	// update orders for current selected asset	
	int selectedRow = GetSelectedRow();
	String selected_id = (selectedRow - 1 >= 0) ? GetAssetItem(selectedRow - 1).assetID : String::empty;
	Array<OrderItem> askOrderItems;
	Array<OrderItem> bidOrderItems;
	StringArray cancelledOrderIds;
	{
		String unconfirmedTransactionsStr = burstKit.getUnconfirmedTransactions();
		var unconfirmedTransactionsJSON;
		if (JSON::parse(unconfirmedTransactionsStr, unconfirmedTransactionsJSON).wasOk() && !threadShouldExit())
		{
			var unconfirmedTransactionsArray = unconfirmedTransactionsJSON.getProperty("unconfirmedTransactions", String::empty);
			if (unconfirmedTransactionsArray.isArray())
			{
				for (int i = 0; i < unconfirmedTransactionsArray.size() && !threadShouldExit(); i++)
				{
					int type = unconfirmedTransactionsArray[i]["type"].toString().getIntValue();
					int subtype = unconfirmedTransactionsArray[i]["subtype"].toString().getIntValue();
					if (type == 2)
					{
						if (subtype == 2) // ask placement
						{
							OrderItem orderItem;
							orderItem.orderID;
							orderItem.assetID = unconfirmedTransactionsArray[i]["attachment"]["asset"].toString();
							if (orderItem.assetID.compare(selected_id) == 0)
							{
								orderItem.account = unconfirmedTransactionsArray[i]["sender"].toString();
								orderItem.accountRS = unconfirmedTransactionsArray[i]["senderRS"].toString();
								orderItem.quantityQNT = unconfirmedTransactionsArray[i]["attachment"]["quantityQNT"].toString().getLargeIntValue();
								orderItem.priceNQT = unconfirmedTransactionsArray[i]["attachment"]["priceNQT"].toString().getLargeIntValue();
								orderItem.height = unconfirmedTransactionsArray[i]["height"].toString().getLargeIntValue();
								orderItem.type = "ask";
								orderItem.cancelled = false;

								bidOrderItems.add(orderItem);
							}
						}
						if (subtype == 3) // bid placement
						{
							OrderItem orderItem;
							orderItem.orderID;
							orderItem.assetID = unconfirmedTransactionsArray[i]["attachment"]["asset"].toString();
							if (orderItem.assetID.compare(selected_id) == 0)
							{
								orderItem.account = unconfirmedTransactionsArray[i]["sender"].toString();
								orderItem.accountRS = unconfirmedTransactionsArray[i]["senderRS"].toString();
								orderItem.quantityQNT = unconfirmedTransactionsArray[i]["attachment"]["quantityQNT"].toString().getLargeIntValue();
								orderItem.priceNQT = unconfirmedTransactionsArray[i]["attachment"]["priceNQT"].toString().getLargeIntValue();
								orderItem.height = unconfirmedTransactionsArray[i]["height"].toString().getLargeIntValue();
								orderItem.type = "bid";
								orderItem.cancelled = false;

								askOrderItems.add(orderItem);
							}
						}
						if (subtype == 4 || subtype == 5) // cancel order tx
						{
							String cancelledOrderId = unconfirmedTransactionsArray[i]["attachment"]["order"].toString();
							if (cancelledOrderId.isNotEmpty())
							{
								cancelledOrderIds.add(cancelledOrderId);
							}
						}
					}
				}
			}
		}
	}


	{
		int pos = 0;
		int numOrderItems = -1;
		if (selectedRow - 1 >= 0)
		{
			int foundItems = 0;
			while (numOrderItems != askOrderItems.size() && foundItems % range == 0 && !threadShouldExit())
			{
				numOrderItems = askOrderItems.size();

				const String firstIndex(pos); // is a zero - based index to the first order to retrieve(optional)
				const String lastIndex(pos + range - 1); // is a zero - based index to the last order to retrieve(optional)
				String allOrdersStr = burstKit.getBidOrders(selected_id, firstIndex, lastIndex);
				var allOrdersJSON;

				if (JSON::parse(allOrdersStr, allOrdersJSON).wasOk() && !threadShouldExit())
				{
					var ordersArray = allOrdersJSON.getProperty("bidOrders", String::empty);
					if (ordersArray.isArray())
					{
						for (int i = 0; i < ordersArray.size() && !threadShouldExit(); i++)
						{
							OrderItem orderItem;
							orderItem.orderID = ordersArray[i]["order"].toString();
							orderItem.assetID = ordersArray[i]["asset"].toString();
							orderItem.account = ordersArray[i]["account"].toString();
							orderItem.accountRS = ordersArray[i]["accountRS"].toString();
							orderItem.quantityQNT = ordersArray[i]["quantityQNT"].toString().getLargeIntValue();
							orderItem.priceNQT = ordersArray[i]["priceNQT"].toString().getLargeIntValue();
							orderItem.height = ordersArray[i]["height"].toString().getLargeIntValue();
							orderItem.type = ordersArray[i]["type"].toString();
							orderItem.cancelled = cancelledOrderIds.contains(orderItem.orderID);

							askOrderItems.add(orderItem);
						}
						foundItems += ordersArray.size();
						pos += ordersArray.size();
					}
				}
			}
		}
		SetSellOrderItems(askOrderItems);
	}
	{
		int pos = 0;
		int numOrderItems = -1;
		if (selectedRow - 1 >= 0)
		{
			int foundItems = 0;
			while (numOrderItems != bidOrderItems.size() && foundItems % range == 0 && !threadShouldExit())
			{
				numOrderItems = bidOrderItems.size();

				const String firstIndex(pos); // is a zero - based index to the first order to retrieve(optional)
				const String lastIndex(pos + range - 1); // is a zero - based index to the last order to retrieve(optional)
				String allOrdersStr = burstKit.getAskOrders(selected_id, firstIndex, lastIndex);
				var allOrdersJSON;

				if (JSON::parse(allOrdersStr, allOrdersJSON).wasOk() && !threadShouldExit())
				{
					var ordersArray = allOrdersJSON.getProperty("askOrders", String::empty);
					if (ordersArray.isArray())
					{
						for (int i = 0; i < ordersArray.size() && !threadShouldExit(); i++)
						{
							OrderItem orderItem;
							orderItem.orderID = ordersArray[i]["order"].toString();
							orderItem.assetID = ordersArray[i]["asset"].toString();
							orderItem.account = ordersArray[i]["account"].toString();
							orderItem.accountRS = ordersArray[i]["accountRS"].toString();
							orderItem.quantityQNT = ordersArray[i]["quantityQNT"].toString().getLargeIntValue();
							orderItem.priceNQT = ordersArray[i]["priceNQT"].toString().getLargeIntValue();
							orderItem.height = ordersArray[i]["height"].toString().getLargeIntValue();
							orderItem.type = ordersArray[i]["type"].toString();
							orderItem.cancelled = cancelledOrderIds.contains(orderItem.orderID);

							bidOrderItems.add(orderItem);
						}
						foundItems += ordersArray.size();
						pos += ordersArray.size();
					}
				}
			}
		}
		SetBuyOrderItems(bidOrderItems);
	}
}

