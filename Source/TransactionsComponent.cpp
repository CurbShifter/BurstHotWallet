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
#include "TransactionsComponent.h"
#include <string>

//==============================================================================
TransactionsComponent::TransactionsComponent() : Thread("Transactions")
{
	cachedTimestamp = 0;
	
	table.getHeader().addColumn("time", 1, 50, 100, -1, TableHeaderComponent::visible | TableHeaderComponent::resizable | TableHeaderComponent::appearsOnColumnMenu | TableHeaderComponent::sortable);
	table.getHeader().addColumn("contact", 2, 50, 100, -1, TableHeaderComponent::visible | TableHeaderComponent::resizable | TableHeaderComponent::appearsOnColumnMenu | TableHeaderComponent::sortable);
	table.getHeader().addColumn("amount", 3, 70, 150, -1, TableHeaderComponent::visible | TableHeaderComponent::resizable | TableHeaderComponent::appearsOnColumnMenu | TableHeaderComponent::sortable);
	table.getHeader().addColumn("fee", 4, 30, 70, -1, TableHeaderComponent::visible | TableHeaderComponent::resizable | TableHeaderComponent::appearsOnColumnMenu | TableHeaderComponent::sortable);
	table.getHeader().addColumn("details", 5, 50, 100, -1, TableHeaderComponent::visible | TableHeaderComponent::resizable | TableHeaderComponent::appearsOnColumnMenu | TableHeaderComponent::sortable);

	table.setHeaderHeight(30);
	table.setRowHeight(30);

	table.setModel(this);
	table.addKeyListener(this);
	table.setMultipleSelectionEnabled(true);
	table.getVerticalScrollBar()->setAutoHide(false);
	table.setColour(TableListBox::ColourIds::backgroundColourId, Colour(0xfffcfcfc));

	table.getHeader().setSortColumnId(1, false);

	addAndMakeVisible(table);

	table.autoSizeAllColumns();
	triggerRefresh = false;

	autoRefreshCounter = 0;
	sortColumnId = 1;
	sortIsForwards = false;
	sortOrderChanged(sortColumnId, sortIsForwards);

	latestCMCtimestamp = (Time::currentTimeMillis() / 1000) - 120;

	startTimer(2000);
}

TransactionsComponent::~TransactionsComponent()
{
	stopTimer();
	stopThread(20000);

	txlog = nullptr;
}

void TransactionsComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);   // clear the background
	/*
    g.setColour (Colours::grey);
	g.drawRect(getLocalBounds(), 30);   // draw an outline around the component

	//	if (isThreadRunning())
	{
		g.setColour(Colours::black);
		g.drawText("Loading...", Rectangle<int>(0, 0, getWidth(), getHeight()), Justification::centred, false);
	}
	*/
}

void TransactionsComponent::resized()
{
	table.setBoundsInset(BorderSize<int>(0, 0, 1, 0));
	table.autoSizeColumn(1);
}

void TransactionsComponent::SetNode(String server, const bool allowNonSSL)
{
	const ScopedLock lock(burstExtLock);
	burstKit.SetNode(server, allowNonSSL);
}

void TransactionsComponent::SetSecretPhrase(String pp)
{
	const ScopedLock lock(burstExtLock);
	burstKit.SetSecretPhrase(pp, 0);

	const File logFileToWriteTo(File::getSpecialLocation(File::SpecialLocationType::userDocumentsDirectory).getChildFile(ProjectInfo::projectName).getChildFile(burstKit.GetAccountRS()).withFileExtension("txlog"));
	if (logFileToWriteTo.getFullPathName().isNotEmpty())
	{
		txlog = nullptr; // delete any previous on account switch
		txlog = new FileLogger(logFileToWriteTo, "", (1000 * 1000) * 100);
	}
}

void TransactionsComponent::SetForceSSL_TSL(const bool forceSSLOn)
{
	const ScopedLock lock(burstExtLock);
	burstKit.SetForceSSL_TSL(forceSSLOn);
}

void TransactionsComponent::SetNodeHop(const bool hopOn)
{
	const ScopedLock lock(burstExtLock);
	burstKit.EnableNodeHop(hopOn ? 7 : 0);
}

void TransactionsComponent::ResetPriceTimer()
{
	latestCMCtimestamp = (Time::currentTimeMillis() / 1000) - 120;
}

void TransactionsComponent::SetCMCkey(const String key)
{
	const ScopedLock lock(tldLock);
	cmcAPIkey = key;
}

void TransactionsComponent::SetCurrencyType(const String currency)
{
	const ScopedLock lock(tldLock);
	currencyType = currency;
}

void TransactionsComponent::GetCurrency(String &key, String &currency)
{
	const ScopedLock lock(tldLock);
	key = cmcAPIkey;
	currency = currencyType;
}

void TransactionsComponent::Refresh()
{
	ResetPriceTimer();
	startThread(); // trigger tx refresh
}

int TransactionsComponent::getNumRows()
{
	return jmax<int>(1, GetCacheSize());
}

void TransactionsComponent::paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool /*rowIsSelected*/)
{
	
	if (GetCacheSize() > rowNumber)
	{
		const TransactionsComponent::txDetails txd = GetCache(getIndexOfSorted(rowNumber));
		int64 blockHeight = jmax<int64>(numberOfBlocks - txd.value[col::height].toString().getLargeIntValue(), 0);
		float neededConfirmations = 10.f;
		if (blockHeight > neededConfirmations)
		{
			g.fillAll(Colours::white);
			g.setGradientFill(ColourGradient(Colours::white, 0, height / 4, Colours::whitesmoke.withAlpha(0.5f), 0, height, false));
			g.fillAll();
		}
		else g.fillAll(Colours::white.darker((1.f - (blockHeight / neededConfirmations)) * 0.3f));

		if (table.isRowSelected(rowNumber))
		{
			g.fillAll(Colours::lightblue.withAlpha(0.5f));
		}
	}
	else if (isThreadRunning())
	{
		g.fillAll(Colours::lightgrey.withAlpha(0.5f));
		g.setColour(Colours::black);
		g.drawText("Loading...", Rectangle<int>(10, 2, width-10, height-2), Justification::left, false);
	}
}

void TransactionsComponent::paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool /*rowIsSelected*/)
{
	if (GetCacheSize() <= rowNumber)
		return;

	g.setColour(Colours::black);
	const TransactionsComponent::txDetails txd = GetCache(getIndexOfSorted(rowNumber));
	String txt = txd.value[columnId - 1].toString();
	if(columnId == 1)
	{
		g.setFont(13.5f);
		String timeStr = Time((txt.getLargeIntValue() + BURSTCOIN_GENESIS_EPOCH) * 1000).toString(true, true, false, true);
		g.drawText(timeStr, 0, 0, width, height, Justification::right);
	}
	else if (columnId == 2)
	{
		g.setFont(14.f);
		if (txt.startsWith("BURST-2222-2222-2222-22222"))
		{
			txd.value[columnId - 1];

			g.drawText("sub type TX", 0, 0, width, height, Justification::centred);
		}
		else if (txt.startsWith("BURST-"))
			g.drawText(txt.substring(6), 0, 0, width, height, Justification::centred);
		else
		{
			if (txt.containsChar(';'))
			{
				StringArray sa = StringArray::fromTokens(txt, ";", "");
				if (sa.size() > 0)
					g.drawText(sa[0], 0, 0, width, height, Justification::centred);
			}
			else g.drawText(txt, 0, 0, width, height, Justification::centred);
		}
	}
	else if(columnId == 3)
	{
		String prefixMain = (txt.startsWith("-")) ? "" : "+";
		String prefix = (txt.startsWith("-")) ? "-" : "+";
		if (txt.startsWith("-"))
		{
			prefixMain = "";
			prefix = "-";
			g.setColour(Colours::darkred);
		}
		else
		{
			prefixMain = "+";
			prefix = "+";
			g.setColour(Colours::darkgreen);
		}

		g.setFont(18.f);
		const String amountStr = txt.getDoubleValue() != 0. ? prefixMain + NeatNr(txt) + " BURST" : String::empty;
		String assetStr;
		if (txd.value[col::asset].toString().isNotEmpty())
		{
			const String name = GetAssetName(txd.value[col::asset].toString());
			const String quantityNQT = txd.value[col::assetQuantityQNT].toString();
			const String decimals = GetAssetDecimals(txd.value[col::asset].toString()); //txd.value[col::assetDecimals].toString();
			double amountDbl = (quantityNQT.getDoubleValue() / pow(10., decimals.getLargeIntValue()));
			String amountStr = String::formatted("%." + String(decimals.getLargeIntValue()) + "f", amountDbl);
			assetStr = (amountStr.isNotEmpty() ? " " : "") + prefix + amountStr + " " + name;
		}
		g.drawText(amountStr + assetStr, 0, 0, width, height, Justification::left);
	}
	else if(columnId == 4)
	{
		g.setFont(12.f);
		g.drawText(NeatNr(txt), 0, 0, width, height, Justification::left);
	}
	else
	{
		g.setFont(16.f);
		g.drawText(txt, 0, 0, width, height, Justification::left);
	}
}

Component* TransactionsComponent::refreshComponentForCell(int /*rowNumber*/, int /*columnId*/, bool /*isRowSelected*/, Component* /*existingComponentToUpdate*/)
{
	return nullptr;
}

void TransactionsComponent::cellClicked(int rowNumber, int /*columnId*/, const MouseEvent &e)
{
	if (e.mods.isRightButtonDown())
	{
		ShowPopupMenu(rowNumber);
	}
}

void TransactionsComponent::cellDoubleClicked(int rowNumber, int /*columnId*/, const MouseEvent&)
{
	ShowPopupMenu(rowNumber);
}

void TransactionsComponent::backgroundClicked(const MouseEvent &e)
{
	if (e.mods.isRightButtonDown())
	{
		ShowPopupMenu(-1);
	}
}

void TransactionsComponent::sortOrderChanged(int newSortColumnId, bool isForwards)
{
	const ScopedLock lock(tldLock);
	const int s = txDetailArray.size();// GetCacheSize();

	if (s == sortedRowIndex.size() && sortColumnId == newSortColumnId && sortIsForwards == isForwards)
		return;

	sortColumnId = newSortColumnId;
	sortIsForwards = isForwards;

	Array<TransactionsComponent::txDetails> arr = txDetailArray;
	sortedRowIndex.clearQuick();
	for (int idx = 0; idx < s; idx++)
	{
		sortedRowIndex.add(idx);
	}
	for (int baseidx = 0; baseidx < s; baseidx++)
	{
		for (int idx = 0; idx < s - 1; idx++)
		{
			const TransactionsComponent::txDetails txd1 = arr[idx];
			const TransactionsComponent::txDetails txd2 = arr[idx + 1];

			const String str1 = txd1.value[newSortColumnId-1].toString();
			const String str2 = txd2.value[newSortColumnId-1].toString();
			bool isBigger = false;
			bool isSmaller = false;
			if (newSortColumnId == 1)
			{// time
				isBigger = str1.getLargeIntValue() > str2.getLargeIntValue();
				isSmaller = str1.getLargeIntValue() < str2.getLargeIntValue();
			}
			else if (newSortColumnId == 2)
			{// address
				isBigger = str1.compare(str2) > 0;
				isSmaller = str1.compare(str2) < 0;
			}
			else if (newSortColumnId == 3)
			{// amount
				isBigger = str1.getLargeIntValue() > str2.getLargeIntValue();
				isSmaller = str1.getLargeIntValue() < str2.getLargeIntValue();
			}
			else if (newSortColumnId == 4)
			{// fee
				isBigger = str1.getLargeIntValue() > str2.getLargeIntValue();
				isSmaller = str1.getLargeIntValue() < str2.getLargeIntValue();
			}
			else if (newSortColumnId == 5)
			{// message
				isBigger = str1.compare(str2) > 0;
				isSmaller = str1.compare(str2) < 0;
			}

			if ((isForwards && isBigger) ||
				(!isForwards && isSmaller))
			{
				arr.move(idx, idx + 1);
				sortedRowIndex.move(idx, idx + 1);
			}
		}
	}
}

int TransactionsComponent::getIndexWhenSorted(const int idx)
{
	const ScopedLock lock(tldLock);

	const int s = txDetailArray.size();// GetCacheSize();
	if (sortedRowIndex.size() != s) // check to update the sort
		sortOrderChanged(sortColumnId, sortIsForwards);

	int r = -1;
	for (int i = 0; i < sortedRowIndex.size(); i++)
	{ // find idx
		if (idx == sortedRowIndex[i])
			r = i;
	}
/*	if (r == -1)
	{
		sortOrderChanged(sortColumnId, sortIsForwards);
		return -1;
	}*/
	return r;
}

int TransactionsComponent::getIndexOfSorted(const int idx)
{
	const ScopedLock lock(tldLock);

	const int s = txDetailArray.size();// GetCacheSize();
	if (sortedRowIndex.size() != s) // check to update the sort
		sortOrderChanged(sortColumnId, sortIsForwards);

	if (idx < sortedRowIndex.size() && idx >= 0)
		return sortedRowIndex[idx];
	else if (idx == sortedRowIndex.size())
		return idx;
	else {
	//	sortOrderChanged(sortColumnId, sortIsForwards);
		return -1;
	}
}

int TransactionsComponent::getColumnAutoSizeWidth(int columnId)
{
	switch (columnId)
	{
	case 1: return 90; break;
	case 2: return 180; break;
	case 3: return 80; break;
	case 4: return 65; break;
	case 5: return 350; break;
	default: return 100; break;
	}
}

String TransactionsComponent::getCellTooltip(int rowNumber, int columnId)
{
	if (columnId == 5 || columnId == 3 || columnId == 4)
	{
		const TransactionsComponent::txDetails txd = GetCache(getIndexOfSorted(rowNumber));
		const String txt = txd.value[columnId - 1].toString();
		
		if (columnId == 5)
			return txt;		
		else if ((columnId == 3 || columnId == 4) && (currency.isNotEmpty() && currency.compare("BURST") != 0))
		{
			const String txt2 = NeatNr(txt);
			return txt2.isNotEmpty() ? txt2 + " BURST\n" + ConvertedValue(txt) : String::empty;
		}
	}
	return String::empty;
}

void TransactionsComponent::selectedRowsChanged(int /*lastRowSelected*/)
{
}

void TransactionsComponent::deleteKeyPressed(int /*lastRowSelected*/)
{
}

void TransactionsComponent::returnKeyPressed(int /*lastRowSelected*/)
{
}

void TransactionsComponent::listWasScrolled()
{
}

bool TransactionsComponent::keyPressed(const KeyPress &/*key*/, Component * /*originatingComponent*/)
{
	return false;
}

bool TransactionsComponent::keyStateChanged(bool /*isKeyDown*/, Component * /*originatingComponent*/)
{
	return false;
}


void TransactionsComponent::timerCallback()
{
	if (isThreadRunning())
	{
		triggerRefresh = true;
		table.updateContent();
		repaint();
	}
	else if (triggerRefresh)
	{
		triggerRefresh = false;
		table.updateContent();
		repaint();
	}

	if (autoRefreshCounter++ > ((1 * 60 * 1000) / jmax<int>(1, Timer::getTimerInterval())))
	{
		autoRefreshCounter = 0;
		Refresh();
	}

	
	String currency_read;
	double price_read = 0.;
	GetPrice(currency_read, price_read);
	if (currency_read.compare(currency_cache) != 0 || price_read != price_cache)
	{
		currency_cache = currency_read;
		price_cache = price_read;
		listeners.call(&InterfaceListener::SetPrice, currency_cache, price_cache);
	}
}

// Thread
TransactionsComponent::txDetails TransactionsComponent::GetCache(int i)
{
	const ScopedLock lock(tldLock);
	return txDetailArray[i];
}

int TransactionsComponent::GetCacheSize()
{
	const ScopedTryLock lock(tldLock);
	return lock.isLocked() ? txDetailArray.size() : 0;
}

void TransactionsComponent::SetPrice(String currency, double price)
{
	const ScopedLock lock(tldLock);
	this->currency = currency;
	this->price = price;
}

void TransactionsComponent::GetPrice(String &currency, double &price)
{
	const ScopedLock lock(tldLock);
	currency = this->currency;
	price = this->price;
}

void TransactionsComponent::SetCache(Array<TransactionsComponent::txDetails> txds)
{
	const ScopedLock lock(tldLock);
	if (txds.size() >= txDetailArray.size())
		txDetailArray.swapWith(txds);
}

void TransactionsComponent::ClearCache()
{
	const ScopedLock lock(tldLock);
	txDetailArray.clear();
}

void TransactionsComponent::run()
{ 
	// coinpaprika / coinmarketcap
	if (!threadShouldExit())
	{
		String cmcAPIkey_t;
		String currencyType;
		GetCurrency(cmcAPIkey_t, currencyType);
		int64 timestampLimit = (Time::currentTimeMillis() / 1000) - 60;
		if ((timestampLimit > latestCMCtimestamp || currentCurrencyType.compare(currencyType) != 0)) // once a minute max
		{
			if (cmcAPIkey_t.isNotEmpty())
			{ // cmc
				if (currencyType.compare("BURST") != 0)
				{
					String cmcURLstr("https://pro-api.coinmarketcap.com/v1/cryptocurrency/quotes/latest?id=573&convert=" + currencyType + "&CMC_PRO_API_KEY=" + cmcAPIkey_t);
					URL cmcURL(cmcURLstr);

					const String cmcOutput = cmcURL.readEntireTextStream();
					String price = cmcOutput.fromFirstOccurrenceOf("\"quote\"", false, true).fromFirstOccurrenceOf("\"price\":", false, true).upToFirstOccurrenceOf(",", false, true).trim(); // "price": 0.0000010425304733232973,
					
					SetPrice(currencyType, price.getDoubleValue());
				}
				else SetPrice(currencyType, 1.);
			}
			else
			{ // coin paprika
				if (currencyType.compare("BURST") != 0 && currencyType.isNotEmpty())
				{
					String cpURLstr("https://api.coinpaprika.com/v1/coins/BURST-BURST/markets?quotes=" + currencyType);
					URL cpURL(cpURLstr);

					double price_final = 0.;
					const String cpOutput = cpURL.readEntireTextStream();
					var cpOutputJSON;
					if (JSON::parse(cpOutput, cpOutputJSON).wasOk())
					{
						if (cpOutputJSON.isArray())
						{
							Array<double> prices;
							for (int i = 0; i < cpOutputJSON.size(); i++)
							{
								const var item = cpOutputJSON[i];
								{
									double price_exchange = item["quotes"][currencyType.toUTF8()]["price"];

									if (price_final == 0. ||
										price_exchange < price_final)
										price_final = price_exchange;
																		
									prices.add(price_exchange);
								}
							}

							prices.sort();
							if (prices.size() > 1) // use the middle price as truth. as some quotes are way too low of high
								price_final = prices[prices.size() / 2];
							
							if (price_final > 0.)
								SetPrice(currencyType, price_final);
						}
					}
				}
				else SetPrice(currencyType, 1.);
			}
			currentCurrencyType = currencyType;
		}
	}

	// refresh the tx list
	int64 calculatedBalance = 0;
	Array<String> knownTx;
	Array<TransactionsComponent::txDetails> txds;
	if (txlog && txlog->getLogFile().existsAsFile() && !threadShouldExit())
	{ // load cache
		StringArray lines;
		txlog->getLogFile().readLines(lines);
		for (int i = lines.size() - 1; i >= 0 && !threadShouldExit(); i--)
		{
			var cacheRowJSON;
			const String line = lines[i];
			if (line.isNotEmpty() && line.startsWithChar('{') && line.endsWithChar('}') && line.contains("Calculated balance change") == false)
			{
				juce::Result r = JSON::parse(lines[i], cacheRowJSON);
				if (r.wasOk())
				{
					const ScopedLock lock(burstExtLock);
					txDetails txDetail = FillTxStruct(line);
					if (knownTx.contains(txDetail.value[col::transaction].toString()) == false && txDetail.value[col::time].toString().isNotEmpty())
					{
						const String amountNQTstr = txDetail.value[col::amount].toString();
						bool minus = amountNQTstr.startsWithChar('-');
						int64 amountNQT = amountNQTstr.getLargeIntValue();
						calculatedBalance += amountNQT;
						if (minus)
						{
							int64 feeNQT = txDetail.value[col::fee].toString().getLargeIntValue();
							calculatedBalance -= feeNQT;
						}

						txds.add(txDetail);
						knownTx.add(txDetail.value[col::transaction].toString()); // save tx id
						SetCache(txds);
					}
				}
			}
		}
	}

	String timestamp; // is the earliest block(in seconds since the genesis block) to retrieve(optional) 
	if (cachedTimestamp > 0)
		timestamp = String(cachedTimestamp);
	
	String accountTransactionIds;
	{
		const ScopedLock lock(burstExtLock);

		if (!threadShouldExit())
		{ // set current numberOfBlocks
			String state = burstKit.getState("true");
			var stateJSON;
			juce::Result r = JSON::parse(state, stateJSON);
			if (r.wasOk())
				numberOfBlocks = stateJSON.getProperty("numberOfBlocks", String::empty).toString().getLargeIntValue();
		}
		accountTransactionIds = burstKit.getAccountTransactionIds(burstKit.GetAccountRS(), timestamp, String::empty, String::empty, String::empty, String::empty, String::empty, true);
	}

	var accountTransactionIdsJSON;
	juce::Result r = JSON::parse(accountTransactionIds, accountTransactionIdsJSON);
	var transactionIdsJSON = accountTransactionIdsJSON.getProperty("transactionIds", String::empty);
	if (transactionIdsJSON.isArray() && !threadShouldExit())
	{
		for (int i = 0; i < transactionIdsJSON.size(); i++)
		{
			const String txid = transactionIdsJSON[i];
			if (knownTx.contains(txid) == false)
			{
				// add some anti spamzors delay
				String txIdDetails;
				txDetails txd;
				{
					const ScopedLock lock(burstExtLock);
					txIdDetails = burstKit.getTransaction(txid);
					txd = FillTxStruct(txIdDetails);
				}
				txds.add(txd);
				SetCache(txds);

				cachedTimestamp = jmax<int>(cachedTimestamp, txd.value[col::time].toString().getLargeIntValue() - 1);

				const String amountNQTstr = txd.value[col::amount].toString();
				bool minus = amountNQTstr.startsWithChar('-');
				int64 amountNQT = amountNQTstr.getLargeIntValue();
				calculatedBalance += amountNQT;
				if (minus)
				{
					int64 feeNQT = txd.value[col::fee].toString().getLargeIntValue();
					calculatedBalance -= feeNQT;
				}
				
				int64 calcConfirmations = jmax<int64>(numberOfBlocks - txd.value[col::height].toString().getLargeIntValue(), 0);
				float neededConfirmations = 10.f;
				if (calcConfirmations > neededConfirmations) // needs enough confirmations to be logged
					txlog->logMessage(txIdDetails);
			}
		}
	}

	{
		const ScopedLock lock(burstExtLock);

		const String myAccountID = burstKit.GetAccountID();
		const String balanceStr = burstKit.getBalance(myAccountID);
		const String balanceNQTStr = burstKit.GetJSONvalue(balanceStr, "balanceNQT");
		const int64 balanceNQT = balanceNQTStr.getLargeIntValue();

		if (balanceNQT > calculatedBalance && !threadShouldExit())
		{
			// difference in balance is probably due to multiouts
			// create a dummy tx with balance diff
			const String txIdDetails = "{\"senderPublicKey\":\"\",\"signature\":\"\",\"feeNQT\":\"\",\"type\":0,\"confirmations\":0,\"fullHash\":\"\",\"version\":1,\"signatureHash\":\"\",\"attachment\":{\"version.Message\":1,\"messageIsText\":true,\"message\":\"Calculated balance change, Multi out(s)\"},\"senderRS\":\"\",\"subtype\":0,\"amountNQT\":\"" +
				String(balanceNQT - calculatedBalance) +
				"\",\"recipient\":\"" +
				myAccountID +
				"\",\"ecBlockHeight\":0,\"block\":\"\",\"blockTimestamp\":0,\"deadline\":0,\"transaction\":\"\",\"timestamp\":" +
				String((Time::currentTimeMillis() / 1000) - BURSTCOIN_GENESIS_EPOCH) +
				",\"height\":" + String(numberOfBlocks) + "}";
			txDetails txd = FillTxStruct(txIdDetails);

			txds.add(txd);
			SetCache(txds);
			//	txlog->logMessage(txIdDetails); // dont log these. not needed since BRS 2.3.1
		}

		const String accountID = burstKit.GetAccountID();
		const String unconfirmedTransactionIdsStr = burstKit.getUnconfirmedTransactionsIds(accountID);
		var unconfirmedTransactionIdsJSON;
		juce::Result r2 = JSON::parse(unconfirmedTransactionIdsStr, unconfirmedTransactionIdsJSON);
		if (r2.wasOk() && !threadShouldExit())
		{
			var unconfirmedTransactionIdsArray = unconfirmedTransactionIdsJSON.getProperty("unconfirmedTransactionIds", String::empty);
			if (unconfirmedTransactionIdsArray.isArray())
			{
				for (int i = 0; i < unconfirmedTransactionIdsArray.size() && !threadShouldExit(); i++)
				{
					const String txid = unconfirmedTransactionIdsArray[i];
					txDetails txd;
					if (txMap.contains(txid) == false)
					{
						const String txIdDetails = burstKit.getTransaction(txid);
						if (txMap.size() > 0xFFFF)
							txMap.clear();
						txMap.set(txid, txIdDetails);
						txd = FillTxStruct(txIdDetails);
					}
					else txd = FillTxStruct(txMap[txid]);

					if (txd.value[col::time].toString().getLargeIntValue() > 0)
						txds.add(txd);
				}
			}
		}
	}

	if (!threadShouldExit())
	{
		SetCache(txds);
		sortOrderChanged(sortColumnId, sortIsForwards);
	}
}

String TransactionsComponent::GetAccountDisplayName(const String account)
{	
	if (displayNames.contains(account) == false) // a simple app lifetime cache
	{
		String displayName;
		
		const String rs = burstKit.ensureAccountRS(String(account));
		displayName = burstKit.getAccountAliases(rs, true);
		if (displayName.isEmpty())
			displayName = rs;

		displayNames.set(account, displayName);

		return displayName;
	}
	else return displayNames[account];
}

TransactionsComponent::txDetails TransactionsComponent::FillTxStruct(String txDetailsStr)
{
	txDetails txDetail;
	var txIdDetailsJSON;
	juce::Result r = JSON::parse(txDetailsStr, txIdDetailsJSON);
	if (r.wasOk())
	{
		const String accountID = burstKit.GetAccountID();
		const String senderID = txIdDetailsJSON["sender"];
		const String recipientID = txIdDetailsJSON["recipient"];

		if (accountID.compare(senderID) == 0 || accountID.compare(recipientID) == 0 || recipientID.isEmpty()) // filter out tx not to or from this account. or empty recipientID if multiout receive
		{
			txDetail.value[col::time] = txIdDetailsJSON["timestamp"].toString();
			{
				String account;
				if (accountID.compare(senderID) != 0)
					account = (senderID);
				else account = (recipientID);

				txDetail.value[col::contact] = GetAccountDisplayName(account);
			}

			if (senderID.compare(recipientID) != 0) // tx not send to self
				txDetail.value[col::amount] = (accountID.compare(senderID) != 0 ? "" : "-") + (txIdDetailsJSON["amountNQT"].toString());
			else txDetail.value[col::amount] = "0";

			txDetail.value[col::fee] = (txIdDetailsJSON["feeNQT"]);

			txDetail.value[col::confirmations] = txIdDetailsJSON["confirmations"];
			txDetail.value[col::transaction] = txIdDetailsJSON["transaction"];
			txDetail.value[col::block] = txIdDetailsJSON["block"];
			txDetail.value[col::blockTimestamp] = txIdDetailsJSON["blockTimestamp"];
			txDetail.value[col::height] = txIdDetailsJSON["height"];
			txDetail.value[col::type] = txIdDetailsJSON["type"];
			txDetail.value[col::subtype] = txIdDetailsJSON["subtype"];
			
			txDetail.value[col::asset] = ""; // asset id (default burst 0)

			const var attachment = txIdDetailsJSON["attachment"];
			String messageData;
			if ((int)(attachment["version.EncryptedMessage"]) == 1)
			{
				const String data(attachment["encryptedMessage"]["data"].toString()); // is the AES-encrypted data
				const String nonce(attachment["encryptedMessage"]["nonce"].toString()); // is the unique nonce associated with the encrypted data
				if ((bool)attachment["encryptedMessage"]["isText"] == true)
					txDetail.value[col::details] = burstKit.decryptFrom(txIdDetailsJSON["senderRS"], data, nonce, "true");
			}
			else if ((int)(attachment["version.Message"]) == 1)
			{
				if (attachment["messageIsText"])
					txDetail.value[col::details] = attachment["message"];
				else
				{ // check if the data can be interpreted as utf8 text (AT limitation can't set messageIsText)
					MemoryBlock m;
					m.loadFromHexString(attachment["message"].toString() + "00"); // assume we need a extra zero termination
					if (m.toString().isNotEmpty())
						txDetail.value[col::details] = m.toString();
					else txDetail.value[col::details] = attachment["message"].toString();
				}
			}
			messageData = txDetail.value[col::details].toString();
			if (messageData.isNotEmpty())
				messageData = ", " + messageData; // prepend spacing
			
			if ((int)(attachment["version.PublicKeyAnnouncement"]) == 1)
			{
				if (messageData.isNotEmpty())
				{
					txDetail.value[col::details] = txDetail.value[col::details].toString() + ", Public Key Announcement: " + attachment["recipientPublicKey"].toString();
					messageData = ", " + messageData + ", Public Key Announcement: " + attachment["recipientPublicKey"].toString();
				}
				else
				{
					txDetail.value[col::details] = "Public Key Announcement: " + attachment["recipientPublicKey"].toString();
					messageData = ", Public Key Announcement: " + attachment["recipientPublicKey"].toString();
				}
				
			}

			// these attachments could include a message too. so no 'else if' here
			if ((int)(attachment["version.AliasAssignment"]) == 1)
			{
				txDetail.value[col::contact] = "Alias assignment";
				txDetail.value[col::details] = attachment["alias"].toString() + messageData;
			}
			else if ((int)(attachment["version.AccountInfo"]) == 1)
			{
				txDetail.value[col::contact] = "Account info update";
				txDetail.value[col::details] = (attachment["name"].toString().isNotEmpty() ? attachment["name"].toString() + ", " : "") + attachment["description"].toString() + messageData;
			}
			else if ((int)(attachment["version.MultiOutCreation"]) == 1)
			{
				if (attachment["recipients"] && attachment["recipients"].isArray())
				{
					String msg;
					for (int itt = 0; itt < attachment["recipients"].size(); itt++)
					{
						msg += GetAccountDisplayName(attachment["recipients"][itt][0].toString()) + ":" + 
							NQT2Burst(attachment["recipients"][itt][1].toString()) + " BURST ";

						if (senderID.compare(accountID) != 0 && attachment["recipients"][itt][0].toString().compare(accountID) == 0) // incoming multiout
							txDetail.value[col::amount] = attachment["recipients"][itt][1].toString(); // we founf the incoming amount. override the total amount
					}
					txDetail.value[col::details] = "MultiOut " + msg + messageData;
				}
			}
			else if ((int)(attachment["version.RewardRecipientAssignment"]) == 1)
			{
				txDetail.value[col::contact] = "Reward Recipient Assignment";
				txDetail.value[col::details] = txIdDetailsJSON["recipientRS"].toString() + messageData;
			}
			else if ((int)(attachment["version.AssetIssuance"]) == 1)
			{
				txDetail.value[col::contact] = "Asset Issuance";
				txDetail.value[col::details] = attachment["name"].toString() + messageData;
			}
			else if ((int)(attachment["version.AssetTransfer"]) == 1)
			{//"type":2,"subtype":1
				txDetail.value[col::asset] = attachment["asset"].toString();
				txDetail.value[col::assetQuantityQNT] = attachment["quantityQNT"];
			}
			else if ((int)(attachment["version.AskOrderPlacement"]) == 1)
			{//"type":2,"subtype":2
				txDetail.value[col::contact] = "Ask Order";

				txDetail.value[col::asset] = attachment["asset"].toString();
				txDetail.value[col::assetQuantityQNT] = attachment["quantityQNT"];
				txDetail.value[col::assetPriceNQT] = attachment["priceNQT"];
			}
			else if ((int)(attachment["version.BidOrderPlacement"]) == 1)
			{//"type":2,"subtype":3
				txDetail.value[col::contact] = "Bid Order";

				txDetail.value[col::asset] = attachment["asset"].toString();
				txDetail.value[col::assetQuantityQNT] = attachment["quantityQNT"];
				txDetail.value[col::assetPriceNQT] = attachment["priceNQT"];
			}
		}
	}
	return txDetail;
}

String TransactionsComponent::GetAssetName(const String assetID)
{
	/*	StringArray assetWhitelistDescription;
	StringPairArray assetsBalances;
	*/
	const int idx = GetAssetIndex(assetID);
	if (idx >= 0)
		return assetWhitelistNames[idx];
	else
	{ // lookup expensive
		String assetStr = burstKit.getAsset(assetID);
		var assetJson;
		Result r = JSON::parse(assetStr, assetJson);

		assetWhitelist.add(assetID);
		assetWhitelistNames.add(assetJson["name"].toString());
		assetWhitelistDescription.add(assetJson["description"].toString());
		assetWhitelistDecimals.add(assetJson["decimals"].toString());

		return assetJson["name"].toString();
	}	
}

String TransactionsComponent::GetAssetDecimals(const String assetID)
{
	const int idx = GetAssetIndex(assetID);
	return idx >= 0 ? assetWhitelistDecimals[idx] : "0";
}

String TransactionsComponent::NeatNr(const String balance)
{
	bool minus = balance.startsWithChar('-');
	String neatNr(balance.removeCharacters("-").paddedLeft('0', 9));
	neatNr = (neatNr.substring(0, neatNr.length() - 8) + "." + neatNr.substring(neatNr.length() - 8, neatNr.length()).trimCharactersAtEnd("0"));
	if (neatNr.compare("0.") != 0)
		return minus ? "-" + neatNr : neatNr;
	else return String::empty;
}

void TransactionsComponent::ShowPopupMenu(int rowNr)
{
	PopupMenu m;
	m.addItem(1, "Copy contact");
	m.addItem(2, "Copy amount");
	m.addItem(3, "Copy fee");
	m.addItem(4, "Copy message");
	m.addItem(6, "Open on explorer.burstcoin.network");
	m.addItem(5, "Export CSV file (all transactions)");
	const int result = m.show();
	
	TransactionsComponent::txDetails txd;
	if (rowNr >= 0)
		txd = GetCache(getIndexOfSorted(rowNr));

	if (result == 1)
	{
		String txt = txd.value[col::contact].toString();
		if (txt.startsWith("BURST-2222-2222-2222-22222"))
			txt = ("no recipient");
		else if (txt.startsWith("BURST-"))
			txt = txt;
		SystemClipboard::copyTextToClipboard(txt);
	}
	if (result == 2)
	{
		String txt = txd.value[col::amount].toString();
		if (txt.containsChar(';'))
		{
			StringArray sa = StringArray::fromTokens(txt, ";", "");
			if (sa.size() > 0)
				txt = sa[0];
		}
		txt = (NeatNr(txt));
		SystemClipboard::copyTextToClipboard(txt);
	}
	if (result == 3)
	{
		String txt = txd.value[col::fee].toString();
		txt = (NeatNr(txt));
		SystemClipboard::copyTextToClipboard(txt);
	}
	if (result == 4)
	{
		String txt = txd.value[col::details].toString();
		SystemClipboard::copyTextToClipboard(txt);
	}
	if (result == 5)
	{
		ExportCSV();
	}
	if (result == 6)
	{
		URL url("https://explorer.burstcoin.network/?action=transaction&id=" + txd.value[col::transaction].toString());
		url.launchInDefaultBrowser();
	}
}

void TransactionsComponent::ExportCSV()
{
	FileChooser myChooser("Select the save location for the CSV file...", File::getSpecialLocation(File::userDesktopDirectory), "*.csv");
	if (myChooser.browseForFileToSave(true))
	{
		File f = myChooser.getResult().withFileExtension("csv");
		f.deleteFile();
		f.appendText("\"timestamp\",\"contact\",\"amount\",\"fee\",\"message\",\"confirmations\",\"transaction\",\"block\",\"blockTimestamp\",\"height\",\"type\",\n");

		for (int i = 0; i < GetCacheSize(); i++)
		{
			const TransactionsComponent::txDetails txd = GetCache(getIndexOfSorted(i));
			for (int columnId = 1; columnId <= 11; columnId++)
			{
			/*	String txt = txd.value[columnId - 1].toString();
				if (columnId == 1)
				{
					txt = Time((txt.getLargeIntValue() + BURSTCOIN_GENESIS_EPOCH) * 1000).toString(true, true, false, true);
				}
				else if (columnId == 2)
				{
					if (txt.startsWith("BURST-2222-2222-2222-22222"))
						txt = ("sub type TX");
					else if (txt.startsWith("BURST-"))
						txt = txt.substring(6);
				}
				else if (columnId == 3)
				{
					txt = NeatNr(txt);
				}
				else if (columnId == 4)
				{
					txt = (NeatNr(txt));
				}
				else if (columnId == 6)
				{
					txt = String(jmax<int64>(numberOfBlocks - txd.value[col::height].toString().getLargeIntValue(), 0));
				}*/
				String txt = txd.value[columnId - 1].toString();
				if (columnId == 1)
				{
					String timeStr = Time((txt.getLargeIntValue() + BURSTCOIN_GENESIS_EPOCH) * 1000).toString(true, true, false, true);
					txt = timeStr;
				}
				else if (columnId == 2)
				{
					if (txt.startsWith("BURST-2222-2222-2222-22222"))
						txt = ("sub type TX");
					else if (txt.startsWith("BURST-"))
						txt = (txt.substring(6));
					else
					{
						if (txt.containsChar(';'))
						{
							StringArray sa = StringArray::fromTokens(txt, ";", "");
							txt = (sa[0]);
						}
						else txt = (txt);
					}
				}
				else if (columnId == 3)
				{
					String prefixMain = (txt.startsWith("-")) ? "" : "+";
					String prefix = (txt.startsWith("-")) ? "-" : "+";
					if (txt.startsWith("-"))
					{
						prefixMain = "";
						prefix = "-";
					}
					else
					{
						prefixMain = "+";
						prefix = "+";
					}

					const String amountStr = txt.getDoubleValue() != 0. ? prefixMain + NeatNr(txt) + " BURST" : String::empty;
					String assetStr;
					if (txd.value[col::asset].toString().isNotEmpty())
					{
						const String name = GetAssetName(txd.value[col::asset].toString());
						const String quantityNQT = txd.value[col::assetQuantityQNT].toString();
						const String decimals = GetAssetDecimals(txd.value[col::asset].toString()); //txd.value[col::assetDecimals].toString();
						double amountDbl = (quantityNQT.getDoubleValue() / pow(10., decimals.getLargeIntValue()));
						String amountStr = String::formatted("%." + String(decimals.getLargeIntValue()) + "f", amountDbl);
						assetStr = (amountStr.isNotEmpty() ? " " : "") + prefix + amountStr + " " + name;
					}
					txt = (amountStr + assetStr);
				}
				f.appendText("\"" + txt + "\",");
			}
			f.appendText("\n");
		}
		if (myChooser.getResult().withFileExtension("csv").existsAsFile())
			NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "CSV File saved !\n" + f.getFullPathName());
		else NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Failed to create CSV file !\n" + f.getFullPathName());
	}
}

String TransactionsComponent::ConvertedValue(String balance)
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
		//String convertedStr = String(conv, (conv > 1. ? 2 : 8));
		String convertedStr = std::to_string(conv);
		r =
			convertedStr.upToFirstOccurrenceOf(".", true, true) +
			convertedStr.fromFirstOccurrenceOf(".", false, true).paddedRight('0', 8).substring(0, (conv > 1. ? 2 : 8)) + " " + currency + "/BURST";
	}

	return r;
}

String TransactionsComponent::NQT2Burst(const String value)
{
	bool minus = value.startsWithChar('-');
	String neatNr(value.removeCharacters("-").paddedLeft('0', 9));
	neatNr = (neatNr.substring(0, neatNr.length() - 8) + "." + neatNr.substring(neatNr.length() - 8, neatNr.length()).trimCharactersAtEnd("0"));
	return minus ? "-" + neatNr : neatNr;
}

String TransactionsComponent::Burst2NQT(const String value)
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

int TransactionsComponent::GetAssetIndex(const String assetID)
{
	return assetWhitelist.indexOf(assetID);
}

void TransactionsComponent::SetAssets(const StringArray assetIDs, const StringArray assetsNames, const StringArray assetsDescription, const StringArray assetsDecimals, const StringPairArray assetsBalances)
{
	if (assetWhitelist.size() > assetIDs.size())
	{ // if we used to have more data than given now. then keep the trailing data. (update the front)
		assetWhitelist.removeRange(0, assetIDs.size());
		StringArray assetIDs_t = assetIDs;
		assetIDs_t.addArray(assetWhitelist);
		assetWhitelist = assetIDs_t;

		assetWhitelistNames.removeRange(0, assetsNames.size());
		StringArray assetNames_t = assetsNames;
		assetNames_t.addArray(assetWhitelistNames);
		assetWhitelistNames = assetNames_t;

		assetWhitelistDescription.removeRange(0, assetsDescription.size());
		StringArray assetDescription_t = assetsDescription;
		assetDescription_t.addArray(assetWhitelistDescription);
		assetWhitelistDescription = assetDescription_t;

		assetWhitelistDecimals.removeRange(0, assetsDecimals.size());
		StringArray assetDecimals_t = assetsDecimals;
		assetDecimals_t.addArray(assetWhitelistDecimals);
		assetWhitelistDecimals = assetDecimals_t;
	}
	else
	{
		assetWhitelist = assetIDs;
		assetWhitelistNames = assetsNames;
		assetWhitelistDescription = assetsDescription;
		assetWhitelistDecimals = assetsDecimals;
	}
	this->assetsBalances = assetsBalances;
}




/*
// depending on CIP18 maybe implement this:
void SearchMultiouts()
{
	{
		String statusStr = burstKit.getBlockchainStatus();
		var statusJSON;
		juce::Result r = JSON::parse(statusStr, statusJSON);
		String numberOfBlocksStr = statusJSON.getProperty("numberOfBlocks", String::empty);
		int startBlockHeight = numberOfBlocksStr.getIntValue();

		// find multi outs, till the first tx timestamp of this account. or the highest cache timestamp. max hf2 height
		// no way around it this will put a heavier load on the node
		for (int i = startBlockHeight; i < endBlockHeight; i++)
		{
			// request each block back up to cachedTimestamp
			// filter out tx with multiout as type
			// scan the multi out for this account number
			// save the tx in the array
			String blockStr = burstKit.getBlock("", String(i), "", "true");
			if (blockStr.contains(myAccountID) == 0 && (blockStr.contains("version.Multi")))
			{ // probably contains a multi out for this account
				var blockJSON;
				juce::Result r = JSON::parse(blockStr, blockJSON);
				var transactions = statusJSON.getProperty("transactions", String::empty);
				if (transactionIdsJSON.isArray())
				{
				//stuff todo
				}
			}
		}
	}
	// get unconfirmed tx
	// when storing cache. leave tx with low confirmation numbers out. to recheck next time (in case of forkage)
}
*/
