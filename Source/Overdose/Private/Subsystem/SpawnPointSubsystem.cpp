#include "Subsystem/SpawnPointSubsystem.h"
#include "NavigationSystem.h"

void USpawnPointSubsystem::Add(TObjectPtr<ASpawnPoint> _spawnPoint)
{
	spawnPoints.Add(_spawnPoint);
}

FVector USpawnPointSubsystem::SpawnAtRandomPoint()
{
	FVector _randomLoc;

	if (spawnPoints.IsEmpty())
		return FVector();

	int _random = FMath::RandRange(0, spawnPoints.Num() - 1);
	while (spawnPoints[_random]->GetUsed() ==true)
	{
		_random = FMath::RandRange(0, spawnPoints.Num() - 1);
	}

	_randomLoc = spawnPoints[_random]->GetActorLocation();

	spawnPoints[_random]->SetUsed(true);

	return _randomLoc;
}

void USpawnPointSubsystem::Reset()
{
	for (TObjectPtr<ASpawnPoint> _spawn : spawnPoints)
		_spawn->SetUsed(false);
}

void USpawnPointSubsystem::RemoveAllPoints()
{
	spawnPoints.Empty();
}