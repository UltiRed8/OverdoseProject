#include "Actor/DestructibleLandActor.h"
#include <Utils/DevUtils.h>

ADestructibleLandActor::ADestructibleLandActor()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = mesh;
	damageTerrain = CreateDefaultSubobject<UDamagableTerrainComponent>("Stats");
	AddOwnedComponent(damageTerrain);

}

void ADestructibleLandActor::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->Mobility = EComponentMobility::Movable;
	if (damageTerrain)
		damageTerrain->OnDamaged().AddDynamic(this, &ADestructibleLandActor::SwitchMesh);
}

void ADestructibleLandActor::SwitchMesh()
{
	if (indexMesh >= allNextMesh.Num())
		return;
	GetMesh()->SetStaticMesh(allNextMesh[indexMesh]);
	indexMesh++;
}