#pragma once

#include "CoreMinimal.h"
#include "GPE/Items/Weapons/ProjectileWeapon.h"
#include "GPE/Projectile/Projectile.h"
#include "Rasputin.generated.h"

UCLASS()
class OVERDOSE_API ARasputin : public AProjectileWeapon
{
	GENERATED_BODY()

public:
	ARasputin();
	virtual float Use(TObjectPtr<AActor> _user)override;
};