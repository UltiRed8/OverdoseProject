#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/GameUserSettings.h"
#include "GameSetBehaviour.generated.h"

UCLASS()
class OVERDOSE_API UGameSetBehaviour : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Debugs") FString label = "Test";
	UPROPERTY(VisibleAnywhere, Category = "Debugs") TObjectPtr<UGameUserSettings> user = nullptr;

public:
	FORCEINLINE FString GetLabel()
	{
		return label;
	}

public:
	virtual void Init();
	virtual void Behaviour(const int& _level);
};
