// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/DeathZone/DeathZone.h"
#include "LavaDeathZone.generated.h"

/**
 * 
 */
UCLASS()
class OVERDOSE_API ALavaDeathZone : public ADeathZone
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	void Init();
	UFUNCTION() void OnLavaBehavior(UStatsComponent* _life);
	
};
