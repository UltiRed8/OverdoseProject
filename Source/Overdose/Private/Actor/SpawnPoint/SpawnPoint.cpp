

#include "Actor/SpawnPoint/SpawnPoint.h"
#include "Subsystem/SpawnPointSubsystem.h"

ASpawnPoint::ASpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	Register();
}

void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnPoint::Register()
{
	TObjectPtr<USpawnPointSubsystem> _sub = GetWorld()->GetGameInstance()->GetSubsystem< USpawnPointSubsystem>();
	if (!_sub)
		return;

	_sub->Add(this);
}

