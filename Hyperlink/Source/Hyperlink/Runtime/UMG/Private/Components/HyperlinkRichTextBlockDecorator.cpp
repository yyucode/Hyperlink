#include "../../public/Components/HyperlinkRichTextBlockdecorator.h"


UHyperlinkRichTextBlockDecorator::UHyperlinkRichTextBlockDecorator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

TSharedPtr<ITextDecorator> UHyperlinkRichTextBlockDecorator::CreateDecorator(URichTextBlock* InOwner)
{
	return MakeShareable(new FHyperlinkRichTextDecorator(InOwner, this));
}

const FHyperlinkStyle* UHyperlinkRichTextBlockDecorator::FindHyperlinkStyle(FName TagOrId, bool bWarnIfMissing)
{
	const FRichHyperlinkRow* HlRow = FindHyperlinkRow(TagOrId, bWarnIfMissing);
	if (HlRow)
	{
		return &HlRow->HlStyle;
	}

	return nullptr;
}

void UHyperlinkRichTextBlockDecorator::OnHyperlinkClick_Implementation(const FString& Type, const FString& Href)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, FString::Printf(TEXT("OnClickHyperlink type =  %s  ; href = %s"), *Type, *Href));
	}
}

FRichHyperlinkRow* UHyperlinkRichTextBlockDecorator::FindHyperlinkRow(FName TagOrId, bool bWarningIfMissing)
{
	if (HyperlinkSet)
	{
		FString ContextString;
		return HyperlinkSet->FindRow<FRichHyperlinkRow>(TagOrId, ContextString, bWarningIfMissing);
	}

	return nullptr;
}

FHyperlinkRichTextDecorator::FHyperlinkRichTextDecorator(URichTextBlock* InOwner, UHyperlinkRichTextBlockDecorator* InDecorator)
	: FRichTextDecorator(InOwner), Decorator(InDecorator)
{
	HlDelegate.BindUObject(Decorator, &UHyperlinkRichTextBlockDecorator::OnHyperlinkClick);
}

bool FHyperlinkRichTextDecorator::Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const
{
	if (RunParseResult.Name == ParseName && RunParseResult.MetaData.Contains(TEXT("id")))
	{
		const FTextRange& IdRange = RunParseResult.MetaData[TEXT("id")];
		const FString TagId = Text.Mid(IdRange.BeginIndex, IdRange.EndIndex - IdRange.BeginIndex);
		const bool bWarnIfMissing = false;
		return Decorator->FindHyperlinkStyle(*TagId, bWarnIfMissing) != nullptr;
	}

	return false;
}

TSharedPtr<SWidget> FHyperlinkRichTextDecorator::CreateDecoratorWidget(const FTextRunInfo& RunInfo,
	const FTextBlockStyle& TextStyle) const
{
	const bool bWarnIfMissing = false;
	const FHyperlinkStyle* HlStyle = Decorator->FindHyperlinkStyle(*RunInfo.MetaData[TEXT("id")], bWarnIfMissing);
	const FString* Href = RunInfo.MetaData.Find(TEXT("href"));
	const FString* Type = RunInfo.MetaData.Find(TEXT("id"));

	const TSharedPtr<FSlateHyperlinkRun::FWidgetViewModel> Model = MakeShareable(new FSlateHyperlinkRun::FWidgetViewModel);
	TSharedPtr<SHyperlinkRichText> HlWidget = SNew(SHyperlinkRichText, Model.ToSharedRef())
		.Text(RunInfo.Content)
		.Style(HlStyle)
		.Href(FString(*Href))
		.Type(FString(*Type))
		.Delegate(HlDelegate);

	return HlWidget;
}


