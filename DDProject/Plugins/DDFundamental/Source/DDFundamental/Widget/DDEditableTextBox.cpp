
#include "DDEditableTextBox.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
TSharedRef<SWidget> UDDEditableTextBox::RebuildWidget()
{
	TSharedRef<SWidget> EditableBox = Super::RebuildWidget();
	return EditableBox;
}

void UDDEditableTextBox::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

FText UDDEditableTextBox::DisplayTextFunc(const FText& _Text)
{
	FString _resultText = _Text.ToString();
	TArray<FString> BanWord;
	BanWord.Add(TEXT("sibal"));
	for (auto& Word : BanWord)
	{
		int32 findIndex = _resultText.Find(Word, ESearchCase::IgnoreCase);
		while (findIndex >= 0)
		{
			int endIndex = findIndex + Word.Len();
			for (int32 index = findIndex; index < endIndex; ++index)
			{
				_resultText.RemoveAt(index);
				_resultText.InsertAt(index, TEXT("*"));
			}

			findIndex = _resultText.Find(Word, ESearchCase::IgnoreCase);
		}
	}

	return FText::FromString(_resultText);
}

void UDDEditableTextBox::HandleOnTextChanged(const FText& _Text)
{
	FString EnteredText = _Text.ToString();
	if (EnteredText.Len() < OriginalText.Len()) // 삭제
	{
		OriginalText.RemoveAt(OriginalText.Len() - 1);
	}
	else // 추가
	{
		FString NewChar = EnteredText.RightChop(OriginalText.Len());
		OriginalText += NewChar;
	}

	const FText MaskedText = DisplayTextFunc(FText::FromString(OriginalText));
	SetText(MaskedText);

	OnTextChanged.Broadcast(_Text);
}

void UDDEditableTextBox::HandleOnTextCommitted(const FText& _Text, ETextCommit::Type _CommitMethod)
{
	FString EnteredText = _Text.ToString();
	if (EnteredText.Len() < OriginalText.Len())
	{
		OriginalText = OriginalText.Left(EnteredText.Len());
	}
	else
	{
		FString NewText = EnteredText.RightChop(OriginalText.Len());
		OriginalText += NewText;
	}

	if (ChangeDisplayTextWhenCommit)
	{
		DisplayText = DisplayTextFunc(FText::FromString(OriginalText)).ToString();
		SetText(FText::FromString(DisplayText));
	}
	else
	{
		SetText(_Text);
	}
	OnTextCommitted.Broadcast(_Text, _CommitMethod);
}

