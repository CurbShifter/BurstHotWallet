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
// http://explorer.testnet.burst.devtrue.net/at/16416979088057940648
#define kohinoor_TESTNET 1
#define kohinoor_MAINNET 0

#define AT_khoinoor "1520790662225426214"
#define khoinoor_URL "http://kohinoor.getburst.net/"
//#define TESTNET_AT_khoinoor_check_str "596f752061726520746865204b6f682d692d4e6f6f72206f776e657221000000"
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

    addAndMakeVisible (accountComboBox = new ComboBox ("accountComboBox"));
    accountComboBox->setEditableText (false);
    accountComboBox->setJustificationType (Justification::centredLeft);
    accountComboBox->setTextWhenNothingSelected (TRANS("BURST-XXXX-XXXX-XXXX-XXXXX"));
    accountComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    accountComboBox->addItem (TRANS("new/import account"), 1);
    accountComboBox->addItem (TRANS("remove account"), 2);
    accountComboBox->addListener (this);

    drawable1 = Drawable::createFromImageData (diamond_svg, diamond_svgSize);

    //[UserPreSize]
	accountComboBox->setColour(ComboBox::ColourIds::backgroundColourId, Colour(0x00ffffff));
	accountComboBox->setColour(ComboBox::ColourIds::textColourId, Colour(0xffffffff));
	accountComboBox->setColour(ComboBox::ColourIds::outlineColourId, Colour(0x00ffffff));
	accountComboBox->setColour(ComboBox::ColourIds::arrowColourId, Colour(0xffffffff));

	accountComboBox->clear();
	updated = false;
	balanceLabel->setFont(Font(22.00f, Font::plain));
	balanceLabel->setText(String::empty, dontSendNotification);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	isPro = false;
	timerDelay = -5;
	iOwnKhoinoor = false;
	khoinoor_priceNQT = 0;

	accountButton->setVisible(false);

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
    accountComboBox = nullptr;
    drawable1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void BalanceComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	/*
    //[/UserPrePaint]

    g.setColour (Colours::black);
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, Rectangle<float> (20, 20, 68, 60),
                               RectanglePlacement::centred, 1.000f);

    //[UserPaint] Add your own custom painting code here..
	*/
	if (iOwnKhoinoor)
	{
		g.setColour(Colours::white.withAlpha(0.f));
		jassert(drawable1 != 0);
		const int pad = 15;
		if (drawable1 != 0)
			drawable1->drawWithin(g, Rectangle<float>(pad, pad / 2, getHeight() - (pad * 2), getHeight() - (pad * 2)), RectanglePlacement::centred, 1.000f);
	}
    //[/UserPaint]
}

void BalanceComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    /*
    //[/UserPreResize]

    balanceLabel->setBounds (155, 45, 152, 24);
    accountButton->setBounds (56, 128, 272, 24);
    accountComboBox->setBounds (104, 8, 248, 24);
    //[UserResized] Add your own custom resize handling here..
	*/
	//accountButton->setBounds(getBounds().withZeroOrigin().withHeight(getHeight() / 2).reduced(3));
	const int pad = 15;
	accountComboBox->setBounds(getBounds().withZeroOrigin().withHeight(getHeight() / 2).withLeft(getHeight() - (pad * 2)).reduced(3));
	balanceLabel->setBounds(accountComboBox->getBounds().withY(getHeight() / 2));
    //[/UserResized]
}

void BalanceComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == accountButton)
    {
        //[UserButtonCode_accountButton] -- add your button handler code here..
        //[/UserButtonCode_accountButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void BalanceComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
	/*
			ScopedPointer<PopupMenu> contextMenu;
		contextMenu = new PopupMenu;

		contextMenu->addItem(1, "Copy Address", true, false);
	//	contextMenu->addItem(2, "Redeem Coupon", true, false);

		if (kohinoor_MAINNET || (kohinoor_TESTNET && burstExt.GetNode().contains("testnet")))
		{
			contextMenu->addItem(3, "Buy the Koh-i-noor diamond " + String(kohinoor_TESTNET ? "TESTNET ONLY " : " ") + "for: " + NQT2Burst(String(khoinoor_priceNQT)) + " BURST", !iOwnKhoinoor, false);
			contextMenu->addItem(4, "go to " + String(khoinoor_URL), true, false);
		}

		int result = contextMenu->show();
		if (result == 1)
		{
			String addressRS(burstExt.GetAccountRS());
			SystemClipboard::copyTextToClipboard(addressRS);
			NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Address " + addressRS + "\nis copied to clipboard");
		}
		else if (result == 3)
		{
			interfaceListeners.call(&InterfaceListener::SetupTransaction, "Buy the Koh-i-noor diamond.", String(AT_khoinoor), String(khoinoor_priceNQT), "normal", "", false);
		}
		else if (result == 4)
			URL(khoinoor_URL).launchInDefaultBrowser();

		contextMenu = nullptr;
		
		*/
	//[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == accountComboBox)
    {
        //[UserComboBoxCode_accountComboBox] -- add your combo box handling code here..
		balanceLabel->setTooltip(String::empty);
		balanceLabel->setText(String::empty, dontSendNotification);

		int numItems = accountComboBox->getNumItems();
		int index = accountComboBox->getSelectedItemIndex();
		if (index < numItems - 2)
			interfaceListeners.call(&InterfaceListener::SetAccountIndex, index);
		else if (index == numItems - 2)
		{
			// new/import account
			interfaceListeners.call(&InterfaceListener::SetAccountIndex, index);
			interfaceListeners.call(&InterfaceListener::CreateWallet);
		}
		else if (index == numItems - 1)
		{
			// remove account
			interfaceListeners.call(&InterfaceListener::RemoveWallet);
		}
		//[/UserComboBoxCode_accountComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void BalanceComponent::AddAssetWhitelist(const StringArray assetIDs)
{
	externalAssetWhitelist.addArray(assetIDs);
}

void BalanceComponent::SetPrice(String currency, double price)
{
	this->currency = currency;
	this->price = price;
}

void BalanceComponent::SetNode(const String server, const bool allowNonSSL)
{
	stopThread(2000);
	{
		const ScopedLock lock(burstExtLock);
		assetID.clear();
		burstExt.SetNode(server, allowNonSSL);
	}

	startThread();
}

void BalanceComponent::SetSecretPhrase(const String passphrase)
{
	const ScopedLock lock(burstExtLock);
	burstExt.SetSecretPhrase(passphrase, 0);

	UpdateBalance();
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
	if (timerDelay++ > (60L * (int64)(1000L / getTimerInterval())))
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
				interfaceListeners.call(&InterfaceListener::Broke, (hasPubKey == false), myBurstRS, pubKey_b64, isPro);
				interfaceListeners.call(&InterfaceListener::SetAssetsBalances, assetsBalances);
			}
			repaint();
		}
	}
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

void BalanceComponent::run()
{
	const ScopedLock lock(burstExtLock);
	UpdateBalanceRun();
	updated = true;
}

void BalanceComponent::UpdateBalanceRun()
{
	// check / update balance
	myBurstRS = burstExt.GetAccountRS();
	if (myBurstRS.isEmpty())
		return;

	// extract the balances for the assets. and whitelist these
	assetsBalances.clear();
	String accountStr = burstExt.getAccount(myBurstRS);
	var accountJson;
	Result r = JSON::parse(accountStr, accountJson);

	uint64 balance_root = accountJson["unconfirmedBalanceNQT"].toString().getLargeIntValue();//"balanceNQT"
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
		String assetsByCurb = burstExt.getAssetsByIssuer(burstExt.convertToAccountID("HotWallet"));
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

	//
	/*String atData = burstExt.getAT(AT_khoinoor);
	String machineData = atData.fromFirstOccurrenceOf("\"machineData\":\"", false, true).upToFirstOccurrenceOf("\"", false, true);
	String accountHex;
	String priceHex;
	uint64 account = 0;
	accountHex = machineData.substring(0, (2 * 8));
	MemoryBlock accountMem;
	accountMem.loadFromHexString(accountHex);
	if (accountMem.getSize() >= 8)
		account = *((uint64*)accountMem.getData());
	String currentOwnerRS = burstExt.ensureAccountRS(String(account));
	iOwnKhoinoor = burstExt.GetAccountRS().compareIgnoreCase(currentOwnerRS) == 0;

	priceHex = machineData.substring((2 * 8 * 2), (2 * 8 * 3));
	MemoryBlock priceMem;
	priceMem.loadFromHexString(priceHex);
	if (priceMem.getSize() >= 8)
		khoinoor_priceNQT = *((uint64*)priceMem.getData());*/


	/* jjos:
	extract a long from the first 8 bytes, it contains the current owner.
	 Current price is the third variable, each one is 8 bytes. hexadecimal and little endian.

	 {
	 "creator": "5219831338759933722",
	 "creatorRS": "BURST-TMSU-YBH5-RVC7-6J6WJ",
	 "at": "16416979088057940648",
	 "atRS": "BURST-DGPA-HZQD-5R5J-GM8P9",
	 "atVersion": 1,
	 "name": "khoinoor",
	 "description": "khoinoor",
	 "machineCode": "12070300003033040308000000350001090000001e090000000c129b020000283507030800000012310000001a06000000331001090000003506030a000000100a000000110700000033100109000000320a033504010a000000100a0000001106000000020a00000007000000060a00000004000000100a000000110a000000070a00000002000000100a000000110a000000030b000000210a0000000b0000000f1a32020000010a0000006400000000000000100a000000110b000000020a00000002000000090a0000000b000000100a0000001103000000020a00000002000000070a00000003000000100a000000110b000000331601000000003302040b00000033160100000000010a0000004b6f682d692d4e6f3310010a000000010a0000006f722068617320613311010a000000010a000000206e6577206f776e3312010a000000010a00000065722e00000000003313010a00000032050402000000000600000033160100000000010a000000596f7520617265203310010a000000010a000000746865204b6f682d3311010a000000010a000000692d4e6f6f72206f3312010a000000010a000000776e6572210000003313010a000000320504010a0000000a00000000000000100a000000110a000000080a00000002000000100a000000010a0000006400000000000000100a000000110b000000110a000000090a0000000b000000100a000000110b000000020a00000002000000060a0000000b000000100a00000011020000001333160106000000010a000000416d6f756e7420733310010a000000010a000000656e7420776173203311010a000000010a0000006e6f7420656e6f753312010a000000010a00000067682e00000000003313010a0000003205043316010600000033020407000000133500040a000000100a0000001105000000020a00000005000000070a00000004000000100a000000110a000000030b0000001f0a0000000b0000000f1a06030000020a00000005000000070a00000004000000100a000000110b000000331601010000003302040b00000013320b033504010a000000100a0000001101000000020000000001000000010a0000000088526a74000000100a0000001102000000010a000000005ed0b200000000100a0000001104000000130000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
	 "machineData": "0a5aeec430d930641acf3c5ef29070482b094516ba0100002764db0404000000005ed0b2000000000b0573f1030000000a5aeec430d930640050b936910100000100000051d8000000000000000000000ba7a23e030000000ba7a23e030000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001f0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000064000000000000000ba7a23e03000000",
	 "balanceNQT": "2660000000",
	 "prevBalanceNQT": "2660000000",
	 "nextBlock": 55378,
	 "frozen": true,
	 "running": false,
	 "stopped": false,
	 "finished": true,
	 "dead": false,
	 "minActivation": "3000000000",
	 "creationBlock": 55200,
	 "requestProcessingTime": 1
	 }
	 */
/*	String khoinoorResp = burstExt.getAccountTransactions(TESTNET_AT_khoinoor, "", "22", "1", "0", "5");
	if (khoinoorResp.contains(TESTNET_AT_khoinoor_check_str))
	{
		String part = khoinoorResp.upToFirstOccurrenceOf(TESTNET_AT_khoinoor_check_str, false, true);
		String currentOwnerRS = part.fromLastOccurrenceOf("recipientRS", false, true).upToFirstOccurrenceOf("\",", false, true).fromFirstOccurrenceOf("BURST-", true, true);
		iOwnKhoinoor = burstExt.GetAccountRS().compareIgnoreCase(currentOwnerRS) == 0;
	}*/
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

void BalanceComponent::InitAccountSelection(const int index)
{
	//StringArray addresses;
	StringArray names;
	//interfaceListeners.call(&InterfaceListener::GetAccountAddresses, addresses);
	interfaceListeners.call(&InterfaceListener::GetAccountNames, names);
	
	int selectedItemIndex = (index < 0) ? accountComboBox->getSelectedItemIndex() : jmin<int>(index, names.size());

	accountComboBox->clear();
	accountComboBox->addItemList(names, 1);
	accountComboBox->addSeparator();
	accountComboBox->addItem(TRANS("new/import account"), names.size() + 2);
	accountComboBox->addItem(TRANS("remove current account"), names.size() + 3);

	accountComboBox->setSelectedItemIndex(jmax<int>(0, selectedItemIndex));
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
  <BACKGROUND backgroundColour="343434">
    <IMAGE pos="20 20 68 60" resource="diamond_svg" opacity="1" mode="1"/>
  </BACKGROUND>
  <LABEL name="balanceLabel" id="21cd31dd3925091c" memberName="balanceLabel"
         virtualName="" explicitFocusOrder="0" pos="155 45 152 24" tooltip="balance"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="EMPTY WALLET"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="18" bold="0" italic="0" justification="10"/>
  <TEXTBUTTON name="accountButton" id="ae4f12654e0537ec" memberName="accountButton"
              virtualName="" explicitFocusOrder="0" pos="56 128 272 24" tooltip="show account options"
              bgColOff="77b517" bgColOn="ff77b517" textCol="ffffffff" buttonText="BURST-XXXX-XXXX-XXXX-XXXXX"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="accountComboBox" id="f53eb928e1072a47" memberName="accountComboBox"
            virtualName="" explicitFocusOrder="0" pos="104 8 248 24" editable="0"
            layout="33" items="new/import account&#10;remove account" textWhenNonSelected="BURST-XXXX-XXXX-XXXX-XXXXX"
            textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: diamond_svg, 13898, "img/diamond.svg"
static const unsigned char resource_BalanceComponent_diamond_svg[] = { 60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,110,99,111,100,105,110,103,61,34,85,84,70,45,56,34,32,115,
116,97,110,100,97,108,111,110,101,61,34,110,111,34,63,62,10,60,33,45,45,32,67,114,101,97,116,101,100,32,119,105,116,104,32,73,110,107,115,99,97,112,101,32,40,104,116,116,112,58,47,47,119,119,119,46,105,
110,107,115,99,97,112,101,46,111,114,103,47,41,32,45,45,62,10,10,60,115,118,103,10,32,32,32,120,109,108,110,115,58,100,99,61,34,104,116,116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,101,
108,101,109,101,110,116,115,47,49,46,49,47,34,10,32,32,32,120,109,108,110,115,58,99,99,61,34,104,116,116,112,58,47,47,99,114,101,97,116,105,118,101,99,111,109,109,111,110,115,46,111,114,103,47,110,115,
35,34,10,32,32,32,120,109,108,110,115,58,114,100,102,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,49,57,57,57,47,48,50,47,50,50,45,114,100,102,45,115,121,110,116,97,120,45,110,
115,35,34,10,32,32,32,120,109,108,110,115,58,115,118,103,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,10,32,32,32,120,109,108,110,115,61,34,104,
116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,10,32,32,32,120,109,108,110,115,58,115,111,100,105,112,111,100,105,61,34,104,116,116,112,58,47,47,115,111,100,
105,112,111,100,105,46,115,111,117,114,99,101,102,111,114,103,101,46,110,101,116,47,68,84,68,47,115,111,100,105,112,111,100,105,45,48,46,100,116,100,34,10,32,32,32,120,109,108,110,115,58,105,110,107,115,
99,97,112,101,61,34,104,116,116,112,58,47,47,119,119,119,46,105,110,107,115,99,97,112,101,46,111,114,103,47,110,97,109,101,115,112,97,99,101,115,47,105,110,107,115,99,97,112,101,34,10,32,32,32,119,105,
100,116,104,61,34,50,49,48,109,109,34,10,32,32,32,104,101,105,103,104,116,61,34,50,57,55,109,109,34,10,32,32,32,118,105,101,119,66,111,120,61,34,48,32,48,32,50,49,48,32,50,57,55,34,10,32,32,32,118,101,
114,115,105,111,110,61,34,49,46,49,34,10,32,32,32,105,100,61,34,115,118,103,56,34,10,32,32,32,105,110,107,115,99,97,112,101,58,118,101,114,115,105,111,110,61,34,48,46,57,50,46,49,32,114,49,53,51,55,49,
34,10,32,32,32,115,111,100,105,112,111,100,105,58,100,111,99,110,97,109,101,61,34,100,105,97,109,111,110,100,46,115,118,103,34,62,10,32,32,60,100,101,102,115,10,32,32,32,32,32,105,100,61,34,100,101,102,
115,50,34,32,47,62,10,32,32,60,115,111,100,105,112,111,100,105,58,110,97,109,101,100,118,105,101,119,10,32,32,32,32,32,105,100,61,34,98,97,115,101,34,10,32,32,32,32,32,112,97,103,101,99,111,108,111,114,
61,34,35,102,102,102,102,102,102,34,10,32,32,32,32,32,98,111,114,100,101,114,99,111,108,111,114,61,34,35,54,54,54,54,54,54,34,10,32,32,32,32,32,98,111,114,100,101,114,111,112,97,99,105,116,121,61,34,49,
46,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,112,97,103,101,111,112,97,99,105,116,121,61,34,48,46,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,112,97,103,101,115,104,97,100,
111,119,61,34,50,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,122,111,111,109,61,34,48,46,51,53,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,120,61,34,45,50,50,49,46,52,50,56,53,55,
34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,121,61,34,53,54,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,100,111,99,117,109,101,110,116,45,117,110,105,116,115,61,34,109,109,34,
10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,117,114,114,101,110,116,45,108,97,121,101,114,61,34,108,97,121,101,114,49,34,10,32,32,32,32,32,115,104,111,119,103,114,105,100,61,34,102,97,108,115,
101,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,119,105,100,116,104,61,34,49,57,50,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,
45,104,101,105,103,104,116,61,34,49,48,50,55,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,120,61,34,45,56,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,
105,110,100,111,119,45,121,61,34,55,48,49,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,109,97,120,105,109,105,122,101,100,61,34,49,34,32,47,62,10,32,32,60,109,101,116,
97,100,97,116,97,10,32,32,32,32,32,105,100,61,34,109,101,116,97,100,97,116,97,53,34,62,10,32,32,32,32,60,114,100,102,58,82,68,70,62,10,32,32,32,32,32,32,60,99,99,58,87,111,114,107,10,32,32,32,32,32,32,
32,32,32,114,100,102,58,97,98,111,117,116,61,34,34,62,10,32,32,32,32,32,32,32,32,60,100,99,58,102,111,114,109,97,116,62,105,109,97,103,101,47,115,118,103,43,120,109,108,60,47,100,99,58,102,111,114,109,
97,116,62,10,32,32,32,32,32,32,32,32,60,100,99,58,116,121,112,101,10,32,32,32,32,32,32,32,32,32,32,32,114,100,102,58,114,101,115,111,117,114,99,101,61,34,104,116,116,112,58,47,47,112,117,114,108,46,111,
114,103,47,100,99,47,100,99,109,105,116,121,112,101,47,83,116,105,108,108,73,109,97,103,101,34,32,47,62,10,32,32,32,32,32,32,32,32,60,100,99,58,116,105,116,108,101,62,60,47,100,99,58,116,105,116,108,101,
62,10,32,32,32,32,32,32,60,47,99,99,58,87,111,114,107,62,10,32,32,32,32,60,47,114,100,102,58,82,68,70,62,10,32,32,60,47,109,101,116,97,100,97,116,97,62,10,32,32,60,103,10,32,32,32,32,32,105,110,107,115,
99,97,112,101,58,108,97,98,101,108,61,34,76,97,97,103,32,49,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,103,114,111,117,112,109,111,100,101,61,34,108,97,121,101,114,34,10,32,32,32,32,32,105,
100,61,34,108,97,121,101,114,49,34,62,10,32,32,32,32,60,103,10,32,32,32,32,32,32,32,105,100,61,34,103,52,52,57,54,34,10,32,32,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,34,114,111,116,97,116,
101,40,45,50,49,46,49,53,53,48,57,44,53,49,46,51,56,57,57,55,52,44,57,49,46,54,52,51,49,55,41,34,10,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,97,97,101,102,102,102,59,102,105,
108,108,45,111,112,97,99,105,116,121,58,49,34,62,10,32,32,32,32,32,32,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,97,97,101,102,102,102,59,102,105,108,
108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,49,46,48,48,53,54,48,48,48,57,34,10,32,32,32,32,32,32,32,32,32,100,61,34,77,32,56,56,46,54,54,48,49,51,51,44,
49,55,56,46,48,53,57,51,50,32,67,32,56,49,46,54,51,56,51,49,52,44,49,54,52,46,51,55,48,53,57,32,55,51,46,48,55,49,48,56,52,44,49,52,55,46,55,52,48,52,56,32,54,57,46,54,50,49,56,52,52,44,49,52,49,46,49,
48,51,53,50,32,53,56,46,48,52,52,51,48,57,44,49,49,56,46,56,50,54,50,54,32,52,55,46,56,48,56,51,57,52,44,57,56,46,50,51,50,55,49,52,32,52,56,46,49,54,50,55,49,50,44,57,55,46,57,51,48,48,56,56,32,99,32,
48,46,49,57,51,50,50,54,44,45,48,46,49,54,53,48,51,53,32,49,50,46,55,54,50,49,56,51,44,49,46,49,48,57,56,53,50,32,50,55,46,57,51,49,48,49,53,44,50,46,56,51,51,48,56,50,32,108,32,50,55,46,53,55,57,54,57,
51,44,51,46,49,51,51,49,52,32,45,48,46,51,57,55,48,52,44,52,52,46,50,52,54,52,49,32,99,32,45,48,46,50,49,56,51,55,44,50,52,46,51,51,53,53,50,32,45,48,46,52,49,49,49,57,44,52,54,46,54,50,50,49,51,32,45,
48,46,52,50,56,52,57,44,52,57,46,53,50,53,56,32,45,48,46,48,49,55,51,44,50,46,57,48,51,54,55,32,45,48,46,51,52,52,48,54,44,53,46,50,55,57,52,32,45,48,46,55,50,54,49,51,44,53,46,50,55,57,52,32,45,48,46,
51,56,50,48,56,44,48,32,45,54,46,52,51,57,56,48,57,44,45,49,49,46,49,57,57,56,55,32,45,49,51,46,52,54,49,54,50,55,44,45,50,52,46,56,56,56,54,32,122,32,109,32,50,49,46,48,55,48,54,57,55,44,45,50,52,46,
48,51,49,56,56,32,99,32,48,46,51,56,49,49,50,44,45,50,54,46,57,48,54,50,55,32,48,46,57,51,49,50,49,44,45,52,57,46,51,48,54,48,49,32,49,46,50,50,50,52,50,44,45,52,57,46,55,55,55,50,32,48,46,50,57,49,50,
49,44,45,48,46,52,55,49,50,32,50,46,52,50,53,57,57,44,45,48,46,56,54,50,48,52,32,52,46,55,52,51,57,52,44,45,48,46,56,54,56,53,49,32,50,46,51,49,55,57,53,44,45,48,46,48,48,54,32,49,51,46,52,57,49,49,49,
44,45,48,46,57,48,54,50,51,32,50,52,46,56,50,57,50,53,44,45,49,46,57,57,57,52,50,32,50,52,46,48,48,56,57,56,44,45,50,46,51,49,52,56,55,51,32,50,51,46,49,50,56,56,49,44,45,50,46,50,55,50,54,49,50,32,50,
51,46,49,50,56,56,49,44,45,49,46,49,49,48,53,51,32,48,44,48,46,52,57,53,51,55,32,45,51,46,53,52,54,54,57,44,55,46,54,50,50,53,55,32,45,55,46,56,56,49,53,51,44,49,53,46,56,51,56,50,49,32,45,52,46,51,51,
52,56,52,44,56,46,50,49,53,54,51,32,45,49,54,46,51,54,55,57,55,44,51,49,46,49,49,53,49,50,32,45,50,54,46,55,52,48,50,55,44,53,48,46,56,56,55,55,51,32,45,49,48,46,51,55,50,51,49,44,49,57,46,55,55,50,54,
49,32,45,49,57,46,49,49,52,53,51,44,51,53,46,57,53,48,50,32,45,49,57,46,52,50,55,49,54,44,51,53,46,57,53,48,50,32,45,48,46,51,49,50,54,51,44,48,32,45,48,46,50,53,54,53,57,44,45,50,50,46,48,49,52,50,50,
32,48,46,49,50,52,53,52,44,45,52,56,46,57,50,48,52,56,32,122,32,109,32,49,55,46,55,55,53,55,52,44,51,48,46,53,56,48,48,57,32,99,32,45,48,46,48,50,57,49,44,45,48,46,52,48,56,51,49,32,52,46,52,48,56,56,
51,44,45,57,46,50,51,50,52,53,32,57,46,56,54,50,49,44,45,49,57,46,54,48,57,50,32,53,46,52,53,51,50,55,44,45,49,48,46,51,55,54,55,52,32,49,53,46,52,56,48,54,53,44,45,50,57,46,53,48,49,48,51,32,50,50,46,
50,56,51,48,55,44,45,52,50,46,52,57,56,52,49,32,54,46,56,48,50,52,51,44,45,49,50,46,57,57,55,51,57,32,49,50,46,52,57,48,56,53,44,45,50,51,46,55,56,56,54,52,52,32,49,50,46,54,52,48,57,53,44,45,50,51,46,
57,56,48,53,55,57,32,48,46,52,51,57,55,49,44,45,48,46,53,54,50,50,55,49,32,50,56,46,56,50,51,49,52,44,45,55,46,50,55,52,56,53,32,50,57,46,49,57,51,55,55,44,45,54,46,57,48,52,50,50,50,32,48,46,49,56,53,
52,44,48,46,49,56,53,51,57,56,32,45,49,53,46,48,54,49,51,57,44,49,57,46,55,54,55,55,53,49,32,45,51,51,46,56,56,49,55,53,44,52,51,46,53,49,54,51,52,49,32,45,51,57,46,48,56,48,56,50,44,52,57,46,51,49,52,
51,56,32,45,52,48,46,48,50,54,52,55,44,53,48,46,52,56,49,50,32,45,52,48,46,48,57,56,49,52,44,52,57,46,52,55,54,48,55,32,122,32,77,32,54,57,46,49,51,50,57,53,49,44,49,54,52,46,57,51,53,56,54,32,67,32,54,
50,46,50,50,49,55,49,52,44,49,53,53,46,54,57,57,54,51,32,52,54,46,54,55,55,55,55,55,44,49,51,53,46,49,48,50,52,55,32,51,52,46,53,57,48,56,55,44,49,49,57,46,49,54,52,51,57,32,50,50,46,53,48,51,57,54,50,
44,49,48,51,46,50,50,54,51,49,32,49,50,46,56,50,52,48,52,54,44,56,57,46,57,55,54,54,57,52,32,49,51,46,48,55,57,57,52,54,44,56,57,46,55,50,48,55,57,52,32,99,32,48,46,52,50,49,56,48,56,44,45,48,46,52,50,
49,56,48,56,32,50,53,46,56,56,49,56,49,44,54,46,49,57,57,53,56,49,32,50,54,46,51,54,53,57,49,57,44,54,46,56,53,54,57,57,32,48,46,51,51,48,52,49,56,44,48,46,52,52,56,55,48,49,32,49,54,46,50,54,50,48,56,
44,51,49,46,51,50,48,54,53,54,32,51,48,46,54,51,50,50,51,52,44,53,57,46,51,53,56,51,51,54,32,55,46,50,57,57,51,53,53,44,49,52,46,50,52,49,56,49,32,49,50,46,57,48,48,49,50,50,44,50,53,46,56,55,49,52,32,
49,50,46,52,52,54,49,52,55,44,50,53,46,56,52,51,53,52,32,45,48,46,52,53,51,57,55,53,44,45,48,46,48,50,55,57,32,45,54,46,52,56,48,48,53,56,44,45,55,46,54,48,55,53,56,32,45,49,51,46,51,57,49,50,57,53,44,
45,49,54,46,56,52,51,56,32,122,32,77,32,55,52,46,50,55,48,48,52,55,44,57,52,46,50,54,51,49,55,32,67,32,54,48,46,55,56,49,56,53,50,44,57,50,46,54,56,48,50,53,51,32,52,57,46,53,51,50,57,53,44,57,49,46,49,
55,50,48,51,52,32,52,57,46,50,55,50,52,56,57,44,57,48,46,57,49,49,53,55,49,32,52,57,46,48,49,50,48,50,54,44,57,48,46,54,53,49,49,48,57,32,53,53,46,50,55,49,53,49,57,44,56,51,46,52,50,50,57,49,50,32,54,
51,46,49,56,50,52,55,50,44,55,52,46,56,52,56,57,49,50,32,55,53,46,54,56,53,49,49,49,44,54,49,46,50,57,56,51,55,55,32,55,55,46,55,49,55,48,50,57,44,53,57,46,52,56,50,53,55,54,32,55,56,46,55,50,48,55,56,
44,54,48,46,57,54,51,50,54,53,32,99,32,50,46,55,54,57,57,57,54,44,52,46,48,56,54,49,55,53,32,50,49,46,53,56,49,54,54,44,51,53,46,51,49,55,48,52,56,32,50,49,46,53,56,49,54,54,44,51,53,46,56,50,57,53,56,
52,32,48,44,48,46,51,49,49,56,56,54,32,45,48,46,51,51,57,51,57,49,44,48,46,53,49,55,56,53,53,32,45,48,46,55,53,52,50,48,49,44,48,46,52,53,55,55,48,57,32,45,48,46,52,49,52,56,49,44,45,48,46,48,54,48,49,
52,32,45,49,49,46,55,56,57,57,57,54,44,45,49,46,52,48,52,52,55,49,32,45,50,53,46,50,55,56,49,57,50,44,45,50,46,57,56,55,51,56,56,32,122,32,109,32,52,48,46,49,49,48,55,57,51,44,50,46,50,57,56,57,51,49,
32,99,32,48,44,45,49,46,53,52,49,57,57,51,32,50,50,46,50,48,57,57,52,44,45,51,55,46,52,49,52,57,56,57,32,50,51,46,49,54,52,54,50,44,45,51,55,46,52,49,52,57,56,57,32,49,46,52,54,50,56,54,44,48,32,50,56,
46,50,56,48,50,49,44,51,50,46,52,50,57,52,48,50,32,50,55,46,52,50,50,49,49,44,51,51,46,49,54,48,55,49,53,32,45,48,46,52,52,53,50,52,44,48,46,51,55,57,52,52,56,32,45,49,48,46,51,49,50,52,52,44,49,46,52,
54,55,56,54,32,45,50,49,46,57,50,55,49,50,44,50,46,52,49,56,54,57,52,32,45,49,49,46,54,49,52,54,57,44,48,46,57,53,48,56,51,52,32,45,50,50,46,56,49,52,53,54,44,49,46,57,55,50,49,48,49,32,45,50,52,46,56,
56,56,54,49,44,50,46,50,54,57,52,56,50,32,45,50,46,49,51,53,53,52,44,48,46,51,48,54,49,57,56,32,45,51,46,55,55,49,44,48,46,49,49,56,48,49,56,32,45,51,46,55,55,49,44,45,48,46,52,51,51,57,48,50,32,122,32,
77,32,57,53,46,52,52,51,50,44,55,53,46,56,52,48,48,54,57,32,67,32,56,57,46,50,54,54,53,44,54,53,46,54,54,51,51,57,53,32,56,52,46,50,49,51,49,54,49,44,53,55,46,49,55,56,54,52,52,32,56,52,46,50,49,51,53,
53,55,44,53,54,46,57,56,53,48,54,56,32,99,32,51,46,57,55,101,45,52,44,45,48,46,49,57,51,53,55,54,32,49,48,46,52,49,50,49,53,55,44,45,48,46,51,54,51,51,53,51,32,50,51,46,49,51,55,50,52,51,44,45,48,46,51,
55,55,50,56,51,32,49,50,46,55,50,53,49,44,45,48,46,48,49,51,57,51,32,50,51,46,48,49,57,54,44,48,46,50,51,49,50,57,50,32,50,50,46,56,55,54,54,57,44,48,46,53,52,52,57,51,57,32,45,49,46,50,49,49,57,44,50,
46,54,53,57,54,57,32,45,50,50,46,53,49,56,56,52,44,51,55,46,49,50,53,56,54,53,32,45,50,50,46,57,54,56,52,57,44,51,55,46,49,53,51,56,57,53,32,45,48,46,51,50,49,57,57,44,48,46,48,50,48,48,55,32,45,53,46,
54,51,57,49,44,45,56,46,50,56,57,56,55,53,32,45,49,49,46,56,49,53,56,44,45,49,56,46,52,54,54,53,53,32,122,32,109,32,55,56,46,54,56,57,50,52,44,52,46,56,50,52,54,53,51,32,99,32,49,46,51,50,50,51,50,44,
45,50,50,46,56,50,48,57,54,52,32,49,46,56,50,52,49,50,44,45,50,56,46,53,53,54,56,49,32,50,46,52,57,56,51,52,44,45,50,56,46,53,53,54,56,49,32,49,46,48,48,53,53,49,44,48,32,50,55,46,50,52,56,52,55,44,50,
57,46,56,57,56,52,57,56,32,50,55,46,50,52,56,52,55,44,51,49,46,48,52,52,48,54,55,32,48,44,48,46,53,50,57,49,51,53,32,45,54,46,50,50,50,49,53,44,50,46,52,50,48,50,57,56,32,45,49,51,46,56,50,55,44,52,46,
50,48,50,53,56,54,32,45,55,46,54,48,52,56,53,44,49,46,55,56,50,50,56,55,32,45,49,52,46,52,52,48,55,54,44,51,46,52,55,49,57,50,50,32,45,49,53,46,49,57,48,57,44,51,46,55,53,52,55,52,52,32,45,49,46,49,49,
57,55,51,44,48,46,52,50,50,49,54,53,32,45,49,46,50,53,48,50,50,44,45,49,46,52,52,55,54,51,54,32,45,48,46,55,50,56,57,49,44,45,49,48,46,52,52,52,53,56,55,32,122,32,77,32,50,51,46,49,49,54,50,49,53,44,56,
53,46,52,49,53,56,50,57,32,99,32,45,57,46,51,49,54,50,56,44,45,50,46,53,52,53,55,54,49,32,45,49,51,46,49,56,52,54,50,57,57,44,45,52,46,48,50,54,56,51,56,32,45,49,50,46,56,52,53,56,51,53,44,45,52,46,57,
49,56,50,57,32,48,46,54,53,49,54,49,57,44,45,49,46,55,49,52,53,55,32,50,51,46,56,50,51,54,56,44,45,50,56,46,51,56,57,54,50,55,32,50,52,46,54,54,49,52,55,50,44,45,50,56,46,51,56,57,54,50,55,32,48,46,51,
54,51,49,49,49,44,48,32,49,46,49,57,50,53,52,50,44,55,46,49,50,55,49,57,32,49,46,56,52,51,49,56,44,49,53,46,56,51,56,50,48,49,32,49,46,51,56,52,53,51,57,44,49,56,46,53,51,54,55,55,55,32,49,46,52,52,50,
50,51,53,44,50,49,46,52,49,51,53,55,49,32,48,46,52,50,53,57,57,55,44,50,49,46,50,52,48,55,49,54,32,45,48,46,52,49,52,56,49,44,45,48,46,48,55,48,53,53,32,45,54,46,55,53,50,57,55,55,44,45,49,46,55,54,55,
53,48,54,32,45,49,52,46,48,56,52,56,49,52,44,45,51,46,55,55,49,32,122,32,109,32,50,48,46,56,54,51,55,56,55,44,45,51,46,50,51,53,52,54,32,99,32,45,48,46,48,48,52,56,44,45,49,46,56,56,51,50,51,49,32,45,
48,46,52,54,50,53,48,57,44,45,57,46,55,49,54,52,57,49,32,45,49,46,48,49,55,48,48,57,44,45,49,55,46,52,48,55,50,52,54,32,45,48,46,53,53,52,53,44,45,55,46,54,57,48,55,53,54,32,45,48,46,56,50,49,52,50,50,
44,45,49,52,46,49,54,57,57,53,50,32,45,48,46,53,57,51,49,54,44,45,49,52,46,51,57,56,50,49,52,32,48,46,50,50,56,50,54,51,44,45,48,46,50,50,56,50,54,51,32,50,46,54,51,56,56,53,53,44,48,46,50,52,53,51,56,
53,32,53,46,51,53,54,56,55,51,44,49,46,48,53,50,53,52,57,32,50,46,55,49,56,48,49,54,44,48,46,56,48,55,49,54,52,32,57,46,49,48,54,51,57,50,44,50,46,48,53,54,57,57,57,32,49,52,46,49,57,54,51,57,44,50,46,
55,55,55,52,49,32,53,46,48,56,57,57,57,55,44,48,46,55,50,48,52,49,49,32,57,46,49,51,50,57,53,44,49,46,54,52,54,50,50,32,56,46,57,56,52,51,51,57,44,50,46,48,53,55,51,53,52,32,45,48,46,51,51,51,53,51,50,
44,48,46,57,50,50,55,50,52,32,45,50,50,46,49,51,56,55,54,55,44,50,53,46,48,49,54,53,48,57,32,45,50,52,46,57,49,48,49,53,54,44,50,55,46,53,50,52,53,56,49,32,45,49,46,57,55,48,48,57,50,44,49,46,55,56,50,
57,48,57,32,45,50,46,48,48,56,54,49,55,44,49,46,55,53,50,50,51,49,32,45,50,46,48,49,55,50,55,55,44,45,49,46,54,48,54,52,51,52,32,122,32,77,32,49,53,53,46,49,56,56,54,52,44,54,57,46,48,56,57,51,57,57,32,
99,32,45,49,49,46,50,56,54,51,50,44,45,49,51,46,52,57,56,49,55,32,45,49,49,46,56,52,55,52,44,45,49,52,46,57,49,51,52,48,52,32,45,53,46,57,50,56,57,52,44,45,49,52,46,57,53,52,56,56,56,32,50,46,48,57,49,
50,54,44,45,48,46,48,49,52,54,54,32,49,51,46,51,48,48,52,50,44,45,50,46,50,53,55,54,48,51,32,49,56,46,50,48,55,54,55,44,45,51,46,54,52,51,51,51,56,32,50,46,50,54,53,48,54,44,45,48,46,54,51,57,54,50,32,
50,46,50,57,52,56,50,44,45,48,46,53,52,50,57,48,55,32,49,46,55,55,50,55,55,44,53,46,55,54,50,53,32,45,48,46,50,57,50,48,51,44,51,46,53,50,55,49,55,51,32,45,48,46,56,48,53,50,56,44,49,48,46,56,50,53,49,
49,32,45,49,46,49,52,48,53,55,44,49,54,46,50,49,55,54,52,32,45,48,46,51,51,53,50,57,44,53,46,51,57,50,53,51,32,45,48,46,57,48,54,55,55,44,57,46,55,57,50,52,53,57,32,45,49,46,50,54,57,57,54,44,57,46,55,
55,55,54,49,57,32,45,48,46,51,54,51,50,49,44,45,48,46,48,49,52,56,52,32,45,53,46,54,48,49,54,52,44,45,53,46,57,51,54,54,51,32,45,49,49,46,54,52,48,57,55,44,45,49,51,46,49,53,57,53,51,51,32,122,32,77,32,
55,49,46,49,52,48,48,51,52,44,52,57,46,48,49,52,49,54,52,32,67,32,53,54,46,49,55,49,54,51,51,44,52,55,46,51,56,57,56,51,49,32,52,50,46,57,56,51,50,51,44,52,52,46,50,48,50,52,57,56,32,52,50,46,57,56,51,
50,51,44,52,50,46,50,48,57,51,49,52,32,99,32,48,44,45,49,46,51,51,51,54,56,54,32,49,48,46,50,49,55,51,55,49,44,45,51,46,57,53,53,55,56,49,32,50,50,46,54,56,49,53,55,56,44,45,53,46,56,50,48,55,57,56,32,
49,53,46,51,51,55,56,50,52,44,45,50,46,50,57,52,57,57,53,32,54,51,46,54,50,51,49,57,50,44,45,50,46,51,51,48,54,48,55,32,55,57,46,54,53,53,56,52,50,44,45,48,46,48,53,56,55,53,32,49,51,46,52,55,48,56,55,
44,49,46,57,48,56,56,52,55,32,50,51,46,53,55,54,51,50,44,52,46,53,55,56,49,55,51,32,50,51,46,48,55,49,48,49,44,54,46,48,57,52,49,51,52,32,45,48,46,52,54,50,53,57,44,49,46,51,56,55,55,52,56,32,45,54,46,
48,51,51,48,55,44,50,46,57,57,56,51,55,52,32,45,49,55,46,57,53,49,53,54,44,53,46,49,57,48,52,51,50,32,45,49,48,46,57,57,56,51,51,44,50,46,48,50,50,56,50,49,32,45,54,52,46,56,48,54,50,56,57,44,50,46,57,
55,50,54,53,54,32,45,55,57,46,51,48,48,48,54,54,44,49,46,51,57,57,56,50,57,32,122,34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,48,50,34,10,32,32,32,32,32,32,32,32,32,105,110,107,
115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,47,62,10,32,32,32,32,32,32,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,
61,34,102,105,108,108,58,35,97,97,101,102,102,102,59,102,105,108,108,45,111,112,97,99,105,116,121,58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,49,46,48,48,53,54,48,48,48,57,34,10,32,32,32,
32,32,32,32,32,32,100,61,34,77,32,55,53,46,48,57,49,50,53,51,44,49,53,48,46,56,50,50,53,57,32,67,32,54,48,46,48,51,55,49,53,49,44,49,50,49,46,53,53,49,32,52,56,46,56,55,53,53,52,49,44,57,56,46,55,52,48,
57,57,57,32,52,57,46,53,50,53,55,56,54,44,57,56,46,53,55,54,55,48,49,32,99,32,49,46,52,55,51,48,53,53,44,45,48,46,51,55,50,49,57,57,32,53,50,46,57,54,56,55,55,52,44,53,46,54,54,56,49,51,57,32,53,51,46,
53,56,54,49,56,52,44,54,46,50,56,53,53,51,57,32,48,46,50,53,51,56,54,44,48,46,50,53,51,56,54,32,48,46,48,54,52,57,44,50,50,46,51,56,56,53,32,45,48,46,52,49,57,55,57,44,52,57,46,49,56,56,49,32,108,32,45,
48,46,56,56,49,51,52,44,52,56,46,55,50,54,53,52,32,122,32,109,32,51,52,46,57,57,57,52,48,55,44,51,46,49,56,55,48,52,32,99,32,48,46,50,55,55,55,54,44,45,50,54,46,52,53,54,49,54,32,48,46,55,57,56,56,55,
44,45,52,56,46,52,50,54,55,50,32,49,46,49,53,56,48,52,44,45,52,56,46,56,50,51,52,55,32,48,46,53,55,53,52,51,44,45,48,46,54,51,53,54,54,32,53,49,46,52,53,56,49,54,44,45,53,46,55,55,49,54,49,54,32,53,50,
46,49,57,50,51,53,44,45,53,46,50,54,56,49,53,51,32,48,46,49,53,56,55,51,44,48,46,49,48,56,56,52,51,32,45,56,46,51,54,56,52,49,44,49,54,46,54,54,48,52,51,51,32,45,49,56,46,57,52,57,49,56,44,51,54,46,55,
56,49,51,48,51,32,45,49,48,46,53,56,48,55,56,44,50,48,46,49,50,48,56,56,32,45,50,50,46,52,50,52,52,50,44,52,50,46,54,57,50,52,51,32,45,50,54,46,51,49,57,50,50,44,53,48,46,49,53,57,48,49,32,45,51,46,56,
57,52,56,44,55,46,52,54,54,53,56,32,45,55,46,52,50,48,50,49,44,49,51,46,57,53,51,49,49,32,45,55,46,56,51,52,50,51,44,49,52,46,52,49,52,53,49,32,45,48,46,52,49,52,48,51,44,48,46,52,54,49,52,49,32,45,48,
46,53,50,53,53,50,44,45,50,48,46,56,48,55,48,51,32,45,48,46,50,52,55,55,54,44,45,52,55,46,50,54,51,50,32,122,32,109,32,50,53,46,53,49,50,57,50,44,49,53,46,50,53,48,54,57,32,99,32,52,46,48,52,57,54,50,
44,45,55,46,55,52,51,49,50,32,49,52,46,48,49,57,48,56,44,45,50,54,46,55,52,56,57,54,32,50,50,46,49,53,52,51,56,44,45,52,50,46,50,51,53,50,32,108,32,49,52,46,55,57,49,52,51,44,45,50,56,46,49,53,54,56,48,
54,32,49,50,46,56,57,57,53,52,44,45,51,46,50,53,48,57,57,57,32,99,32,55,46,48,57,52,55,52,44,45,49,46,55,56,56,48,53,32,49,51,46,52,49,44,45,51,46,49,52,53,54,49,32,49,52,46,48,51,51,57,49,44,45,51,46,
48,49,54,56,32,48,46,57,50,54,57,50,44,48,46,49,57,49,51,54,56,32,45,54,53,46,55,52,57,52,44,56,53,46,53,48,49,48,55,53,32,45,54,57,46,57,55,52,50,52,44,56,57,46,53,50,57,50,55,53,32,45,48,46,54,57,55,
51,56,44,48,46,54,54,52,57,49,32,50,46,48,52,53,51,55,44,45,53,46,49,50,54,51,53,32,54,46,48,57,52,57,56,44,45,49,50,46,56,54,57,52,55,32,122,32,77,32,52,55,46,55,51,53,49,48,51,44,49,51,53,46,57,50,49,
55,51,32,67,32,50,57,46,48,53,53,48,53,49,44,49,49,49,46,50,51,55,48,57,32,49,51,46,57,56,57,57,54,57,44,57,48,46,56,50,49,57,55,32,49,52,46,50,53,55,49,52,53,44,57,48,46,53,53,52,55,57,53,32,99,32,48,
46,50,54,55,49,55,53,44,45,48,46,50,54,55,49,55,52,32,53,46,57,51,54,54,57,52,44,48,46,57,57,57,48,49,57,32,49,50,46,53,57,56,57,51,49,44,50,46,56,49,51,55,54,53,32,108,32,49,50,46,49,49,51,49,53,57,44,
51,46,50,57,57,53,51,56,32,56,46,57,49,54,57,51,49,44,49,55,46,49,56,57,55,49,50,32,99,32,49,56,46,51,54,52,57,53,57,44,51,53,46,52,48,51,50,52,32,51,52,46,52,53,57,51,55,57,44,54,54,46,57,54,54,53,53,
32,51,52,46,49,52,49,52,56,51,44,54,54,46,57,53,54,32,45,48,46,49,56,48,56,52,55,44,45,48,46,48,48,54,32,45,49,53,46,54,49,50,52,57,50,44,45,50,48,46,50,48,55,52,52,32,45,51,52,46,50,57,50,53,52,54,44,
45,52,52,46,56,57,50,48,56,32,122,32,77,32,55,50,46,49,52,53,54,51,53,44,57,51,46,53,56,55,54,53,53,32,67,32,54,48,46,50,53,52,52,49,51,44,57,50,46,49,57,50,54,48,57,32,53,48,46,51,52,55,50,49,50,44,57,
48,46,56,57,55,51,55,55,32,53,48,46,49,50,57,54,51,50,44,57,48,46,55,48,57,51,54,50,32,52,57,46,55,49,53,52,50,51,44,57,48,46,51,53,49,52,51,52,32,53,55,46,55,50,56,50,53,49,44,56,49,46,50,52,56,48,49,
51,32,55,48,46,50,57,54,56,57,51,44,54,55,46,55,57,55,50,49,54,32,108,32,55,46,52,50,49,52,49,49,44,45,55,46,57,52,50,50,57,55,32,49,48,46,55,56,57,50,54,55,44,49,55,46,55,55,51,48,50,50,32,99,32,53,46,
57,51,52,48,57,55,44,57,46,55,55,53,49,54,49,32,49,48,46,55,56,57,50,54,56,44,49,55,46,57,56,55,53,50,53,32,49,48,46,55,56,57,50,54,56,44,49,56,46,50,52,57,54,57,55,32,48,44,48,46,55,53,56,51,54,54,32,
45,52,46,49,53,51,51,49,50,44,48,46,52,48,56,48,54,55,32,45,50,55,46,49,53,49,50,48,52,44,45,50,46,50,56,57,57,56,51,32,122,32,77,32,49,50,52,46,49,48,48,51,57,44,56,48,46,53,49,54,49,49,51,32,99,32,53,
46,51,52,50,54,44,45,56,46,55,49,49,48,49,32,49,48,46,52,51,50,49,53,44,45,49,55,46,48,55,57,53,50,32,49,49,46,51,49,48,49,51,44,45,49,56,46,53,57,54,54,56,57,32,48,46,56,55,55,57,56,44,45,49,46,53,49,
55,49,54,56,32,49,46,56,57,53,52,53,44,45,50,46,54,52,56,52,54,56,32,50,46,50,54,49,48,52,44,45,50,46,53,49,52,32,49,46,54,53,57,51,54,44,48,46,54,49,48,51,50,56,32,50,55,46,57,52,50,53,53,44,51,50,46,
57,50,55,52,52,52,32,50,54,46,55,56,53,54,51,44,51,50,46,57,51,52,57,48,57,32,45,48,46,55,49,55,54,44,48,46,48,48,52,54,32,45,49,48,46,56,48,55,54,54,44,48,46,57,48,53,56,56,50,32,45,50,50,46,52,50,50,
51,53,44,50,46,48,48,50,55,56,49,32,45,49,49,46,54,49,52,54,56,44,49,46,48,57,54,57,32,45,50,50,46,53,56,55,44,49,46,57,57,56,49,53,49,32,45,50,52,46,51,56,50,57,51,44,50,46,48,48,50,55,56,49,32,108,32,
45,51,46,50,54,53,51,52,44,48,46,48,48,56,52,32,122,32,77,32,57,53,46,56,48,57,57,53,53,44,55,53,46,54,55,54,55,56,57,32,99,32,45,53,46,57,52,48,54,57,55,44,45,57,46,55,49,51,52,32,45,49,48,46,53,57,52,
50,50,52,44,45,49,55,46,56,54,55,55,55,32,45,49,48,46,51,52,49,49,55,49,44,45,49,56,46,49,50,48,56,50,52,32,48,46,50,53,51,48,53,52,44,45,48,46,50,53,51,48,53,52,32,49,48,46,50,53,57,52,57,44,45,48,46,
51,51,55,57,53,55,32,50,50,46,50,51,54,53,50,54,44,45,48,46,49,56,56,54,55,53,32,108,32,50,49,46,55,55,54,52,51,44,48,46,50,55,49,52,50,50,32,45,49,48,46,56,49,56,54,53,44,49,55,46,56,50,52,51,55,55,32,
99,32,45,53,46,57,53,48,50,54,44,57,46,56,48,51,52,48,55,32,45,49,49,46,48,57,54,49,51,44,49,55,46,56,51,53,54,51,55,32,45,49,49,46,52,51,53,50,53,44,49,55,46,56,52,57,52,48,49,32,45,48,46,51,51,57,49,
52,44,48,46,48,49,51,55,55,32,45,53,46,52,55,55,49,57,44,45,55,46,57,50,50,51,48,51,32,45,49,49,46,52,49,55,56,56,53,44,45,49,55,46,54,51,53,55,48,49,32,122,32,109,32,55,57,46,50,57,56,55,56,53,44,45,
52,46,52,54,48,53,52,32,99,32,48,46,52,57,50,48,56,44,45,49,48,46,53,48,57,53,56,54,32,49,46,49,55,48,56,54,44,45,49,57,46,48,55,57,53,55,57,32,49,46,53,48,56,52,44,45,49,57,46,48,52,52,52,51,32,48,46,
56,55,53,54,50,44,48,46,48,57,49,49,56,32,50,54,46,55,55,56,55,55,44,51,48,46,49,54,50,49,51,56,32,50,54,46,54,54,52,53,53,44,51,48,46,57,53,52,56,52,49,32,45,48,46,48,56,53,44,48,46,53,56,57,57,54,53,
32,45,50,53,46,54,48,57,56,44,55,46,49,49,53,49,57,57,32,45,50,56,46,48,54,50,48,52,44,55,46,49,55,51,56,54,55,32,45,48,46,54,54,54,54,44,48,46,48,49,53,57,53,32,45,48,46,55,48,51,57,57,44,45,54,46,52,
49,55,54,51,54,32,45,48,46,49,49,48,57,49,44,45,49,57,46,48,56,52,50,55,56,32,122,32,77,32,50,50,46,52,57,51,57,48,57,44,56,52,46,55,49,56,53,51,32,99,32,45,54,46,53,54,55,57,52,54,44,45,49,46,56,53,48,
54,54,56,32,45,49,50,46,48,54,54,55,54,52,44,45,51,46,52,57,54,55,51,57,32,45,49,50,46,50,49,57,53,57,54,44,45,51,46,54,53,55,57,51,52,32,45,48,46,49,53,50,56,51,50,44,45,48,46,49,54,49,49,57,53,32,53,
46,50,50,48,57,52,49,44,45,54,46,54,54,57,55,57,53,32,49,49,46,57,52,49,55,50,44,45,49,52,46,52,54,51,53,53,52,32,56,46,57,52,54,55,56,56,44,45,49,48,46,51,55,53,49,53,54,32,49,50,46,51,56,53,53,49,49,
44,45,49,51,46,55,52,49,56,49,51,32,49,50,46,56,51,57,48,54,57,44,45,49,50,46,53,55,32,48,46,51,52,48,55,49,44,48,46,56,56,48,50,53,57,32,48,46,57,50,53,48,56,54,44,55,46,55,48,57,52,57,49,32,49,46,50,
57,56,54,49,52,44,49,53,46,49,55,54,48,55,49,32,48,46,51,55,51,53,50,55,44,55,46,52,54,54,53,56,32,48,46,57,50,50,54,51,44,49,52,46,56,50,48,48,51,49,32,49,46,50,50,48,50,50,55,44,49,54,46,51,52,49,48,
48,49,32,48,46,54,56,56,54,54,54,44,51,46,53,49,57,54,53,50,32,48,46,50,53,55,49,57,50,44,51,46,52,57,54,48,51,49,32,45,49,53,46,48,56,48,48,51,52,44,45,48,46,56,50,53,53,56,52,32,122,32,77,32,52,52,46,
54,54,51,50,50,44,56,50,46,54,50,56,53,52,32,67,32,52,52,46,51,55,49,49,55,50,44,56,49,46,54,48,52,57,55,53,32,52,51,46,56,50,48,51,48,57,44,55,51,46,56,50,50,48,56,55,32,52,51,46,52,51,57,48,56,44,54,
53,46,51,51,51,50,51,52,32,52,50,46,55,54,54,54,53,55,44,53,48,46,51,54,48,51,49,55,32,52,50,46,56,48,51,49,57,44,52,57,46,57,50,57,53,57,53,32,52,52,46,54,54,49,50,50,57,44,53,48,46,57,50,51,57,56,56,
32,99,32,50,46,52,53,55,51,54,56,44,49,46,51,49,53,49,52,51,32,49,55,46,54,49,52,49,52,57,44,52,46,50,48,48,55,50,52,32,50,50,46,48,54,52,54,57,49,44,52,46,50,48,48,55,50,52,32,49,46,56,55,52,54,56,52,
44,48,32,51,46,52,48,56,53,49,52,44,48,46,52,57,53,53,49,56,32,51,46,52,48,56,53,49,52,44,49,46,49,48,49,49,52,57,32,48,44,48,46,54,48,53,54,51,51,32,45,53,46,50,55,54,49,55,44,54,46,56,50,55,55,56,51,
32,45,49,49,46,55,50,52,56,50,51,44,49,51,46,56,50,55,48,48,49,32,45,54,46,52,52,56,54,53,51,44,54,46,57,57,57,50,49,57,32,45,49,50,46,48,54,48,50,48,50,44,49,51,46,49,49,48,55,57,51,32,45,49,50,46,52,
55,48,49,48,56,44,49,51,46,53,56,49,50,55,56,32,45,48,46,52,48,57,57,48,56,44,48,46,52,55,48,52,56,53,32,45,48,46,57,56,52,50,51,52,44,48,46,48,49,55,57,55,32,45,49,46,50,55,54,50,56,51,44,45,49,46,48,
48,53,54,32,122,32,109,32,49,49,49,46,49,51,52,49,49,44,45,49,51,46,52,57,51,51,54,32,45,49,49,46,51,55,55,53,50,44,45,49,51,46,53,48,55,54,54,56,32,53,46,51,52,51,57,50,44,45,48,46,56,53,49,57,53,57,
32,99,32,50,46,57,51,57,49,53,44,45,48,46,52,54,56,53,55,57,32,56,46,51,57,56,52,51,44,45,49,46,54,52,57,50,54,51,32,49,50,46,49,51,49,55,50,44,45,50,46,54,50,51,55,52,52,32,108,32,54,46,55,56,55,56,44,
45,49,46,55,55,49,55,56,53,32,45,48,46,49,49,56,49,50,44,54,46,49,52,51,51,52,52,32,99,32,45,48,46,48,54,53,44,51,46,51,55,56,56,51,57,32,45,48,46,52,48,52,51,53,44,49,48,46,54,51,55,57,55,53,32,45,48,
46,55,53,52,50,44,49,54,46,49,51,49,52,49,50,32,108,32,45,48,46,54,51,54,48,56,44,57,46,57,56,56,48,54,54,32,122,32,77,32,56,49,46,54,57,56,56,51,54,44,52,57,46,52,54,50,57,50,50,32,99,32,45,49,55,46,
53,48,51,48,50,44,45,49,46,53,52,57,49,48,56,32,45,51,52,46,48,49,52,44,45,52,46,51,53,54,57,55,56,32,45,51,55,46,54,55,56,49,48,52,44,45,54,46,52,48,55,53,54,55,32,45,49,46,50,53,48,49,51,51,44,45,48,
46,54,57,57,54,50,56,32,45,49,46,48,51,54,52,56,50,44,45,49,46,48,53,51,53,55,52,32,49,46,49,51,52,49,50,55,44,45,49,46,56,55,56,56,53,52,32,52,46,53,50,55,55,57,57,44,45,49,46,55,50,49,52,57,57,32,49,
54,46,57,50,54,54,48,51,44,45,51,46,57,57,52,48,55,57,32,50,55,46,56,53,49,53,50,52,44,45,53,46,49,48,52,57,49,50,32,49,51,46,53,48,48,53,57,57,44,45,49,46,51,55,50,55,50,52,32,53,49,46,48,50,50,51,55,
55,44,45,49,46,51,54,49,48,50,55,32,54,53,46,48,56,50,56,48,55,44,48,46,48,50,48,50,57,32,49,48,46,54,51,53,53,55,44,49,46,48,52,52,56,53,52,32,50,56,46,51,48,56,50,55,44,52,46,51,52,52,54,52,49,32,50,
57,46,52,54,53,50,56,44,53,46,53,48,49,54,53,57,32,49,46,54,49,50,53,44,49,46,54,49,50,53,48,50,32,45,57,46,48,57,51,57,50,44,52,46,53,50,50,52,54,55,32,45,50,52,46,48,49,49,50,50,44,54,46,53,50,54,49,
53,54,32,45,56,46,49,56,57,54,55,44,49,46,49,48,48,48,51,53,32,45,53,51,46,52,55,56,50,50,57,44,50,46,48,56,51,54,55,56,32,45,54,49,46,56,52,52,52,49,52,44,49,46,51,52,51,50,50,56,32,122,34,10,32,32,32,
32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,53,48,48,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,111,114,45,99,117,114,118,97,116,117,114,101,61,34,
48,34,32,47,62,10,32,32,32,32,32,32,60,112,97,116,104,10,32,32,32,32,32,32,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,97,97,101,102,102,102,59,102,105,108,108,45,111,112,97,99,105,116,121,
58,49,59,115,116,114,111,107,101,45,119,105,100,116,104,58,49,46,48,48,53,54,48,48,48,57,34,10,32,32,32,32,32,32,32,32,32,100,61,34,77,32,55,53,46,51,55,55,48,55,55,44,49,53,48,46,53,50,52,56,55,32,67,
32,54,48,46,56,51,56,53,48,57,44,49,50,50,46,50,52,54,51,56,32,52,57,46,48,55,50,57,56,55,44,57,56,46,57,55,57,56,55,54,32,52,57,46,50,51,49,52,55,52,44,57,56,46,56,50,49,53,51,50,32,99,32,48,46,51,55,
53,48,53,51,44,45,48,46,51,55,52,55,49,53,32,53,49,46,49,51,56,56,56,54,44,53,46,53,49,54,53,55,56,32,53,50,46,57,55,50,56,50,54,44,54,46,49,52,55,54,54,56,32,49,46,49,53,56,53,53,44,48,46,51,57,56,54,
54,32,49,46,50,56,55,54,51,44,51,46,54,51,50,52,49,32,48,46,55,53,48,56,52,44,49,56,46,56,49,48,54,55,32,45,48,46,51,53,54,53,51,44,49,48,46,48,56,49,48,56,32,45,48,46,55,49,48,54,52,44,51,49,46,55,57,
49,55,50,32,45,48,46,55,56,54,57,50,44,52,56,46,50,52,53,56,53,32,45,48,46,48,55,54,51,44,49,54,46,52,53,52,49,51,32,45,48,46,49,56,55,56,56,44,50,57,46,57,49,54,49,53,32,45,48,46,50,52,56,48,51,44,50,
57,46,57,49,53,54,32,45,48,46,48,54,48,49,44,45,53,46,53,101,45,52,32,45,49,50,46,48,48,52,53,52,52,44,45,50,51,46,49,51,55,57,53,32,45,50,54,46,53,52,51,49,49,51,44,45,53,49,46,52,49,54,52,53,32,122,
32,109,32,51,52,46,57,57,57,57,49,51,44,49,56,46,54,52,52,54,53,32,99,32,45,48,46,48,49,48,50,44,45,49,55,46,49,57,53,52,50,32,48,46,50,55,53,56,57,44,45,51,56,46,55,51,48,49,50,32,48,46,54,51,53,55,54,
44,45,52,55,46,56,53,52,57,32,108,32,48,46,54,53,52,51,50,44,45,49,54,46,53,57,48,53,32,49,52,46,49,55,56,50,57,44,45,49,46,49,57,52,51,55,32,99,32,55,46,55,57,56,48,53,44,45,48,46,54,53,54,57,49,32,49,
57,46,49,49,49,55,57,44,45,49,46,54,52,49,53,56,32,50,53,46,49,52,49,54,51,44,45,50,46,49,56,56,49,54,32,54,46,48,50,57,56,52,44,45,48,46,53,52,54,53,56,32,49,49,46,49,52,57,54,57,44,45,48,46,56,48,55,
52,52,32,49,49,46,51,55,55,52,53,44,45,48,46,53,55,57,54,57,32,48,46,51,53,51,57,50,44,48,46,51,53,51,57,51,32,45,51,52,46,53,48,51,52,50,44,54,55,46,52,51,56,51,50,32,45,52,55,46,54,48,57,57,49,44,57,
49,46,54,50,55,50,50,32,108,32,45,52,46,51,53,56,57,56,44,56,46,48,52,52,56,32,45,48,46,48,49,56,54,44,45,51,49,46,50,54,52,52,32,122,32,109,32,50,52,46,56,55,49,55,55,44,49,46,53,57,57,50,32,99,32,50,
46,55,56,48,50,56,44,45,53,46,50,53,52,50,54,32,49,50,46,49,54,53,55,44,45,50,51,46,49,50,56,56,32,50,48,46,56,53,54,53,44,45,51,57,46,55,50,49,50,32,56,46,54,57,48,56,44,45,49,54,46,53,57,50,52,49,32,
49,54,46,51,50,48,54,49,44,45,51,48,46,54,55,50,56,51,32,49,54,46,57,53,53,49,51,44,45,51,49,46,50,56,57,56,51,50,32,49,46,49,51,57,55,56,44,45,49,46,49,48,56,51,51,49,32,50,53,46,57,51,56,55,44,45,55,
46,54,49,51,49,51,55,32,50,54,46,53,55,57,56,56,44,45,54,46,57,55,49,57,53,57,32,48,46,51,52,48,56,49,44,48,46,51,52,48,56,49,32,45,54,53,46,49,54,56,51,56,44,56,51,46,51,49,57,57,54,49,32,45,54,55,46,
57,49,53,57,57,44,56,54,46,48,50,55,55,57,49,32,45,48,46,56,52,49,56,49,44,48,46,56,50,57,54,50,32,48,46,55,52,52,50,49,44,45,50,46,55,57,48,53,52,32,51,46,53,50,52,52,56,44,45,56,46,48,52,52,56,32,122,
32,77,32,52,54,46,50,51,51,56,57,49,44,49,51,51,46,51,49,48,49,50,32,67,32,50,56,46,53,48,50,54,53,57,44,49,48,57,46,57,52,50,52,56,32,49,52,46,49,48,50,56,53,50,44,57,48,46,55,49,52,52,48,52,32,49,52,
46,50,51,52,51,50,49,44,57,48,46,53,56,49,48,53,32,99,32,48,46,49,51,49,52,54,57,44,45,48,46,49,51,51,51,53,54,32,53,46,54,51,53,53,56,54,44,49,46,50,53,53,53,55,52,32,49,50,46,50,51,49,51,55,50,44,51,
46,48,56,54,53,49,32,108,32,49,49,46,57,57,50,51,51,55,44,51,46,51,50,56,57,55,55,32,51,46,56,50,53,49,54,51,44,54,46,57,54,57,52,56,51,32,99,32,54,46,49,57,56,52,57,49,44,49,49,46,50,57,51,55,51,32,51,
55,46,48,52,49,50,54,50,44,55,49,46,56,51,48,55,32,51,54,46,53,57,54,55,54,57,44,55,49,46,56,51,48,55,32,45,48,46,50,50,52,49,48,54,44,48,32,45,49,52,46,57,49,52,56,51,56,44,45,49,57,46,49,49,56,57,55,
32,45,51,50,46,54,52,54,48,55,49,44,45,52,50,46,52,56,54,54,32,122,32,77,32,55,51,46,54,53,52,48,51,53,44,57,51,46,50,54,50,53,52,49,32,67,32,54,48,46,57,51,51,49,57,51,44,57,49,46,55,48,48,56,50,52,32,
53,48,46,51,56,57,52,56,50,44,57,48,46,52,48,48,48,50,56,32,53,48,46,50,50,51,53,54,55,44,57,48,46,51,55,49,56,56,52,32,99,32,45,48,46,52,55,55,48,56,53,44,45,48,46,48,56,48,57,51,32,50,54,46,48,57,54,
48,57,50,44,45,50,56,46,54,55,54,56,50,51,32,50,54,46,57,53,54,49,55,44,45,50,57,46,48,48,56,48,52,51,32,48,46,52,50,52,53,53,57,44,45,48,46,49,54,51,52,57,56,32,52,46,57,56,49,57,54,55,44,54,46,54,50,
52,51,48,50,32,49,48,46,49,50,55,53,55,52,44,49,53,46,48,56,52,48,48,49,32,53,46,49,52,53,54,48,55,44,56,46,52,53,57,55,32,49,48,46,48,48,48,51,49,55,44,49,54,46,51,57,57,52,52,50,32,49,48,46,55,56,56,
50,52,51,44,49,55,46,54,52,51,56,55,50,32,49,46,49,56,56,57,54,49,44,49,46,56,55,55,56,49,52,32,49,46,49,57,57,49,53,52,44,50,46,50,52,49,49,52,56,32,48,46,48,53,57,57,52,44,50,46,49,51,54,52,53,56,32,
45,48,46,55,53,52,57,54,54,44,45,48,46,48,54,57,51,56,32,45,49,49,46,55,56,48,54,50,49,44,45,49,46,52,48,51,57,49,51,32,45,50,52,46,53,48,49,52,54,51,44,45,50,46,57,54,53,54,51,49,32,122,32,77,32,49,49,
53,46,51,56,54,52,52,44,57,53,46,57,55,57,32,99,32,48,44,45,49,46,49,50,56,55,56,50,32,50,49,46,53,50,52,50,44,45,51,53,46,56,50,54,50,56,55,32,50,50,46,50,50,52,52,51,44,45,51,53,46,56,50,54,50,56,55,
32,49,46,52,56,53,50,44,48,32,50,55,46,50,52,56,57,49,44,51,49,46,54,56,55,54,51,57,32,50,53,46,57,50,56,57,52,44,51,49,46,56,57,48,56,54,49,32,45,48,46,55,54,54,49,51,44,48,46,49,49,55,57,53,51,32,45,
57,46,55,54,52,53,56,44,48,46,57,50,53,52,49,49,32,45,49,57,46,57,57,54,53,54,44,49,46,55,57,52,51,53,50,32,45,49,48,46,50,51,49,57,57,44,48,46,56,54,56,57,52,32,45,50,48,46,55,53,51,48,56,44,49,46,56,
52,56,57,48,50,32,45,50,51,46,51,56,48,50,49,44,50,46,49,55,55,54,57,50,32,45,50,46,54,50,55,49,51,44,48,46,51,50,56,55,57,32,45,52,46,55,55,54,54,44,48,46,51,49,50,51,49,50,32,45,52,46,55,55,54,54,44,
45,48,46,48,51,54,54,49,32,122,32,77,32,57,55,46,50,56,53,54,51,56,44,55,55,46,53,52,55,51,57,50,32,67,32,57,50,46,48,51,49,51,55,56,44,54,56,46,56,56,49,53,52,51,32,56,55,46,50,49,49,57,48,57,44,54,48,
46,56,53,54,57,54,57,32,56,54,46,53,55,53,55,48,57,44,53,57,46,55,49,53,48,48,56,32,56,53,46,52,50,50,54,53,49,44,53,55,46,54,52,53,50,57,57,32,56,53,46,52,56,56,51,52,56,44,53,55,46,54,51,56,54,56,57,
32,49,48,55,46,50,56,54,48,55,44,53,55,46,54,51,49,53,49,49,32,108,32,50,49,46,56,54,55,49,44,45,48,46,48,48,55,50,32,45,55,46,55,51,54,49,51,44,49,50,46,53,55,55,50,48,51,32,99,32,45,49,51,46,51,48,48,
50,44,50,49,46,54,50,51,49,53,49,32,45,49,52,46,50,52,51,54,54,44,50,51,46,49,51,54,52,55,56,32,45,49,52,46,52,49,51,48,53,44,50,51,46,49,49,57,48,50,52,32,45,48,46,48,57,48,56,44,45,48,46,48,48,57,52,
32,45,52,46,52,54,52,48,57,44,45,55,46,49,48,55,50,53,54,32,45,57,46,55,49,56,51,53,50,44,45,49,53,46,55,55,51,49,48,54,32,122,32,109,32,55,55,46,57,54,52,55,57,50,44,45,49,46,48,51,53,57,57,55,32,99,
32,48,46,52,48,50,57,49,44,45,55,46,53,50,50,53,53,49,32,49,46,48,49,51,51,50,44,45,49,53,46,56,54,51,54,54,54,32,49,46,51,53,54,52,57,44,45,49,56,46,53,51,53,56,48,57,32,108,32,48,46,54,50,51,57,51,44,
45,52,46,56,53,56,52,52,51,32,49,50,46,57,49,57,54,54,44,49,52,46,54,52,56,55,50,51,32,99,32,55,46,49,48,53,56,50,44,56,46,48,53,54,55,57,56,32,49,50,46,54,56,56,52,52,44,49,52,46,56,55,57,57,53,32,49,
50,46,52,48,53,56,51,44,49,53,46,49,54,50,53,54,49,32,45,48,46,53,50,53,56,44,48,46,53,50,53,56,48,53,32,45,49,48,46,50,54,49,48,53,44,51,46,49,50,49,54,57,54,32,45,50,49,46,54,53,51,57,55,44,53,46,55,
55,52,48,48,54,32,108,32,45,54,46,51,56,52,52,57,44,49,46,52,56,54,51,50,56,32,122,32,77,32,50,52,46,56,52,57,52,57,54,44,56,52,46,56,50,57,55,57,57,32,67,32,49,56,46,52,55,48,57,54,50,44,56,51,46,48,
52,52,51,54,55,32,49,50,46,54,53,48,53,57,44,56,49,46,51,56,51,48,51,53,32,49,49,46,57,49,53,51,51,52,44,56,49,46,49,51,55,57,52,57,32,49,49,46,48,54,55,51,54,57,44,56,48,46,56,53,53,50,57,52,32,49,52,
46,57,48,50,55,57,53,44,55,53,46,54,52,50,52,56,50,32,50,50,46,52,48,51,53,52,44,54,54,46,56,56,51,49,57,57,32,50,56,46,57,48,55,51,48,57,44,53,57,46,50,56,56,49,55,50,32,51,52,46,51,57,50,53,54,49,44,
53,51,46,50,51,56,48,52,53,32,51,52,46,53,57,50,57,56,56,44,53,51,46,52,51,56,52,55,50,32,99,32,48,46,53,48,51,55,54,56,44,48,46,53,48,51,55,54,54,32,50,46,53,56,49,56,50,54,44,51,50,46,55,49,52,56,51,
54,32,50,46,49,55,57,49,54,56,44,51,51,46,55,55,56,51,50,51,32,45,48,46,49,55,56,57,50,57,44,48,46,52,55,50,53,56,51,32,45,53,46,53,52,52,49,50,55,44,45,48,46,54,48,49,53,54,52,32,45,49,49,46,57,50,50,
54,54,44,45,50,46,51,56,54,57,57,54,32,122,32,109,32,49,57,46,55,57,50,53,49,53,44,45,57,46,51,53,55,55,49,54,32,99,32,45,50,46,49,51,56,51,44,45,50,55,46,49,48,54,53,56,52,32,45,50,46,49,51,52,49,44,
45,50,52,46,55,55,49,55,51,57,32,45,48,46,48,52,51,48,52,44,45,50,51,46,57,50,48,50,49,57,32,49,46,57,48,50,51,57,56,44,48,46,55,55,52,54,57,51,32,50,49,46,56,48,57,55,54,53,44,52,46,52,56,55,48,56,54,
32,50,52,46,51,56,50,48,50,49,44,52,46,53,52,54,56,52,49,32,49,46,51,48,48,57,49,44,48,46,48,51,48,50,50,32,45,51,46,48,54,52,49,52,55,44,53,46,50,54,48,50,57,55,32,45,49,55,46,50,49,56,50,53,56,44,50,
48,46,54,51,48,51,55,56,32,108,32,45,54,46,52,54,55,53,52,55,44,55,46,48,50,51,49,55,32,45,48,46,54,53,51,49,56,44,45,56,46,50,56,48,49,55,32,122,32,77,32,49,53,53,46,56,54,49,56,53,44,54,56,46,54,56,
50,50,56,54,32,99,32,45,53,46,54,54,57,48,55,44,45,54,46,55,54,54,55,54,53,32,45,49,48,46,51,48,55,52,44,45,49,50,46,53,56,53,52,52,32,45,49,48,46,51,48,55,52,44,45,49,50,46,57,51,48,51,57,49,32,48,44,
45,48,46,51,52,52,57,53,32,49,46,50,52,52,52,51,44,45,48,46,54,51,53,48,52,32,50,46,55,54,53,52,44,45,48,46,54,52,52,54,52,52,32,50,46,54,51,55,53,49,44,45,48,46,48,49,54,54,53,32,49,52,46,53,55,54,49,
50,44,45,50,46,51,48,51,54,53,56,32,49,56,46,52,53,57,51,50,44,45,51,46,53,51,54,49,51,54,32,49,46,55,50,57,50,56,44,45,48,46,53,52,56,56,53,52,32,49,46,56,48,50,49,53,44,48,46,49,48,57,57,50,50,32,49,
46,50,52,56,56,53,44,49,49,46,50,56,57,57,54,55,32,45,49,46,48,49,54,56,57,44,50,48,46,53,52,55,54,49,51,32,45,48,46,49,54,56,54,55,44,50,48,46,49,52,49,55,54,51,32,45,49,50,46,49,54,54,49,55,44,53,46,
56,50,49,50,48,52,32,122,32,77,32,56,52,46,50,49,50,56,51,54,44,52,57,46,48,49,52,48,50,51,32,99,32,45,49,57,46,53,55,53,49,48,55,44,45,49,46,49,51,49,51,51,52,32,45,52,49,46,48,49,57,51,54,50,44,45,52,
46,56,54,49,54,53,32,45,51,57,46,55,53,48,52,55,44,45,54,46,57,49,52,55,54,32,48,46,54,55,52,55,56,51,44,45,49,46,48,57,49,56,50,50,32,49,50,46,54,57,57,50,52,44,45,51,46,55,48,50,51,57,52,32,50,51,46,
54,54,48,56,54,56,44,45,53,46,49,51,54,56,57,53,32,49,49,46,51,48,56,52,48,51,44,45,49,46,52,55,57,56,56,52,32,53,52,46,51,48,52,51,51,54,44,45,50,46,48,54,49,53,57,54,32,54,54,46,51,54,57,54,48,54,44,
45,48,46,56,57,55,57,52,55,32,49,50,46,51,57,56,50,53,44,49,46,49,57,53,55,54,51,32,50,49,46,50,56,56,53,51,44,50,46,54,54,49,54,56,49,32,50,56,46,49,53,54,56,49,44,52,46,54,52,50,55,55,53,32,108,32,53,
46,53,51,48,56,44,49,46,53,57,53,51,49,32,45,51,46,54,53,57,52,52,44,49,46,50,57,49,56,51,56,32,99,32,45,54,46,52,52,56,49,54,44,50,46,50,55,54,50,57,57,32,45,50,50,46,48,49,48,57,50,44,52,46,52,50,54,
53,53,52,32,45,51,57,46,53,56,49,51,55,44,53,46,52,54,56,56,50,57,32,45,49,56,46,54,55,56,52,50,44,49,46,49,48,56,32,45,50,48,46,55,52,56,50,49,44,49,46,49,48,53,53,48,50,32,45,52,48,46,55,50,54,56,48,
52,44,45,48,46,48,52,57,49,53,32,122,34,10,32,32,32,32,32,32,32,32,32,105,100,61,34,112,97,116,104,52,52,57,56,34,10,32,32,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,111,110,110,101,99,116,
111,114,45,99,117,114,118,97,116,117,114,101,61,34,48,34,32,47,62,10,32,32,32,32,60,47,103,62,10,32,32,60,47,103,62,10,60,47,115,118,103,62,10,0,0};

const char* BalanceComponent::diamond_svg = (const char*) resource_BalanceComponent_diamond_svg;
const int BalanceComponent::diamond_svgSize = 13898;


//[EndFile] You can add extra defines here...
//[/EndFile]
