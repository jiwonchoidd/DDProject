// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlockDecorator.h"
#include "Framework/Text/SlateHyperlinkRun.h"
#include "DDRichTextHyperLinkDecorator.generated.h"

UCLASS(hidecategories=Object, MinimalAPI)
class UDDHyperLinkTextBlockWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FHyperlinkStyle HyperlinkStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return &HyperlinkStyle;
	}
};

class FDDHyperlinkDecorator : public ITextDecorator
{
public:
	static TSharedRef< FDDHyperlinkDecorator > Create(const FTextBlockStyle& _TextBlockStyle, const FSlateHyperlinkRun::FOnClick& NavigateDelegate, const FSlateHyperlinkRun::FOnGetTooltipText& InToolTipTextDelegate = FSlateHyperlinkRun::FOnGetTooltipText(), const FSlateHyperlinkRun::FOnGenerateTooltip& InToolTipDelegate = FSlateHyperlinkRun::FOnGenerateTooltip() );
	virtual ~FDDHyperlinkDecorator() override {}
public:
	virtual bool Supports( const FTextRunParseResults& RunParseResult, const FString& Text ) const override;
	virtual TSharedRef< ISlateRun > Create(const TSharedRef<class FTextLayout>& TextLayout, const FTextRunParseResults& RunParseResult, const FString& OriginalText, const TSharedRef< FString >& InOutModelText, const ISlateStyle* Style) override;
protected:
	FDDHyperlinkDecorator(const FTextBlockStyle& _TextBlockStyle, const FSlateHyperlinkRun::FOnClick& InNavigateDelegate, const FSlateHyperlinkRun::FOnGetTooltipText& InToolTipTextDelegate = FSlateHyperlinkRun::FOnGetTooltipText(), const FSlateHyperlinkRun::FOnGenerateTooltip& InToolTipDelegate = FSlateHyperlinkRun::FOnGenerateTooltip() );
protected:
	FSlateHyperlinkRun::FOnClick NavigateDelegate;
protected:
	FSlateHyperlinkRun::FOnGetTooltipText ToolTipTextDelegate;
	FSlateHyperlinkRun::FOnGenerateTooltip ToolTipDelegate;
	FTextBlockStyle DefaultTextBlockStyle;
};

/**
 *  RichText 링크 첨부 허용 데코레이션
 *  Ex) 해당 이벤트 내용은 <link color="#4682b4" url="www.naver.com">링크</>를 확인해주세요
 */
UCLASS()
class DDFUNDAMENTAL_API UDDRichTextHyperLinkDecorator : public URichTextBlockDecorator
{
	GENERATED_BODY()

public:
	virtual TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	bool bUseUnderline = true;
};