// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"


UCLASS()
class OVERDOSE_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	bool used = false;
	
public:	
	FORCEINLINE bool GetUsed() { return used; }
	FORCEINLINE void SetUsed(const bool _status) {  used = _status; }
	ASpawnPoint();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void Register();

};
