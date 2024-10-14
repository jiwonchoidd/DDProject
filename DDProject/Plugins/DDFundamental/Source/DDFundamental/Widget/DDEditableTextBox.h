// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/EditableTextBox.h"
#include "DDEditableTextBox.generated.h"

/**
 * 
 */
UCLASS()
class DDFUNDAMENTAL_API UDDEditableTextBox : public UEditableTextBox
{
	GENERATED_BODY()

private:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
protected:
	// ------------------------------------------------
	virtual FText DisplayTextFunc(const FText& _Text);
	// ------------------------------------------------
public:
	FText GetOriginText() const { return FText::FromString(OriginalText); } 
private:
	virtual void HandleOnTextChanged(const FText& _Text) override;
	virtual void HandleOnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod) override;
private:
	UPROPERTY(Category = UVic_EditableTextBox, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool ChangeDisplayTextWhenChange = false;

	UPROPERTY(Category = UVic_EditableTextBox, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool ChangeDisplayTextWhenCommit = false;

private:
	FString OriginalText;
	FString DisplayText;
};