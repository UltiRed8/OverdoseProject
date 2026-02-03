// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomSetWidget.h"
#include <Components/VerticalBox.h>
#include "GraphicsMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVERDOSE_API UGraphicsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<UCustomSetWidget> widget = nullptr;
	UPROPERTY(EditAnywhere) TArray<TSubclassOf<UGameSetBehaviour>> settings = {};
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UVerticalBox> verticalBox = nullptr;

	virtual void NativeConstruct() override;
	void GenerateSettings();
};
