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

#ifndef __JUCE_HEADER_88F37D9343714708__
#define __JUCE_HEADER_88F37D9343714708__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "Listeners.h"
#include "./QR-code/JuceQrCodeGenerator.h"

ApplicationProperties& getAppProperties();
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TradeInterfaceComponent  : public Component,
                                 public TradeInterfaceComponentListener,
                                 public ButtonListener,
                                 public ComboBoxListener,
                                 public SliderListener
{
public:
    //==============================================================================
    TradeInterfaceComponent ();
    ~TradeInterfaceComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	String NQT2Burst(const String value, const String decimals);
	String Burst2NQT(const String value, const String decimals);
	uint64 toQT(const String value, const String decimals);

	void NewAsset() override;
	void SetAssetData(const AssetItem asset) override;
	void SetAssetBurstNQT(const uint64 balanceNQT) override;
	void SetRecommendedSellAndBuyPrice(const String buyPrice, const String sellPrice) override;
	void SetBuyOrderItems(Array<OrderItem> buyOrders) override;
	void SetSellOrderItems(Array<OrderItem> sellOrders) override;
	void SetOrder(OrderItem orders) override;
	void CancelAskOrder(String orderID) override;
	void CancelBidOrder(String orderID) override;

	void UpdateTotalBuyLabel(const bool useTotal = false);
	void UpdateTotalSellLabel(const bool useTotal = false);


	void SetUserBurstAddress(String rs, String publicKey)
	{
		accountRS = rs;
		accountPubkey = publicKey;

		buyOrderTableComponent->SetUserBurstAddress(rs);
		sellOrderTableComponent->SetUserBurstAddress(rs);

		qrDrawable = qrCodeGenerator.generateQRpath(rs, 100.f);
	}

	void addTradeComponentListener(TradeComponentListener* const l)      { tradeComponentListeners.add(l); };
	void removeTradeComponentListener(TradeComponentListener* const l)   { tradeComponentListeners.remove(l); };
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

    // Binary resources:
    static const char* burst_logo_white_svg;
    static const int burst_logo_white_svgSize;
    static const char* bursticonblue_svg;
    static const int bursticonblue_svgSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	JuceQrCodeGenerator qrCodeGenerator;
	ScopedPointer<Drawable> qrDrawable;
	String accountRS;
	String accountPubkey;

	uint64 userBalanceNQT = 0;
	AssetItem asset;
	ListenerList <TradeComponentListener> tradeComponentListeners;

	uint64 GetUINT64(const String uint64Str);
	MemoryBlock GetUINT64MemoryBlock(const String uint64Str);

	class OrderTableComponent : public Component,
		public TableListBoxModel
	{
	public:
		OrderTableComponent(const bool isBuyOrders = false);
		~OrderTableComponent();

		void paint(Graphics&) override;
		void resized() override;

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

		void SetUserBurstAddress(String rs)
		{
			accountRS = rs;
		}
		void SetOrders(const Array<OrderItem> &orders)
		{
			this->orders = orders;
			table.updateContent();
		}

		void SetDecimals(uint64 dec) { this->dec = dec; };
		String NQT2Burst(const uint64 value, const uint64 decimals)
		{
			String v = String(value).paddedLeft('0', decimals + 1);
			return (v.substring(0, v.length() - decimals) + "." + v.substring(v.length() - decimals, v.length()).trimCharactersAtEnd("0"));
		}

		void addTradeComponentListener(TradeInterfaceComponentListener* const l)      { tradeInterfaceComponentListeners.add(l); };
		void removeTradeComponentListener(TradeInterfaceComponentListener* const l)   { tradeInterfaceComponentListeners.remove(l); };
	private:
		ListenerList <TradeInterfaceComponentListener> tradeInterfaceComponentListeners;
		TableListBox table;
		bool isBuyOrders = false;
		Array<OrderItem> orders;
		String accountRS;
		uint64 dec = 8;
	};
	Colour GetAssetColor(float iTime);
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextEditor> nameTextEditor;
    ScopedPointer<TextEditor> descriptionTextEditor;
    ScopedPointer<TextButton> buyButton;
    ScopedPointer<TextButton> sellButton;
    ScopedPointer<ComboBox> sellAmountComboBox;
    ScopedPointer<ComboBox> buyAmountComboBox;
    ScopedPointer<Label> label2;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> balanceNumLabel;
    ScopedPointer<ComboBox> sellPriceComboBox;
    ScopedPointer<ComboBox> buyPriceComboBox;
    ScopedPointer<Slider> decimalsSlider;
    ScopedPointer<Label> decimalslabel;
    ScopedPointer<Label> quantityLabel;
    ScopedPointer<TextButton> createButton;
    ScopedPointer<TextButton> assetMenuButton;
    ScopedPointer<ComboBox> quantityComboBox;
    ScopedPointer<OrderTableComponent> buyOrderTableComponent;
    ScopedPointer<OrderTableComponent> sellOrderTableComponent;
    ScopedPointer<Label> totalBuyLabel;
    ScopedPointer<Label> totalSellLabel;
    ScopedPointer<Label> nameLabel;
    ScopedPointer<TextEditor> descriptionStaticTextEditor;
    ScopedPointer<Label> balanceNumLabel2;
    ScopedPointer<ComboBox> buyTotalComboBox;
    ScopedPointer<ComboBox> sellTotalComboBox;
    ScopedPointer<Label> quantityLabel2;
    ScopedPointer<Label> quantityLabel3;
    ScopedPointer<ComboBox> whitelistAssetComboBox;
    ScopedPointer<TextButton> whitelistAddTextButton;
    ScopedPointer<TextButton> whitelistRemoveTextButton;
    ScopedPointer<Label> whitelistLabel;
    ScopedPointer<Label> createLabel;
    ScopedPointer<Drawable> drawable1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TradeInterfaceComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_88F37D9343714708__
