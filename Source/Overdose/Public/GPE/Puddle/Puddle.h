#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puddle.generated.h"

UENUM()
enum EPuddleType : uint8
{
	TYPENONE,
	HEAL,
	DAMAGE,
	POISON,
	FLAME,
};

UCLASS()
class OVERDOSE_API APuddle : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnterPuddle, AActor*, _actor);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExitPuddle, AActor*, _actor);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSetPuddleType);
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (UIMin = 1, ClampMin = 1, EditCondition = "type != 0 && type <= 2")) int amount = 25;
	UPROPERTY(EditAnywhere, Category = "Settings") bool removeOnTrigger = true;
	UPROPERTY(BlueprintAssignable) FOnEnterPuddle onEnterPuddle;
	UPROPERTY(BlueprintAssignable) FOnExitPuddle onExitPuddle;
	UPROPERTY(BlueprintAssignable) FOnSetPuddleType onSetPuddleType;
	UPROPERTY(EditAnywhere, Category = "Settings") int turnLifeSpan = 0;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugs") TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") TEnumAsByte<EPuddleType> type = HEAL;

public:	
	APuddle();

public:
	FORCEINLINE void SetRemoveOnTrigger(const bool _status)
	{
		removeOnTrigger = _status;
	}
	FORCEINLINE FOnEnterPuddle& OnEnterPuddle()
	{
		return onEnterPuddle;
	}
	FORCEINLINE FOnExitPuddle& OnExitPuddle()
	{
		return onExitPuddle;
	}
	FORCEINLINE FOnSetPuddleType& OnSetPuddleType()
	{
		return onSetPuddleType;
	}
	FORCEINLINE void SetPuddleType(TEnumAsByte<EPuddleType> _type) 
	{ 
		type = _type; 
		onSetPuddleType.Broadcast();
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE TEnumAsByte<EPuddleType> GetPuddleType()
	{
		return type;
	}

private:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* _other);
	virtual void NotifyActorEndOverlap(AActor* _other);
	void TriggerEffect(AActor* _actor);
	void Remove();
	void RegisterTurnLifeSpan();
	UFUNCTION() void DecrementTurnLifeSpan(int _index);
};