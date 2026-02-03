#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GPE/Components/ExplosableComponent.h>
#include "PlaceableRubiksCube.generated.h"

UCLASS()
class OVERDOSE_API APlaceableRubiksCube : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Debugs") TObjectPtr<UStaticMeshComponent> mesh = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugs") TObjectPtr<UExplosableComponent> explosableComponent = nullptr;

public:	
	APlaceableRubiksCube();

private:
	virtual void BeginPlay() override;
	void Timer();
	void EndTimer();
};