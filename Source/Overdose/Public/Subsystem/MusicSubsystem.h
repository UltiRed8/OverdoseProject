#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MusicSubsystem.generated.h"

UCLASS()
class OVERDOSE_API UMusicSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeatTrigger);
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOnBeatTrigger onBeatTrigger;

public:
	FORCEINLINE UFUNCTION(BlueprintCallable) FOnBeatTrigger& OnBeatTrigger()
	{
		return onBeatTrigger;
	}
};