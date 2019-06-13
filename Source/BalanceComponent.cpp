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

//[Headers] You can add your own extra header files here...
#include <string>
//[/Headers]

#include "BalanceComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
BalanceComponent::BalanceComponent ()
    : Thread("ShoutComponent")
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (balanceLabel = new Label ("balanceLabel",
                                                 TRANS("EMPTY WALLET")));
    balanceLabel->setTooltip (TRANS("balance"));
    balanceLabel->setFont (Font (18.00f, Font::plain));
    balanceLabel->setJustificationType (Justification::topRight);
    balanceLabel->setEditable (false, false, false);
    balanceLabel->setColour (Label::textColourId, Colours::white);
    balanceLabel->setColour (TextEditor::textColourId, Colours::black);
    balanceLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (accountButton = new TextButton ("accountButton"));
    accountButton->setTooltip (TRANS("show account options"));
    accountButton->setButtonText (TRANS("BURST-XXXX-XXXX-XXXX-XXXXX"));
    accountButton->addListener (this);
    accountButton->setColour (TextButton::buttonColourId, Colour (0x0077b517));
    accountButton->setColour (TextButton::buttonOnColourId, Colour (0xff77b517));
    accountButton->setColour (TextButton::textColourOffId, Colours::white);


    //[UserPreSize]
	updated = false;
	balanceLabel->setFont(Font(22.00f, Font::plain));
	//[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	isPro = false;
	timerDelay = -5;

	startTimer(1000);
    //[/Constructor]
}

BalanceComponent::~BalanceComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	stopThread(5000);
    //[/Destructor_pre]

    balanceLabel = nullptr;
    accountButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void BalanceComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void BalanceComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    /*
    //[/UserPreResize]

    balanceLabel->setBounds (155, 45, 152, 24);
    accountButton->setBounds (27, 13, 272, 24);
    //[UserResized] Add your own custom resize handling here..
	*/
	accountButton->setBounds(getBounds().withZeroOrigin().withHeight(getHeight() / 2).reduced(3));
	balanceLabel->setBounds(accountButton->getBounds().withY(getHeight() / 2));
    //[/UserResized]
}

void BalanceComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == accountButton)
    {
        //[UserButtonCode_accountButton] -- add your button handler code here..
		ScopedPointer<PopupMenu> contextMenu;
		contextMenu = new PopupMenu;
		
		contextMenu->addItem(1, "Copy Address", true, false);

		int result = contextMenu->show();
		if (result == 1)
		{
			String addressRS(burstExt.GetAccountRS());
			SystemClipboard::copyTextToClipboard(addressRS);
			NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Address " + addressRS + "\nis copied to clipboard");
		}

		contextMenu = nullptr;
		//[/UserButtonCode_accountButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void BalanceComponent::AddAssetWhitelist(const StringArray assetIDs)
{
	externalAssetWhitelist.addArray(assetIDs);
}

void BalanceComponent::SetNode(const String server, const bool allowNonSSL)
{
	stopThread(500);
	const ScopedLock lock(burstExtLock);

	assetID.clear();
	burstExt.SetNode(server, allowNonSSL);

	startThread();
}

void BalanceComponent::SetPrice(String currency, double price)
{
	this->currency = currency;
	this->price = price;
}

void BalanceComponent::SetSecretPhrase(const String passphrase)
{
	const ScopedLock lock(burstExtLock);
	burstExt.SetSecretPhrase(passphrase, 0);
}

void BalanceComponent::SetForceSSL_TSL(const bool forceSSLOn)
{
	const ScopedLock lock(burstExtLock);
	burstExt.SetForceSSL_TSL(forceSSLOn);
}

void BalanceComponent::SetNodeHop(const bool hopOn)
{
	const ScopedLock lock(burstExtLock);
	burstExt.EnableNodeHop(hopOn ? 7 : 0);
}

void BalanceComponent::timerCallback()
{
	if (timerDelay++ > 60 * (1000 / getTimerInterval()))
	{
		timerDelay = 0;
		startThread();
	}

	const ScopedTryLock lock(burstExtLock);
	if (lock.isLocked())
	{
		if (balance.isNotEmpty() && balanceLabel->getText().compare(balance) != 0 && myBurstRS.isNotEmpty() && updated)
		{
			updated = false;
			accountButton->setButtonText(myBurstRS);

			String tooltip(balance);
			tooltip += "\n";
			for (int i = 1; i < assetsBalances.getAllKeys().size(); i++)
			{
				String assetDecimals;
				const String assetName = GetAssetName(assetsBalances.getAllKeys()[i], assetDecimals);
				String nr;
				nr = String::formatted("%." + assetDecimals + "f", assetsBalances.getAllValues()[i].getLargeIntValue() / pow(10., assetDecimals.getLargeIntValue()), assetDecimals.getLargeIntValue());
				tooltip += nr + " " + assetName + "\n";
			}
			balanceLabel->setTooltip(tooltip);


			balanceLabel->setText(balance_converted, dontSendNotification);

			{ // show the secure account option, if the wallet is empty and has no pubkey
				interfaceListeners.call(&InterfaceListener::Broke, (hasPubKey == false), pubKey_b64, isPro);
				interfaceListeners.call(&InterfaceListener::SetAssetsBalances, assetsBalances);
			}
			repaint();
		}
	}
}

void BalanceComponent::run()
{
	const ScopedLock lock(burstExtLock);
	UpdateBalanceRun();
	updated = true;
}

String BalanceComponent::NQT2Burst(const String value)
{
	bool minus = value.startsWithChar('-');
	String neatNr(value.removeCharacters("-").paddedLeft('0', 9));
	neatNr = (neatNr.substring(0, neatNr.length() - 8) + "." + neatNr.substring(neatNr.length() - 8, neatNr.length()).trimCharactersAtEnd("0"));
	return minus ? "-" + neatNr : neatNr;
}

void BalanceComponent::UpdateBalance()
{
	startThread();
}

void BalanceComponent::UpdateBalanceRun()
{
	// check / update balance
	myBurstRS = burstExt.GetAccountRS();	
	if (myBurstRS.isEmpty())
		return;

	// extract the balances for the assets. and allow these to be whitelisted
	assetsBalances.clear();
	String accountStr = burstExt.getAccount(myBurstRS);
	var accountJson;
	Result r = JSON::parse(accountStr, accountJson);
	
	uint64 balance_root = accountJson["balanceNQT"].toString().getLargeIntValue();
	balance = String(balance_root);
	assetsBalances.set("0", balance); // 0 is BURST

	if (accountJson["assetBalances"].isArray())
	{
		for (int i = 0; i < accountJson["assetBalances"].size(); i++)
		{
			const String assetID = accountJson["assetBalances"][i]["asset"];
			const String balanceQNT = accountJson["assetBalances"][i]["balanceQNT"];
			assetsBalances.set(assetID, balanceQNT);
		}
	}

	for (int i = 0; i < externalAssetWhitelist.size(); i++)
		assetsBalances.set(externalAssetWhitelist[i], "0");

	

	if (threadShouldExit())
		return;

	String pubKey_hex;
	hasPubKey = true;
	if (balance.length() > 8)
		balance = (balance.substring(0, balance.length() - 8) + "." + balance.substring(balance.length() - 8, balance.length()).trimCharactersAtEnd("0") + " BURST");
	else if (balance.getLargeIntValue() > 0)
		balance = (balance + " planck");
	else
	{
		String publicKeyJSONStr = burstExt.getAccountPublicKey(myBurstRS);
		String publicKeyStr = burstExt.GetJSONvalue(publicKeyJSONStr, "publicKey");

		String reedSolomon;
		String addressID;
		burstExt.GetWallet(0, pubKey_hex, pubKey_b64, reedSolomon, addressID);

		if (publicKeyStr.isEmpty())
			hasPubKey = false;

		if (hasPubKey)
			balance = ("EMPTY WALLET");
		else balance = ("NEW EMPTY WALLET");
	}

	if (threadShouldExit())
		return;

	if (currency.isEmpty() || currency.compare("BURST") == 0)
	{
		balance_converted = String(balance_root / 100000000.) + (" BURST");
	}
	else
	{ // market conversion
		double conv = price * (balance_root / 100000000.);
		//String convertedStr = String(conv, (conv > 1. ? 2 : 8));
		String convertedStr = std::to_string(conv);
		balance_converted = 
			convertedStr.upToFirstOccurrenceOf(".", true, true) + 
			convertedStr.fromFirstOccurrenceOf(".", false, true).paddedRight('0', 8).substring(0, (conv > 1. ? 2 : 8)) + " " + currency + "/BURST";
	}

	if (threadShouldExit())
		return;

	// determine if pro
	if (assetID.isEmpty())
	{ // find the HotWallet asset
		String assetsByCurb = burstExt.getAssetsByIssuer(burstExt.ensureAccountID("HotWallet"));
		var assetsByCurbJson;
		Result r = JSON::parse(assetsByCurb, assetsByCurbJson);
		if (assetsByCurbJson["assets"].isArray() && assetsByCurbJson["assets"][0].isArray())
		{
			for (int i = 0; i < assetsByCurbJson["assets"][0].size(); i++)
			{
				if (assetsByCurbJson["assets"][0][i]["name"].toString().compareIgnoreCase("HotWallet") == 0)
				{
					assetID = assetsByCurbJson["assets"][0][i]["asset"].toString();
					assetIDNumberOfAccounts = (int64)assetsByCurbJson["assets"][0][i]["numberOfAccounts"];
				}
			}
		}
	}
	if (assetID.isNotEmpty())
	{
		isPro = (assetsBalances[assetID].getLargeIntValue() > 0);		
		//	String getAssetAccountsJson = burstExt.getAssetAccounts(assetID);
		//	isPro = getAssetAccountsJson.contains(myBurstRS);		
	}
}

String BalanceComponent::GetAssetName(const String assetID, String &decimals)
{
	if (assetWhitelistNames.containsKey(assetID))
	{
		decimals = assetWhitelistDecimals[assetID];
		return assetWhitelistNames[assetID];
	}
	else
	{ // lookup expensive
		String assetStr = burstExt.getAsset(assetID);
		var assetJson;
		Result r = JSON::parse(assetStr, assetJson);

		assetWhitelistNames.set(assetID, assetJson["name"].toString());
		decimals = assetJson["decimals"].toString();
		assetWhitelistDecimals.set(assetID, decimals);

		return assetJson["name"].toString();
	}	
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="BalanceComponent" componentName=""
                 parentClasses="public Component, public Thread, public Timer, public BalanceComponentListener"
                 constructorParams="" variableInitialisers="Thread(&quot;ShoutComponent&quot;)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="343434"/>
  <LABEL name="balanceLabel" id="21cd31dd3925091c" memberName="balanceLabel"
         virtualName="" explicitFocusOrder="0" pos="155 45 152 24" tooltip="balance"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="EMPTY WALLET"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="18" bold="0" italic="0" justification="10"/>
  <TEXTBUTTON name="accountButton" id="ae4f12654e0537ec" memberName="accountButton"
              virtualName="" explicitFocusOrder="0" pos="27 13 272 24" tooltip="show account options"
              bgColOff="77b517" bgColOn="ff77b517" textCol="ffffffff" buttonText="BURST-XXXX-XXXX-XXXX-XXXXX"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
