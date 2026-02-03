#include "GPE/Items/Weapons/Rasputin.h"

ARasputin::ARasputin()
{
	name = "Rasputin";
}

float ARasputin::Use(TObjectPtr<AActor> _user)
{
	Super::Use(_user);
	FVector _fromLocation = GetActorLocation();
	FVector _toLocation = _fromLocation;
	_toLocation.Z -= 2000;

	FHitResult _result;
	FCollisionQueryParams _params;
	_params.AddIgnoredActor(this);
	_params.AddIgnoredActor(_user);
	if (GetWorld()->LineTraceSingleByChannel(_result, _fromLocation, _toLocation, ECollisionChannel::ECC_MAX, _params))
	{
		_result.Location.Z += 20;
		TObjectPtr<AProjectile> _projectile = GetWorld()->SpawnActor<AProjectile>(projectile, _result.Location, _user->GetActorRotation());
		if (_projectile)
		{
			_projectile->SetProjectileOwner(_user);
		}
	}
	return removeDelay;
}