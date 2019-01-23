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
	InterfaceListener() {};
	virtual ~InterfaceListener() {};
	virtual void GetAppValue(const String, String &) {};
	virtual void SetAppValue(const String, const String) {};

	virtual void SetupTransaction(const String requestHeader, const String recipient, const String amount, const String fee, const String msg, const bool /*encrypted*/) {};
	virtual void SendBurstcoin(const String recipient, const String amount, const String fee, const String msg, const bool /*encrypted*/) {};
	virtual void GetAccountDisplayName(const uint64, const String, String &) {};
	virtual void UpdateBalance(String &) {};
	
	virtual void SavePassPhraseWithNewPIN(const String) {};
	virtual void SavePassPhrase(String passphrase, String pin) {};
	virtual void LoadPassPhrase() {};
	virtual void UnloadPassPhrase() {};
	virtual void LoadPassPhraseReturn(String pin) {};

	virtual void SetCMCkey(const String key) {};
	virtual void SetCurrencyType(const String currency) {};
	virtual void SetPrice(String currency, String price) {};
#if ALLOW_EXT_REQ == 1
	virtual void OpenHttpSocket(const String host_address, const int port, bool &ok) {};
	virtual void CloseHttpSocket() {};
#endif
};

class SettingsListener
{
public:
	SettingsListener() {};
	virtual ~SettingsListener() {};

	virtual void SetSecretPhrase(const String) {};
	virtual void SetBurstRS(const String) {};
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

class SendComponentListener
{
public:
	SendComponentListener() {};
	virtual ~SendComponentListener() {};
	virtual void SetupTransaction(const String requestHeader, const String recipient, const String amount, const String fee, const String msg, const bool /*encrypted*/) {};
	virtual void SetRecipients(StringArray recipients) {};
	virtual void SetAmounts(StringArray amounts) {};
	virtual void SetSuggestedFees(uint64 /*cheap*/, uint64 /*normal*/, uint64 /*priority*/) {};
	virtual void SetPrice(String currency, String price) {};
};

class TransactionsComponentListener
{
public:
	TransactionsComponentListener() {};
	virtual ~TransactionsComponentListener() {};
	virtual void SetNode(const String) {};
	virtual void SetSecretPhrase(const String) {};
	virtual void Refresh() {};

	virtual void SetCMCkey(const String key) {};
	virtual void SetCurrencyType(const String currency) {};
};

#endif //__LISTENERS__