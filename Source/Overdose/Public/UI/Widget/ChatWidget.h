// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "ChatWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVERDOSE_API UChatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> chatText = nullptr;
};
