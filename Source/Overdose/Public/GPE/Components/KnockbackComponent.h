#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KnockbackComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERDOSE_API UKnockbackComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (UIMin = 0.0f, ClampMin = 0.0f)) float knockbackMultiplier = 20.0f;
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (UIMin = 0.0f, ClampMin = 0.0f)) float damagingVelocityTreshold = 200.0f;
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (UIMin = 0.0f, ClampMin = 0.0f)) float damageVelocityMultiplier = 0.5f;
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (UIMin = 0.0f, ClampMin = 0.0f)) float terrainDamageVelocityMultiplier = 3.0f;

public:
	UKnockbackComponent();

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
	double GlobalVelocity();
	void CheckWall();

public:
	void ApplyKnockback(const float _strength,  FVector _direction);
	UFUNCTION() void Debug();
};