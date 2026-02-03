// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/Items/Weapons/ProjectileWeapon.h"

AProjectileWeapon::AProjectileWeapon()
{
	spline = CreateDefaultSubobject<USplineComponent>("Spline");

	spline->SetHiddenInGame(!isSplineVisible);
	spline->SetupAttachment(RootComponent);
}