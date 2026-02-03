#include "GPE/Bags/Bag.h"
#include "Utils/DevUtils.h"
#include "Components/StatsComponent.h"
#include "GPE/Items/Tools/Teleporter.h"
#include "GPE/Items/Tools/HealZoneTool.h"
#include "GPE/Items/Weapons/RubiksCube.h"
#include "GPE/Items/Weapons/Rasputin.h"
#include "GPE/Items/Weapons/FallingMokia.h"
#include "GPE/Items/Weapons/Bazooka.h"
#include "Actor/Characters/AntCharacter.h"
#include "Actor/Characters/AntController.h"
#include <Subsystem/GameSubsystem.h>


ABag::ABag()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	AddOwnedComponent(mesh);
	text = CreateDefaultSubobject<UTextRenderComponent>("Text");
	text->SetupAttachment(mesh);
	text->SetText(FText::FromString("UNKNOWN"));
}

void ABag::BeginPlay()
{
	Super::BeginPlay();
	itemId = FMath::RandRange(0, bagType == WEAPONS ? 3 : 1);
	if (bagType == HEALS) text->SetText(FText::FromString("+25HP"));
	else if (itemId == 0) text->SetText(FText::FromString(bagType == WEAPONS ? "Bazooka" : "Teleporter"));
	else if (itemId == 1) text->SetText(FText::FromString(bagType == WEAPONS ? "Rubik's Cube" : "Heal Zone"));
	else if (itemId == 2) text->SetText(FText::FromString("Rasputin"));
	else if (itemId == 3) text->SetText(FText::FromString("Falling Mokia"));

	RegisterTurnLifeSpan();
}

void ABag::NotifyActorBeginOverlap(AActor* _other)
{
	Super::NotifyActorBeginOverlap(_other);
	TObjectPtr<UStatsComponent> _life = _other->GetComponentByClass<UStatsComponent>();
	TObjectPtr<UInventoryComponent> _inventory = nullptr;
	if (TObjectPtr<AAntCharacter> _ant = Cast<AAntCharacter>(_other))
	{
		TObjectPtr<AAntController> _controller = _ant->GetTeamController();
		_inventory = _controller->GetInventory();
	}
	if (!_inventory)
		return;
	if (!_life)
		return;
	switch (bagType)
	{
		case HEALS:
			_life->Heal(25);
			_life->SetIsPoisoined(false);
			_life->SetIsOnFire(false);
			break;
		case WEAPONS:
			_inventory->AddWeapon(GiveRandomWeapon());
			break;
		case TOOLS:
			_inventory->AddTool(GiveRandomTool());
			break;
	}
	CheckRemove();
}

void ABag::CheckRemove()
{
	if (!destroyOnPickup)
		return;
	Destroy();
}

TObjectPtr<AWeapon> ABag::GiveRandomWeapon()
{
	TObjectPtr<AWeapon> _newWeapon = nullptr;
	switch (itemId)
	{
		case 0:
			_newWeapon = NewObject<ABazooka>();
			break;
		case 1:
			_newWeapon = NewObject <ARubiksCube>();
			break;
		case 2:
			_newWeapon = NewObject <ARasputin>();
			break;
		case 3:
			_newWeapon = NewObject <AFallingMokia>();
			break;
		default:
			break;
	}
	return _newWeapon;
}

TObjectPtr<ATool> ABag::GiveRandomTool()
{
	TObjectPtr<ATool> _newTool = nullptr;
	switch (itemId)
	{
		case 0:
			_newTool = NewObject<ATeleporter>();
			break;
		case 1 :
			_newTool = NewObject <AHealZoneTool>();
			break;
		default:
			break;
	}
	return _newTool;
}

void ABag::RegisterTurnLifeSpan()
{
	TObjectPtr<UGameSubsystem> _sub = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (!_sub)
		return;

	_sub->OnTurnStarted().AddDynamic(this, &ABag::DecrementLifeSpan);
}

void ABag::DecrementLifeSpan(int _index)
{
	if (turnLifeSpan == 0)
		Destroy();

	turnLifeSpan--;
}
