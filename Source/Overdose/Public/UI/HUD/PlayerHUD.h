#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/GamePlayerWidget.h"
#include "PlayerHUD.generated.h"

UCLASS()
class OVERDOSE_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Settings") TSubclassOf<UGamePlayerWidget> gamePlayerWidget = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") TObjectPtr<UGamePlayerWidget> currentPlayerWidget = nullptr;

private:
	virtual void BeginPlay();
	void Init();
};
