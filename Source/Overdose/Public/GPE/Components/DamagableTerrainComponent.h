#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamagableTerrainComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERDOSE_API UDamagableTerrainComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamaged);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyed);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMesh);
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (UIMin = 0, ClampMin = 0)) TArray<int>  life = {};
	UPROPERTY(BlueprintAssignable) FOnDamaged onDamaged;
	UPROPERTY(BlueprintAssignable) FOnDestroyed onDestroyed;
	int indexLife = 0;
public:
	FORCEINLINE FOnDamaged& OnDamaged()
	{
		return onDamaged;
	}
	FORCEINLINE FOnDestroyed& OnDestroyed()
	{
		return onDestroyed;
	}

	FORCEINLINE  TArray<int> GetLifes()
	{
		return life;
	}
private:
	void RemoveActor();
public:
	void Damage(const int& _amount);
};