/*
Copyright (C) 2018  CurbShifter

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
*/

#ifndef __LISTENERS__
#define __LISTENERS__

#include "JuceHeader.h"
#include "BurstExt.h"
#include "BurstSocket.h"

struct OrderItem
{
	OrderItem() :
		priceNQT(0),
		quantityQNT(0),
		height(0),
		cancelled(false)
	{};

	bool operator< (const OrderItem& other) const noexcept
	{
		return (priceNQT > other.priceNQT) || (priceNQT == other.priceNQT && quantityQNT > other.quantityQNT);
	};

	String assetID;
	String orderID;
	String account;
	String accountRS;
	String type;
	uint64 quantityQNT;
	uint64 priceNQT;
	uint64 height;
	bool cancelled;
};

struct AssetItem
{
	AssetItem() :
		decimals(0),
		quantityQNT(0),
		numberOfTrades(0),
		numberOfTransfers(0),
		numberOfAccounts(0),
		balance(0)
	{};

	bool operator< (const AssetItem& other) const noexcept
	{
		return (((double)balance / (double)quantityQNT) > ((double)other.balance / (double)other.quantityQNT)) || 
		(balance == other.balance && (numberOfAccounts * (numberOfTrades + numberOfTransfers)) > (other.numberOfAccounts * (other.numberOfTrades + other.numberOfTransfers)));
	};

	String assetID;

	String name;
	String account_RS;
	String account_ID;
	String description;

	uint64 balance;
	uint64 decimals;
	uint64 quantityQNT;

	uint64 numberOfTrades;
	uint64 numberOfTransfers;
	uint64 numberOfAccounts;
};



class InterfaceListener
{
public:
	struct couponArgs
	{
		String recipient;
		String amountNQT;
		String feeNQT;
		String deadline;
		String msg;
		String password;
		bool encrypted;
	};

	InterfaceListener() {};
	virtual ~InterfaceListener() {};
	virtual void GetAppValue(const String, String &) {};
	virtual void SetAppValue(const String, const String) {};

	virtual void SetForceSSL_TSL(const bool forceSSLOn) {};
	virtual void SetNodeHop(const bool hopOn) {};

	virtual void SetupTransaction(const String requestHeader, const String recipient, const String amount, const String fee, const String msg, const bool /*encrypted*/) {};
	virtual void SendBurstcoin(const String recipient, const String amount, const String fee, const String msg, const bool /*encrypted*/) {};
	virtual void SendAsset(const String recipient, const String assetID, const String amountNQT, const String feeNQT, const String msg, const bool encrypted) {};
	virtual void MakeCoupon(couponArgs args) {};
	virtual void SendHotWalletLicense(const String recipient) {};

	virtual void GetAccountDisplayName(const uint64, const String, String &) {};
	//virtual void UpdateBalance(String &) {};

	virtual void CreateWallet() {};
	virtual void RemoveWallet() {};
	virtual void SavePassPhraseWithNewPIN(const String) {};
	virtual void SavePassPhrase(String passphrase, String pin, String address) {};
	virtual void LoadPassPhrase() {};
	virtual void UnloadPassPhrase() {};
	virtual void LoadPassPhraseReturn(String pin) {};

	virtual void GetAccountNames(StringArray &addresses) {};
	virtual void GetAccountAddresses(StringArray &addresses) {};
	virtual void GetAccountIndex(int &index) {};
	virtual void SetAccountIndex(const int index) {};

	virtual void WalletPubKeyToClipboard(const int index) {};
	virtual void SetCMCkey(const String key) {};
	virtual void SetCurrencyType(const String currency) {};
	virtual void SetPrice(String currency, double price) {};
#if ALLOW_EXT_REQ == 1
	virtual void OpenHttpSocket(const String host_address, const int port, bool &ok) {};
	virtual void CloseHttpSocket() {};
#endif
	virtual void Broke(const bool show, const String addressRS, const String pubKey_b64, const bool isPro) {};
	virtual void SetAssetsBalances(const StringPairArray assetsBalances) {};

	virtual void SystemTrayNotify(const String message, const String tooltip, const bool highlight) {};
};

class SettingsListener
{
public:
	SettingsListener() {};
	virtual ~SettingsListener() {};

	virtual void SetNode(const String, const bool) {};
	virtual void SetSecretPhrase(const String) {};
	virtual void SetForceSSL_TSL(const bool forceSSLOn) {};
	virtual void SetNodeHop(const bool hopOn) {};

	virtual void EnableControls(const bool) {};
	virtual void CreateWallet() {};
	virtual void NewWallet() {};
	virtual void ExportWallet() {};
	virtual void ImportWallet() {};

	virtual void SetCMCkey(const String key) {};
	virtual void SetCurrencyType(const String currency) {};
};

class PinComponentListener
{
public:
	PinComponentListener() {};
	virtual ~PinComponentListener() {};
};

class HistoryComponentListener
{
public:
	HistoryComponentListener() {};
	virtual ~HistoryComponentListener() {};

	virtual void ShowSecureAccount(const bool show, const String addressRS, const String pubKey_b64, const bool isPro) {};
};

class SendComponentListener
{
public:
	SendComponentListener() {};
	virtual ~SendComponentListener() {};
	virtual void SetupTransaction(const String requestHeader, const String recipient, const String amount, const String fee, const String msg, const bool /*encrypted*/) {};
	virtual void SetRecipients(StringArray recipients) {};
	virtual void SetAmounts(StringArray amounts) {};
	virtual void SetSuggestedFees(uint64 /*cheap*/, uint64 /*normal*/, uint64 /*priority*/) {};
	virtual void SetPrice(String currency, double price) {};
	virtual void SetAssets(const StringArray assetIDs, const StringArray assetsNames, const StringArray assetsDescription, const StringArray assetsDecimals, const StringPairArray assetsBalances) {};
};

class TransactionsComponentListener
{
public:
	TransactionsComponentListener() {};
	virtual ~TransactionsComponentListener() {};
	virtual void SetNode(const String, const bool) {};
	virtual void SetSecretPhrase(const String) {};
	virtual void SetForceSSL_TSL(const bool forceSSLOn) {};
	virtual void SetNodeHop(const bool hopOn) {};
	virtual void Refresh() {};

	virtual void SetCMCkey(const String key) {};
	virtual void SetCurrencyType(const String currency) {};

	virtual void ResetPriceTimer() {};
	virtual void SetAssets(const StringArray assetIDs, const StringArray assetsNames, const StringArray assetsDescription, const StringArray assetsDecimals, const StringPairArray assetsBalances) {};
};

class TradeComponentListener
{
public:
	TradeComponentListener() {};
	virtual ~TradeComponentListener() {};

	virtual void SetNode(const String, const bool) {};
	virtual void SetSecretPhrase(const String) {};
	virtual void SetForceSSL_TSL(const bool forceSSLOn) {};
	virtual void SetNodeHop(const bool hopOn) {};
	virtual void SetAssets(const StringArray assetIDs, const StringArray assetsNames, const StringArray assetsDescription, const StringArray assetsDecimals, const StringPairArray assetsBalances) {};
	virtual void Refresh() {};
	virtual void CancelAskOrder(String orderID) {};
	virtual void CancelBidOrder(String orderID) {};
	virtual void PlaceAskOrder(String orderID, uint64 quantityQNT, uint64 priceNQT) {};
	virtual void PlaceBidOrder(String assetID, uint64 quantityQNT, uint64 priceNQT) {};
	virtual void CreateAsset(String name, String description, uint64 quantityQNT, uint64 decimals) {};
};

class BalanceComponentListener
{
public:
	BalanceComponentListener() {};
	virtual ~BalanceComponentListener() {};
	virtual void SetNode(const String, const bool) {};
	virtual void SetSecretPhrase(const String) {};
	virtual void SetForceSSL_TSL(const bool forceSSLOn) {};
	virtual void SetNodeHop(const bool hopOn) {};
	virtual void UpdateBalance() {};
	virtual void InitAccountSelection(const int index) {};
	
	virtual void SetPrice(String currency, double price) {};
	virtual void AddAssetWhitelist(const StringArray assetIDs) {};
};

class TradeInterfaceComponentListener
{
public:
	TradeInterfaceComponentListener() {};
	virtual ~TradeInterfaceComponentListener() {};

	virtual void NewAsset() {};
	virtual void SetAssetData(const AssetItem asset) {};
	virtual void SetRecommendedSellAndBuyPrice(const String buyPrice, const String sellPrice) {};
	virtual void SetBuyOrderItems(Array<OrderItem> buyOrders) {};
	virtual void SetSellOrderItems(Array<OrderItem> sellOrders) {};
	virtual void SetOrder(OrderItem orders) {};
	virtual void CancelAskOrder(String orderID) {};
	virtual void CancelBidOrder(String orderID) {};

	virtual void SetAssetBurstNQT(const uint64 balance) {};
};

class ShoutComponentListener
{
public:
	ShoutComponentListener() {};
	virtual ~ShoutComponentListener() {};
	virtual void SetNode(const String, const bool) {};
	virtual void SetForceSSL_TSL(const bool forceSSLOn) {};
	virtual void SetNodeHop(const bool hopOn) {};
};

class HttpServerListener
{
public:
	HttpServerListener() {};
	virtual ~HttpServerListener() {};
};


class ChatComponentListener
{
public:
	ChatComponentListener() {};
	virtual ~ChatComponentListener() {};

	virtual void SetNode(const String, const bool) {};
	virtual void SetSecretPhrase(const String) {};
	virtual void SetForceSSL_TSL(const bool forceSSLOn) {};
	virtual void SetNodeHop(const bool hopOn) {};
	virtual void SetAssetsBalances(const StringPairArray assetsBalances) {};

	virtual void SocketSendMessage(const String, const String, const bool) {};
	virtual void SocketSendFile(const String, const File, const bool) {};
	virtual void SaveFileStream(File, MemoryBlock) {};
	virtual void NotifyTab(uint64 recipientID, uint64 senderID, bool isPriv, String msg) {};
	virtual void ActivateTab(const int index, const bool forceShow) {};

	virtual void NewTab(const String, bool, bool) {};
	virtual void RemoveTab(uint64 recipientID, bool isPriv) {};

	virtual void OpenCloseSocket(const bool open) {};

	virtual void GetHoldSize(int &holdMultiplier) {};
	virtual void SetHoldSize(const int newHoldMultiplier) {};

	virtual void SetForceBlock(const bool stayOnline) {};
};

class MessageListListener
{
public:
	MessageListListener() {};
	virtual ~MessageListListener() {};

	virtual void AddMessage(BurstSocket::BurstSocketThread::txPacketIn) {};
};

class ChatBoxListener
{
public:
	ChatBoxListener() {};
	virtual ~ChatBoxListener() {};

	virtual void SetMaxETx(int) {};
	virtual void PrimeResize(bool &) {};
	virtual void ScrollToBottom(int) {};
};

class MenuListener
{
public:
	MenuListener() {};
	virtual ~MenuListener() {};

	virtual void ActivateTab(const int, const bool) {};
	virtual void AddTab(const String &, uint64, uint64, String, bool, const int, const bool) {};
	virtual void RemoveTab(const int) {};
	virtual void SetIsOnline(const bool) {};
	virtual void SetStatusText(const String, const double) {};
	virtual void NotifyTab(uint64, uint64, bool, String) {};
	virtual void ReloadChannelItems() {};
	virtual void SetAccountRS(const String, const String pubkey) {};
};


#endif //__LISTENERS__