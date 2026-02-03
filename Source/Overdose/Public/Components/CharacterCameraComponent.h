// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include <Components/ArrowComponent.h>

#include "CharacterCameraComponent.generated.h"
/**
 * 
 */

UCLASS()

class OVERDOSE_API UCharacterCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTopView);

	UPROPERTY(EditAnywhere, Category = "Settings")  TObjectPtr<UCameraComponent> topViewCamera = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") TObjectPtr<USpringArmComponent> springArm = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") TObjectPtr<UArrowComponent> arrowTopView = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") FVector maxZoom = FVector();
	UPROPERTY(EditAnywhere, Category = "Settings") float zoom = 50;
	UPROPERTY(EditAnywhere, Category = "Settings") float deZoom = 90;
	float speed = 10.0f;
	bool isAim = false;
	bool isTopView = false;
	FVector basePosition = FVector();
	FOnTopView OnTopView;

public:
	UCharacterCameraComponent();

public:
	void BeginPlay();

public:
	FORCEINLINE bool IsAim() const { return isAim; };
	UFUNCTION(BlueprintCallable)FORCEINLINE bool IsTopView() const { return isTopView; };
	FORCEINLINE void SetTopView(const bool _newView) { isTopView = _newView; };
	FORCEINLINE TObjectPtr<UArrowComponent> GetArrowOfTopView() const { return arrowTopView; };
	FORCEINLINE TObjectPtr<UCameraComponent> GetTopViewCamera() const { return topViewCamera;};
public:
	void SwitchCamera();
	void ToggleViewPoint();
	void TopView();
	void BaseView();
	void Aim();
	void ResetView();
	void Init();
};
