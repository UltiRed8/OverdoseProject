// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <UI/Player/PlayerLifeBarWidget.h>
#include <UI/Player/InventoryWidget.h>
#include "GamePlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVERDOSE_API UGamePlayerWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UInventoryWidget> inventory = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UPlayerLifeBarWidget> playerLifeBar1 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UPlayerLifeBarWidget> playerLifeBar2 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UImage> focus = nullptr;


	FORCEINLINE TObjectPtr<UPlayerLifeBarWidget> GetProgressBar1()
	{
		return playerLifeBar1;
	}
	FORCEINLINE TObjectPtr<UPlayerLifeBarWidget> GetProgressBar2()
	{
		return playerLifeBar2;
	}
	FORCEINLINE TObjectPtr<UImage> GetFocus()
	{
		return focus;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE UInventoryWidget* GetInventoryWidget()
	{
		return inventory;
	}
};
