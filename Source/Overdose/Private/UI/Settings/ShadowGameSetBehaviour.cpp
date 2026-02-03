#include "UI/Settings/ShadowGameSetBehaviour.h"

void UShadowGameSetBehaviour::Init()
{
	Super::Init();
	label = "Shadow";
}

void UShadowGameSetBehaviour::Behaviour(const int& _level)
{
	Super::Behaviour(_level);
	user->SetShadowQuality(_level);
	user->ApplySettings(true);
}