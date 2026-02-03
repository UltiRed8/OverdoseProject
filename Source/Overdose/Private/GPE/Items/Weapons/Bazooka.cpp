#include "GPE/Items/Weapons/Bazooka.h"
#include "Utils/DevUtils.h"

ABazooka::ABazooka()
{
	name = "Bazooka";
}

float ABazooka::Use(TObjectPtr<AActor> _user)
{
	Super::Use(_user);
	FVector _location = GetActorLocation();

	TObjectPtr<AProjectile> _projectile = GetWorld()->SpawnActor<AProjectile>(projectile, _location, GetActorRotation());
	if (_projectile)
	{
		_projectile->SetProjectileOwner(_user);
	}
	return removeDelay;
}