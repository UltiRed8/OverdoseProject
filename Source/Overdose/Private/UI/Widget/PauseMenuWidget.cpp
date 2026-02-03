// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/PauseMenuWidget.h"
#include "Utils/DevUtils.h"
#include "Kismet/GameplayStatics.h"
#include <Actor/Characters/AntCharacter.h>
#include <Actor/Characters/AntController.h>
#include <Gamemodes/AntGameModeBase.h>
#include <Subsystem/GhostAntSubsystem.h>
#include <Subsystem/SpawnPointSubsystem.h>
#include <Subsystem/GameSubsystem.h>

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BindButtons();
}

void UPauseMenuWidget::BindButtons()
{
	backToMainMenu->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnBackToMenu);

}

void UPauseMenuWidget::OnBackToMenu()
{
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	TArray<AAntController*> _controllers = _subsystem->GetAllControllers();

	for (TObjectPtr<AAntController> _controller : _controllers)
	{
		UGameplayStatics::RemovePlayer(_controller.Get(), true);
	}

	UGameplayStatics::CreatePlayer(this, 0);

	TObjectPtr<UAntSubsystem> _antSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAntSubsystem>();
	_antSubsystem->RemoveAllAnts();

	TObjectPtr<UGhostAntSubsystem> _ghostSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGhostAntSubsystem>();
	_ghostSubsystem->RemoveAllGhostAnts();

	TObjectPtr<USpawnPointSubsystem> _spawnPointSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<USpawnPointSubsystem>();
	_spawnPointSubsystem->RemoveAllPoints();

	UGameplayStatics::OpenLevel(this, mainMenuName);
}
