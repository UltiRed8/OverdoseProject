#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "CustomGameViewportClient.generated.h"

UENUM(Blueprintable)
enum class EGameInputMethod : uint8
{
	GI_Default,
	GI_Player1KeyboardMouseOnly,
};

UCLASS(Blueprintable)
class OVERDOSE_API UCustomGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inputs") EGameInputMethod gameInputMethod;

public:
	FORCEINLINE void SetGameInputMethod(EGameInputMethod _gameInputMethod)
	{
		gameInputMethod = _gameInputMethod;
	}

public:
	virtual void Init(struct FWorldContext& _worldContext, UGameInstance* _owningGameInstance, bool _bCreateNewAudioDevice = true)override;
	bool OverrideInputAxisHandler(FInputKeyEventArgs& _eventArgs, float& _delta, float& _deltaTime, int32& _numSamples);
	bool OverrideInputKey(FInputKeyEventArgs& _eventArgs);
};