#include "GPE/Puddle/Puddle.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Actor/Characters/AntCharacter.h>
#include "Kismet/GameplayStatics.h"
#include <Gamemodes/AntGameModeBase.h>
#include "Utils/DevUtils.h"
#include <Subsystem/GameSubsystem.h>

APuddle::APuddle()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->SetupAttachment(RootComponent);
	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void APuddle::BeginPlay()
{
	Super::BeginPlay();

	turnLifeSpan = FMath::RandRange(2, 4);
	RegisterTurnLifeSpan();
}

void APuddle::NotifyActorBeginOverlap(AActor* _other)
{
	if (Cast<AAntCharacter>(_other))
	{
		TriggerEffect(_other);
		onEnterPuddle.Broadcast(_other);
		Remove();
	}
}

void APuddle::NotifyActorEndOverlap(AActor* _other)
{
	if (Cast<AAntCharacter>(_other))
		onExitPuddle.Broadcast(_other);
}

void APuddle::TriggerEffect(AActor* _actor)
{
	if (AAntCharacter* _character = Cast<AAntCharacter>(_actor))
	{
		TObjectPtr<UStatsComponent> _component = _character->GetComponentByClass<UStatsComponent>();
		switch (type)
		{
			case TYPENONE:
				break;
			case POISON:
				UKismetSystemLibrary::PrintString(this, "Poison Puddle!");
				_component->SetIsPoisoined(true);
				break;
			case HEAL:
				UKismetSystemLibrary::PrintString(this, "Heal Puddle!");
				_component->Heal(amount);
				break;
			case DAMAGE:
				UKismetSystemLibrary::PrintString(this, "Damage Puddle!");
				_component->TakeDamage(amount);
				break;
			case FLAME:
				UKismetSystemLibrary::PrintString(this, "Flame Puddle!");
				_component->SetIsOnFire(true);
				break;
		}
	}
}

void APuddle::Remove()
{
	if (removeOnTrigger)
	{
		Destroy();
		onExitPuddle.Broadcast(nullptr);
	}
}

void APuddle::RegisterTurnLifeSpan()
{
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (_subsystem)
		_subsystem->OnTurnStarted().AddDynamic(this, &APuddle::DecrementTurnLifeSpan);
}

void APuddle::DecrementTurnLifeSpan(int _index)
{
	if (turnLifeSpan == 0)
		Destroy();
	turnLifeSpan--;
}