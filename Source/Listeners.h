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
	virtual void MakeCoupon(couponArgs args) {};
	virtual void SendHotWalletLicense(const String recipient) {};

	virtual void GetAccountDisplayName(const uint64, const String, String &) {};
	//virtual void UpdateBalance(String &) {};
	
	virtual void CreateWallet() {};
	virtual void SavePassPhraseWithNewPIN(const String) {};
	virtual void SavePassPhrase(String passphrase, String pin) {};
	virtual void LoadPassPhrase() {};
	virtual void UnloadPassPhrase() {};
	virtual void LoadPassPhraseReturn(String pin) {};

	virtual void WalletPubKeyToClipboard(const int index) {};
	virtual void SetCMCkey(const String key) {};
	virtual void SetCurrencyType(const String currency) {};
	virtual void SetPrice(String currency, double price) {};
#if ALLOW_EXT_REQ == 1
	virtual void OpenHttpSocket(const String host_address, const int port, bool &ok) {};
	virtual void CloseHttpSocket() {};
#endif
	virtual void Broke(const bool show, const String pubKey_b64, const bool isPro) {};
};

class SettingsListener
{
public:
	SettingsListener() {};
	virtual ~SettingsListener() {};

	virtual void SetNode(const String) {};
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

	virtual void ShowSecureAccount(const bool show, const String pubKey_b64, const bool isPro) {};
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
};

class TransactionsComponentListener
{
public:
	TransactionsComponentListener() {};
	virtual ~TransactionsComponentListener() {};
	virtual void SetNode(const String) {};
	virtual void SetSecretPhrase(const String) {};
	virtual void SetForceSSL_TSL(const bool forceSSLOn) {};
	virtual void SetNodeHop(const bool hopOn) {};
	virtual void Refresh() {};

	virtual void SetCMCkey(const String key) {};
	virtual void SetCurrencyType(const String currency) {};

	virtual void ResetPriceTimer() {};
};

class BalanceComponentListener
{
public:
	BalanceComponentListener() {};
	virtual ~BalanceComponentListener() {};
	virtual void SetNode(const String) {};
	virtual void SetSecretPhrase(const String) {};
	virtual void SetForceSSL_TSL(const bool forceSSLOn) {};
	virtual void SetNodeHop(const bool hopOn) {};
	virtual void UpdateBalance() {};
	virtual void SetPrice(String currency, double price) {};
};

class ShoutComponentListener
{
public:
	ShoutComponentListener() {};
	virtual ~ShoutComponentListener() {};
	virtual void SetNode(const String) {};
	virtual void SetForceSSL_TSL(const bool forceSSLOn) {};
	virtual void SetNodeHop(const bool hopOn) {};
};

class HttpServerListener
{
public:
	HttpServerListener() {};
	virtual ~HttpServerListener() {};
};

#endif //__LISTENERS__