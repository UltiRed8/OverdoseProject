// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <GPE/Items/Weapons/Weapon.h>
#include <GPE/Items/Tools/Tool.h>
#include "InventoryComponent.generated.h"

UCLASS()
class USlot : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY() TObjectPtr<AItem> item = nullptr;
	UPROPERTY() int amount = -1;
	UPROPERTY() int lockedTurns = 0;

	void SetItemSlot(TObjectPtr<AItem> _item);
	UFUNCTION(BlueprintCallable) int GetAmount();
	UFUNCTION(BlueprintCallable) int& GetLockedTurns();
	UFUNCTION(BlueprintCallable) AItem* GetItem();
	void AddAmount();
	UFUNCTION(BlueprintCallable) void DecreaseAmount();
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERDOSE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TArray<TObjectPtr<USlot>> slots = {};

public:
	void AddWeapon(TObjectPtr<AWeapon> _weapon);

	void AddTool(TObjectPtr<ATool> _tool);

	UFUNCTION(BlueprintCallable) FORCEINLINE TArray<USlot*> GetSlots() { return slots; }

public:	
	UInventoryComponent();
	void Init();
	void InitTuto();
	UFUNCTION() void DecrementeLockedTurnsForAllItem();
	void Reset();

protected:
	virtual void BeginPlay() override;
};