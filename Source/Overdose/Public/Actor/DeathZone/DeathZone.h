// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StatsComponent.h"
#include "DeathZone.generated.h"

UCLASS()
class OVERDOSE_API ADeathZone : public AActor
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnTurn, class UStatsComponent*, _statistique);
	UPROPERTY(EditAnywhere, Category = "GPE/DeathZone") TObjectPtr<UStaticMeshComponent> deathZoneGpe = nullptr;

protected:
	FOnPawnTurn onPawnTurn;
	
public:	
	ADeathZone();

protected:
	virtual void NotifyActorBeginOverlap(AActor* _other);
};
