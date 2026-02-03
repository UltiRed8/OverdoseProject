#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include "EndRoundWidger.generated.h"

UCLASS()
class OVERDOSE_API UEndRoundWidger : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buttons", meta = (BindWidget)) TObjectPtr<UButton> nextRoundButton = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team Name", meta = (BindWidget)) TObjectPtr<UTextBlock> nameTeamTextBlock = nullptr;

public:
	void NativeConstruct();

private:
	UFUNCTION() void OnNextRound();

public:
	UFUNCTION() void Open(FString _name);
};