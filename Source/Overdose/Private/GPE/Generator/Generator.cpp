#include "GPE/Generator/Generator.h"
#include "NavigationSystem.h"
#include "Utils/DevUtils.h"
#include "Gamemodes/AntGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include <Subsystem/SpawnPointSubsystem.h>
#include <Subsystem/GameSubsystem.h>

AGenerator::AGenerator()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	terrainComponent = CreateDefaultSubobject<UDamagableTerrainComponent>("DamagableTerrain");
	AddOwnedComponent(terrainComponent);

	explosableComponent = CreateDefaultSubobject<UExplosableComponent>("ExplosableComponent");
	AddOwnedComponent(explosableComponent);

}

void AGenerator::BeginPlay()
{
	Super::BeginPlay();
	InitEvents();
	terrainComponent->OnDestroyed().AddDynamic(this, &AGenerator::Explode);
}

void AGenerator::SetBagToRandomPosition(ABag* _bag)
{
	TObjectPtr<USpawnPointSubsystem> _sub = GetWorld()->GetGameInstance()->GetSubsystem< USpawnPointSubsystem>();
	if (!_sub)
		return;
	_bag->SetActorLocation(_sub->SpawnAtRandomPoint());
}

TObjectPtr<ABag> AGenerator::SpawnBag()
{
	isRecharged = false;
	TObjectPtr<ABag> _bag = nullptr;
	_bag = GetWorld()->SpawnActor<ABag>(spawnBag, GetActorLocation(), FRotator(0,0,0));
	if (_bag)
		SetBagToRandomPosition(_bag);
	onGenerated.Broadcast();
	return _bag;
}

void AGenerator::InitEvents()
{
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (_subsystem)
		_subsystem->onTurnStarted.AddDynamic(this, &AGenerator::BagOnEvent);
}



void AGenerator::Explode()
{
	explosableComponent->Explode();
	LOG("EXPLOSION GENERATOR");
}

void AGenerator::BagOnEvent( const int _index)
{
	if (isRecharged)
		SpawnBag();
	else isRecharged = true;
}