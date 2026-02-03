#include "GPE/Items/Tools/PlaceableHealZone.h"
#include "Kismet/GameplayStatics.h"
#include <Gamemodes/AntGameModeBase.h>
#include <Components/StatsComponent.h>
#include <Subsystem/GameSubsystem.h>
#include <Utils/DevUtils.h>

APlaceableHealZone::APlaceableHealZone()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = mesh;
}

void APlaceableHealZone::BeginPlay()
{
	Super::BeginPlay();
	RegisterTurnLifeSpan();

	TObjectPtr<UGameSubsystem> _sub = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem >();
	if (!_sub)
		return;

	_sub->OnRoundStarted().AddDynamic(this, &APlaceableHealZone::ClearList);

}

void APlaceableHealZone::NotifyActorBeginOverlap(AActor* _other)
{
	if (!_other)
		return;
	AAntCharacter* _ant = Cast<AAntCharacter>(_other);

	if (allAnts.Contains(_ant))
		return;

	if (_ant)
	{
		allAnts.Add(_ant);
		TObjectPtr<UStatsComponent> _stats = _other->GetComponentByClass<UStatsComponent>();
		if (!_stats)
			return;
		_stats->Heal(25);
		onHealzoneSpawned.Broadcast();
	}
}


void APlaceableHealZone::RegisterTurnLifeSpan()
{
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (_subsystem)
	{
		_subsystem->OnTurnStarted().AddDynamic(this, &APlaceableHealZone::DecrementTurnLifeSpan);
	}
}

void APlaceableHealZone::DecrementTurnLifeSpan(int _index)
{
	if (turnLifeSpan == 0)
		Destroy();
	
	turnLifeSpan--;
}

void APlaceableHealZone::ClearList(const int _index)
{
	allAnts.Empty();
}


