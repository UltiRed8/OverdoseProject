#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GPE/Components/DamagableTerrainComponent.h>
#include "Sound/SoundCue.h"
#include "DestructibleLandActor.generated.h"

UCLASS()
class OVERDOSE_API ADestructibleLandActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere ,Category = "Settings|Meshs") TArray<TObjectPtr<UStaticMesh>> allNextMesh = {};
	UPROPERTY(EditAnywhere, Category = "Settings|Sounds") TObjectPtr<USoundCue> breakingSound = nullptr;
	UPROPERTY(EditAnywhere, Category = "Debugs") TObjectPtr<UDamagableTerrainComponent> damageTerrain = nullptr;
	int indexMesh = 0;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugs|Mesh") TObjectPtr<UStaticMeshComponent> mesh = nullptr;

public:
	FORCEINLINE TObjectPtr<USoundCue> GetBreakingSound()
	{
		return breakingSound;
	}
	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetMesh() const
	{
		return mesh;
	}
	FORCEINLINE void SetMesh(TObjectPtr<UStaticMeshComponent>  _newMesh)
	{
		mesh = _newMesh;
	}
	FORCEINLINE TObjectPtr<UDamagableTerrainComponent> GetStat() const
	{
		return damageTerrain;
	}

public:	
	ADestructibleLandActor();

private:
	virtual void BeginPlay() override;

public:
	UFUNCTION() void SwitchMesh();
};