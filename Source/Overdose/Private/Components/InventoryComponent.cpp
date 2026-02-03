#include "Components/InventoryComponent.h"
#include "Utils/DevUtils.h"
#include <GPE/Items/Weapons/Bazooka.h>
#include <GPE/Items/Weapons/FallingMokia.h>
#include <GPE/Items/Weapons/Rasputin.h>
#include <GPE/Items/Weapons/RubiksCube.h>
#include <GPE/Items/Tools/HealZoneTool.h>
#include <GPE/Items/Tools/Teleporter.h>
#include <Subsystem/GameSubsystem.h>

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	_subsystem->OnTurnTimerEnded().AddDynamic(this, &UInventoryComponent::DecrementeLockedTurnsForAllItem);

}

void UInventoryComponent::Init()
{
	Reset();
	for (int _index = 0; _index < 4; _index++)
	{
		TObjectPtr<AWeapon> _newItem = nullptr;

		switch (_index)
		{
		case 0:
			_newItem = NewObject<ABazooka>();
			_newItem->SetUsesAmount(10);
			break;
		case 1:
			_newItem = NewObject<AFallingMokia>();
			_newItem->SetUsesAmount(1);
			_newItem->SetLockedTurns(2);
			break;
		case 2:
			_newItem = NewObject<ARasputin>();
			_newItem->SetUsesAmount(1);
			_newItem->SetLockedTurns(3);
			break;
		case 3:
			_newItem = NewObject<ARubiksCube>();
			_newItem->SetUsesAmount(5);
			break;
		default:
			break;
		}
		AddWeapon(_newItem);
	}

	for (int _index = 0; _index < 2; _index++)
	{
		TObjectPtr<ATool> _newItem = nullptr;

		switch (_index)
		{
		case 0:
			_newItem = NewObject<AHealZoneTool>();
			_newItem->SetUsesAmount(1);
			break;
		case 1:
			_newItem = NewObject<ATeleporter>();
			_newItem->SetUsesAmount(2);
			break;
		default:
			break;
		}
		AddTool(_newItem);
	}
}

void UInventoryComponent::InitTuto()
{
	TObjectPtr<AWeapon> _newWeapon = nullptr;
	_newWeapon = NewObject<ABazooka>();
	_newWeapon->SetUsesAmount(20);

	AddWeapon(_newWeapon);

	TObjectPtr<ATool> _newTool = nullptr;

	_newTool = NewObject<ATeleporter>();
	_newTool->SetUsesAmount(1);

	AddTool(_newTool);
}

void UInventoryComponent::DecrementeLockedTurnsForAllItem()
{
	for (TObjectPtr<USlot> _slot : slots)
	{
		if (_slot && _slot->lockedTurns > 0)
			_slot->lockedTurns--;
	}
}

void UInventoryComponent::AddWeapon(TObjectPtr<AWeapon> _weapon)
{
	if (slots.Num() <= 0)
	{
		TObjectPtr<USlot> _newSlot = NewObject<USlot>(this);
		_newSlot->SetItemSlot(_weapon);
		slots.Add(_newSlot);
		return;
	}
	for (TObjectPtr<USlot> _slot : slots)
	{
		if (!_slot->item)
		{
			continue;
		}
		if (_weapon->GetClass() == _slot->item->GetClass())
		{
			_slot->amount++;
			return;
		}
	}
	TObjectPtr<USlot> _newSlot = NewObject<USlot>(this);
	_newSlot->SetItemSlot(_weapon);
	slots.Add(_newSlot);
	return;
}

void UInventoryComponent::AddTool(TObjectPtr<ATool> _tool)
{
	if (slots.Num() <= 0)
	{
		TObjectPtr<USlot> _newSlot = NewObject<USlot>(this);
		_newSlot->SetItemSlot(_tool);
		slots.Add(_newSlot);
		return;
	}
	for (TObjectPtr<USlot> _slot : slots)
	{
		if (!_slot->item)
		{
			continue;
		}
		if (_tool->GetClass() == _slot->item->GetClass())
		{
			_slot->amount++;
			return;
		}
	}
	TObjectPtr<USlot> _newSlot = NewObject<USlot>(this);
	_newSlot->SetItemSlot(_tool);
	slots.Add(_newSlot);
	return;
}

void USlot::SetItemSlot(TObjectPtr<AItem> _item)
{
	item = _item;
	amount = _item->GetUsesAmount();
	lockedTurns = _item->GetLockedTurns();
}

int USlot::GetAmount()
{
	return amount;
}

int& USlot::GetLockedTurns()
{
	return lockedTurns;
}

void UInventoryComponent::Reset()
{
	slots.Empty();
}
AItem* USlot::GetItem()
{
	return item;
}

void USlot::AddAmount()
{
	amount++;
}

void USlot::DecreaseAmount()
{
	amount--;
}