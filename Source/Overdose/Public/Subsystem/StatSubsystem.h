#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StatSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FStatData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") int damages = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") int terrainDestroyed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") int ghostObjectPickedUp = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") int playTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") bool hasFirstKill = false;
};

UCLASS()
class OVERDOSE_API UStatSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category = "Debug") TArray<FStatData> statDatas;
public:
	UFUNCTION(BlueprintCallable) FORCEINLINE TArray<FStatData>& GetStatDatas()
	{
		return statDatas;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE FStatData& GetStatData(const int _id)
	{
		return statDatas[_id];
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetStatDatas(TArray<FStatData> _datas)
	{
		statDatas = _datas;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE void IncrementePlayTime() { statDatas[0].playTime++; }

public:
	UStatSubsystem();
private:
	void InitDatas();
public:
	UFUNCTION(BlueprintCallable) void Reset();
};
