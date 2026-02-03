#include "Components/CharacterCameraComponent.h"
#include <Actor/Characters/AntCharacter.h>
#include <Utils/DevUtils.h>

UCharacterCameraComponent::UCharacterCameraComponent()
{
	topViewCamera = CreateDefaultSubobject<UCameraComponent>("Top View Camera");
	topViewCamera->SetWorldLocationAndRotation(FVector(0, 0, 2000), FQuat(FRotator(-90)));
	arrowTopView = CreateDefaultSubobject<UArrowComponent>("Arrow");
	arrowTopView->SetupAttachment(topViewCamera);

}

void UCharacterCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UCharacterCameraComponent::SwitchCamera()
{
	TObjectPtr<APlayerController> _currentPlayer = GetWorld()->GetFirstPlayerController();
	_currentPlayer->SetViewTarget(topViewCamera->GetOwner());
}

void UCharacterCameraComponent::ToggleViewPoint()
{
	bool _isMainCameraActive = IsActive();
	SetActive(!_isMainCameraActive);
	topViewCamera->SetActive(_isMainCameraActive);
}

void UCharacterCameraComponent::TopView()
{
	FVector _location = GetOwner()->GetActorLocation();
	_location.Z = 2000;
	topViewCamera->SetWorldLocation(_location);
	SetActive(false);
	topViewCamera->SetActive(true);
	isTopView = true;
	OnTopView.Broadcast();

}

void UCharacterCameraComponent::BaseView()
{
	TObjectPtr<AAntCharacter> _ant;
	if (_ant && _ant->IsItemUse())
		return;
	SetActive(true);
	topViewCamera->SetActive(false);
	isTopView = false;
}

void UCharacterCameraComponent::Aim()
{
	if (IsTopView())
	{
		topViewCamera->SetFieldOfView(zoom);
		SetFieldOfView(deZoom);
		return;
	}
	SetFieldOfView(zoom);
	//SetFieldOfView()
	SetRelativeLocation(FVector(60.0,30.0,60));
	isAim = true;
}

void UCharacterCameraComponent::ResetView()
{
	topViewCamera->SetFieldOfView(deZoom);
	SetFieldOfView(deZoom);
	ResetRelativeTransform();
	isAim = false;
}


void UCharacterCameraComponent::Init()
{
	basePosition = GetComponentLocation();
	maxZoom = GetComponentLocation() * GetComponentLocation();
}


