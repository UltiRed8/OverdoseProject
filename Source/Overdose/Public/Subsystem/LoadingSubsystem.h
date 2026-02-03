#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <functional>
#include "LoadingSubsystem.generated.h"

UCLASS()
class OVERDOSE_API ULoading : public UObject
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoad);
	UPROPERTY(VisibleAnywhere, Category = "Debug") FOnLoad onLoad;
	std::function<bool()> condition;

public:
	FORCEINLINE void SetCondition(const std::function<bool()> _condition)
	{
		condition = _condition;
	}
	FORCEINLINE std::function<bool()> GetCondition()
	{
		return condition;
	}
	FORCEINLINE FOnLoad& OnLoad()
	{
		return onLoad;
	}
};

UCLASS()
class OVERDOSE_API ULoadingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadingStarted);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadingEnded);
	UPROPERTY(VisibleAnywhere, Category = "Debug") TArray<TObjectPtr<ULoading>> loadingsStates;
	UPROPERTY(VisibleAnywhere, Category = "Debug") int loadIndex = -1;
	UPROPERTY(VisibleAnywhere, Category = "Debug") bool isLoading = false;
	UPROPERTY(VisibleAnywhere, Category = "Debug") FTimerHandle timer;
	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category = "Debug") FOnLoadingStarted onLoadingStarted;
	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category = "Debug") FOnLoadingEnded onLoadingEnded;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Debug") TObjectPtr<UTexture2D> loadingTexture;

public:
	FORCEINLINE FOnLoadingStarted& OnLoadingStarted()
	{
		return onLoadingStarted;
	}
	FORCEINLINE FOnLoadingEnded& OnLoadingEnded()
	{
		return onLoadingEnded;
	}
public:
	void Load(const float& _conditionDelay = 1.0f);
	TObjectPtr<ULoading> AddLoadingState();
	UFUNCTION(BlueprintCallable) void StopLoad();
private:
	void StartTimer();
	void TimerCheck();
	void StopTimer();
	void LoadNextState();
	void Clear();
};