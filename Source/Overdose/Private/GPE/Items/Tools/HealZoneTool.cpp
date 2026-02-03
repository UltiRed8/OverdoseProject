#include "GPE/Items/Tools/HealZoneTool.h"
#include <Actor/Characters/AntCharacter.h>
#include <GPE/Puddle/Puddle.h>
#include <Utils/DevUtils.h>

AHealZoneTool::AHealZoneTool()
{
	name = "HealZone";
}

float AHealZoneTool::Use(TObjectPtr<AActor> _user)
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
		_finalLocation.X += 35;
		GetWorld()->SpawnActor<APlaceableHealZone>(placeableHealZone, _finalLocation, FRotator(), _parameters);
	}
	return removeDelay;
}