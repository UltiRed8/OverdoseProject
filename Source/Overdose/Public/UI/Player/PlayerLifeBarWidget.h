#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/ProgressBar.h>
#include <Actor/Characters/AntCharacter.h>
#include "PlayerLifeBarWidget.generated.h"

UCLASS()
class OVERDOSE_API UPlayerLifeBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Debugs") TObjectPtr<UProgressBar> lifeProgressBar = nullptr;

private:
	virtual void NativeConstruct() override;

public:
	UFUNCTION() void OnAddLife(float _percent);
	UFUNCTION() void OnTakeDamage(float _percent);
	UFUNCTION() void OnSwitchUpdate();
	UFUNCTION(BlueprintCallable) void SetHidden();
};