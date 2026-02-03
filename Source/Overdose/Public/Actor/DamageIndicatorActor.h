#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/TextRenderComponent.h>
#include "DamageIndicatorActor.generated.h"

UCLASS()
class OVERDOSE_API ADamageIndicatorActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Settings") TObjectPtr<UTextRenderComponent> text;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") int amount = 0;

public:
	FORCEINLINE void SetDamagesAmount(int _amount)
	{
		amount = _amount;
	}

public:	
	ADamageIndicatorActor();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable) void UpdateText();
};