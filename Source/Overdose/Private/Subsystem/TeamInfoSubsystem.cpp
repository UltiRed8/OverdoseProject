#include "Subsystem/TeamInfoSubsystem.h"

UTeamInfoSubsystem::UTeamInfoSubsystem()
{
	for (int _index = 0; _index < 2; _index++)
		teamDatas.Add(FTeamData());
}