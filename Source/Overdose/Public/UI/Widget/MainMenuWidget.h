// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/ComboBoxKey.h>
#include <Components/TextBlock.h>
#include "GameViewportClient/CustomGameViewportClient.h"
#include "MainMenuWidget.generated.h"

UCLASS()
class OVERDOSE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "LevelToLoad", meta = (BindWidget)) FName levelToLoad = "";

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugs") EGameInputMethod inputMethod = EGameInputMethod::GI_Player1KeyboardMouseOnly;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buttons", meta = (BindWidget)) TObjectPtr<UButton> btnPreviousInputMethod = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buttons", meta = (BindWidget)) TObjectPtr<UButton> btnNextInputMethod = nullptr;

public:
	virtual void NativeConstruct() override;
	void InitBinding();

private:
	UFUNCTION() void OnPreviousInputMethod();
	UFUNCTION() void OnNextInputMethod();
	void UpdateInputMethod();

	void LoadLevel();
};