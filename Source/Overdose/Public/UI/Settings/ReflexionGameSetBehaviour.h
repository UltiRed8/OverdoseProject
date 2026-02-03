#pragma once

#include "CoreMinimal.h"
#include "UI/Settings/GameSetBehaviour.h"
#include "ReflexionGameSetBehaviour.generated.h"

UCLASS()
class OVERDOSE_API UReflexionGameSetBehaviour : public UGameSetBehaviour
{
	GENERATED_BODY()
	
	virtual void Init() override;
	virtual void Behaviour(const int& _level) override;
};