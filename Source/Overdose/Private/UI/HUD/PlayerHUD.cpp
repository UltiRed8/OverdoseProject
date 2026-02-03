#include "UI/HUD/PlayerHUD.h"

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void APlayerHUD::Init()
{
	currentPlayerWidget = CreateWidget<UGamePlayerWidget>(GetWorld(), gamePlayerWidget);
	if (currentPlayerWidget)
		currentPlayerWidget->AddToViewport();
}