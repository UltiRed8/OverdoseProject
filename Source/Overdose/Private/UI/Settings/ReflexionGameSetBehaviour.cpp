#include "UI/Settings/ReflexionGameSetBehaviour.h"

void UReflexionGameSetBehaviour::Init()
{
	Super::Init();
	label = "Reflexion";
}

void UReflexionGameSetBehaviour::Behaviour(const int& _level)
{
	Super::Behaviour(_level);
	user->SetReflectionQuality(_level);
	user->ApplySettings(true);
}