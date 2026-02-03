// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "GPE/Puddle/Puddle.h"
#include "LobbyWidget.generated.h"

USTRUCT(BlueprintType)
struct FSettings
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool teamDisco;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool teamSport;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) TEnumAsByte<EPuddleType> puddleType;
};

UCLASS()
class OVERDOSE_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UButton> playButton = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FSettings teamSetting1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FSettings teamSetting2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName levelToLoad = "LVL_Demo";
};
