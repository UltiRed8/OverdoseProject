#include "GPE/Items/Weapons/RubiksCube.h"
#include <Utils/DevUtils.h>
#include "GPE/Components/DamagableTerrainComponent.h"
#include "Components/StatsComponent.h"
#include "GPE/Components/KnockbackComponent.h"
#include "Kismet/KismetMathLibrary.h"

ARubiksCube::ARubiksCube()
{
	name = "RubiksCube";
}

float ARubiksCube::Use(TObjectPtr<AActor> _user)
{
	Super::Use(_user);
	FVector _location = _user->GetActorLocation();

	FVector _targetPos = _location;
	FHitResult _result;
	_targetPos.Z -= 4000;

	FCollisionQueryParams _params;
	_params.AddIgnoredActor(_user);
	FActorSpawnParameters _parameters;
	_parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	if (GetWorld()->LineTraceSingleByChannel(_result, _location, _targetPos, ECollisionChannel::ECC_MAX, _params))
	{
	    FVector _finalLocation = _result.Location;
	    _finalLocation.Z += 20;
		GetWorld()->SpawnActor<APlaceableRubiksCube>(placeableCube, _finalLocation, FRotator(), _parameters);
	}
	return removeDelay;
}