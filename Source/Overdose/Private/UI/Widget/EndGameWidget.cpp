#include "UI/Widget/EndGameWidget.h"
#include <Subsystem/TeamInfoSubsystem.h>
#include <Subsystem/StatSubsystem.h>

void UEndGameWidget::Open(TArray<AAntController*> _controllers)
{
	TObjectPtr<UTeamInfoSubsystem> _subsystemTeamInfo = GetWorld()->GetGameInstance()->GetSubsystem<UTeamInfoSubsystem>();
	TArray<FTeamData> _teamDatas = _subsystemTeamInfo->GetTeamDatas();

	if (_teamDatas[_controllers[0]->GetTeamID() - 1].winAmount > _teamDatas[_controllers[1]->GetTeamID() - 1].winAmount)
	{
		nameTeamTextBlock->SetText(FText::FromString(_controllers[0]->GetTeamName()));
	}
	else
	{
		nameTeamTextBlock->SetText(FText::FromString(_controllers[1]->GetTeamName()));
	}

	team1Name->SetText(FText::FromString(_teamDatas[_controllers[0]->GetTeamID() - 1].name));
	team1Score->SetText(FText::FromString("Score : " + (FString::FromInt(_teamDatas[_controllers[0]->GetTeamID() - 1].winAmount))));

	team2Name->SetText(FText::FromString(_teamDatas[_controllers[1]->GetTeamID() - 1].name));
	team2Score->SetText(FText::FromString("Score : " + (FString::FromInt(_teamDatas[_controllers[1]->GetTeamID() - 1].winAmount))));

	TObjectPtr<UStatSubsystem> _subStat = GetWorld()->GetGameInstance()->GetSubsystem<UStatSubsystem>();
	TArray<FStatData> _statData = _subStat->GetStatDatas();

	team1DamageTaken->SetText(FText::FromString("Damage Taken : " + FString::FromInt(_statData[_controllers[0]->GetTeamID() - 1].damages)));
	team2DamageTaken->SetText(FText::FromString("Damage Taken : " + FString::FromInt(_statData[_controllers[1]->GetTeamID() - 1].damages)));

	team1ItemPickup->SetText(FText::FromString("Item Pickup by ghost : " + FString::FromInt(_statData[_controllers[0]->GetTeamID() - 1].ghostObjectPickedUp)));
	team2ItemPickup->SetText(FText::FromString("Item Pickup by ghost : " + FString::FromInt(_statData[_controllers[1]->GetTeamID() - 1].ghostObjectPickedUp)));

	if (_statData[0].hasFirstKill)
	{
		team1IsFirstBlood->SetText(FText::FromString("FIRST DEATH"));
		team1IsFirstBlood->SetColorAndOpacity(FColor::Red);
		team2IsFirstBlood->RemoveFromParent();
	}
	else
	{
		team2IsFirstBlood->SetText(FText::FromString("FIRST DEATH"));
		team2IsFirstBlood->SetColorAndOpacity(FColor::Red);
		team1IsFirstBlood->RemoveFromParent();
	}
}