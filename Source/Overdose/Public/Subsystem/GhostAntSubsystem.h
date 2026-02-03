// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <Actor/Characters/GhostAntCharacter.h>
#include "GhostAntSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class OVERDOSE_API UGhostAntSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	UPROPERTY() TArray<TObjectPtr<AGhostAntCharacter>> ghostAnts = {};

public:
	void AddGhost(TObjectPtr<AGhostAntCharacter> _ghost);
	UFUNCTION(BlueprintCallable) void RemoveAllGhostAnts();
};
