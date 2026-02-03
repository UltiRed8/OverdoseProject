#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <GPE/Puddle/Puddle.h>
#include "TeamInfoSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FTeamData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") TObjectPtr<USkeletalMesh> mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") TEnumAsByte<EPuddleType> puddleType = TYPENONE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") int winAmount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") FString name = "INSERT NAME";
};

UCLASS()
class OVERDOSE_API UTeamInfoSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Debugs") TArray<FTeamData> teamDatas;

public:
	UFUNCTION(BlueprintCallable) FORCEINLINE TArray<FTeamData>& GetTeamDatas()
	{
		return teamDatas;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetTeamDatas(TArray<FTeamData> _datas)
	{
		teamDatas = _datas;
	}

public:
	UTeamInfoSubsystem();
};