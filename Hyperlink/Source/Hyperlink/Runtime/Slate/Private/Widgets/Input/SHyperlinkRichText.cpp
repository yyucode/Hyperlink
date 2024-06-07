#include "../../../Public/Widgets/Input/SHyperlinkRichText.h"

void SHyperlinkRichText::Construct(const FArguments& InArgs, const TSharedRef<FSlateHyperlinkRun::FWidgetViewModel>& InViewModel)
{
	ViewModel = InViewModel;
	this->HyperDelegate = InArgs._Delegate;
	this->Href = InArgs._Href;
	this->Type = InArgs._Type;
	check(InArgs._Style);
	const FButtonStyle* UnderlineStyle = InArgs._UnderlineStyle != nullptr ? InArgs._UnderlineStyle : &InArgs._Style->UnderlineStyle;
	const FTextBlockStyle* TextStyle = InArgs._TextStyle != nullptr ? InArgs._TextStyle : &InArgs._Style->TextStyle;
	TAttribute<FMargin> Padding = InArgs._Padding.IsSet() ? InArgs._Padding : InArgs._Style->Padding;

	SButton::Construct(
		SButton::FArguments()
		.Text(InArgs._Text)
		.ContentPadding(Padding)
		.ButtonStyle(UnderlineStyle)
		.TextStyle(TextStyle)
		.OnClicked(FOnClicked::CreateRaw(this, &SHyperlinkRichText::OnClicked))
		.ForegroundColor(FSlateColor::UseForeground())
		.TextShapingMethod(InArgs._TextShapingMethod)
		.TextFlowDirection(InArgs._TextFlowDirection)
	);
}

FReply SHyperlinkRichText::OnClicked() const
{
	HyperDelegate.ExecuteIfBound(Type, Href);
	return FReply::Handled();
}