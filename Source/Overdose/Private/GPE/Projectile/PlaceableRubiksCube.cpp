#include "GPE/Projectile/PlaceableRubiksCube.h"

APlaceableRubiksCube::APlaceableRubiksCube()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = mesh;
	explosableComponent = CreateDefaultSubobject<UExplosableComponent>("ExplosableComponent");
	AddOwnedComponent(explosableComponent);
}

void APlaceableRubiksCube::BeginPlay()
{
	Super::BeginPlay();
	Timer();
}

void APlaceableRubiksCube::Timer()
{
	FTimerHandle _timer = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(_timer, this, &APlaceableRubiksCube::EndTimer, 2);
}

void APlaceableRubiksCube::EndTimer()
{
	explosableComponent->Explode();
	Destroy();
}