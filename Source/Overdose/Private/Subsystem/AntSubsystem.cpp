#include "Subsystem/AntSubsystem.h"
#include <Utils/DevUtils.h>

void UAntSubsystem::AddAnt(TObjectPtr<AAntCharacter> _ant)
{
	ants.Add(_ant);
}

void UAntSubsystem::RemoveAllAnts()
{
	ants.Empty();
}