#include "UI/Player/SlotInventoryWidget.h"
#include "Kismet/GameplayStatics.h"

void USlotInventoryWidget::PlaySoundOnClick()
{
	if (!soundOnClick)
		return;
	FVector _location = GetOwningPlayerPawn()->GetActorLocation();
	UGameplayStatics::PlaySoundAtLocation(this, soundOnClick, _location);
}

void USlotInventoryWidget::CloseMenu()
{
	SetVisibility(ESlateVisibility::Hidden);
}