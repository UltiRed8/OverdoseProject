#include "UI/Widget/EndRoundWidger.h"
#include <Kismet/GameplayStatics.h>
#include <Actor/Characters/AntController.h>
#include <Actor/Characters/AntCharacter.h>
#include <Utils/DevUtils.h>
#include <Subsystem/GhostAntSubsystem.h>
#include <Subsystem/GameSubsystem.h>
#include <Subsystem/SpawnPointSubsystem.h>

void UEndRoundWidger::NativeConstruct()
{
	Super::NativeConstruct();
	nextRoundButton->OnClicked.AddDynamic(this, &UEndRoundWidger::OnNextRound);
}
void UEndRoundWidger::OnNextRound()
{
	TObjectPtr<UAntSubsystem> _antSub = GetWorld()->GetGameInstance()->GetSubsystem<UAntSubsystem>();
	_antSub->RemoveAllAnts();

	TObjectPtr<UGhostAntSubsystem> _ghostSub = GetWorld()->GetGameInstance()->GetSubsystem<UGhostAntSubsystem>();
	_ghostSub->RemoveAllGhostAnts();

	TObjectPtr<USpawnPointSubsystem> _spawnSub = GetWorld()->GetGameInstance()->GetSubsystem<USpawnPointSubsystem>();
	_spawnSub->RemoveAllPoints();
}

void UEndRoundWidger::Open(FString _name)
{
	nameTeamTextBlock->SetText(FText::FromString(_name));
	SetVisibility(ESlateVisibility::Visible);
}