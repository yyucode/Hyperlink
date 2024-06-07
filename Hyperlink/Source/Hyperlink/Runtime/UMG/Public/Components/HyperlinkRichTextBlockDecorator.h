
#pragma once
#include "CoreMinimal.h"
#include "Components/RichTextBlockDecorator.h"
#include "Runtime/Slate/Public/Framework/Text/ITextDecorator.h"
#include "Runtime/SlateCore/Public/Styling/SlateTypes.h"
#include "../../../Slate/Public/Widgets/Input/SHyperlinkRichText.h"

#include "HyperlinkRichTextBlockDecorator.generated.h"

USTRUCT(BlueprintType)
struct HYPERLINK_API FRichHyperlinkRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)
	FHyperlinkStyle HlStyle;
};

UCLASS(Abstract, Blueprintable)
class HYPERLINK_API UHyperlinkRichTextBlockDecorator : public URichTextBlockDecorator
{
	GENERATED_BODY()
public:
	UHyperlinkRichTextBlockDecorator(const FObjectInitializer& ObjectInitializer);
	
	virtual TSharedPtr<ITextDecorator> CreateDecorator(class URichTextBlock* InOwner) override;
	
	virtual const FHyperlinkStyle* FindHyperlinkStyle(FName TagOrId, bool bWarnIfMissing);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Hyperlink")
	void OnHyperlinkClick(const FString& Type, const FString& Href);
	virtual void OnHyperlinkClick_Implementation(const FString& Type, const FString& Href);
protected:
	FRichHyperlinkRow* FindHyperlinkRow(FName TagOrId, bool bWarningIfMissing);
	
	UPROPERTY(EditAnywhere, Category = Appearance, meta = (RequiredAssetDataTags = "RowStructure=RichHyperlinkRowEx"))
	class UDataTable* HyperlinkSet;
};

class HYPERLINK_API FHyperlinkRichTextDecorator : public FRichTextDecorator
{
public:
	FHyperlinkRichTextDecorator(URichTextBlock* InOwner, UHyperlinkRichTextBlockDecorator* InDecorator);
	virtual bool Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const override;
protected:
	virtual TSharedPtr<SWidget> CreateDecoratorWidget(const FTextRunInfo& RunInfo, const FTextBlockStyle& TextStyle) const override;
private:
	UHyperlinkRichTextBlockDecorator* Decorator;
	FHyperlinkDelegate HlDelegate;
	FString ParseName = FString("a");
};