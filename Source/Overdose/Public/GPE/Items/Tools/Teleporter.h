#pragma once
#include "CoreMinimal.h"
#include "GPE/Items/Tools/Tool.h"
#include "Teleporter.generated.h"

UCLASS()
class OVERDOSE_API ATeleporter : public ATool
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeleported, AActor*, _actor);
	FOnTeleported onTeleported;

	UPROPERTY(EditAnywhere, Category = "Settings|Sounds") TObjectPtr<USoundWave> teleportSound = nullptr;
public:
	FORCEINLINE FOnTeleported& OnTeleported()
	{
		return onTeleported;
	}

public:
	ATeleporter();

private:
	virtual float Use(TObjectPtr<AActor> _user) override;

	void TeleportActor(TObjectPtr<AActor> _user);
};