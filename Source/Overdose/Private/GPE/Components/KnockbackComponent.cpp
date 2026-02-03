#include "GPE/Components/KnockbackComponent.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include "Actor/Characters/AntController.h"
#include <Actor/Characters/AntCharacter.h>
#include "Utils/DevUtils.h"
#include <Actor/DestructibleLandActor.h>

UKnockbackComponent::UKnockbackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UKnockbackComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* _owner = GetOwner();
	if (AAntCharacter* _ant = Cast<AAntCharacter>(_owner))
		_ant->OnDebug().AddDynamic(this, &UKnockbackComponent::Debug);
}

void UKnockbackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckWall();
}

void UKnockbackComponent::CheckWall()
{
	TObjectPtr<AActor> _owner = GetOwner();
	AAntCharacter* _ant = Cast<AAntCharacter>(_owner);
	if (_ant->GetGhost()) return;
	double _globalVelocity = GlobalVelocity();

	if (GlobalVelocity() <= damagingVelocityTreshold)
		return;

	FVector _start = _owner->GetActorLocation();
	FVector _end = _start + _owner->GetVelocity() * 0.05;
	FHitResult _results;
	
	FCollisionQueryParams _params;
	_params.AddIgnoredActor(_owner);
	if (GetWorld()->LineTraceSingleByChannel(_results, _start, _end, ECollisionChannel::ECC_MAX, _params))
	{
		TObjectPtr<AGhostAntCharacter> _ghost = Cast< AGhostAntCharacter>(_results.GetActor());
		if (_ghost)
			return;
		TObjectPtr<UCharacterMovementComponent> _movement = _owner->GetComponentByClass<UCharacterMovementComponent>();
		if (!_movement)
			return;
		_movement->AddImpulse(_owner->GetVelocity() * -1.0f, true);
		
		if (_ant)
		{
			_globalVelocity = (_globalVelocity - damagingVelocityTreshold) / 100 * damageVelocityMultiplier;
			if (_globalVelocity > 35)
				_globalVelocity = 35;
			_ant->GetStat()->TakeDamage(_globalVelocity);
		}
		if (TObjectPtr<UDamagableTerrainComponent> _component = _results.GetActor()->GetComponentByClass<UDamagableTerrainComponent>())
		{
			int _damageToTerrain = _globalVelocity * terrainDamageVelocityMultiplier ;
			_component->Damage(_damageToTerrain);
		}
	}
}

double UKnockbackComponent::GlobalVelocity()
{
	FVector _velocity = GetOwner()->GetVelocity();
	double _globalVelocity = abs(_velocity.X) + abs(_velocity.Y) + abs(_velocity.Y);
	return _globalVelocity;
}

void UKnockbackComponent::ApplyKnockback(const float _strength,  FVector _direction)
{
	TObjectPtr<AActor> _owner = GetOwner();
	if (!_owner)
	{
		LOG("BOMBOCLATT");
		return;
	}

	FVector _currentVelocity = _owner->GetVelocity();
	_currentVelocity += _direction * _strength * knockbackMultiplier;
	_currentVelocity += FVector(0.0f, 0.0f, 0.1f) * _strength * knockbackMultiplier;
	_currentVelocity.Z = FMath::Clamp(_currentVelocity.Z ,-450, 450);
	TObjectPtr<UCharacterMovementComponent> _movement = _owner->GetComponentByClass<UCharacterMovementComponent>();
	if (TObjectPtr<AAntCharacter> _ant = Cast<AAntCharacter>(_owner))
	{
		_ant->SetKnockBackStatus(true);
		//LOG(_owner->GetVelocity().ToString());
	//LOG("BONBOCLATTT");
	}
	if (!_movement)
		return;
	_movement->AddImpulse(_currentVelocity, true);
	//_owner->SetActorRotation(FRotator(_direction.X, _direction.Y, _direction.Z));
	//LOG(_owner->GetVelocity().ToString());
}

void UKnockbackComponent::Debug()
{
	ApplyKnockback(100, GetOwner()->GetActorForwardVector());
}