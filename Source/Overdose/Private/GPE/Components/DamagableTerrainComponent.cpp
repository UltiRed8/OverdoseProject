#include "GPE/Components/DamagableTerrainComponent.h"
#include <Utils/DevUtils.h>
#include <Actor/DestructibleLandActor.h>
#include <Kismet/GameplayStatics.h>
#include <Subsystem/StatSubsystem.h>

void UDamagableTerrainComponent::RemoveActor()
{
	onDestroyed.Broadcast();
	if (TObjectPtr<ADestructibleLandActor> _landActor = Cast<ADestructibleLandActor>(GetOwner()))
	{
		if (TObjectPtr<USoundCue> _sound = _landActor->GetBreakingSound())
		{
			UGameplayStatics::PlaySoundAtLocation(this, _sound, _landActor->GetActorLocation());
		}
	}

	GetOwner()->Destroy();

	TObjectPtr<UStatSubsystem> _statSub = GetWorld()->GetGameInstance()->GetSubsystem<UStatSubsystem>();
	if (!_statSub)
		return;
	_statSub->GetStatData(0).terrainDestroyed ++;

}
void UDamagableTerrainComponent::Damage(const int& _amount)
{
	if (GetOwner()->IsActorBeingDestroyed())
		return;
	if (life.IsEmpty())
	{
		RemoveActor();
		return;
	}
	life[0] -= _amount;
	//LOG(FString::FromInt(_amount));
	if (life[0] <= 0)
	{
		if (life.Num() >= 2)
		{
			life[0] -= life[1];
		}
		life.RemoveAt(0);
		onDamaged.Broadcast();
	}
}
