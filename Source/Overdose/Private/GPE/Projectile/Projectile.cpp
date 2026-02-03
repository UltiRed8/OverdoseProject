#include "GPE/Projectile/Projectile.h"
#include "Utils/DevUtils.h"
#include <Actor/Characters/AntCharacter.h>

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	splineLine = CreateDefaultSubobject<USplineComponent>("SplineLine");
	RootComponent = splineLine;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->SetupAttachment(splineLine);
	AddOwnedComponent(mesh);
	mesh->SetWorldLocation(GetActorLocation());
	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	explosableComponent = CreateDefaultSubobject<UExplosableComponent>("ExplosableComponent");
	AddOwnedComponent(explosableComponent);
	currentProjectilePosition = GetActorLocation();
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	onSpawn.Broadcast();
	currentProjectilePosition = GetActorLocation();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePosition();
	Explosion();
}

void AProjectile::UpdatePosition()
{
	percent += GetWorld()->GetDeltaSeconds() * speed;
	percent = percent > 1.0 ? 1.0 : percent;
	currentProjectilePosition = splineLine->GetLocationAtTime(percent, ESplineCoordinateSpace::World, true);
	mesh->SetWorldLocation(currentProjectilePosition);
}

void AProjectile::Explosion()
{
	if (percent != 1.0f)
		return;
	onEndMovement.Broadcast();
	explosableComponent->Explode();
	Destroy();
}

void AProjectile::NotifyActorBeginOverlap(AActor* _other)
{
	if (!_other)
		return;
	if (shouldHaveOwner)
	{
		if (!projectileOwner)
		{
			if (Cast<AAntCharacter>(_other))
			{
				projectileOwner = _other;
			}
			return;
		}
		if (_other == projectileOwner)
			return;
	}
	TObjectPtr<AActor> _otherOwner = _other->GetOwner();
	if (_otherOwner && _otherOwner == projectileOwner)
		return;
	onHitActor.Broadcast(_other);
	CheckHitActor(_other);
	Destroy();
}

void AProjectile::CheckHitActor(TObjectPtr<AActor> _actor)
{
	if (IsExplode())
	{
		isExplode = false;
		explosableComponent->Explode();
	}
}

void AProjectile::AddIgnoredActor(TObjectPtr<AActor> _actor)
{
	projectileOwner = _actor;
}