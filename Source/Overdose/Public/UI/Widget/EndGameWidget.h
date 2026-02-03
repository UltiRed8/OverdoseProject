#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Actor/Characters/AntController.h>
#include "EndGameWidget.generated.h"

UCLASS()
class OVERDOSE_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> team1Name = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> team2Name = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> team1Score = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> team2Score = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> team1DamageTaken = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> team2DamageTaken = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> team1ItemPickup = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> team2ItemPickup = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> team1IsFirstBlood = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> team2IsFirstBlood = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> nameTeamTextBlock = nullptr;

public:
	void Open(TArray<AAntController*> _controllers);
};