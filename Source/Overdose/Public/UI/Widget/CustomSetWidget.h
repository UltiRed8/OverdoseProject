// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <UI/Settings/GameSetBehaviour.h>
#include "CustomSetWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVERDOSE_API UCustomSetWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UButton> lowButton = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UButton> mediumButton = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UButton> epicButton = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UButton> ultraButton = nullptr;

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UTextBlock> nameSettings = nullptr;

	UPROPERTY(EditAnywhere) TObjectPtr<UGameSetBehaviour> behaviour = nullptr;

private:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION() virtual void OnLowClick();
	UFUNCTION() virtual void OnMediumClick();
	UFUNCTION() virtual void OnEpicClick();
	UFUNCTION() virtual void OnUltraClick();

public:
	UFUNCTION() void Init(const FString& _name);
	void SetBehaviour(TObjectPtr<UGameSetBehaviour> _behaviour);
};
