#pragma once

#include "CoreMinimal.h"
#include "GPE/Items/Tools/Tool.h"
#include "GPE/Items/Tools/PlaceableHealZone.h"
#include "HealZoneTool.generated.h"

UCLASS()
class OVERDOSE_API AHealZoneTool : public ATool
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "Debugs") TSubclassOf<APlaceableHealZone> placeableHealZone = nullptr;

public:
	AHealZoneTool();

private:
	virtual float Use(TObjectPtr<AActor> _user)override;
};