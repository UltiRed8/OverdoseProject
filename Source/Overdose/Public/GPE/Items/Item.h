#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

UCLASS()
class OVERDOSE_API AItem : public AActor
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemUsed);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNoMoreUses, const float , _time);
protected:
	UPROPERTY(EditAnywhere, Category = "Settings") TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") bool limitedUses = true;
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (UIMin = 1, ClampMin = 1, EditCondition = "limitedUses")) int usesAmount = 1;
	UPROPERTY(EditAnywhere, Category = "Settings") int lockedTurns = 0;
	UPROPERTY(EditAnywhere, Category = "Name") FString name = "INSERT NAME ITEM";
	UPROPERTY(EditAnywhere, Category = "Settings") TObjectPtr<USoundWave> sheathSound = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") TObjectPtr<USoundWave> drawSound = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") float removeDelay = 0.0f;
	UPROPERTY(BlueprintAssignable) FOnItemUsed onItemUsed;
	bool isUse = false;
	bool isStore = false;
	FOnNoMoreUses onNoMoreUses;
public:
	FORCEINLINE FOnItemUsed& OnItemUsed()
	{
		return onItemUsed;
	}
	FORCEINLINE FOnNoMoreUses& OnNoMoreUses()
	{
		return onNoMoreUses;
	}
	FORCEINLINE FString GetNameItem() { return name; }
	FORCEINLINE const int GetUsesAmount() { return usesAmount; }
	FORCEINLINE void SetUsesAmount(const int _usesAmount) { usesAmount = _usesAmount; }
	FORCEINLINE void SetLockedTurns(const int _lockedTurns) { lockedTurns = _lockedTurns; }
public:
	AItem();
private:
	void CheckUses();
public:
	void Store();
	void Take();
	void Delete();
	virtual void BeginPlay() override;
	virtual float Use(TObjectPtr<AActor> _user);
	UFUNCTION() void ForceDestroy();
	UFUNCTION(BlueprintCallable) void RegisterEndTurn();
	UFUNCTION(BlueprintCallable) FORCEINLINE int GetLockedTurns() { return lockedTurns; }
	UFUNCTION(BlueprintCallable) void SheathWeaponSound();
	UFUNCTION(BlueprintCallable)void DrawWeaponSound();
};