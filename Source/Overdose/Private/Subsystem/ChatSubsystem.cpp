#include "Subsystem/ChatSubsystem.h"
#include "Utils/DevUtils.h"

UChatSubsystem::UChatSubsystem()
{
}

void UChatSubsystem::GetTextToDisplay()
{
	if (!chatWidget)
		return;
	if (textList.Num() <= 0)
		return;

	chatWidget->chatText->SetText(FText::FromString(textList[0]));
	textList.RemoveAt(0);
}

void UChatSubsystem::CleanChatText()
{
	chatWidget->chatText->SetText(FText::FromString(""));
}

void UChatSubsystem::DamageByRubiksCube(FString _name)
{
	TArray<FString> _rubiksText = 
	{
		_name + " dance on the wrong dance floor",
		_name + " has slipped on a toy",
		"Oh ! " + _name + " didn't watch the ground",
		"The wrong dance move for " + _name,
	};

	int _rand = FMath::RandRange(0, _rubiksText.Num() - 1);
	AddText(_rubiksText[_rand]);
}

void UChatSubsystem::DamageByBazooka(FString _sender, FString _receiver)
{
	TArray<FString> _bazooText =
	{
		"A direct hit from " + _sender + " on " + _receiver,
		_sender + " cover " + _receiver + " with confetti",
		_sender + " has try to choke " + _receiver + " with confetti",
	};

	int _rand = FMath::RandRange(0, _bazooText.Num() - 1);
	AddText(_bazooText[_rand]);
}

void UChatSubsystem::DamageByFall(FString _name)
{
	TArray<FString> _fallText =
	{
		_name + " as fallen on the dance the floor",
		"Ouch ! " + _name + " dances with a broken ankle now",
		_name + " tried to do a Triple Hustle in mid air",
	};

	int _rand = FMath::RandRange(0, _fallText.Num() - 1);
	AddText(_fallText[_rand]);
}

void UChatSubsystem::DamageByRasputin(FString _name)
{
	TArray<FString> _rasputinText =
	{
		"Rasputin has infected " + _name,
		"Rasputin jump on " + _name,
		_name + " has became an addict to Russian Folklore",
	};

	int _rand = FMath::RandRange(0, _rasputinText.Num() - 1);
	AddText(_rasputinText[_rand]);
}

void UChatSubsystem::DamageByMokia(FString _name)
{
	TArray<FString> _mokiaText =
	{
		"The last call has striked " + _name,
		"A call for destroying the dance floor",
		_name + " fired up after this call !",
	};

	int _rand = FMath::RandRange(0, _mokiaText.Num() - 1);
	AddText(_mokiaText[_rand]);
}

void UChatSubsystem::DamageByPoison(FString _name)
{
	TArray<FString> _poisonText =
	{
		_name + " is poisoned",
		_name + " has drunk too much of Ant Honey",
		_name + " has consumed too much of Amy Sugar",
	};

	int _rand = FMath::RandRange(0, _poisonText.Num() - 1);
	AddText(_poisonText[_rand]);
}

void UChatSubsystem::DamageByFlame(FString _name)
{
	TArray<FString> _flameText =
	{
		_name + " gets hyped up too much",
		_name + " is burning",
		_name + " burned his feet",
	};

	int _rand = FMath::RandRange(0, _flameText.Num() - 1);
	AddText(_flameText[_rand]);
}

void UChatSubsystem::Death(FString _name)
{
	TArray<FString> _deathText =
	{
		_name + " his flow will resonate to the Paradise",
		"A King of the night is dead... Goodbye " + _name,
		_name + " put his dance rival in the wind",
		_name + " dance with death now",
		"Doing the dancing move of the death is cool, when you're good " + _name,
	};

	int _rand = FMath::RandRange(0, _deathText.Num() - 1);
	AddText(_deathText[_rand]);
}

void UChatSubsystem::Ghost(FString _name)
{
	TArray<FString> _ghostText =
	{
		"Death is no more for " + _name,
		_name + " king of the night become a soul king",
		"Death could not control the envy of " + _name + " for dancing",
	};

	int _rand = FMath::RandRange(0, _ghostText.Num() - 1);
	AddText(_ghostText[_rand]);
}

void UChatSubsystem::AddText(FString _text)
{
	if (textList.Num() <= 0)
		onNeedToShow.Broadcast();

	textList.Add(_text);
}