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
#define SHOUT_ADDRESS "HotWallet"
#define SHOUT_PREFIX "Shout: "
//[/Headers]

#include "ShoutComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ShoutComponent::ShoutComponent ()
    : Thread("ShoutComponent")
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (textButton = new TextButton ("new button"));
    textButton->setButtonText (TRANS("shout"));
    textButton->addListener (this);
    textButton->setColour (TextButton::buttonColourId, Colour (0x0077b517));
    textButton->setColour (TextButton::buttonOnColourId, Colour (0xff77b517));
    textButton->setColour (TextButton::textColourOffId, Colours::white);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	timerDelay = 0;
	totalShowTime = 0;
	totalShowTimeLoop = 60;
	totalAmountNQTs = 0;
	startTimer(100);

    //[/Constructor]
}

ShoutComponent::~ShoutComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	stopThread(5000);
    //[/Destructor_pre]

    textButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ShoutComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff343434));

    //[UserPaint] Add your own custom painting code here..
	{
		const ScopedTryLock lock(shoutsLock);
		if (lock.isLocked())
		{
			int si = 0;
			float rate = (1000.f / getTimerInterval());
			bool drawn = false;
			for (int i = 0; i < shouts.size(); i++)
			{
				if (timerDelay >= si &&
					timerDelay < si + (int)(shouts[i].showtime * rate) && drawn == false)
				{
					drawn = true;
					g.setColour(Colours::white);
					g.drawText(shouts[i].message, getBounds().withZeroOrigin().withTrimmedLeft(5).withTrimmedRight(135).toFloat(), Justification::centredLeft);

					g.setColour(Colours::dimgrey);
					float frac = (timerDelay - si) / (float)(shouts[i].showtime * rate);
					g.fillRect(getBounds().withHeight(3).withTrimmedRight(100 + ((getWidth() - 100) * frac)).withZeroOrigin().toFloat());

				//	g.drawText(String((int)(shouts[i].showtime * rate) - (timerDelay - si)), getBounds().withZeroOrigin().withTrimmedLeft(5).withTrimmedRight(105).toFloat(), Justification::centredRight);
				}
				si += (int)shouts[i].showtime * rate;
			}
		}
	}
    //[/UserPaint]
}

void ShoutComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	/*
    //[/UserPreResize]

    textButton->setBounds (408, 0, 78, 24);
    //[UserResized] Add your own custom resize handling here..
	*/
	textButton->setBounds(getWidth() - 100, 5, 94, getHeight() - 10);
    //[/UserResized]
}

void ShoutComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButton)
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
		uint64 total = 0;
		{
			const ScopedLock lock(shoutsLock);
			total = totalAmountNQTs;
		}
		ScopedPointer<PopupMenu> contextMenu;
		contextMenu = new PopupMenu;

		contextMenu->addItem(10, "The shout price is based on the usage", false);
		String amount;
		if (total <= 0)
		{
			contextMenu->addItem(1, "FREE shout ! Get the full 60 seconds !", true);
		//	amount = "0";
		}
		else
		{
			contextMenu->addItem(2, "Buy " + String((int)(totalShowTime * 0.1)) + " sec (24h) for " + String((total / 100000000.) * 0.2, 2) + " BURST", true);
			contextMenu->addItem(3, "Buy " + String((int)(totalShowTime * 0.25)) + " sec (24h) for " + String((total / 100000000.) * 0.5, 2) + " BURST", true);
			contextMenu->addItem(4, "Buy " + String((int)(totalShowTime * 0.5)) + " sec (24h) for " + String((total / 100000000.), 2) + " BURST", true);

		}
		int result = contextMenu->show();
		if (result == 1)
			amount = "0";
		if (result == 2)
			amount = String((int64)(total * 0.2));
		if (result == 3)
			amount = String((int64)(total * 0.5));
		if (result == 4)
			amount = String((int64)(total));

		if (amount.isNotEmpty())
		{
			interfaceListeners.call(&InterfaceListener::SetupTransaction,
				"Shout ! Shout ! Let it all out !",
				SHOUT_ADDRESS, amount, "normal", SHOUT_PREFIX, false);
		}

		contextMenu = nullptr;
        //[/UserButtonCode_textButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

bool ShoutComponent::hitTest (int x, int y)
{
    //[UserCode_hitTest] -- Add your code here...
    return true;
    //[/UserCode_hitTest]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ShoutComponent::SetForceSSL_TSL(const bool forceSSLOn)
{
	const ScopedLock lock(burstExtLock);
	burstExt.SetForceSSL_TSL(forceSSLOn);
}

void ShoutComponent::SetNodeHop(const bool hopOn)
{
	const ScopedLock lock(burstExtLock);
	burstExt.EnableNodeHop(hopOn ? 7 : 0);
}

void ShoutComponent::SetNode(const String server)
{
	stopThread(500);
	const ScopedLock lock(burstExtLock);
	burstExt.SetNode(server);
	startThread();
}

void ShoutComponent::timerCallback()
{
	const ScopedTryLock lock(shoutsLock);
	if (timerDelay++ > totalShowTime * (1000 / getTimerInterval()))
	{
		timerDelay = 0;
		startThread();
	}
	repaint();
}

void ShoutComponent::run()
{
	String account;
	String timestamp;
	{
		const ScopedLock lock(burstExtLock);
		account = (burstExt.ensureAccountRS(SHOUT_ADDRESS)); // is the account ID
		timestamp = String((Time::currentTimeMillis() / 1000) - BURSTCOIN_GENESIS_EPOCH - (60 * 60 * 24)); // is the earliest block(in seconds since the genesis block) to retrieve(optional)
	}

	int freeTokenBase = 10000000; // 0.1 burst
	uint64 alivetimes = 0;
	uint64 amountNQTs = 0;
	Array<shout> compiledShouts;
	if (!threadShouldExit())
	{
		const ScopedLock lock(burstExtLock);
		const String accountTransactions = burstExt.getAccountTransactions(account, timestamp); // , type, subtype, firstIndex, lastIndex, numberOfConfirmations
		const String unconfirmedAccountTransactions = burstExt.getUnconfirmedTransactions(account); // , type, subtype, firstIndex, lastIndex, numberOfConfirmations
		// collect the shouts
		var accountTransactionsJson;

		for (int type = 0; type < 2; type++)
		{
			Result r = JSON::parse((type == 0 ? accountTransactions : unconfirmedAccountTransactions), accountTransactionsJson);
			String arrayName(type == 0 ? "transactions" : "unconfirmedTransactions");

			if (accountTransactionsJson[arrayName.toUTF8()].isArray())
			{
				int freeToken = freeTokenBase;
				for (int i = 0; i < accountTransactionsJson[arrayName.toUTF8()].size() && !threadShouldExit(); i++)
				{
					int index = accountTransactionsJson[arrayName.toUTF8()].size() - 1 - i; // reverse order, bcz free token
					if (accountTransactionsJson[arrayName.toUTF8()][index]["attachment"]["messageIsText"])
					{
						const String amountNQT = accountTransactionsJson[arrayName.toUTF8()][index]["amountNQT"].toString();
						const String message = accountTransactionsJson[arrayName.toUTF8()][index]["attachment"]["message"].toString().trim();
						const String timestamp = accountTransactionsJson[arrayName.toUTF8()][index]["timestamp"].toString();
						if (message.isNotEmpty() && amountNQT.getLargeIntValue() >= freeTokenBase - freeToken)
						{
							shout s;
							s.message = message.startsWith(SHOUT_PREFIX) ? message.substring(String(SHOUT_PREFIX).length()) : message;
							s.amountNQT = (uint64)amountNQT.getLargeIntValue();
							s.alivetime = (Time::currentTimeMillis() / 1000) - ((uint64)timestamp.getLargeIntValue() + BURSTCOIN_GENESIS_EPOCH);

							if (s.amountNQT < freeToken)
							{ // first one below 1 burst gets 1 burst free
								s.amountNQT = freeToken;
								freeToken = 0;
							}

							compiledShouts.add(s);
						}
					}
				}
			}
		}
	}

	int totalShowTimeSum = 0;

	if (compiledShouts.size() > 0 && !threadShouldExit())
	{
		for (int i = 0; i < compiledShouts.size(); i++)
		{
			alivetimes = compiledShouts[i].alivetime;
			amountNQTs += compiledShouts[i].amountNQT;
		}

		for (int i = 0; i < compiledShouts.size(); i++)
		{
			float alive = (float)compiledShouts[i].alivetime;
			float amount = (float)compiledShouts[i].amountNQT;

			float showtime = ((float)totalShowTimeLoop / (float)amountNQTs) * amount;
			compiledShouts.getReference(i).showtime = jmax<float>(showtime, 1.f);

			totalShowTimeSum += compiledShouts[i].showtime;
		}
	}
	else
	{
		shout s;
		s.message = "Reach the community, a FREE blockchain shout space available !";
		s.amountNQT = freeTokenBase;
		s.alivetime = (Time::currentTimeMillis() / 1000) - ((uint64)timestamp.getLargeIntValue() + BURSTCOIN_GENESIS_EPOCH);
		s.showtime = totalShowTimeLoop;

		compiledShouts.add(s);

		amountNQTs = 0;
		totalShowTimeSum = totalShowTimeLoop;
	}

	{
		const ScopedLock lock(shoutsLock);
		totalAmountNQTs = amountNQTs;
		totalShowTime = totalShowTimeSum;
		shouts = compiledShouts;
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ShoutComponent" componentName=""
                 parentClasses="public Component, public Thread, public Timer, public ShoutComponentListener"
                 constructorParams="" variableInitialisers="Thread(&quot;ShoutComponent&quot;)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <METHODS>
    <METHOD name="hitTest (int x, int y)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff343434"/>
  <TEXTBUTTON name="new button" id="b480356a07fca6d6" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="408 0 78 24" bgColOff="77b517"
              bgColOn="ff77b517" textCol="ffffffff" buttonText="shout" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
