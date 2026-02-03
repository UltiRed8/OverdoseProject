#pragma once

#include "CoreMinimal.h"
#include "GPE/Items/Weapons/ProjectileWeapon.h"
#include "GPE/Projectile/Projectile.h"
#include "FallingMokia.generated.h"

UCLASS()
class OVERDOSE_API AFallingMokia : public AProjectileWeapon
{
	GENERATED_BODY()

public:
	AFallingMokia();
	virtual float Use(TObjectPtr<AActor> _user)override;

	//void Activate(TObjectPtr<AActor> _user);
};