#include "UI/Player/PlayerLifeBarWidget.h"
#include <Subsystem/AntSubsystem.h>
#include <Actor/Characters/AntController.h>
#include "Utils/DevUtils.h"
#include "Kismet/GameplayStatics.h"

void UPlayerLifeBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Cast<AAntController>(GetOwningPlayer())->OnSwitch().AddDynamic(this, &UPlayerLifeBarWidget::OnSwitchUpdate);
	OnSwitchUpdate();
}

void UPlayerLifeBarWidget::OnAddLife(float _percent)
{
	lifeProgressBar->SetPercent(_percent);
}

void UPlayerLifeBarWidget::OnTakeDamage(float _percent)
{
	lifeProgressBar->SetPercent(_percent);
}

void UPlayerLifeBarWidget::SetHidden()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerLifeBarWidget::OnSwitchUpdate()
{
	TObjectPtr<AAntCharacter> _player = Cast<AAntCharacter>(GetOwningPlayerPawn());
	if (!_player)
	{
		SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	lifeProgressBar->SetPercent(_player->GetStat()->GetCurrentLifeInPercent());
	SetVisibility(ESlateVisibility::Visible);
}