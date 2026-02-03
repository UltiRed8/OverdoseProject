#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPE/Bags/EnumBagType.h"
#include "Components/InventoryComponent.h"
#include <Components/TextRenderComponent.h>
#include "Bag.generated.h"

UCLASS()
class OVERDOSE_API ABag : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Debugs") TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Debugs") TObjectPtr<UTextRenderComponent> text = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") TEnumAsByte<EBagType> bagType = NONE;
	UPROPERTY(EditAnywhere, Category = "Settings") bool destroyOnPickup = true;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") int itemId = -1;
	UPROPERTY(EditAnywhere, Category = "Settings") int turnLifeSpan = 3;

public:	
	FORCEINLINE void SetBagType(TEnumAsByte<EBagType> _newType) { bagType = _newType; }
	ABag();

private:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* _other);
	void CheckRemove();
	TObjectPtr<AWeapon> GiveRandomWeapon();
	TObjectPtr<ATool> GiveRandomTool();
	void RegisterTurnLifeSpan();
	UFUNCTION() void DecrementLifeSpan(int _index);

};