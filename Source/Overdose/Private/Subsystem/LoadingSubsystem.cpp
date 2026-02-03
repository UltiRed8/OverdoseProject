#include "Subsystem/LoadingSubsystem.h"
#include "Utils/DevUtils.h"

void ULoadingSubsystem::Load(const float& _conditionDelay)
{
	if (isLoading)
		return;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &ULoadingSubsystem::TimerCheck, _conditionDelay, true);
	GetWorld()->GetTimerManager().PauseTimer(timer);
	isLoading = true;
	onLoadingStarted.Broadcast();
	LoadNextState();
}
void ULoadingSubsystem::StopLoad()
{
	StopTimer();
	Clear();
}
void ULoadingSubsystem::Clear()
{
	loadingsStates.Empty();
	loadIndex = -1;
	isLoading = false;
	StopTimer();
	GetWorld()->GetTimerManager().ClearTimer(timer);
}
void ULoadingSubsystem::StartTimer()
{
	GetWorld()->GetTimerManager().UnPauseTimer(timer);
}
void ULoadingSubsystem::TimerCheck()
{
	if (!isLoading)
		return;
	LOG_CT("Checking Loading State: " + FString::FromInt(loadIndex), FColor::Yellow, 10);
	if (loadingsStates[loadIndex]->GetCondition()())
	{
		LoadNextState();
	}
}
void ULoadingSubsystem::StopTimer()
{
	GetWorld()->GetTimerManager().PauseTimer(timer);
}
void ULoadingSubsystem::LoadNextState()
{
	loadIndex++;
	if (loadIndex == loadingsStates.Num())
	{
		onLoadingEnded.Broadcast();
		Clear();
		return;
	}
	StartTimer();
	loadingsStates[loadIndex]->OnLoad().Broadcast();
}
TObjectPtr<ULoading> ULoadingSubsystem::AddLoadingState()
{
	TObjectPtr<ULoading> _state = NewObject<ULoading>();
	loadingsStates.Add(_state);
	return _state;
}