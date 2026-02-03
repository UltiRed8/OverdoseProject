// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DeathZone/LavaDeathZone.h"
#include <Actor/Characters/AntCharacter.h>
#include <Subsystem/StatSubsystem.h>

void ALavaDeathZone::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ALavaDeathZone::Init()
{
	onPawnTurn.AddDynamic(this, &ALavaDeathZone::OnLavaBehavior);
}

void ALavaDeathZone::OnLavaBehavior(UStatsComponent* _life)
{ 
	if (_life)
	{
		_life->Kill(true);
	}
}
