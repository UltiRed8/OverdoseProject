#include "GPE/Components/ExplosableComponent.h"
#include <GPE/Components/KnockbackComponent.h>
#include <Components/StatsComponent.h>
#include <GPE/Components/DamagableTerrainComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Utils/DevUtils.h>
#include <GPE/Projectile/Projectile.h>
#include "Subsystem/StatSubsystem.h"
#include "Subsystem/ChatSubsystem.h"
#include "Actor/Characters/AntCharacter.h"
#include "Actor/Characters/AntController.h"

TArray<AActor*> UExplosableComponent::ActorInRadius()
{
	TArray<AActor*> _actorInRadius;
	TArray<AActor*> _actorsToIgnore = TArray<AActor*>();
	_actorsToIgnore.Add(GetOwner());
	UKismetSystemLibrary::SphereOverlapActors(this, GetOwnerLocation(), radius, filter, nullptr, _actorsToIgnore, _actorInRadius);
	return _actorInRadius;
}
FVector UExplosableComponent::GetOwnerLocation()
{
	FVector _location;
	AActor* _owner = GetOwner();
	if (AProjectile* _projectile = Cast<AProjectile>(_owner))
	{
		_location = _projectile->GetPosition();
	}
	else
	{
		_location = _owner->GetActorLocation();
	}
	return _location;
}
void UExplosableComponent::Explode()
{
	actorInRadius = ActorInRadius();
	onExplosion.Broadcast();

	for (AActor* _actor : actorInRadius)
	{
		if (!_actor)
			return;
		TObjectPtr<UDamagableTerrainComponent> _damageComponent = _actor->GetComponentByClass< UDamagableTerrainComponent>();
		TObjectPtr<UStatsComponent> _stats = _actor->GetComponentByClass< UStatsComponent>();
		const float _distance = FVector::Distance(GetOwnerLocation(), _actor->GetActorLocation());
		int _damageToAnt = (1 - _distance / radius) * damageToAnt;
		int _damageToWalls = (1 - _distance / radius) * damageToWalls * damageToWallMultiplier;
	
		_damageToAnt = _damageToAnt < 0 ? 0 : _damageToAnt;
		_damageToWalls = _damageToWalls < 0 ? 0 : _damageToWalls;

		const int _knocbackValue = (radius - _distance) * knockbackMultiplier;
		TObjectPtr<UKnockbackComponent> _knockbackComponent = _actor->GetComponentByClass< UKnockbackComponent>();
	 
		if (_knockbackComponent)
			_knockbackComponent->ApplyKnockback(_knocbackValue * 1.5f , UKismetMathLibrary::FindLookAtRotation(GetOwnerLocation(), _actor->GetActorLocation()).Vector());
		
		if (_damageComponent)
			_damageComponent->Damage(_damageToWalls);
		
		if (TObjectPtr<AAntCharacter> _ant = Cast<AAntCharacter>(_actor))
		{

		_ant->SetKnockBackStatus(true);
		}
		if (_stats)
		{
			if (_damageToAnt != 0)
				_stats->TakeDamage(_damageToAnt);			
		}		
	}
}