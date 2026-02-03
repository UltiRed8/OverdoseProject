#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <InputMappingContext.h>
#include <Components/CharacterCameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/StatsComponent.h>
#include "GhostAntCharacter.h"
#include <GPE/Components/KnockbackComponent.h>
#include "GPE/Puddle/Puddle.h"
#include <Components/FallDamageComponent.h>
#include "GenericPlatform/ICursor.h"
#include <Sound/SoundCue.h>
#include <Components/WidgetComponent.h>
#include "AntCharacter.generated.h"

class AAntController;

UCLASS()
class OVERDOSE_API AAntCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Debugs") bool isTurn = false;

	UPROPERTY(EditAnywhere, Category = "Settings") TSubclassOf<AGhostAntCharacter> ghostAnt = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") TObjectPtr<AGhostAntCharacter> ghost = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") TObjectPtr<AAntController> teamController;
	UPROPERTY(EditAnywhere, Category = "Settings")TSubclassOf<APuddle> puddleToSpawn = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") TObjectPtr<APuddle> deathPuddle = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Stats", meta = (ClampMin = 5, ClampMax = 15, UIMin = 5, UIMax = 15)) int topViewCameraSpeed = 7;
	UPROPERTY(EditAnywhere, Category = "Settings|Stats", meta = (ClampMin = 0 , ClampMax = 2 , UiMin = 0 , UIMax = 2)) float delayOfJump = 0.1;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") TObjectPtr<AItem> item = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") TObjectPtr<UEnhancedInputComponent> inputs = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") int sideMovements = 0;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") bool goingLeft = false;
	bool canPlay = false;
	bool bWeapon = false;
	bool ItemUseP = false;
	bool isMoving = false;
	bool knockbackStatus = false;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") FString name = "Bill";

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemUsed);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGhost);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDebug);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpStarted);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathUpdate);
	FOnDeath onDeath;
	FOnGhost onGhost;
	FVector randomPosition;
	FOnDeathUpdate onDeathUpdate;
	UPROPERTY(BlueprintAssignable) FOnDebug onDebug;
	UPROPERTY(BlueprintAssignable) FOnJumpStarted onJump;
	UPROPERTY(BlueprintAssignable) FOnItemUsed onItemUsed;

private:
	UPROPERTY(EditAnywhere, Category = "Settings|Sounds") TObjectPtr<USoundWave> poisonStatusSound = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Sounds") TObjectPtr<USoundWave> fireStatusSound = nullptr;
	UPROPERTY(EditAnywhere, Category = "Debugs|Components") TObjectPtr<USpringArmComponent> springArm = nullptr;
	UPROPERTY(EditAnywhere, Category = "Debugs|Components") TObjectPtr<UStatsComponent> stat;
	UPROPERTY(EditAnywhere, Category = "Debugs|Components") TObjectPtr<UKnockbackComponent> knockback = nullptr;
	UPROPERTY(EditAnywhere, Category = "Debugs|Components") TObjectPtr<UFallDamageComponent> falling = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Inputs|Mappings") TObjectPtr<UInputMappingContext> InputMappings = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Inputs") TObjectPtr<UInputAction> movementActionUp = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Inputs") TObjectPtr<UInputAction> movementActionDown = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Inputs") TObjectPtr<UInputAction> movementActionRight = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Inputs") TObjectPtr<UInputAction> movementActionLeft = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Inputs") TObjectPtr<UInputAction> rotationAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Inputs") TObjectPtr<UInputAction> SwitchAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Inputs") TObjectPtr<UInputAction> jumping = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Inputs") TObjectPtr<UInputAction> switchAnt = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Inputs") TObjectPtr<UInputAction> debug = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Inputs") TObjectPtr<UInputAction> aim = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Inputs") TObjectPtr<UInputAction> itemUse = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Inputs") TObjectPtr<UInputAction> moveCameraTopView  = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Inputs") TObjectPtr<UInputAction> TopViewDown = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings|Inputs") TObjectPtr<USoundCue> playerSound = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Debugs") int movementValue = 0;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|PositionArrow") TObjectPtr<UArrowComponent> healArrow = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|PositionArrow") TObjectPtr<UArrowComponent> teleporterArrow = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|PositionArrow") TObjectPtr<UArrowComponent> bazookaArrow = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|PositionArrow") TObjectPtr<UArrowComponent> fallingMokiaArrow = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|PositionArrow") TObjectPtr<UArrowComponent> rasputinArrow = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|PositionArrow") TObjectPtr<UArrowComponent> rubiksCubeArrow = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugs|Components") TObjectPtr<UCharacterCameraComponent> camera = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugs|Components") TObjectPtr<UWidgetComponent> widget = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugs|Components") TObjectPtr<UWidgetComponent> widget2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool isJump = true;

public:
	UFUNCTION(BlueprintCallable) FORCEINLINE bool IsSideWalking()
	{
		return sideMovements >= 1;
	}
	
	UFUNCTION(BlueprintCallable) FORCEINLINE bool GetKnockBackStatus()
	{
		return knockbackStatus;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetKnockBackStatus(bool _status)
	{
		knockbackStatus = _status;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE bool IsGoingLeft()
	{
		return goingLeft;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetIsTurn(const bool _value)
	{
		isTurn = _value;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE bool IsTurn()
	{
		return isTurn;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetName(FString _name)
	{
		name = _name;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE FString GetName()
	{
		return name;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetInputMappingContext(UInputMappingContext* _InputMappings)
	{
		InputMappings = _InputMappings;
	}

	UFUNCTION(BlueprintCallable) FORCEINLINE bool IsJumping()
	{
		return isJump;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE UKnockbackComponent* GetKnockback()
	{
		return knockback;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE AItem* GetItem()
	{
		return item;
	}
	FORCEINLINE void SetItem(TObjectPtr<AItem> _item)
	{
		item = _item;
	}
	FORCEINLINE TObjectPtr<APuddle> GetDeathPuddle()
	{
		return deathPuddle;
	}
	FORCEINLINE FOnDebug& OnDebug()
	{
		return onDebug;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE AGhostAntCharacter* GetGhost() 
	{
		return ghost;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE UStatsComponent* GetStat()
	{
		return stat.Get();
	}
	FORCEINLINE bool IsDead() const
	{
		return stat->IsDead();
	}
	FORCEINLINE FOnDeath& OnDeath()
	{
		return onDeath;
	}
	FORCEINLINE FOnJumpStarted& OnJumpStarted()
	{
		return onJump;
	}
	//FORCEINLINE FOnItemUsed& OnItemUsed()
	//{
	//	return onItemUsed;
	//}
	FORCEINLINE FOnGhost& OnGhost()
	{
		return onGhost;
	}
	FORCEINLINE  bool IsItemUse()
	{
		return ItemUseP;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE UCharacterCameraComponent* GetCamera() const
	{
		return camera;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE AAntController* GetTeamController()
	{
		return teamController;
	}
	FORCEINLINE void SetTeamController(TObjectPtr<AAntController> _teamController)
	{
		teamController = _teamController;
	}
	FORCEINLINE TObjectPtr<UEnhancedInputComponent> GetInputs() const
	{
		return inputs;
	}
	FORCEINLINE bool CanPlay() const
	{
		return canPlay;
	}
	FORCEINLINE TObjectPtr<USoundWave> GetFireSoundStatus() 
	{
		return fireStatusSound;
	}
	FORCEINLINE TObjectPtr<USoundWave> GetPoisonSoundStatus()
	{
		return poisonStatusSound;
	}
	FORCEINLINE void ResetMovementValue()
	{
		movementValue = 0;
	}
	FORCEINLINE int GetMovementValue()
	{
		return movementValue;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE bool IsAiming()
	{
		return camera->IsAim();
	}

public:
	AAntCharacter();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void UseItem();
	void Jumping();
	void Register();
	void DelayJump();
	void BindActions();
	//void ActiveIputs();
	void ActiveTopView();
	void IncrementMoving();
	void DecrementMoving();
	void SpawnRandomPuddle();
	void Rotation(const FInputActionInstance& _input);
	void MovementUp(const FInputActionInstance& _input);
	void MovementLeft(const FInputActionInstance& _input);
	void MovementDown(const FInputActionInstance& _input);
	void MovementRight(const FInputActionInstance& _input);
	//void RotationEndRound(const FInputActionInstance& _input);
	void MoveTopViewCamera(const FInputActionInstance& _input);
	FVector GetRandomPosition();
	TObjectPtr<AGhostAntCharacter> Ghost();
	UFUNCTION() void InitInputSystem();
	UFUNCTION(BlueprintCallable) void Dead(bool _isInDeathZone, AAntCharacter* _ant);
	void DesactivateAnt();
	UFUNCTION() void ClearHand();
	UFUNCTION(BlueprintCallable) AItem* SelectItem(AItem* _item);
	UFUNCTION() void IncrementSideMovement();
	UFUNCTION() void DecrementSideMovement();
	UFUNCTION() void StartGoingLeft();
	UFUNCTION() void StopGoingLeft();

public:
	void StoreItem();
	void ActiveBaseView();
	//UFUNCTION() void Stop(const float _time = 0.0f);
	//UFUNCTION() void EndOfTurn();
	UFUNCTION() void BindHealthBar();
};