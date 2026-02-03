#include "GPE/Items/Item.h"
#include "Kismet/GameplayStatics.h"
#include <Gamemodes/AntGameModeBase.h>
#include <Utils/DevUtils.h>
#include <Subsystem/GameSubsystem.h>

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = mesh;
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void AItem::CheckUses()
{
	if (usesAmount > 0)
		return;
	onNoMoreUses.Broadcast(usesAmount);
	FTimerHandle _timer;
	GetWorld()->GetTimerManager().SetTimer(_timer, this, &AItem::Delete, removeDelay + 0.1f);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle _delay;
}

float AItem::Use(TObjectPtr<AActor> _user)
{
	if (lockedTurns >= 1)
		return -1.0f;
	if (limitedUses && usesAmount <= 0) // peut etre enlever le usesAmount de la verification
		return -1.0f;
	onItemUsed.Broadcast();

	if (!limitedUses)
		return -1.0f;
	usesAmount--;
	isUse = true;
	CheckUses();
	return removeDelay;
}

void AItem::ForceDestroy()
{
	if (isUse)
		Destroy();
}

void AItem::RegisterEndTurn()
{
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (_subsystem)
	{
		_subsystem->OnTurnEnded().AddDynamic(this, &AItem::ForceDestroy);
	}
}

void AItem::Store()
{
	if (isStore)
		return;
	
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	isStore = true;

	SheathWeaponSound();
}

void AItem::Take()
{
	if (!isStore) return;
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	isStore = false;
	DrawWeaponSound();
}

void AItem::Delete()
{
	Destroy();
}

void AItem::SheathWeaponSound()
{
	if (!sheathSound)
		return;
	UGameplayStatics::PlaySoundAtLocation(this, sheathSound, GetActorLocation());
}

void AItem::DrawWeaponSound()
{
	if (!drawSound)
		return;
	UGameplayStatics::PlaySoundAtLocation(this, drawSound, GetActorLocation());
}