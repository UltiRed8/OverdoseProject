#include "Subsystem/StatSubsystem.h"

UStatSubsystem::UStatSubsystem()
{
	InitDatas();
}
void UStatSubsystem::InitDatas()
{
	for (int _index = 0; _index < 2; _index++)
	{
		statDatas.Add(FStatData());
	}
}
void UStatSubsystem::Reset()
{
	statDatas.Empty();
	InitDatas();
}