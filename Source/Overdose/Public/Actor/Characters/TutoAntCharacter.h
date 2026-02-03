// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <EnhancedInputComponent.h>
#include <GPE/Items/Item.h>
#include "TutoAntCharacter.generated.h"


UCLASS()
class OVERDOSE_API ATutoAntCharacter : public ACharacter
{
	GENERATED_BODY()

	bool isGhost = false;
	UPROPERTY(EditAnywhere, Category = "Settings|Stats") int topViewCameraSpeed = 7;
	UPROPERTY(EditAnywhere, Category = "Settings|Stats") float delayOfJump = 0.1;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") TObjectPtr<AItem> item = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") TObjectPtr<UEnhancedInputComponent> inputs = nullptr;

public:

	ATutoAntCharacter();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
