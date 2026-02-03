#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExplosableComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERDOSE_API UExplosableComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExplosion);
	UPROPERTY(EditAnywhere, Category = "Settings") int radius = 300;
	UPROPERTY(EditAnywhere, Category = "Settings") int damageToAnt = 30;
	UPROPERTY(EditAnywhere, Category = "Settings") int damageToWalls = 50;
	UPROPERTY(EditAnywhere, Category = "Settings") float knockbackMultiplier = 1.f;
	UPROPERTY(EditAnywhere, Category = "Settings") float damageToWallMultiplier = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Settings") bool applyPoisonEffect = false;
	UPROPERTY(EditAnywhere, Category = "Settings")  bool applyFireEffect = false;
	UPROPERTY(VisibleAnywhere, Category = "Debug") TArray<TEnumAsByte<EObjectTypeQuery>> filter;
	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category = "Debug") FOnExplosion onExplosion;
	UPROPERTY(EditAnywhere, Category = "Settings") TArray<AActor*> actorInRadius = {};
public:	
	FORCEINLINE FOnExplosion& OnExplosion() {return onExplosion;}
	UFUNCTION(BlueprintCallable) FORCEINLINE TArray<AActor*> GetActorInRadius() { return actorInRadius; }

private:
	TArray<AActor*> ActorInRadius();
	FVector GetOwnerLocation();
public:	
	void Explode();
};