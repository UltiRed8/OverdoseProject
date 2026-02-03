#include "Subsystem/GameSubsystem.h"
#include "Gamemodes/AntGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include <NavigationSystem.h>
#include <Actor/Characters/AntController.h>
#include <Subsystem/LoadingSubsystem.h>
#include <Utils/DevUtils.h>
#include "Subsystem/AntSubsystem.h"

#include "PlayerStates/AntPlayerState.h"
#include <Subsystem/SpawnPointSubsystem.h>
#include <Subsystem/TeamInfoSubsystem.h>

void UGameSubsystem::Init(TObjectPtr<AAntGameModeBase> _gameMode)
{
	gameMode = _gameMode;
	InitLoading();
	TObjectPtr<ULoadingSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULoadingSubsystem>();
	_subsystem->OnLoadingEnded().AddDynamic(this, &UGameSubsystem::StartRound);
}

void UGameSubsystem::InitLoading()
{
	TObjectPtr<ULoadingSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULoadingSubsystem>();
	TObjectPtr<ULoading> _loadingControllers = _subsystem->AddLoadingState();
	_loadingControllers->OnLoad().AddDynamic(this, &UGameSubsystem::InitControllers);
	_loadingControllers->SetCondition([&]() {
		return controllers.Num() == playerAmount;
		});

	TObjectPtr<ULoading> _loadingControllersInit = _subsystem->AddLoadingState();
	_loadingControllersInit->OnLoad().AddDynamic(this, &UGameSubsystem::DoControllersInit);
	_loadingControllersInit->SetCondition([&]() {
		return true;
		});

	TObjectPtr<ULoading> _loadingWidgets = _subsystem->AddLoadingState();
	_loadingWidgets->OnLoad().AddDynamic(this, &UGameSubsystem::InitWidgets);
	_loadingWidgets->SetCondition([&]() {
		return true;
		});

	TObjectPtr<ULoading> _loadingInitHUD = _subsystem->AddLoadingState();
	_loadingInitHUD->OnLoad().AddDynamic(this, &UGameSubsystem::InitHUD);
	_loadingInitHUD->SetCondition([&]() {
		return true;
		});

	TObjectPtr<ULoading> _loadingColors = _subsystem->AddLoadingState();
	_loadingColors->OnLoad().AddDynamic(this, &UGameSubsystem::LoadColors);
	_loadingColors->SetCondition([&]() {
		return true;
		});

	TObjectPtr<ULoading> _loadingMine = _subsystem->AddLoadingState();
	_loadingMine->OnLoad().AddDynamic(this, &UGameSubsystem::InitSpawnMine);
	_loadingMine->SetCondition([&]() {
		return true;
		});

	TObjectPtr<ULoading> _loadingVulnerability = _subsystem->AddLoadingState();
	_loadingVulnerability->OnLoad().AddDynamic(this, &UGameSubsystem::InitVulnerability);
	_loadingVulnerability->SetCondition([&]() {
		return true;
		});

	TObjectPtr<ULoading> _loadingHealthBars = _subsystem->AddLoadingState();
	_loadingHealthBars->OnLoad().AddDynamic(this, &UGameSubsystem::InitHealth);
	_loadingHealthBars->SetCondition([&]() {
		return true;
		});

	TObjectPtr<ULoading> _loadingBindPauses = _subsystem->AddLoadingState();
	_loadingBindPauses->OnLoad().AddDynamic(this, &UGameSubsystem::BindPause);
	_loadingBindPauses->SetCondition([&]() {
		return true;
		});

	TObjectPtr<ULoading> _loadingTeamName = _subsystem->AddLoadingState();
	_loadingTeamName->OnLoad().AddDynamic(this, &UGameSubsystem::SetTeamName);
	_loadingTeamName->SetCondition([&]() {
		return true;
		});

	_subsystem->Load(0.05f);
	loadFinish = true;
}

void UGameSubsystem::DoControllersInit()
{
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		_controller->Init();
	}
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		for (TObjectPtr<AAntCharacter> _ant : _controller->GetAnts())
		{
			_ant->OnGhost().AddDynamic(this, &UGameSubsystem::CheckIsTeamDead);
		}
	}
}

void UGameSubsystem::InitWidgets()
{
	if (!gameMode->GetMenu())
		return;
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		TObjectPtr<UGamePlayerWidget> _widget = CreateWidget<UGamePlayerWidget>(GetWorld(), gameMode->GetMenu());
		_widget->SetOwningPlayer(_controller);
		_widget->AddToPlayerScreen();

		_controller->SetWidget(_widget);
	}
}

void UGameSubsystem::InitVulnerability()
{
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		for (TObjectPtr<AAntCharacter> _character : _controller->GetAnts())
		{
			_character->GetStat()->SetInvulnerability(false);
		}
	}
}

void UGameSubsystem::InitHealth()
{
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		_controller->GetWidget()->GetProgressBar1()->OnSwitchUpdate();
		_controller->GetWidget()->GetProgressBar2()->OnSwitchUpdate();
	}
}

void UGameSubsystem::BindPause()
{
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		_controller->onPauseEvent.AddDynamic(this, &UGameSubsystem::PauseAllTimer);
	}
}

void UGameSubsystem::SetDefaultItem()
{
	LOG_CT("INVENTORY", FColor::Purple, 10);
	for (TObjectPtr<AAntController> _controller : controllers)
	{		
		//_controller->GetInventory()->Reset();
		_controller->GetInventory()->Init();
	}
}

void UGameSubsystem::SetTutoItem()
{
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		_controller->GetInventory()->InitTuto();
	}
}

void UGameSubsystem::SetTeamName()
{
	TObjectPtr<UTeamInfoSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamInfoSubsystem>();
	
	for(TObjectPtr<AAntController> _controller : controllers)
	{
		FString _name = _subsystem->GetTeamDatas()[_controller->GetTeamID() - 1].name;
		_controller->SetTeamName(_name);
	}
}

AAntController* UGameSubsystem::WhoWin()
{
	AAntController* _winner = nullptr;
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		_winner = _controller;
		int _numberOfDeadAnt = 0;
		for (TObjectPtr<AAntCharacter> _ant : _controller->GetAnts())
		{
			if (_ant->GetGhost())
			{
				_numberOfDeadAnt++;
			}
		}
		if (_numberOfDeadAnt >= _controller->GetAntsPerTeam())
		{
			_winner = nullptr;
		}
		else
		{
			return _winner;
		}
	}
	return nullptr;
}

AAntController* UGameSubsystem::WhoWinForce()
{
	// Nombre de fourmis en vie
	// Nombre de points de vies
	// Random
	winner = nullptr;
	int _scores[2];
	int _index = 0;
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		int _score = 0;
		for (TObjectPtr<AAntCharacter> _ant : _controller->GetAnts())
		{
			if (!_ant->GetGhost())
			{
				_score++;
			}
		}
		if (_index == 1)
		{
			if (_score > _scores[0])
			{
				winner = _controller;
			}
		}
		else
		{
			winner = _controller;
		}
		_scores[_index] = _score;
		_index++;
	}
	if (_scores[0] == _scores[1])
	{
		LifeTeam();
		if (lifeTeam1 == lifeTeam2)
		{
			return controllers[FMath::RandRange(0, 1)];
		}
		else
		{
			winner = lifeTeam1 > lifeTeam2 ? controllers[0] : controllers[1];
		}
	}
	return winner;
}

void UGameSubsystem::InitSpawnMine()
{
	if (!gameMode->GetSubMine())
		return;
	const int _numberOfMine = FMath::RandRange(mineMin, mineMax);
	TObjectPtr<UAntSubsystem> _subSystem = GetWorld()->GetGameInstance()->GetSubsystem< UAntSubsystem>();
	int _tries = 0;
	for (int _index = 0; _index < _numberOfMine; _index++)
	{
		FVector _randomPos = GetRandomAvailableLocation();
		for (TObjectPtr< AAntCharacter> _ant : _subSystem->GetAnts())
		{
			while (FVector::Distance(_randomPos, _ant->GetActorLocation()) <= 300)
			{
				_tries++;
				if (_tries > 5)
					return;
				_randomPos = GetRandomAvailableLocation();
			}
			break;
		}
		_randomPos.Z -= 20;
		GetWorld()->SpawnActor<AMine>(gameMode->GetSubMine(), _randomPos, FRotator(0));
	}
}

void UGameSubsystem::LoadColors()
{
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		_controller->UpdateColor();
	}
}

void UGameSubsystem::InitControllers()
{
	controllers.Empty();
	for (int _index = 0; _index < playerAmount; _index++)
	{
		UGameplayStatics::CreatePlayer(this, _index, true);
		TObjectPtr<AAntController> _antController = Cast<AAntController>(UGameplayStatics::GetPlayerController(GetWorld(), _index));

		_antController->SetTeamID(_index + 1);
		controllers.Add(_antController);
	}
	onPlayersCreated.Broadcast();
}

void UGameSubsystem::InitHUD()
{
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		for (TObjectPtr<AAntCharacter> _ant : _controller->GetAnts())
		{
			_ant->BindHealthBar();
		}
	}
}

void UGameSubsystem::StartRound()
{
	roundIsEnded = false;
	if (gameMode->IsTutoPlay())
	{
		SetTutoItem();
		return;
	}
	currentRound++;

	onRoundStarted.Broadcast(currentRound);
	if (maxRounds != -1 && currentRound > maxRounds)
	{
		return;
	}
	SetDefaultItem();
	StartTurn();
	GetWorld()->GetTimerManager().SetTimer(roundTimer, this, &UGameSubsystem::GameTimerEnded, roundTimeLimit * 60);
}

void UGameSubsystem::StartTurn()
{
	if (gameMode->IsTutoPlay())
		return;
	TObjectPtr<USpawnPointSubsystem> _sub = GetWorld()->GetGameInstance()->GetSubsystem< USpawnPointSubsystem>();
	if (!_sub)
		return;
	_sub->Reset();

	if (gameTimerEnded)
	{
		TObjectPtr<UTeamInfoSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamInfoSubsystem>();
		WhoWinForce();
		_subsystem->GetTeamDatas()[winner->GetTeamID() - 1].winAmount++;

		for (TObjectPtr<AAntController> _controller : controllers)
		{
			if (_subsystem->GetTeamDatas()[_controller->GetTeamID() - 1].winAmount >= roundsToWin)
			{
				TObjectPtr<UEndGameWidget> _endGame = CreateWidget<UEndGameWidget>(GetWorld(), gameMode->GetEndGame());
				_endGame->AddToViewport();
				PauseAllTimer(true);
				gameTimerEnded = false;
				_endGame->Open(GetAllControllers());
				return;
			}
		}
		TObjectPtr<UEndRoundWidger> _endRound = CreateWidget<UEndRoundWidger>(GetWorld(), gameMode->GetEndRound());
		_endRound->AddToViewport();
		if (!winner)
		{
			LOG_CT("PAS DE CONTROLLER", FColor::Red, 100);
			return;
		}
		_endRound->Open(winner->GetTeamName());
		gameTimerEnded = false;
		return;
	}
	currentTurn++;
	onTurnStarted.Broadcast(currentTurn);

	if (maxTurns != -1 && currentTurn > maxTurns)
	{
		currentTurn = 0;
		StartRound();
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(turnTimer, this, &UGameSubsystem::TurnTimerEnded, turnTimeLimit);
}

bool UGameSubsystem::CheckTeams()
{
	bool _isATeamFullDead = false;
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		int _numberOfDeadAnt = 0;
		for (TObjectPtr<AAntCharacter> _character : _controller->GetAnts())
		{
			if (_character->GetGhost())
			{
				_numberOfDeadAnt++;
			}
		}
		if (_numberOfDeadAnt >= _controller->GetAntsPerTeam())
		{
			_isATeamFullDead = true;
			return _isATeamFullDead;
		}
	}
	return _isATeamFullDead;
}

void UGameSubsystem::CheckTurn()
{
	EndTurn();
	StartTurn();
}

void UGameSubsystem::TurnTimerEnded()
{
	CheckIsTeamDead();
	onTurnTimerEnded.Broadcast();
	EndTurn();
	StartTurn();
}

void UGameSubsystem::PlayerDidAction()
{
	LifeTeam();
	if (roundIsEnded)
		return;

	onPlayerEndAction.Broadcast();
	if (!CheckTeams())
	{
		CheckTeamHasFinishedTurns();
	}
	else
	{
		CheckIsTeamDead();
	}
}

void UGameSubsystem::CheckGameState()
{
	TObjectPtr<UTeamInfoSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamInfoSubsystem>();
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		if (_subsystem->GetTeamDatas()[_controller->GetTeamID() - 1].winAmount == roundsToWin)
		{
			TObjectPtr<UEndGameWidget> _endGame = CreateWidget<UEndGameWidget>(GetWorld(), gameMode->GetEndGame());
			_endGame->AddToViewport();
			PauseAllTimer(true);
			_endGame->Open(GetAllControllers());
			return;
		}
	}
	TObjectPtr<UEndRoundWidger> _endRound = CreateWidget<UEndRoundWidger>(GetWorld(), gameMode->GetEndRound());
	_endRound->AddToViewport();
	_endRound->Open(winner->GetTeamName());
}

void UGameSubsystem::CheckTeamHasFinishedTurns()
{
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		if (TObjectPtr<AAntPlayerState> _antState = _controller->GetPlayerState<AAntPlayerState>())
		{
			if (_antState->GetCanPlay())
				return;
		}
	}
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		if (TObjectPtr<AAntPlayerState> _antState = _controller->GetPlayerState<AAntPlayerState>())
		{
			_antState->SetCanPlay(true);
		}
	}
	TurnTimerEnded();
}

void UGameSubsystem::CheckIsTeamDead()
{
	for (TObjectPtr<AAntController> _controller : controllers)
	{
		int _numberOfDeadAnt = 0;
		for (TObjectPtr<AAntCharacter> _character : _controller->GetAnts())
		{
			if (_character->GetGhost())
			{
				_numberOfDeadAnt++;
			}
		}
		if (_numberOfDeadAnt >= _controller->GetAntsPerTeam())
		{
			TObjectPtr<UTeamInfoSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamInfoSubsystem>();
			_subsystem->GetTeamDatas()[WhoWinForce()->GetTeamID() - 1].winAmount++;
			roundIsEnded = true;
			CheckGameState();
			return;
		}
	}
}

void UGameSubsystem::EndTurn()
{
	GetWorld()->GetTimerManager().ClearTimer(turnTimer);
	onTurnEnded.Broadcast();
}

void UGameSubsystem::GameTimerEnded()
{
	gameTimerEnded = true;
}

void UGameSubsystem::PauseAllTimer(bool _status)
{
	if (_status)
	{
		GetWorld()->GetTimerManager().PauseTimer(turnTimer);
		GetWorld()->GetTimerManager().PauseTimer(roundTimer);
		LOG(turnTimer.ToString());
	}
	else
	{
		GetWorld()->GetTimerManager().UnPauseTimer(turnTimer);
		GetWorld()->GetTimerManager().UnPauseTimer(roundTimer);
	}
}

const FVector UGameSubsystem::GetRandomAvailableLocation()
{
	TObjectPtr<USpawnPointSubsystem> _sub = GetWorld()->GetGameInstance()->GetSubsystem< USpawnPointSubsystem>();
	if (_sub)
		return _sub->SpawnAtRandomPoint();

	return FVector();
}

void UGameSubsystem::LifeTeam()
{
	lifeTeam1 = 0;
	lifeTeam2 = 0;
	int _index = 0;

	for (TObjectPtr<AAntController> _controller : controllers)
	{
		for (TObjectPtr<AAntCharacter> _character : _controller->GetAnts())
		{
			_index == 0 ? lifeTeam1 += _character->GetStat()->GetCurrentLife() : lifeTeam2 += _character->GetStat()->GetCurrentLife();
		}
		_index++;
	}
	//TObjectPtr<UProgressBar>
}

void UGameSubsystem::Reset()
{
	GetWorld()->GetTimerManager().ClearTimer(turnTimer);
	GetWorld()->GetTimerManager().ClearTimer(roundTimer);
}
