// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotInventoryWidget.h"
#include <Components/VerticalBox.h>
#include "InventoryWidget.generated.h"

class AAntController;

/**
 * 
 */
UCLASS()
class OVERDOSE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpen);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClose);
	UPROPERTY(EditAnywhere, Category = "Settings") TArray<TObjectPtr<USlotInventoryWidget>> slots = {};
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "Debug") TObjectPtr<UVerticalBox> mainVerticalBox = nullptr;
	UPROPERTY(EditAnywhere, Category = "Item to store") TArray<TSubclassOf<AItem>> itemsToStore = {};
	UPROPERTY(BlueprintAssignable) FOnOpen onOpen;
	UPROPERTY(BlueprintAssignable) FOnClose onClose;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") TObjectPtr<AAntController> controller = nullptr;
public:
	FORCEINLINE FOnOpen& OnOpen()
	{
		return onOpen;
	}
	FORCEINLINE FOnClose& OnClose()
	{
		return onClose;
	}
	FORCEINLINE void SetController(TObjectPtr<AAntController> _controller)
	{
		controller = _controller;
	}
public:
	virtual void NativeConstruct() override;
	void Init();
private:
	UFUNCTION(BluePrintCallable) TArray<USlotInventoryWidget*> GetSlots()
	{
		return slots;
	}
};