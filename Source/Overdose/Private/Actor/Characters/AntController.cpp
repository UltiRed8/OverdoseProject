#include "Actor/Characters/AntController.h"
#include <Actor/Characters/AntCharacter.h>
#include <Utils/DevUtils.h>
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Subsystem/TeamInfoSubsystem.h>
#include <Gamemodes/AntGameModeBase.h>
#include <Subsystem/GameSubsystem.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <PlayerStates/AntPlayerState.h>

AAntController::AAntController()
{
	inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	AddOwnedComponent(inventory);
}
void AAntController::BeginPlay()
{
	Super::BeginPlay();
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (_subsystem)
	{
		_subsystem->OnTurnEnded().AddDynamic(this, &AAntController::SwitchAnt);
	}
	SetMouseCursorWidget(EMouseCursor::Default, cursorMouse);

	SetShowMouseCursor(false);
}
void AAntController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AAntController::AddAnt()
{
	FActorSpawnParameters _param = FActorSpawnParameters();
	_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if (!teamCharacter)
	{
		LOG_CT("NO TEAM CHARACTER IN BP_ANTCONTROLLER", FColor::Red, 10000);
	}
	TObjectPtr<AAntCharacter> _ant = GetWorld()->SpawnActor<AAntCharacter>(teamCharacter, _param);
	if (!_ant)
		return;
	_ant->SetTeamController(this);
	ants.Add(_ant);
}
void AAntController::RemoveAnt(const int _index)
{
	ants.RemoveAt(_index);
}
void AAntController::UpdateColor()
{
	for (TObjectPtr<AAntCharacter> _ant : ants)
	{
		if (!_ant)
			continue;
		TObjectPtr<UTeamInfoSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamInfoSubsystem>();
		_ant->GetMesh()->SetSkeletalMesh(_subsystem->GetTeamDatas()[teamId - 1].mesh);
	}
}
void AAntController::InitBinding()
{
	inputs = Cast<UEnhancedInputComponent>(InputComponent);
	if (inputs)
	{
		inputs->BindAction(openInventory, ETriggerEvent::Completed, this, &AAntController::OpenInventory);
		inputs->BindAction(pauseAction, ETriggerEvent::Completed, this, &AAntController::OnPauseEvent);
	}
}

void AAntController::StopInputs()
{
	isInputsEnabled = false;
	ants[currentAnt]->ActiveBaseView();
	ants[currentAnt]->SetIsTurn(false);
	TObjectPtr<AAntPlayerState> _antState = GetPlayerState<AAntPlayerState>();
	if (_antState)
		_antState->SetCanPlay(false);
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (_subsystem)
		_subsystem->PlayerDidAction();
}

void AAntController::OnPauseEvent()
{
	UGameplayStatics::SetGamePaused(this, !UGameplayStatics::IsGamePaused(this));
	SetShowMouseCursor(UGameplayStatics::IsGamePaused(this));
	onPauseEvent.Broadcast(UGameplayStatics::IsGamePaused(this));
}

void AAntController::OpenInventory()
{
	if (!isInputsEnabledEarly)
		return;

	if (Cast< AGhostAntCharacter>(GetPawn()))
		return;

	if (ants[currentAnt]->GetCamera()->IsTopView())
		return;

	onOpenInventory.Broadcast();
	
	if (ants[currentAnt])
	{
		ants[currentAnt]->DisableInput(this);
		if(ants[currentAnt]->GetMovementValue() != 0)
		{
			ants[currentAnt]->ResetMovementValue();
		}
	}
	TObjectPtr<UInventoryWidget> _widget = GetWidget()->GetInventoryWidget();
	const bool _isVisible = _widget->IsVisible();
	if (_isVisible)
	{
		_widget->OnClose().Broadcast();
	}
	else
	{
		_widget->SetController(this);
		_widget->OnOpen().Broadcast();
	}
	
	//SetShowMouseCursor(!_isVisible);
	FInputModeGameAndUI _modeUI;
	FInputModeGameOnly _modeGame;
	if (!_isVisible)
	{
		//SetInputMode(_modeUI);
		isInventoryOpen = true;
	}
	else
	{
		//SetInputMode(_modeGame);
		isInventoryOpen = false;
	}
	if (_isVisible)
	{
		ants[currentAnt]->EnableInput(this);
	}
}

//void AAntController::EnablePause()
//{
//	inputs->BindAction(pauseAction, ETriggerEvent::Completed, this, &AAntController::OnPauseEvent);
//}

//void AAntController::EnableInventory()
//{
//	if (hasInventory) return;
//	inputs->BindAction(openInventory, ETriggerEvent::Completed, this, &AAntController::OpenInventory);
//	hasInventory = true;
//}

void AAntController::EndOfTurn(const float _inDelay)
{
	if (isCalled)return;
	if (endTurn) return;
	isInputsEnabledEarly = false;
	onTurnFinished.Broadcast();
	onTurnFinishedDelayed.Broadcast(_inDelay == 0.0f);
	if (_inDelay == 0.0f)
		StopInputs();
	else
	{
		GetWorld()->GetTimerManager().SetTimer(pendingRemoveInputsTimer, this, &AAntController::StopInputs, 1.0f, false, _inDelay);
	}
	endTurn = true;
}

void AAntController::EndOfTurnDelayed(const float _notUsed)
{
	EndOfTurn(5.0f);
	isCalled = true;
}

void AAntController::Init()
{
	InitTeam();
	InitBinding();
	InitLifeTeam();
	Possess(ants[0]);
	onFullTeamCreated.Broadcast(ants); 
}
void AAntController::SwitchAnt()
{
	GetWorld()->GetTimerManager().ClearTimer(pendingRemoveInputsTimer);
	if (ants[currentAnt] && ants[currentAnt]->GetItem())
	{
		ants[currentAnt]->GetItem()->Destroy();
		ants[currentAnt]->SetItem(nullptr);
	}
	currentAnt++;
	currentAnt %= ants.Num();
	if (ants[currentAnt])
	{
		ants[currentAnt]->SetIsTurn(true);
		if (ants[currentAnt]->GetGhost())
		{
			endTurn = false;
			Possess(ants[currentAnt]->GetGhost());
			ants[currentAnt]->GetGhost()->EnableInput(this);
			ants[currentAnt]->GetGhost()->BindActions();
			ants[currentAnt]->GetGhost()->Visible();
			ants[currentAnt]->GetGhost()->ActiveBaseView();
			ants[currentAnt]->GetGhost()->SetPossess(true);
			SetInputMode(FInputModeGameOnly());
		}
		else
		{
			Possess(ants[currentAnt]);
			ants[currentAnt]->EnableInput(this);
			//EnableInput(this);
			ants[currentAnt]->ActiveBaseView();
			isInputsEnabled = true;
			//EnableInventory();

			SetInputMode(FInputModeGameOnly());
			SetShowMouseCursor(false);
			
			if (GetWidget()->GetInventoryWidget()->IsVisible())
			{
				ESlateVisibility _visibility = ESlateVisibility::Hidden;
				GetWidget()->GetInventoryWidget()->SetVisibility(_visibility);
			}
			FTimerHandle timer;
			endTurn = false;
		}
	}
	onSwitch.Broadcast();
	isInputsEnabled = true;
	isInputsEnabledEarly = true;
	FTimerHandle _timer;
	GetWorld()->GetTimerManager().SetTimer(_timer, this, &AAntController::Called, 2);
}

void AAntController::BindStatsEvents(TObjectPtr<UStatsComponent> _stats)
{
	if (_stats)
	{
		_stats->OnAddLife().AddDynamic(this, &AAntController::UpdateHealLifeBar);
		_stats->OnTakeDamage().AddDynamic(this, &AAntController::UpdateDamageLifeBar);
		_stats->OnDeath().AddDynamic(this, &AAntController::UpdateLifeBarVisibility);
	}
}

void AAntController::UpdateHealLifeBar(float _percent, AAntCharacter* _ant)
{
	if (!_ant->IsControlled())
		return;
	widget->GetProgressBar1()->OnAddLife(_percent);
	widget->GetProgressBar2()->OnAddLife(_percent);
}

void AAntController::UpdateDamageLifeBar(float _percent, AAntCharacter* _ant)
{
	if (!_ant->IsControlled())
		return;
	widget->GetProgressBar1()->OnTakeDamage(_percent);
	widget->GetProgressBar2()->OnTakeDamage(_percent);
}

void AAntController::UpdateLifeBarVisibility(bool _inDeathZone, AAntCharacter* _ant)
{
	TObjectPtr<APawn> _pawn = GetPawn();
	if (_ant != _pawn && _ant->GetGhost() == _pawn)
	{
		widget->GetProgressBar1()->SetHidden();
		widget->GetProgressBar2()->SetHidden();
	}
}

void AAntController::InitLifeTeam()
{
	for (TObjectPtr<AAntCharacter> _ant : ants)
	{
		teamLife += _ant->GetStat()->GetCurrentLife();
	}
}

void AAntController::InitTeam()
{
	if (!teamCharacter)
		return;
	for (int _index = 0; _index < antsPerTeam; _index++)
	{
		AddAnt();
	}
}