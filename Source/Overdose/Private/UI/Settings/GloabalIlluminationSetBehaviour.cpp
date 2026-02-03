#include "UI/Settings/GloabalIlluminationSetBehaviour.h"

void UGloabalIlluminationSetBehaviour::Init()
{
	Super::Init();
	label = "Global Illumination";
}

void UGloabalIlluminationSetBehaviour::Behaviour(const int& _level)
{
	Super::Behaviour(_level);
	user->SetGlobalIlluminationQuality(_level);
	user->ApplySettings(true);
}