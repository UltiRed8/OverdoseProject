#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include <GPE/Puddle/Puddle.h>
#include "AntPlayerState.generated.h"

UCLASS()
class OVERDOSE_API AAntPlayerState : public APlayerState
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "State") bool canPlay = true;
	UPROPERTY(EditAnywhere , Category = "Puddle") TEnumAsByte<EPuddleType> deathPuddleType = POISON;

public:
	FORCEINLINE EPuddleType GetDeathPuddleType()
	{
		return deathPuddleType;
	}

	FORCEINLINE void SetDeathPuddleType(const EPuddleType& _deathPuddleType)
	{
		deathPuddleType = _deathPuddleType;
	}

	FORCEINLINE void SetCanPlay(const bool _status)
	{
		canPlay = _status;
	}

	FORCEINLINE bool GetCanPlay()
	{
		return canPlay;
	}
};