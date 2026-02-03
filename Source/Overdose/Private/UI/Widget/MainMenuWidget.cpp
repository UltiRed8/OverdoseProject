// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/MainMenuWidget.h"
#include "Utils/DevUtils.h"
#include "Kismet/GameplayStatics.h"
#include <GameViewportClient/CustomGameViewportClient.h>
#include <Subsystem/GameSubsystem.h>

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitBinding();
}

void UMainMenuWidget::InitBinding()
{
	btnPreviousInputMethod->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPreviousInputMethod);
	btnNextInputMethod->OnClicked.AddDynamic(this, &UMainMenuWidget::OnNextInputMethod);
}

void UMainMenuWidget::OnPreviousInputMethod()
{
	if (inputMethod == EGameInputMethod::GI_Default)
	{
		inputMethod = EGameInputMethod::GI_Player1KeyboardMouseOnly;
	}
	else
	{
		inputMethod = EGameInputMethod::GI_Default;
	}
	UpdateInputMethod();
}

void UMainMenuWidget::OnNextInputMethod()
{
	if (inputMethod == EGameInputMethod::GI_Default)
	{
		inputMethod = EGameInputMethod::GI_Player1KeyboardMouseOnly;
	}
	else
	{
		inputMethod = EGameInputMethod::GI_Default;
	}
	UpdateInputMethod();
}

void UMainMenuWidget::UpdateInputMethod()
{
	if (TObjectPtr<UCustomGameViewportClient> _viewport = Cast<UCustomGameViewportClient>(GetWorld()->GetGameViewport()))
	{
		_viewport->SetGameInputMethod(inputMethod);
	}
	if (TObjectPtr<UGameSubsystem> _system = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>())
	{
		_system->SetControllerController(inputMethod == EGameInputMethod::GI_Default);
	}
}

void UMainMenuWidget::LoadLevel()
{
	if (levelToLoad == "")
	{
		return;
	}
	UGameplayStatics::OpenLevel(this, levelToLoad);
}