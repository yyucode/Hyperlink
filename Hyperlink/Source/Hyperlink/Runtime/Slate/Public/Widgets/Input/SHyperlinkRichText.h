#pragma once

#include "CoreMinimal.h"
#include "Runtime/SlateCore/Public/Styling/SlateTypes.h"
#include "Runtime/Slate/Public/Widgets/Input/SHyperlink.h"
#include "Runtime/Slate/Public/Framework/Text/SlateHyperlinkRun.h"


class FWidgetViewModel;
enum class ETextShapingMethod : uint8;
DECLARE_DELEGATE_TwoParams(FHyperlinkDelegate, const FString&, const FString&);

class SHyperlinkRichText : public SHyperlink
{
public:

	SLATE_BEGIN_ARGS(SHyperlinkRichText)
		: _Text()
		, _Href()
		, _Type()
		, _Style(&FCoreStyle::Get().GetWidgetStyle< FHyperlinkStyle >("SHyperlinkRichText"))
		, _TextStyle(nullptr)
		, _UnderlineStyle(nullptr)
		, _Padding()
		, _OnNavigate()
		, _Delegate()
		, _TextShapingMethod()
		, _TextFlowDirection()
		{}

		SLATE_ATTRIBUTE(FText, Text)
		SLATE_ARGUMENT(FString, Href)
		SLATE_ARGUMENT(FString, Type)
		SLATE_STYLE_ARGUMENT(FHyperlinkStyle, Style)
		SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle)
		SLATE_STYLE_ARGUMENT(FButtonStyle, UnderlineStyle)
		SLATE_ATTRIBUTE(FMargin, Padding)
		SLATE_EVENT(FSimpleDelegate, OnNavigate)
		SLATE_EVENT(FHyperlinkDelegate, Delegate)
		SLATE_ARGUMENT(TOptional<ETextShapingMethod>, TextShapingMethod)
		SLATE_ARGUMENT(TOptional<ETextFlowDirection>, TextFlowDirection)
	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs, const TSharedRef< FSlateHyperlinkRun::FWidgetViewModel >& InViewModel);

	FReply OnClicked() const;

private:
	FHyperlinkDelegate HyperDelegate;
	FString Href;
	FString Type;
	TSharedPtr< FSlateHyperlinkRun::FWidgetViewModel > ViewModel;
};
