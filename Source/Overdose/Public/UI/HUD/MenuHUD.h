#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <UI/Widget/MainMenuWidget.h>
#include "MenuHUD.generated.h"

UCLASS()
class OVERDOSE_API AMenuHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Settings") TSubclassOf<UMainMenuWidget> mainMenuWidget = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") TObjectPtr<UMainMenuWidget> currentMenu = nullptr;

private:
	virtual void BeginPlay() override;
	void Init();
};