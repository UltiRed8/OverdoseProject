#include "Actor/Characters/GhostAntCharacter.h"
#include <Subsystem/AntSubsystem.h>
#include <Subsystem/GhostAntSubsystem.h>
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include "Actor/Characters/AntController.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/CapsuleComponent.h>
#include <Utils/DevUtils.h>
#include <Gamemodes/AntGameModeBase.h>
#include <Kismet/GameplayStatics.h>
#include <GPE/Mine/Mine.h>
#include <Subsystem/GameSubsystem.h>
#include <Subsystem/StatSubsystem.h>
#include <PlayerStates/AntPlayerState.h>


AGhostAntCharacter::AGhostAntCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	springArm->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCharacterCameraComponent>("Camera");
	camera->SetupAttachment(springArm);

	bUseControllerRotationYaw = true;
	springArm->bUsePawnControlRotation = true;
	springArm->bInheritPitch = true;
	springArm->bInheritYaw = true;
	springArm->bInheritRoll = false;
	
	JumpMaxCount = 2;

	Cast<UCharacterMovementComponent>(GetMovementComponent())->bRunPhysicsWithNoController = true;

	detectSphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	detectSphere->InitSphereRadius(75.0f);
	detectSphere->SetupAttachment(RootComponent);

	detectSphere->SetHiddenInGame(false);
	detectSphere->SetGenerateOverlapEvents(true);
}

void AGhostAntCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGhostAntCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGhostAntCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InitInputSystem();
	BindActions();
}

void AGhostAntCharacter::Init()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UGhostAntSubsystem>()->AddGhost(this);
}

void AGhostAntCharacter::BindActions()
{
	inputs = Cast<UEnhancedInputComponent>(InputComponent);
	if (inputs)
	{
		inputs->ClearActionBindings();
		inputs->BindAction(movementActionUp, ETriggerEvent::Triggered, this, &AGhostAntCharacter::MovementUp);
		inputs->BindAction(movementActionDown, ETriggerEvent::Triggered, this, &AGhostAntCharacter::MovementDown);
		inputs->BindAction(movementActionLeft, ETriggerEvent::Triggered, this, &AGhostAntCharacter::MovementLeft);
		inputs->BindAction(movementActionRight, ETriggerEvent::Triggered, this, &AGhostAntCharacter::MovementRight);

		inputs->BindAction(movementActionLeft, ETriggerEvent::Started, this, &AGhostAntCharacter::IncrementSideMovement);
		inputs->BindAction(movementActionLeft, ETriggerEvent::Started, this, &AGhostAntCharacter::StartGoingLeft);
		inputs->BindAction(movementActionLeft, ETriggerEvent::Completed, this, &AGhostAntCharacter::DecrementSideMovement);
		inputs->BindAction(movementActionLeft, ETriggerEvent::Completed, this, &AGhostAntCharacter::StopGoingLeft);

		inputs->BindAction(movementActionRight, ETriggerEvent::Started, this, &AGhostAntCharacter::IncrementSideMovement);
		inputs->BindAction(movementActionRight, ETriggerEvent::Completed, this, &AGhostAntCharacter::DecrementSideMovement);

		inputs->BindAction(jumping, ETriggerEvent::Started, this, &AGhostAntCharacter::JumpWithDelay);
		inputs->BindAction(rotationAction, ETriggerEvent::Triggered, this, &AGhostAntCharacter::Rotation);
		inputs->BindAction(useItemAction, ETriggerEvent::Completed, this, &AGhostAntCharacter::Interact);
		TObjectPtr<AAntController> _controller = Cast<AAntController>(GetController());
		inputs->BindAction(switchAnt, ETriggerEvent::Started, _controller.Get(), &AAntController::SwitchAnt);

		inputs->BindAction(SwitchAction, ETriggerEvent::Started, this, &AGhostAntCharacter::ActiveTopView);
		inputs->BindAction(SwitchAction, ETriggerEvent::Completed, this, &AGhostAntCharacter::ActiveBaseView);
	}
}


void AGhostAntCharacter::InitInputSystem()
{
	TObjectPtr< UEnhancedInputLocalPlayerSubsystem> _inputSystem = GetWorld()->GetFirstPlayerController()->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	_inputSystem->ClearAllMappings();
	_inputSystem->AddMappingContext(InputMapping, 0);
}

void AGhostAntCharacter::NotifyActorBeginOverlap(AActor* _other)
{
	Super::NotifyActorBeginOverlap(_other);
	TObjectPtr<ABag> _item = Cast<ABag>(_other);
	TObjectPtr<AMine> _mine = Cast<AMine>(_other);

	if (!_item && !_mine) return;

	if (item) return;

	canPickItem = true;

	if(_item)
		allItems.Add(_item);

	else if(_mine)
		allItems.Add(_mine);	
}

void AGhostAntCharacter::NotifyActorEndOverlap(AActor* _other)
{
	Super::NotifyActorEndOverlap(_other);
	TObjectPtr<ABag> _item = Cast<ABag>(_other);
	TObjectPtr<AMine> _mine = Cast<AMine>(_other);

	if (!_item && !_mine) return;

	if (_item && allItems.Contains(_item))
	{
	    allItems.Remove(_item);
		LOG_CT("Remove", FColor::Red, 2);
	}

	else if (_mine && allItems.Contains(_mine))
	{
		allItems.Remove(_mine);
		LOG_CT("Remove2", FColor::Red, 2);
	}
}

void AGhostAntCharacter::MovementUp(const FInputActionInstance& _input)
{
	if (!teamController->AreInputsEnabled())
		return;
	if (camera && camera->IsTopView())
	{
		camera->GetTopViewCamera()->AddLocalOffset(FVector(0, 0, camera->GetArrowOfTopView()->GetForwardVector().X * topViewcameraSpeed));
		return;
	}
	if (camera->IsAim()) return;
	AddMovementInput(GetActorForwardVector() * 1);
}

void AGhostAntCharacter::MovementDown(const FInputActionInstance& _input)
{
	if (!teamController->AreInputsEnabled())
		return;
	if (camera && camera->IsTopView())
	{
		camera->GetTopViewCamera()->AddLocalOffset(FVector(0, 0, camera->GetArrowOfTopView()->GetForwardVector().X * -topViewcameraSpeed));

		return;
	}
	if (camera->IsAim()) return;
	AddMovementInput(GetActorForwardVector() * -1);
}

void AGhostAntCharacter::MovementLeft(const FInputActionInstance& _input)
{
	if (!teamController->AreInputsEnabled())
		return;
	if (camera && camera->IsTopView())
	{
		camera->GetTopViewCamera()->AddLocalOffset(FVector(0, camera->GetArrowOfTopView()->GetRightVector().Y * -topViewcameraSpeed, 0));
		return;
	}
	if (camera->IsAim()) return;
	AddMovementInput(GetActorRightVector() * -1);
}

void AGhostAntCharacter::MovementRight(const FInputActionInstance& _input)
{
	if (!teamController->AreInputsEnabled())
		return;
	if (camera && camera->IsTopView())
	{
		camera->GetTopViewCamera()->AddLocalOffset(FVector(0, camera->GetArrowOfTopView()->GetRightVector().Y * topViewcameraSpeed, 0));
		return;
	}
	if (camera->IsAim()) return;
	AddMovementInput(GetActorRightVector() * 1);
}

void AGhostAntCharacter::JumpWithDelay()
{
	if (!teamController->AreInputsEnabled())
		return;
	if (camera && camera->IsTopView()) return;
	if (camera->IsAim()) return;
	FTimerHandle _timer;
	onJumpStarted.Broadcast();
	GetWorld()->GetTimerManager().SetTimer(_timer, this, &AGhostAntCharacter::Jump, delayOfJump);
}

void AGhostAntCharacter::Rotation(const FInputActionInstance& _input)
{
	if (camera && camera->IsTopView())
		return;
	const FVector2D& _axis = _input.GetValue().Get<FVector2D>();
	AddControllerYawInput(_axis.X);
	AddControllerPitchInput(-_axis.Y);
}

void AGhostAntCharacter::GiveItem()
{
	TObjectPtr<AAntGameModeBase> _gameMode = Cast<AAntGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (!item || item->IsActorBeingDestroyed())
	{
		return;
	}

	if (item->IsAttachedTo(this))
	{
		FVector _posAnt = GetActorLocation();
		FVector _targetPos = _posAnt;
		FHitResult _result;
		_targetPos.Z -= 4000;
		FCollisionQueryParams _params;
		_params.AddIgnoredActor(this);
		if (GetWorld()->LineTraceSingleByChannel(_result, _posAnt, _targetPos, ECollisionChannel::ECC_MAX, _params))
		{
			item->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
			item->SetActorLocation(_result.Location);
			item->SetActorEnableCollision(true);
			item = nullptr;
			allItems.Empty();
			hasItem = false;
			FTimerHandle _timer;
			GetWorld()->GetTimerManager().SetTimer(_timer,this, &AGhostAntCharacter::End, 5);
			//teamController->EndOfTurn();
		}
		TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
		if (!_subsystem)
			return;
		_subsystem->PlayerDidAction();
	}
}

void AGhostAntCharacter::GetItem()
{
	if (canPickItem == true)
	{
		if (allItems.IsEmpty())
			return;
		item = allItems[0];
		hasItem = true;
		if (item)
		{
			onPickedUp.Broadcast();
			item->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("R_wrist"));
			item->SetActorEnableCollision(false);
			canPickItem = false;
		}
		
		TObjectPtr<UStatSubsystem> _statSub = GetWorld()->GetGameInstance()->GetSubsystem<UStatSubsystem>();
		if (!_statSub)
			return;
		_statSub->GetStatData(teamController->GetTeamID() - 1).ghostObjectPickedUp ++;
	}
}

void AGhostAntCharacter::ActiveTopView()
{
	if (useitem) return;
	camera->TopView();
}

void AGhostAntCharacter::ActiveBaseView()
{
	if (useitem) return;
	camera->BaseView();
}

void AGhostAntCharacter::Visible()
{
	if (isVisible) return;
	SetActorHiddenInGame(false);
	isVisible = true;
	onSpawn.Broadcast();
}

void AGhostAntCharacter::Interact()
{
	if (!teamController->AreInputsEnabled())
		return;
	if (item) GiveItem();
	else GetItem();
}
void AGhostAntCharacter::End()
{
	teamController->EndOfTurn();
}
void AGhostAntCharacter::IncrementSideMovement()
{
	sideMovements++;
}
void AGhostAntCharacter::DecrementSideMovement()
{
	sideMovements--;
}
void AGhostAntCharacter::StartGoingLeft()
{
	goingLeft = true;
}
void AGhostAntCharacter::StopGoingLeft()
{
	goingLeft = false;
}