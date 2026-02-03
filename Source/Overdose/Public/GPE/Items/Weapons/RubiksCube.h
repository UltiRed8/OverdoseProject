#pragma once

#include "CoreMinimal.h"
#include "GPE/Items/Weapons/Weapon.h"
#include <GPE/Projectile/PlaceableRubiksCube.h>
#include "RubiksCube.generated.h"

UCLASS()
class OVERDOSE_API ARubiksCube : public AWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Settings") TSubclassOf<APlaceableRubiksCube> placeableCube = nullptr;

public:
	ARubiksCube();

private:
	virtual float Use(TObjectPtr<AActor> _user)override;
};