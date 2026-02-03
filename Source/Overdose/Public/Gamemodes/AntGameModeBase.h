#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <UI/Widget/EndRoundWidger.h>
#include <UI/Widget/EndGameWidget.h>
#include "UI/Widget/GamePlayerWidget.h"
#include <GPE/Mine/Mine.h>
#include "AntGameModeBase.generated.h"

UCLASS()
class OVERDOSE_API AAntGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Settings|Menus") TSubclassOf<UGamePlayerWidget> menu = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Menus") TSubclassOf<UEndRoundWidger> endRound = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Menus") TSubclassOf<UEndGameWidget> endGame = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") TSubclassOf<AMine> subMine = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") bool tutoPlay = true;

public:
	FORCEINLINE TSubclassOf<UGamePlayerWidget> GetMenu()
	{
		return menu;
	}
	FORCEINLINE TSubclassOf<UEndRoundWidger> GetEndRound()
	{
		return endRound;
	}
	FORCEINLINE TSubclassOf<UEndGameWidget> GetEndGame()
	{
		return endGame;
	}
	FORCEINLINE TSubclassOf<AMine> GetSubMine()
	{
		return subMine;
	}
	UFUNCTION(BluePrintCallable) FORCEINLINE  bool IsTutoPlay()
	{
		return tutoPlay;
	}
	FORCEINLINE void IsTuto(bool _tutoPlay)
	{
		tutoPlay = _tutoPlay;
	}

private:
	virtual void StartPlay() override;
	void Init();
};