#include "Subsystem/GhostAntSubsystem.h"

void UGhostAntSubsystem::AddGhost(TObjectPtr<AGhostAntCharacter> _ghost)
{
	ghostAnts.Add(_ghost);
}

void UGhostAntSubsystem::RemoveAllGhostAnts()
{
	ghostAnts.Empty();
}