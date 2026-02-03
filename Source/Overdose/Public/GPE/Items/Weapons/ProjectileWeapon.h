#pragma once

#include "CoreMinimal.h"
#include "GPE/Items/Weapons/Weapon.h"
#include "ProjectileWeapon.generated.h"

UCLASS()
class OVERDOSE_API AProjectileWeapon : public AWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Settings") bool isSplineVisible = false;

protected:
	UPROPERTY(EditAnywhere, Category = "Settings") TSubclassOf<AProjectile> projectile = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugs") TObjectPtr<USplineComponent> spline = nullptr;
	
public:
	AProjectileWeapon();
};