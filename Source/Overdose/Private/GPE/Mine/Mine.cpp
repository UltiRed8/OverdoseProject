#include "GPE/Mine/Mine.h"
#include <Utils/DevUtils.h>
#include "GPE/Components/DamagableTerrainComponent.h"
#include "Components/StatsComponent.h"
#include "GPE/Components/KnockbackComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include <Actor/Characters/AntCharacter.h>

AMine::AMine()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("RootComponent");
	RootComponent = mesh;
	mesh->SetGenerateOverlapEvents(true);
	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	explosableComponent = CreateDefaultSubobject<UExplosableComponent>("ExplosableComponent");
	AddOwnedComponent(explosableComponent);
}

void AMine::NotifyActorBeginOverlap(AActor* _other)
{
	Super::NotifyActorBeginOverlap(_other);
	
	if (TObjectPtr<AAntCharacter> _ant = dynamic_cast<AAntCharacter*>(_other))
	{
		FTimerHandle _timer;
		GetWorldTimerManager().SetTimer(_timer, this,&AMine::Explosion, 2);
	}
}

void AMine::Explosion()
{
	explosableComponent->Explode();
	Destroy();
}