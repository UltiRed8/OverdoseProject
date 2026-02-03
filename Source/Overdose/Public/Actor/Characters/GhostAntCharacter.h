// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GPE/Items/Item.h"
#include <InputMappingContext.h>
#include <Components/CharacterCameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include "Components/SphereComponent.h"
#include <GPE/Bags/Bag.h>
#include "GhostAntCharacter.generated.h"

class AAntController;

UCLASS()
class OVERDOSE_API AGhostAntCharacter : public ACharacter
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpStarted);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickedUp);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawn);

	UPROPERTY(EditAnywhere) TObjectPtr<AActor> item = nullptr;
	UPROPERTY(EditAnywhere, Category = "Stat", meta = (ClampMin = 5, ClampMax = 15, UIMin = 5, UIMax = 15)) int topViewcameraSpeed = 7;
	UPROPERTY(EditAnywhere, Category = "Material") TObjectPtr<UMaterialInterface> ghostMaterial;
	UPROPERTY(EditAnywhere, Category = "Settings|Stats", meta = (ClampMin = 0, ClampMax = 2, UiMin = 0, UIMax = 2)) float delayOfJump = 0.1;
	
	UPROPERTY(VisibleAnywhere, Category = "Debugs") int sideMovements = 0;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") bool goingLeft = false;

	UPROPERTY(VisibleAnywhere) TArray<TObjectPtr<AActor>> allItems = {};
	UPROPERTY(VisibleAnywhere) TObjectPtr<AAntController> teamController  ;
#pragma region BOOL
	bool useitem = false;
	bool canPickItem = false;
	bool isVisible = false;
	bool hasItem = false;
	UPROPERTY(BlueprintAssignable) FOnJumpStarted onJumpStarted;
	UPROPERTY(BlueprintAssignable) FOnPickedUp onPickedUp;
	UPROPERTY(BlueprintAssignable) FOnSpawn onSpawn;
	/*UPROPERTY(BlueprintAssignable)*/ bool isGhostPossess = false;
#pragma endregion

#pragma region Components
	UPROPERTY(EditAnywhere, Category = "Component") TObjectPtr<USpringArmComponent> springArm = nullptr;
	UPROPERTY(EditAnywhere, Category = "Component") TObjectPtr<UCharacterCameraComponent> camera = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<USphereComponent> detectSphere = nullptr;
#pragma endregion

#pragma region MAPPING
private:
	UPROPERTY(EditAnywhere, Category = "Mapping") TObjectPtr<UInputMappingContext> InputMapping = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input") TObjectPtr<UEnhancedInputComponent> inputs = nullptr;
#pragma endregion

#pragma region INPUTS
	UPROPERTY(EditAnywhere, Category = "Input") TObjectPtr<UInputAction> movementActionUp = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input") TObjectPtr<UInputAction> movementActionDown = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input") TObjectPtr<UInputAction> movementActionRight = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input") TObjectPtr<UInputAction> movementActionLeft = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input") TObjectPtr<UInputAction> rotationAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input") TObjectPtr<UInputAction> jumping = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input") TObjectPtr<UInputAction> switchAnt = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input") TObjectPtr<UInputAction> useItemAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input") TObjectPtr<UInputAction> SwitchAction = nullptr;
#pragma endregion

public:
	UFUNCTION(BlueprintCallable) FORCEINLINE bool IsSideWalking()
	{
		return sideMovements >= 1;
	}

	UFUNCTION(BlueprintCallable) FORCEINLINE bool IsGhostPossess()
	{
		return isGhostPossess;
	}

	UFUNCTION(BlueprintCallable) FORCEINLINE void SetPossess(bool _possess)
	{
		isGhostPossess = _possess;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE bool IsGoingLeft()
	{
		return goingLeft;
	}
	FORCEINLINE FOnJumpStarted& OnJumpStarted()
	{
		return onJumpStarted;
	}
	FORCEINLINE FOnPickedUp& OnPickedUp()
	{
		return onPickedUp;
	}
	FORCEINLINE void SetModel(TObjectPtr<USkeletalMesh> _model)
	{
		GetMesh()->SetSkeletalMesh(_model);
		if (!ghostMaterial)
			return;
		for (int _index = 0; _index < 2; _index++)
		{
			GetMesh()->SetMaterial(_index, ghostMaterial);
		}
	}
	UFUNCTION() FORCEINLINE FOnSpawn& OnSpawn() { return onSpawn; }
	FORCEINLINE void SetTeamController(TObjectPtr<AAntController> _teamController)
	{
		teamController = _teamController;
	}

	FORCEINLINE TObjectPtr<UEnhancedInputComponent> GetInputs()
	{
		return inputs;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE  bool HasItem()
	{
		return hasItem;
	}
public:
	AGhostAntCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void Init();
	void BindActions();
	void InitInputSystem();
	virtual void NotifyActorBeginOverlap(AActor* _other);
	virtual void NotifyActorEndOverlap(AActor* _other);

public:
	void MovementUp(const FInputActionInstance& _input);
	void MovementDown(const FInputActionInstance& _input);
	void MovementLeft(const FInputActionInstance& _input);
	void MovementRight(const FInputActionInstance& _input);
	void JumpWithDelay();
	void Rotation(const FInputActionInstance& _input);
	void GiveItem();
	void GetItem();
	void ActiveTopView();
	void ActiveBaseView();
	void Visible();
	void Interact();
	void End();
	UFUNCTION() void IncrementSideMovement();
	UFUNCTION() void DecrementSideMovement();
	UFUNCTION() void StartGoingLeft();
	UFUNCTION() void StopGoingLeft();
};