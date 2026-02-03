#include "GameViewportClient/CustomGameViewportClient.h"
#include <Utils/DevUtils.h>
#include <GameFramework/PlayerInput.h>
#include <Subsystem/GameSubsystem.h>

void UCustomGameViewportClient::Init(struct FWorldContext& _worldContext, UGameInstance* _owningGameInstance, bool _bCreateNewAudioDevice)
{
	Super::Init(_worldContext, _owningGameInstance, _bCreateNewAudioDevice);
	OnOverrideInputAxis().BindUObject(this, &UCustomGameViewportClient::OverrideInputAxisHandler);
	OnOverrideInputKey().BindUObject(this, &UCustomGameViewportClient::OverrideInputKey);
    TObjectPtr<UGameSubsystem> _sub = GetWorld()->GetGameInstance()->GetSubsystem< UGameSubsystem>();
    if (!_sub)
        return;

    _sub->SetControllerController(gameInputMethod == EGameInputMethod::GI_Default);
}

bool UCustomGameViewportClient::OverrideInputAxisHandler(FInputKeyEventArgs& _eventArgs, float& _delta, float& _deltaTime, int32& _numSamples)
{
    if (gameInputMethod == EGameInputMethod::GI_Default)
        return false;
    if (_eventArgs.IsGamepad()) 
    {
        if (const TObjectPtr<UGameInstance> _GI = GetGameInstance()) 
        {
            const int32 _numLocalPlayers = _GI->GetNumLocalPlayers();
            if (_numLocalPlayers > 1) 
            {
                const TObjectPtr<ULocalPlayer> _targetPlayer = _GI->GetLocalPlayerByIndex(1);
                const int32 _controllerId = _targetPlayer->GetControllerId();
                if (_controllerId < 0) { _eventArgs.ControllerId++; }
                if (_targetPlayer && _targetPlayer->PlayerController)
                {
                    _eventArgs.ControllerId = _controllerId;
                    _targetPlayer->PlayerController->InputKey(FInputKeyParams(_eventArgs.Key, (double)_delta, _deltaTime, _numSamples, _eventArgs.IsGamepad(), _eventArgs.InputDevice));
                    return true;
                }
            }
        }
    }
    return false;
}

bool UCustomGameViewportClient::OverrideInputKey(FInputKeyEventArgs& _eventArgs)
{
    if (gameInputMethod == EGameInputMethod::GI_Default)
        return false;
    if (_eventArgs.IsGamepad()) 
    {
        if (const TObjectPtr<UGameInstance> _GI = GetGameInstance()) 
        {
            const int32 _numLocalPlayers = _GI->GetNumLocalPlayers();
            if (_numLocalPlayers > 1) 
            {
                const TObjectPtr<ULocalPlayer> _targetPlayer = _GI->GetLocalPlayerByIndex(1);
                const int32 _controllerId = _targetPlayer->GetControllerId();
                if (_controllerId < 0) { _eventArgs.ControllerId++; }
                if (_targetPlayer && _targetPlayer->PlayerController)
                {
                    _eventArgs.ControllerId = _controllerId;
                    FInputKeyParams _params = FInputKeyParams(_eventArgs.Key, _eventArgs.Event, static_cast<double>(_eventArgs.AmountDepressed), _eventArgs.IsGamepad(), _eventArgs.InputDevice);
                    const bool _bResult = _targetPlayer->PlayerController->InputKey(_params);
                    if (!_bResult && _eventArgs.Key.IsMouseButton())
                    {
                        return true;
                    }
                    return _bResult;
                }
            }
        }
    }
    return false;
}
