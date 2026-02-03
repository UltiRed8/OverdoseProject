#include "Components/FallDamageComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Utils/DevUtils.h"
#include <Actor/Characters/AntCharacter.h>
#include <Subsystem/ChatSubsystem.h>

UFallDamageComponent::UFallDamageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFallDamageComponent::BeginPlay()
{
	Super::BeginPlay();
	owner = Cast<ACharacter>(GetOwner());
}

void UFallDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!owner)
		return;
	if (owner->GetCharacterMovement()->IsFalling() && !isFalling)
	{
		isFalling = true;
		heighestPoint = owner->GetActorLocation().Z;
	}
	else if (!owner->GetCharacterMovement()->IsFalling() && isFalling)
	{
		isFalling = false;
		ApplyDamages();
	}
	if (!isFalling)
		return;
	heighestPoint = owner->GetActorLocation().Z > heighestPoint ? owner->GetActorLocation().Z : heighestPoint;
}

void UFallDamageComponent::ApplyDamages()
{
	float _distance = heighestPoint - owner->GetActorLocation().Z;
	if (_distance >= heightTreshold)
	{
		_distance /= 10.0f;
		_distance /= 2.0f;
		_distance *= fallDamageMultiplier;
		AAntCharacter* _ant = dynamic_cast<AAntCharacter*>(owner.Get());
		if (!_ant)
			return;
		UStatsComponent* _stats = _ant->GetStat();
		if (!_stats)
			return;
		_stats->TakeDamage(_distance);
		GetWorld()->GetGameInstance()->GetSubsystem<UChatSubsystem>()->DamageByFall(_ant->GetName());
	}
}