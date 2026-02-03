#include "UI/Settings/TextureGameSetBehaviour.h"

void UTextureGameSetBehaviour::Init()
{
	Super::Init();
	label = "Textures";
}

void UTextureGameSetBehaviour::Behaviour(const int& _level)
{
	Super::Behaviour(_level);
	user->SetTextureQuality(_level);
	user->ApplySettings(true);
}