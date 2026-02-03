#include "Gamemodes/AntGameModeBase.h"
#include <Subsystem/GameSubsystem.h>

void AAntGameModeBase::StartPlay()
{
	Super::StartPlay();
	Init();
}

void AAntGameModeBase::Init()
{
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (!_subsystem)
		return;
	_subsystem->Init(this);
}