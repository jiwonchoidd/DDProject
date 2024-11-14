// Fill out your copyright notice in the Description page of Project Settings.


#include "DDRichTextHyperLinkDecorator.h"

#include "Components/RichTextBlock.h"
#include "Framework/Text/TextDecorators.h"

TSharedRef<FDDHyperlinkDecorator> FDDHyperlinkDecorator::Create(const FTextBlockStyle& _TextBlockStyle, const FSlateHyperlinkRun::FOnClick& NavigateDelegate,
    const FSlateHyperlinkRun::FOnGetTooltipText& InToolTipTextDelegate, const FSlateHyperlinkRun::FOnGenerateTooltip& InToolTipDelegate)
{
    return MakeShareable( new FDDHyperlinkDecorator(_TextBlockStyle, NavigateDelegate, InToolTipTextDelegate, InToolTipDelegate ) );
}

bool FDDHyperlinkDecorator::Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const
{
    const FTextRange* const pUrlMeta = RunParseResult.MetaData.Find(TEXT("url"));
    return (RunParseResult.Name == TEXT("link") && pUrlMeta != nullptr);
}

TSharedRef<ISlateRun> FDDHyperlinkDecorator::Create(const TSharedRef<FTextLayout>& TextLayout, const FTextRunParseResults& RunParseResult, const FString& OriginalText,
                                                      const TSharedRef<FString>& InOutModelText, const ISlateStyle* Style)
{
    // Set style
    FTextBlockStyle TextStyle;
    const FTextRange* const MetaDataTextStyleNameRange = RunParseResult.MetaData.Find(TEXT("style"));
    if(MetaDataTextStyleNameRange == NULL)
    {
        TextStyle = DefaultTextBlockStyle;
    }
    else
    {
        const FString MetaDataTextStyleName = OriginalText.Mid(MetaDataTextStyleNameRange->BeginIndex, MetaDataTextStyleNameRange->EndIndex - MetaDataTextStyleNameRange->BeginIndex);
        FString TextStyleName = *MetaDataTextStyleName;

        if (!TextStyleName.IsEmpty() && Style->HasWidgetStyle<FTextBlockStyle>(FName(*TextStyleName)))
        {
            TextStyle = Style->GetWidgetStyle<FTextBlockStyle>(FName(*TextStyleName));
        }
    }
    
    //set color
    const FTextRange* const MetaDataTextColorNameRange = RunParseResult.MetaData.Find(TEXT("color"));
    TOptional<FLinearColor> OptColor;
    if (MetaDataTextColorNameRange != NULL)
    {
        FLinearColor TempColor;
        const FString MetaDataTextColorName = OriginalText.Mid(MetaDataTextColorNameRange->BeginIndex, MetaDataTextColorNameRange->EndIndex - MetaDataTextColorNameRange->BeginIndex);
        if (!MetaDataTextColorName.IsEmpty() && MetaDataTextColorName[0] == TCHAR('#'))
        {
            TempColor = FLinearColor(FColor::FromHex(MetaDataTextColorName));
            OptColor = TempColor;
        }
        else if (TempColor.InitFromString(*MetaDataTextColorName))
        {
            OptColor = TempColor;
        }
    }
    
    if(OptColor.IsSet())
    {
        TextStyle.ColorAndOpacity = FSlateColor(OptColor.GetValue());
    }
    
    FTextRange ModelRange;
    ModelRange.BeginIndex = InOutModelText->Len();
    *InOutModelText += OriginalText.Mid(RunParseResult.ContentRange.BeginIndex, RunParseResult.ContentRange.EndIndex - RunParseResult.ContentRange.BeginIndex);
    ModelRange.EndIndex = InOutModelText->Len();
   
    FRunInfo RunInfo(RunParseResult.Name);
    for (const TPair<FString, FTextRange>& Pair : RunParseResult.MetaData)
    {
        RunInfo.MetaData.Add(Pair.Key, OriginalText.Mid(Pair.Value.BeginIndex, Pair.Value.EndIndex - Pair.Value.BeginIndex));
    }
    const FButtonStyle UserNameButton = FButtonStyle()
            .SetNormal(FSlateNoResource())
            .SetPressed(FSlateNoResource())
            .SetHovered(FSlateNoResource());

    const FHyperlinkStyle HyperlinkStyle = FHyperlinkStyle()
                                           .SetUnderlineStyle(UserNameButton)
                                           .SetTextStyle(TextStyle)
                                           .SetPadding(FMargin(0.0f));
   
    return FSlateHyperlinkRun::Create(RunInfo, InOutModelText, HyperlinkStyle, NavigateDelegate, ToolTipDelegate, ToolTipTextDelegate, ModelRange);
}

FDDHyperlinkDecorator::FDDHyperlinkDecorator(const FTextBlockStyle& _TextBlockStyle, const FSlateHyperlinkRun::FOnClick& InNavigateDelegate,
                                                 const FSlateHyperlinkRun::FOnGetTooltipText& InToolTipTextDelegate, const FSlateHyperlinkRun::FOnGenerateTooltip& InToolTipDelegate):
    NavigateDelegate(InNavigateDelegate),
    ToolTipTextDelegate(InToolTipTextDelegate)
    , ToolTipDelegate(InToolTipDelegate)
    , DefaultTextBlockStyle(_TextBlockStyle)
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

TSharedPtr<ITextDecorator> UDDRichTextHyperLinkDecorator::CreateDecorator(URichTextBlock* InOwner)
{
    FTextBlockStyle DefaultBlockStyle = InOwner->GetCurrentDefaultTextStyle();

    if(bUseUnderline)
    {
        if(const FSlateBrush* DefaultBrush = FCoreStyle::Get().GetBrush(TEXT("DefaultTextUnderline")))
        {
            DefaultBlockStyle.UnderlineBrush = *(DefaultBrush);
        }
    }
    
    return FDDHyperlinkDecorator::Create(DefaultBlockStyle, FSlateHyperlinkRun::FOnClick::CreateLambda([=](const FSlateHyperlinkRun::FMetadata& Metadata)
    {
        const FString* URL = Metadata.Find(TEXT("url"));
        if (URL)
        {
            FPlatformProcess::LaunchURL(**URL, nullptr, nullptr);
        }
    }));
}