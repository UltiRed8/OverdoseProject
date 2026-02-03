#include "Actor/Characters/AntCharacter.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Utils/DevUtils.h>
#include <Subsystem/AntSubsystem.h>
#include <Subsystem/GhostAntSubsystem.h>
#include <NavigationSystem.h>
#include "Actor/Characters/AntController.h"
#include <PlayerStates/AntPlayerState.h>
#include <Components/CapsuleComponent.h>
#include "Kismet/GameplayStatics.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Actor/DeathZone/LavaDeathZone.h>
#include <Subsystem/TeamInfoSubsystem.h>
#include <Gamemodes/AntGameModeBase.h>
#include "Subsystem/SpawnPointSubsystem.h"
#include <Subsystem/GameSubsystem.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/KismetMathLibrary.h>
#include <GPE/Items/Tools/Teleporter.h>
#include <GPE/Items/Weapons/FallingMokia.h>
#include <Subsystem/ChatSubsystem.h>
#include <GPE/Items/Weapons/Bazooka.h>
#include <GPE/Items/Weapons/Rasputin.h>
#include <GPE/Items/Weapons/RubiksCube.h>
#include <GPE/Items/Tools/HealZoneTool.h>
#include "InputActionValue.h"


AAntCharacter::AAntCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	springArm->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCharacterCameraComponent>("Camera");
	camera->SetupAttachment(springArm);

	widget = CreateDefaultSubobject<UWidgetComponent>("Widget");
	widget->SetupAttachment(RootComponent);

	widget2 = CreateDefaultSubobject<UWidgetComponent>("Widget2");
	widget2->SetupAttachment(widget);

	Cast<UCharacterMovementComponent>(GetMovementComponent())->bRunPhysicsWithNoController = true;


	springArm->bUsePawnControlRotation = true;
	springArm->bInheritPitch = true;
	springArm->bInheritYaw = true;
	springArm->bInheritRoll = false;

	stat = CreateDefaultSubobject<UStatsComponent>("Statistique");
	AddOwnedComponent(stat);

	knockback = CreateDefaultSubobject<UKnockbackComponent>("Knockback");
	AddOwnedComponent(knockback);
	falling = CreateDefaultSubobject<UFallDamageComponent>("Falling");
	AddOwnedComponent(falling);

	JumpMaxCount = 2;


	healArrow = CreateDefaultSubobject<UArrowComponent>("HealArrow");

	teleporterArrow = CreateDefaultSubobject<UArrowComponent>("teleporterArrow");

	bazookaArrow = CreateDefaultSubobject<UArrowComponent>("bazookaArrow");

	fallingMokiaArrow = CreateDefaultSubobject<UArrowComponent>("fallingMokiaArrow");

	rasputinArrow = CreateDefaultSubobject<UArrowComponent>("rasputinArrow");

	rubiksCubeArrow = CreateDefaultSubobject<UArrowComponent>("rubiksCubeArrow");
}

void AAntCharacter::BeginPlay()
{
	Super::BeginPlay();
	Register();
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	FVector _location = GetRandomPosition();
	_location.Z += 40;
	SetActorLocation(_location);
	if (stat)
		stat->OnDeath().AddDynamic(this, &AAntCharacter::Dead);

	//if (InputMappings)
	//{
	//	
	//UInputModifier
	//InputMappings->GetMapping(4).Modifiers.Add()
	//	
	//}

}

void AAntCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator _rotation = widget->GetRelativeRotation();
	_rotation.Yaw += 50.0 * DeltaTime;
	widget->SetRelativeRotation(_rotation);

	if (movementValue != 0)
	{ 
		//knockbackStatus = false;
		return;
	}
	else if (UKismetMathLibrary::NearlyEqual_FloatFloat(GetVelocity().Length(), 0.0, 0.1))
	{
		if (item)
		{
			if (camera && camera->IsTopView())
				return;
			item->Take();
		}
	}

	//if (GetVelocity() == FVector::ZeroVector)
	//{
	//	knockbackStatus = false;
	//}
	
	if (Cast<UCharacterMovementComponent>(GetMovementComponent())->IsFalling())
	{
		knockbackStatus = false;
	}
}

void AAntCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InitInputSystem();
	BindActions();
}

void AAntCharacter::InitInputSystem()
{
	TObjectPtr< UEnhancedInputLocalPlayerSubsystem> _inputSystem = teamController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	_inputSystem->AddMappingContext(InputMappings, 0);
}

void AAntCharacter::MovementUp(const FInputActionInstance& _input)
{
	if (!teamController->AreInputsEnabled())
		return;
	TObjectPtr<AGameModeBase> _gm = UGameplayStatics::GetGameMode(this);
	TObjectPtr<AAntGameModeBase> _antGameMode = Cast<AAntGameModeBase>(_gm);

	if (item && movementValue == 0)
	{
		IncrementMoving();
		item->Store();
	}
	if (camera && camera->IsTopView())
	{
		camera->GetTopViewCamera()->AddLocalOffset(FVector(0, 0, camera->GetArrowOfTopView()->GetForwardVector().X * topViewCameraSpeed));
		return;
	}
	if (camera->IsAim())
		return;
	AddMovementInput(GetActorForwardVector() * 1);
	isMoving = true;
}

void AAntCharacter::MovementDown(const FInputActionInstance& _input)
{
	if (!teamController->AreInputsEnabled())
		return;
	TObjectPtr<AGameModeBase> _gm = UGameplayStatics::GetGameMode(this);
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (item && movementValue == 0)
	{
		IncrementMoving();
		item->Store();
	}
	if (_subsystem && !_subsystem->LoadingFinish())
		return;
	if (camera && camera->IsTopView())
	{
		camera->GetTopViewCamera()->AddLocalOffset(FVector(0, 0, camera->GetArrowOfTopView()->GetForwardVector().X * -topViewCameraSpeed));
		return;
	}
	if (camera->IsAim())
		return;
	AddMovementInput(GetActorForwardVector() * -1);
	isMoving = true;
}

void AAntCharacter::MovementLeft(const FInputActionInstance& _input)
{
	if (!teamController->AreInputsEnabled())
		return;
	TObjectPtr<AGameModeBase> _gm = UGameplayStatics::GetGameMode(this);
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (item && movementValue == 0)
	{
		IncrementMoving();
		item->Store();
	}
	if (_subsystem && !_subsystem->LoadingFinish())
		return;
	if (camera && camera->IsTopView())
	{
		camera->GetTopViewCamera()->AddLocalOffset(FVector(0, camera->GetArrowOfTopView()->GetRightVector().Y * -topViewCameraSpeed, 0));
		return;
	}
	if (camera->IsAim())
		return;
	AddMovementInput(GetActorRightVector() * -1);
	isMoving = true;
}

void AAntCharacter::MovementRight(const FInputActionInstance& _input)
{
	if (!teamController->AreInputsEnabled())
		return;
	TObjectPtr<AGameModeBase> _gm = UGameplayStatics::GetGameMode(this);
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (item && movementValue == 0)
	{
		IncrementMoving();
		item->Store();
	}
	if (_subsystem && !_subsystem->LoadingFinish())
		return;
	if (camera && camera->IsTopView())
	{
		camera->GetTopViewCamera()->AddLocalOffset(FVector(0, camera->GetArrowOfTopView()->GetRightVector().Y * topViewCameraSpeed, 0));
		return;
	}
	if (camera->IsAim())
		return;
	AddMovementInput(GetActorRightVector() * 1);

	//if (rotationAction->Modifiers[0].Get())
	//{

	//LOG(rotationAction->Modifiers[0].GetName());
	//}
	// 
	//if (InputMappings)
	//{
	//	
	//	TObjectPtr<UInputModifierScalar> _action = Cast<UInputModifierScalar>(rotationAction->Modifiers[1]);
	//	if (_action)
	//	{
	//		_action->Scalar.Set(0.5, 0.5, 0.5); /*= FVector(0.5, 0.5, 0.5);*/
	//		LOG("WESH");
	//	}
	//	//InputMappings->GetMapping(4).Modifiers.Add(Cast<UInputModifier>(_action));

	//}
}

void AAntCharacter::Register()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UAntSubsystem>()->AddAnt(this);
}

void AAntCharacter::BindActions()
{
	inputs = Cast<UEnhancedInputComponent>(InputComponent);
	if (inputs)
	{
		inputs->ClearActionBindings();
		inputs->BindAction(movementActionUp, ETriggerEvent::Triggered, this, &AAntCharacter::MovementUp);
		inputs->BindAction(movementActionUp, ETriggerEvent::Started, this, &AAntCharacter::StoreItem);
		inputs->BindAction(movementActionUp, ETriggerEvent::Completed, this, &AAntCharacter::DecrementMoving);

		inputs->BindAction(movementActionDown, ETriggerEvent::Triggered, this, &AAntCharacter::MovementDown);
		inputs->BindAction(movementActionDown, ETriggerEvent::Started, this, &AAntCharacter::StoreItem);
		inputs->BindAction(movementActionDown, ETriggerEvent::Completed, this, &AAntCharacter::DecrementMoving);

		inputs->BindAction(movementActionLeft, ETriggerEvent::Triggered, this, &AAntCharacter::MovementLeft);
		inputs->BindAction(movementActionLeft, ETriggerEvent::Started, this, &AAntCharacter::StoreItem);
		inputs->BindAction(movementActionLeft, ETriggerEvent::Started, this, &AAntCharacter::IncrementSideMovement);
		inputs->BindAction(movementActionLeft, ETriggerEvent::Started, this, &AAntCharacter::StartGoingLeft);
		inputs->BindAction(movementActionLeft, ETriggerEvent::Completed, this, &AAntCharacter::DecrementSideMovement);
		inputs->BindAction(movementActionLeft, ETriggerEvent::Completed, this, &AAntCharacter::StopGoingLeft);
		inputs->BindAction(movementActionLeft, ETriggerEvent::Completed, this, &AAntCharacter::DecrementMoving);

		inputs->BindAction(movementActionRight, ETriggerEvent::Triggered, this, &AAntCharacter::MovementRight);
		inputs->BindAction(movementActionRight, ETriggerEvent::Started, this, &AAntCharacter::StoreItem);
		inputs->BindAction(movementActionRight, ETriggerEvent::Started, this, &AAntCharacter::IncrementSideMovement);
		inputs->BindAction(movementActionRight, ETriggerEvent::Completed, this, &AAntCharacter::DecrementSideMovement);
		inputs->BindAction(movementActionRight, ETriggerEvent::Completed, this, &AAntCharacter::DecrementMoving);

		inputs->BindAction(jumping, ETriggerEvent::Started, this, &AAntCharacter::Jumping);
		inputs->BindAction(jumping, ETriggerEvent::Completed, this, &AAntCharacter::DecrementMoving);

		inputs->BindAction(rotationAction, ETriggerEvent::Triggered, this, &AAntCharacter::Rotation);

		inputs->BindAction(SwitchAction, ETriggerEvent::Started, this, &AAntCharacter::ActiveTopView);

		inputs->BindAction(SwitchAction, ETriggerEvent::Completed, this , &AAntCharacter::ActiveBaseView);

		inputs->BindAction(aim, ETriggerEvent::Started, camera.Get(), &UCharacterCameraComponent::Aim);
		inputs->BindAction(aim, ETriggerEvent::Completed, camera.Get(), &UCharacterCameraComponent::ResetView);
		inputs->BindAction(itemUse, ETriggerEvent::Completed, this, &AAntCharacter::UseItem);
		inputs->BindAction(moveCameraTopView, ETriggerEvent::Triggered, this, &AAntCharacter::MoveTopViewCamera);
	}
}

void AAntCharacter::Jumping()
{
	if (!teamController->AreInputsEnabled())
		return;
	if (camera && camera->IsTopView())
		return;
	if (camera->IsAim())
		return;
	FTimerHandle _timer;
	onJump.Broadcast();
	GetWorld()->GetTimerManager().SetTimer(_timer, this, &AAntCharacter::DelayJump, delayOfJump);
}

void AAntCharacter::Rotation(const FInputActionInstance& _input)
{
	TObjectPtr<AGameModeBase> _gm = UGameplayStatics::GetGameMode(this);
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();

	if (_subsystem && !_subsystem->LoadingFinish())
		return;
	if (camera && camera->IsTopView())
		return;
	
	const FVector2D& _axis = _input.GetValue().Get<FVector2D>();
	AddControllerYawInput(_axis.X);
	AddControllerPitchInput(-_axis.Y);

	//if (InputMappings)
//{
//	
//UInputModifier
 //InputMappings->GetMapping(4).Modifiers.Add()
//	
//}

	
}

//void AAntCharacter::RotationEndRound(const FInputActionInstance& _input)
//{
//	const FVector2D& _axis = _input.GetValue().Get<FVector2D>();
//	if (ghost)
//	{
//		ghost->AddControllerYawInput(_axis.X);
//		ghost->AddControllerPitchInput(-_axis.Y);
//	}
//	else
//	{
//		AddControllerYawInput(_axis.X);
//		AddControllerPitchInput(-_axis.Y);
//	}
//}

void AAntCharacter::MoveTopViewCamera(const FInputActionInstance& _input)
{
	TObjectPtr<AGameModeBase> _gm = UGameplayStatics::GetGameMode(this);
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();

	if (_subsystem && !_subsystem->LoadingFinish())
		return;
	const FVector2D& _axis = _input.GetValue().Get<FVector2D>();
	camera->GetTopViewCamera()->AddLocalOffset(FVector(0, _axis.X * topViewCameraSpeed, _axis.Y * topViewCameraSpeed));	
}

//void AAntCharacter::EndOfTurn()
//{	
//	if (ghost)
//	{
//		if (!IsControlled()) return;
//		GetGhost()->GetInputs()->ClearActionEventBindings();
//		//GetGhost()->GetInputs()->BindAction(rotationAction, ETriggerEvent::Triggered, this, &AAntCharacter::RotationEndRound);
//	}
//	else if (inputs)
//	{
//		inputs->ClearActionEventBindings();
//		//if (InputComponent)
//		//{
//			//inputs = Cast<UEnhancedInputComponent>(InputComponent);
//			//if (rotationAction)
//				//inputs->BindAction(rotationAction, ETriggerEvent::Triggered, this, &AAntCharacter::RotationEndRound);
//		//}
//	}
//	ActiveBaseView();
//
//	isTurn = false;
//	
//	TObjectPtr<AAntPlayerState> _antState = teamController->GetPlayerState<AAntPlayerState>() ;
//	_antState->SetCanPlay(false);
//
//	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
//	if (!_subsystem)
//		return;
//	_subsystem->PlayerDidAction();
//}

//void AAntCharacter::Stop(const float _time)
//{
//	TObjectPtr<AAntGameModeBase> _antGameMode = GetWorld()->GetAuthGameMode<AAntGameModeBase>();
//	if (_antGameMode && !_antGameMode->IsTutoPlay())
//	{
//		FTimerHandle _timer;
//		GetWorld()->GetTimerManager().SetTimer(_timer, this, &AAntCharacter::EndOfTurn, 1.0f , false ,_time);
//		teamController->EndOfTurn();
//		//teamController->EnableInventory();
//	}
//}

void AAntCharacter::StoreItem()
{
	if (camera && camera->IsTopView())
		return;
	IncrementMoving();
	if(item)
		item->Store();
}

void AAntCharacter::IncrementMoving()
{
	if (movementValue > 1)
		return;
	movementValue++;
}

void AAntCharacter::DecrementMoving()
{
	movementValue--;
	if (movementValue != 0)
		movementValue = 0;
}

TObjectPtr<AGhostAntCharacter> AAntCharacter::Ghost()
{
	if(item)
		item->Destroy();

	GetWorld()->GetGameInstance()->GetSubsystem<UChatSubsystem>()->Ghost(name);
	FActorSpawnParameters _params;
	_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	TObjectPtr<AGhostAntCharacter> _ghost = GetWorld()->SpawnActor<AGhostAntCharacter>(ghostAnt, GetActorLocation(), GetActorRotation(), _params);
	if (!_ghost)
	{
		LOG("Ghost didn't spawned! (1)");
		return nullptr;
	}
	ghost = _ghost;
	ghost->SetActorHiddenInGame(true);
	TObjectPtr<UTeamInfoSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamInfoSubsystem>();
	if (!_subsystem)
		return nullptr;
	if (!teamController)
	{
		LOG("TeamController is null!");
		return nullptr;
	}

	ghost->SetModel(_subsystem->GetTeamDatas()[teamController->GetTeamID() - 1].mesh);
	if (IsPawnControlled())
		GetController()->Possess(ghost);
	ghost->SetTeamController(teamController);
	onGhost.Broadcast();
	return ghost;
}

FVector AAntCharacter::GetRandomPosition()
{
	TObjectPtr<USpawnPointSubsystem> _sub = GetWorld()->GetGameInstance()->GetSubsystem< USpawnPointSubsystem>();
	if (_sub)
		return _sub->SpawnAtRandomPoint();

	return FVector();
}

void AAntCharacter::Dead(bool _isInDeathZone, AAntCharacter* _ant)
{
	if (stat->IsDead() || !stat->MinLife()) return;

	FTimerHandle _time;

	if (IsControlled())
	{
		if (teamController->GetIsInventoryOpen())
		{
			teamController->OpenInventory();
		}
	}

	GetWorld()->GetTimerManager().SetTimer(_time, this, &AAntCharacter::DesactivateAnt, 2.0f);
	SetActorEnableCollision(false);
	UGameplayStatics::PlaySound2D(GetWorld(), playerSound);
	Cast<UCharacterMovementComponent>(GetMovementComponent())->bRunPhysicsWithNoController = false;
	GetWorld()->GetGameInstance()->GetSubsystem<UChatSubsystem>()->Death(name);
	Ghost();
	if (!ghost)
	{
		LOG("Ghost didn't spawn! (2)");
		return;
	}
	GetWorld()->GetGameInstance()->GetSubsystem<UGhostAntSubsystem>()->AddGhost(ghost);
	if(!_isInDeathZone)
		SpawnRandomPuddle();

	TObjectPtr<AAntPlayerState> _antState = teamController->GetPlayerState<AAntPlayerState>();
	_antState->SetCanPlay(false);

	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (!_subsystem)
		return;
	_subsystem->PlayerDidAction();
}

void AAntCharacter::DesactivateAnt()
{
	SetActorHiddenInGame(true);
}

void AAntCharacter::SpawnRandomPuddle()
{
	FActorSpawnParameters _param = FActorSpawnParameters();
	_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector _fromLocation = ghost->GetActorLocation();
	FVector _toLocation = _fromLocation;
	_toLocation.Z -= 2000;
	FHitResult _result;
	FCollisionQueryParams _params;
	_params.AddIgnoredActor(this);
	_params.AddIgnoredActor(ghost);
	if (GetWorld()->LineTraceSingleByChannel(_result, _fromLocation, _toLocation, ECollisionChannel::ECC_MAX, _params))
	{
		_result.Location.Z += 0.1;
		deathPuddle = GetWorld()->SpawnActor<APuddle>(puddleToSpawn, _result.Location, FRotator(0), _param);
		TObjectPtr<UTeamInfoSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UTeamInfoSubsystem>();
		if (!deathPuddle || !_subsystem)
			return;
		deathPuddle->SetPuddleType(_subsystem->GetTeamDatas()[teamController->GetTeamID() - 1].puddleType);
	}
}

//void AAntCharacter::ActiveIputs()
//{
//	EnableInput(teamController);
//}

void AAntCharacter::ActiveTopView()
{
	TObjectPtr<AGameModeBase> _gm = UGameplayStatics::GetGameMode(this);
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();

	if (_subsystem && !_subsystem->LoadingFinish())
		return;
	if (ItemUseP)
		return;
	camera->TopView();
}

void AAntCharacter::ActiveBaseView()
{
	TObjectPtr<AGameModeBase> _gm = UGameplayStatics::GetGameMode(this);
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();

	if (_subsystem && !_subsystem->LoadingFinish())
		return;
	if (ItemUseP)
		return;
	camera->BaseView();
}

void AAntCharacter::BindHealthBar()
{
	if (teamController)
		teamController->BindStatsEvents(stat);
}

void AAntCharacter::DelayJump()
{
	if (!teamController->AreInputsEnabled())
		return;
	if (camera && camera->IsTopView())
		return;
	if (camera->IsAim())
		return;

	if (item && movementValue == 0)
		item->Store();
	Jump();
	isJump = true;
}

void AAntCharacter::UseItem()
{
	if (!teamController->AreInputsEnabledEarly())
		return;
	TObjectPtr<AGameModeBase> _gm = UGameplayStatics::GetGameMode(this);
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();

	if ((!camera->IsAim() && !camera->IsTopView()) && (item != Cast<ATeleporter>(item) || item != Cast<AFallingMokia>(item)))
	{
		return;
	}

	if (_subsystem && !_subsystem->LoadingFinish())
		return;
	if (!item)
		return;
	if (item->IsActorBeingDestroyed())
	{
		ItemUseP = false;
		return;
	}
	float _delay = item->Use(this);
	onItemUsed.Broadcast();
	camera->ResetView();
	if (_delay < 0.0f)
		return;
	if (_delay == 0.0f)
	{
		ClearHand();
		return;
	}
	FTimerHandle _timer;
//	LOG("Removing item in " + FString::SanitizeFloat(_delay));
	GetWorld()->GetTimerManager().SetTimer(_timer, this, &AAntCharacter::ClearHand, _delay);
	//ClearHand();
}

void AAntCharacter::ClearHand()
{
	item = nullptr;
}

AItem* AAntCharacter::SelectItem(AItem* _item)
{
	if (!teamController->AreInputsEnabled())
		return nullptr;
	bWeapon = true;
	if (item)
		item->Destroy();
	item = _item;
	if (item)
	{

		if (TObjectPtr<ATeleporter> _teleporter = Cast<ATeleporter>(item))
		{
			_teleporter->AttachToComponent(teleporterArrow, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true));
		}
		else if (TObjectPtr<AFallingMokia> _fallingMokia = Cast<AFallingMokia>(item))
		{
			_fallingMokia->AttachToComponent(fallingMokiaArrow, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true));
		}
		else if (TObjectPtr<ABazooka> _bazooka = Cast<ABazooka>(item))
		{
			_bazooka->AttachToComponent(bazookaArrow, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true));
		}
		else if (TObjectPtr<ARasputin> _rasputin = Cast<ARasputin>(item))
		{
			_rasputin->AttachToComponent(rasputinArrow, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true));
		}
		else if (TObjectPtr<ARubiksCube> _rubiksCube  = Cast<ARubiksCube>(item))
		{
			_rubiksCube->AttachToComponent(rubiksCubeArrow, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true));
		}
		else if (TObjectPtr<AHealZoneTool> _healArrow = Cast<AHealZoneTool>(item))
		{
			_healArrow->AttachToComponent(healArrow, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true));
		}

		item->OnNoMoreUses().AddDynamic(teamController, &AAntController::EndOfTurnDelayed);
	}
	return item;
}

void AAntCharacter::IncrementSideMovement()
{
	sideMovements++;
}
void AAntCharacter::DecrementSideMovement()
{
	sideMovements--;
}
void AAntCharacter::StartGoingLeft()
{
	goingLeft = true;
}
void AAntCharacter::StopGoingLeft()
{
	goingLeft = false;
}