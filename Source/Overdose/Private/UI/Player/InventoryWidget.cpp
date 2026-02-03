// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Player/InventoryWidget.h"
#include <Components/HorizontalBox.h>
#include "Utils/DevUtils.h"
#include <Actor/Characters/AntController.h>

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Init();
}

void UInventoryWidget::Init()
{
	TObjectPtr<AAntCharacter> _ant = Cast<AAntCharacter>(GetOwningPlayerPawn());
	TObjectPtr<AAntController> _controller = _ant->GetTeamController();
	TObjectPtr<UInventoryComponent> _inventory = _controller->GetInventory();
	if (!_inventory)
		return;

	for (TObjectPtr<UWidget> _widget : mainVerticalBox->GetAllChildren())
	{
		if (TObjectPtr<UVerticalBox> _verticalBox = Cast<UVerticalBox>(_widget))
		{
			for (TObjectPtr<UWidget> _verticalBoxWidget : _verticalBox->GetAllChildren())
			{
				if (TObjectPtr<UHorizontalBox> _horizontalBox = Cast<UHorizontalBox>(_verticalBoxWidget))
				{
					for (TObjectPtr<UWidget> _horizontalBoxWidget : _horizontalBox->GetAllChildren())
					{
						if (TObjectPtr<USlotInventoryWidget> _slot = Cast<USlotInventoryWidget>(_horizontalBoxWidget))
						{
							if (_slot->GetItem())
							{								
								TObjectPtr<AItem> _item = GetWorld()->SpawnActor<AItem>(_slot->GetItem());

								_slot->SetNameSlot(FText::FromString(_item->GetNameItem()));
								_item->Destroy();
								slots.Add(_slot);
							}
						}
					}
				}
			}
		}

	}
}