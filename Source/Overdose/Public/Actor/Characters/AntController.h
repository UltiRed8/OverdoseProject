#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <Subsystem/AntSubsystem.h>
#include <UI/Widget/GamePlayerWidget.h>
#include <Components/InventoryComponent.h>
#include <UI/Player/CursorWidget.h>
#include "AntController.generated.h"

UCLASS()
class OVERDOSE_API AAntController : public APlayerController
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwitch);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFullTeamCreated, TArray<AAntCharacter*>, _ants);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPause, bool, _pause);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenInventory);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAction);
	UPROPERTY(VisibleAnywhere, Category = "Debugs") TArray<TObjectPtr<AAntCharacter>> ants = {};
	UPROPERTY(VisibleAnywhere, Category = "Debugs") TObjectPtr<UInventoryComponent> inventory = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") int antsPerTeam = 4;
	UPROPERTY(EditAnywhere, Category = "Settings") TSubclassOf<AAntCharacter> teamCharacter = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") TObjectPtr<UEnhancedInputComponent> inputPlayer = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") FString teamName = "TEAM_NAME";
	UPROPERTY(EditAnywhere, Category = "Settings") TObjectPtr<UInputAction> openInventory = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") TObjectPtr<UInputAction> pauseAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings") bool isInventoryOpen = false;
	UPROPERTY(EditAnywhere, Category = "Inputs") TObjectPtr<UEnhancedInputComponent> inputs = nullptr;
	UPROPERTY(VisibleAnywhere) int teamLife = 0;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") TArray<FString> names;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnFinished);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurnFinishedDelayed, bool,_instant );
	UPROPERTY(VisibleAnywhere, Category = "Debugs") bool isInputsEnabled = true;
	UPROPERTY(VisibleAnywhere, Category = "Debugs") bool isInputsEnabledEarly = true;
	UPROPERTY(BlueprintAssignable) FOnTurnFinished onTurnFinished;
	UPROPERTY(BlueprintAssignable) FOnTurnFinishedDelayed onTurnFinishedDelayed;

	int currentAnt = 0;
	int teamId = 0;
	bool hasInventory = true;
	bool endTurn = false;
	bool isCalled = false;
	FTimerHandle pendingRemoveInputsTimer;
	TObjectPtr<UCursorWidget> cursorMouse = nullptr;
	FOnSwitch onSwitch;
	FOnFullTeamCreated onFullTeamCreated;
	TObjectPtr<UGamePlayerWidget> widget;

public:
	AAntController();

	UFUNCTION(BlueprintCallable) FORCEINLINE bool AreInputsEnabled()
	{
		return isInputsEnabled;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE bool AreInputsEnabledEarly()
	{
		return isInputsEnabledEarly;
	}

	UPROPERTY(BlueprintAssignable) FOnPause onPauseEvent;
	UPROPERTY(BlueprintAssignable) FOnOpenInventory onOpenInventory;

	FORCEINLINE FOnTurnFinishedDelayed& OnTurnFinishedDelayed()
	{
		return onTurnFinishedDelayed;
	}

	FORCEINLINE FOnTurnFinished& OnTurnFinished()
	{
		return onTurnFinished;
	}

	UFUNCTION(BlueprintCallable) FORCEINLINE UInventoryComponent* GetInventory() { return inventory; }
	
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetIsInventoryOpen(bool _state) { isInventoryOpen = _state; }

	FORCEINLINE TObjectPtr<UEnhancedInputComponent> GetInputs() { return inputs; }
	FORCEINLINE void SetTeamName(const FString& _name)
	{
		teamName = _name;
		if (teamName == "Disco") names = { "Benny", "Robin", "Norma", "Marc" };
		else names = { "Morten", "Tina", "Rose-Marie", "Michael" };
		for (TObjectPtr<AAntCharacter> _ant : ants)
		{
			_ant->SetName(names[0]);
			names.RemoveAt(0);
		}
	}
	FORCEINLINE const FString& GetTeamName()
	{
		return teamName;
	}
	FORCEINLINE void SetTeamID(const int _id)
	{
		teamId = _id;
	}
	FORCEINLINE int GetTeamLife() { return teamLife; };
	UFUNCTION(BlueprintCallable) FORCEINLINE int GetTeamID()
	{
		return teamId;
	}
	FORCEINLINE TArray<TObjectPtr<AAntCharacter>>& GetAnts()
	{
		return ants;
	}
	FORCEINLINE FOnSwitch& OnSwitch()
	{
		return onSwitch;
	}
	FORCEINLINE FOnFullTeamCreated& OnFullTeamCreated()
	{
		return onFullTeamCreated;
	}
	FORCEINLINE void SetWidget(TObjectPtr<UGamePlayerWidget> _widget)
	{
		widget = _widget;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE UGamePlayerWidget* GetWidget()
	{
		return widget;
	}
	FORCEINLINE bool GetIsInventoryOpen()
	{
		return isInventoryOpen;
	}
	FORCEINLINE int  GetAntsPerTeam() { return antsPerTeam; }

	FORCEINLINE TObjectPtr<AAntCharacter>& GetCurrentAnt() { return ants[currentAnt]; };

	FORCEINLINE void Called()
	{
		isCalled = false;
	}


	void RemoveAnt(const int _index);
private:
	virtual void BeginPlay() override;
	void Tick(float DeltaTime);
	void InitTeam();
	void AddAnt();
	void InitBinding();
	UFUNCTION() void StopInputs();
	void OnPauseEvent();
public:
	UFUNCTION() void SwitchAnt();
	UFUNCTION() void UpdateHealLifeBar(float _percent, AAntCharacter* _ant);
	UFUNCTION() void UpdateDamageLifeBar(float _percent, AAntCharacter* _ant);
	UFUNCTION() void UpdateLifeBarVisibility(bool _inDeathZone, AAntCharacter* _ant);
	void InitLifeTeam();
	void Init();
	void UpdateColor();
	void BindStatsEvents(TObjectPtr<UStatsComponent> _stats);
	void OpenInventory();
	UFUNCTION() void EndOfTurn(const float _inDelay = 0.0f);
	UFUNCTION() void EndOfTurnDelayed(const float _notUsed);
};