#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <Actor/Characters/AntCharacter.h>
#include "AntSubsystem.generated.h"

UCLASS()
class OVERDOSE_API UAntSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	UPROPERTY() TArray<TObjectPtr<AAntCharacter>> ants = {};

public:
	UFUNCTION(BlueprintCallable) FORCEINLINE TArray<AAntCharacter*> GetAnts() const
	{
		return ants;
	}

public:
	void AddAnt(TObjectPtr<AAntCharacter> _ant);
	UFUNCTION(BlueprintCallable) void RemoveAllAnts();
};