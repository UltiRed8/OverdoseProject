#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor/Characters/AntCharacter.h"
#include "PlaceableHealZone.generated.h"

UCLASS()
class OVERDOSE_API APlaceableHealZone : public AActor
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealzoneSpawned);
	UPROPERTY(EditAnywhere, Category = "Setting")TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setting") int turnLifeSpan = 3;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") TArray<TObjectPtr<AAntCharacter>> allAnts = {};
	FOnHealzoneSpawned onHealzoneSpawned;
	
public:	
	APlaceableHealZone();

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* _other);
	void RegisterTurnLifeSpan();
	UFUNCTION() void DecrementTurnLifeSpan(int _index);
	void ClearList(const int _index);

};
