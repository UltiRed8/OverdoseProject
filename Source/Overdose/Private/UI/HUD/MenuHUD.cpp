#include "UI/HUD/MenuHUD.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void AMenuHUD::Init()
{
	currentMenu = CreateWidget<UMainMenuWidget>(GetWorld(), mainMenuWidget);
	if (currentMenu)
		currentMenu->AddToViewport();
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}