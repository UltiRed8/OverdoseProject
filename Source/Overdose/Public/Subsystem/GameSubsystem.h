#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <UI/Widget/GamePlayerWidget.h>
#include "Gamemodes/AntGameModeBase.h"
#include "GameSubsystem.generated.h"

UCLASS()
class OVERDOSE_API UGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundStarted, const int, _roundIndex);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurnStarted, const int, _turnIndex);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnFinish);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnTimerEnded);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerEndAction);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundEnded);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnEnded);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayersCreated);

	UPROPERTY(EditAnywhere) TArray<AAntController*> controllers;

	UPROPERTY(VisibleAnywhere) TObjectPtr<AAntController> winner = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Players") int playerAmount = 2;
	UPROPERTY(EditAnywhere, Category = "Settings|Game") int maxRounds = -1;
	UPROPERTY(EditAnywhere, Category = "Settings|Game") int maxTurns = -1;
	UPROPERTY(EditAnywhere, Category = "Settings|Game") int turnTimeLimit = 45; // in seconds
	UPROPERTY(EditAnywhere, Category = "Settings|Game") int roundTimeLimit = 10; // in minutes
	UPROPERTY(EditAnywhere, Category = "Settings|Mines") int mineMin = 20;
	UPROPERTY(EditAnywhere, Category = "Settings|Mines") int mineMax = 30;
	UPROPERTY(EditAnywhere, Category = "Settings|Game") int roundsToWin = 2;

	UPROPERTY(EditAnywhere, Category = "Settings|LifeTeam") int lifeTeam1 = 0;
	UPROPERTY(EditAnywhere, Category = "Settings|LifeTeam") int lifeTeam2 = 0;

	//UPROPERTY(EditAnywhere) TObjectPtr<UProgressBar>  teamLife1 = nullptr;
	//UPROPERTY(EditAnywhere) TObjectPtr<UProgressBar>  teamLife2 = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Debugs|Infos") int currentTurn = 0;
	UPROPERTY(VisibleAnywhere, Category = "Debugs|Infos") int currentRound = 0;
	UPROPERTY(VisibleAnywhere, Category = "Debugs|Infos") bool gameTimerEnded = false;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") TObjectPtr<AAntGameModeBase> gameMode = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Debugs") bool roundIsEnded = false;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") bool isControllerController = false;

public:
	UPROPERTY() FTimerHandle turnTimer;
	UPROPERTY() FTimerHandle  roundTimer;
	UPROPERTY(BlueprintAssignable) FOnRoundStarted onRoundStarted;
	UPROPERTY(BlueprintAssignable) FOnRoundEnded onRoundEnded;
	UPROPERTY(BlueprintAssignable) FOnTurnStarted onTurnStarted;
	UPROPERTY(BlueprintAssignable) FOnTurnTimerEnded onTurnTimerEnded;
	UPROPERTY(BlueprintAssignable) FOnTurnEnded onTurnEnded;
	UPROPERTY(BlueprintAssignable) FOnPlayersCreated onPlayersCreated;
	UPROPERTY(BlueprintAssignable) FOnTurnFinish onTurnFinish;
	UPROPERTY(BlueprintAssignable) FOnPlayerEndAction onPlayerEndAction;

	bool loadFinish = false;

public:
	UFUNCTION(BlueprintCallable) FORCEINLINE int GetRoundTimeLimit()
	{
		return roundTimeLimit;
	}
	FORCEINLINE void SetControllerController(bool _value)
	{
		isControllerController = _value;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE bool GetControllerController()
	{
		return isControllerController;
	}
	FORCEINLINE FOnPlayersCreated& OnPlayersCreated()
	{
		return onPlayersCreated;
	}
	FORCEINLINE FOnRoundStarted& OnRoundStarted()
	{
		return onRoundStarted;
	}
	FORCEINLINE FOnTurnFinish& OnTurnFinish()
	{
		return onTurnFinish;
	}
	FORCEINLINE FOnTurnStarted& OnTurnStarted()
	{
		return onTurnStarted;
	}
	FORCEINLINE FOnTurnTimerEnded& OnTurnTimerEnded()
	{
		return onTurnTimerEnded;
	}
	FORCEINLINE FOnTurnEnded& OnTurnEnded()
	{
		return onTurnEnded;
	}
	FORCEINLINE FOnPlayerEndAction& OnPlayerEndAction()
	{
		return onPlayerEndAction;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE TArray<AAntController*> GetAllControllers()
	{
		return controllers;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetCurrentTurn(int _currentTurn)
	{
		currentTurn = _currentTurn;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetCurrentRound(int _currentRound)
	{
		currentRound = _currentRound;
	}
	FORCEINLINE bool LoadingFinish() const { return loadFinish; };

	FORCEINLINE FOnRoundEnded& OnRoundEnded() { return onRoundEnded; }

	UFUNCTION(BlueprintCallable) FORCEINLINE int GetMaxRounds() { return maxRounds; }
	UFUNCTION(BlueprintCallable) FORCEINLINE int GetMaxTurns() { return maxTurns; }
	UFUNCTION(BlueprintCallable) FORCEINLINE int GetTurnTimeLimit() { return turnTimeLimit; }
	UFUNCTION(BlueprintCallable) FORCEINLINE int GetCurrentRound() { return currentRound; }
	UFUNCTION(BlueprintCallable) FORCEINLINE int GetCurrentTurn() { return currentTurn; }

	UFUNCTION(BlueprintCallable) FORCEINLINE int GetLifeTeam1() { return lifeTeam1; }
	UFUNCTION(BlueprintCallable) FORCEINLINE int GetLifeTeam2() { return lifeTeam2; }
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetLifeTeam1(int _life) { lifeTeam1 = _life; }
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetLifeTeam2(int _life) { lifeTeam2 = _life; }

public:
	void Init(TObjectPtr<AAntGameModeBase> _gameMode);

private:
	void InitLoading();
	UFUNCTION() void InitControllers();
	UFUNCTION() void InitWidgets();
	UFUNCTION() void DoControllersInit();
	UFUNCTION() void InitHUD();
	UFUNCTION() void LoadColors();
	UFUNCTION() void InitSpawnMine();
	UFUNCTION() void InitVulnerability();
	UFUNCTION() void InitHealth();
	UFUNCTION() void BindPause();
	UFUNCTION() void SetDefaultItem();
	void SetTutoItem();
	UFUNCTION() void SetTeamName();
	UFUNCTION() AAntController* WhoWin();
	UFUNCTION() AAntController* WhoWinForce();

public:
	UFUNCTION() void PlayerDidAction();

private:
	UFUNCTION() void StartRound();
	UFUNCTION() void GameTimerEnded();
	void StartTurn();
	void TurnTimerEnded();
	void CheckTurn();
	void CheckGameState();
	void CheckTeamHasFinishedTurns();

public:
	UFUNCTION() void CheckIsTeamDead();

public:
	void EndTurn();
	UFUNCTION(BlueprintCallable) void PauseAllTimer(bool _status);
	bool CheckTeams();
	const FVector GetRandomAvailableLocation();
	UFUNCTION(BlueprintCallable) void LifeTeam();


	UFUNCTION(BlueprintCallable) void Reset();
};