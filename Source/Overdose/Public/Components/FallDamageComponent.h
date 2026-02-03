#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FallDamageComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERDOSE_API UFallDamageComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Debugs") bool isFalling = false;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") int heighestPoint = 0;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") TObjectPtr<ACharacter> owner = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") int heightTreshold = 500;
	UPROPERTY(EditAnywhere, Category = "Settings") float fallDamageMultiplier = 1.0f;

public:
	UFallDamageComponent();
private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ApplyDamages();
};