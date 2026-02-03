#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPE/Bags/EnumBagType.h"
#include "GPE/Bags/Bag.h"
#include "GPE/Components/DamagableTerrainComponent.h"
#include "Generator.generated.h"

UCLASS()
class OVERDOSE_API AGenerator : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGenerated);
	UPROPERTY(EditAnywhere, Category = "Debugs") TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") TSubclassOf<ABag> spawnBag = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Sounds") TObjectPtr<USoundWave> generatedSoundEffect = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Sounds") TObjectPtr<USoundWave> generatedSpecificSoundEffect = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category = "Debugs") FOnGenerated onGenerated;
	UPROPERTY(EditAnywhere, Category = "Debugs") bool isRecharged = false;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<UDamagableTerrainComponent> terrainComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<UExplosableComponent> explosableComponent = nullptr;
	 
public:
	FORCEINLINE UFUNCTION(BlueprintCallable) FOnGenerated& OnGenerator()
	{
		return onGenerated;
	}
	
public:	
	AGenerator();

private:
	virtual void BeginPlay() override;
	void SetBagToRandomPosition(ABag* _bag);
	TObjectPtr<ABag> SpawnBag();
	void InitEvents();
	UFUNCTION() void Explode();
	UFUNCTION() void BagOnEvent( const int _index);
};