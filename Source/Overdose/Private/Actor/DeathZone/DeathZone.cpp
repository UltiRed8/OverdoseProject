// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DeathZone/DeathZone.h"
#include <Subsystem/StatSubsystem.h>
#include "Actor/Characters/AntCharacter.h"
#include "Actor/Characters/AntController.h"


ADeathZone::ADeathZone()
{
	PrimaryActorTick.bCanEverTick = true;
	deathZoneGpe = CreateDefaultSubobject<UStaticMeshComponent>("Gpe");
	RootComponent = deathZoneGpe;
	deathZoneGpe->SetGenerateOverlapEvents(true);
	deathZoneGpe->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ADeathZone::NotifyActorBeginOverlap(AActor* _other)
{
	Super::NotifyActorBeginOverlap(_other);

	TObjectPtr<UStatsComponent> _life = _other->GetComponentByClass< UStatsComponent>();
	if (!_life)
	{
		return;
	}
	TObjectPtr<UStatSubsystem> _statSub = GetWorld()->GetGameInstance()->GetSubsystem<UStatSubsystem>();
	if (!_statSub) return;
	TObjectPtr<AAntCharacter> _ant = Cast<AAntCharacter>(_other);

	if (_ant)
	{

		if (!_ant->GetStat())
			return;
		//_statSub->GetStatData(_ant->GetTeamController()->GetTeamID() - 1).damages += _ant->GetStat()->GetCurrentLife();
		//_ant->GetStat()->Kill(true);
		//_ant->Stop(0.1f);
	}
	onPawnTurn.Broadcast(_life);
}



