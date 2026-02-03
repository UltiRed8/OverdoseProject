#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Actor/SpawnPoint/SpawnPoint.h"
#include "SpawnPointSubsystem.generated.h"

UCLASS()
class OVERDOSE_API USpawnPointSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category = "Debugs") TArray<TObjectPtr<ASpawnPoint>> spawnPoints = {};

public:
	void Add(TObjectPtr<ASpawnPoint> _spawnPoint);
	FVector SpawnAtRandomPoint();
	void Reset();
	UFUNCTION(BlueprintCallable) void RemoveAllPoints();
};