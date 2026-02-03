#pragma once

#include "CoreMinimal.h"
#include "GPE/Items/Weapons/ProjectileWeapon.h"
#include "GPE/Projectile/Projectile.h"
#include "Bazooka.generated.h"

UCLASS()
class OVERDOSE_API ABazooka : public AProjectileWeapon
{
	GENERATED_BODY()

public:
	ABazooka();
	virtual float Use(TObjectPtr<AActor> _user)override;
};
