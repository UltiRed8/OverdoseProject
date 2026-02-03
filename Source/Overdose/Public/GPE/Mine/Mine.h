#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GPE/Components/ExplosableComponent.h>
#include "Mine.generated.h"

UCLASS()
class OVERDOSE_API AMine : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Debugs") TObjectPtr<UStaticMeshComponent> mesh = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugs") TObjectPtr<UExplosableComponent> explosableComponent = nullptr;
	
public:	
	AMine();

protected:
	virtual void NotifyActorBeginOverlap(AActor* _other);
	void Explosion();
};