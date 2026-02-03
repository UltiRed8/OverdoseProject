// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVERDOSE_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UButton> backToMainMenu = nullptr;

private:
	UPROPERTY(EditAnywhere) FName mainMenuName = "LVL_TitleMenu";

	virtual void NativeConstruct() override;
	void BindButtons();
	UFUNCTION() void OnBackToMenu();
};
