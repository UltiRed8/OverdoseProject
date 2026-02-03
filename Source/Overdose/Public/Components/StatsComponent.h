#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Actor/DamageIndicatorActor.h>
#include "StatsComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERDOSE_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAddLife , float , _addLife, AAntCharacter* , _ant);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTakeDamage , float , _takeDamage, AAntCharacter*, _ant);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDeath, bool, isInDeathZone, AAntCharacter*, _ant);

	FOnAddLife onAddLife;
	FOnTakeDamage onTakeDamage;
	FOnDeath onDeath;

#pragma region Stat
	UPROPERTY(EditAnywhere, Category = "Stat" , meta = (ClampMin = 0, ClampMax = 100, UIMin = 0, UIMax = 100)) int maxLife = 100;
	UPROPERTY(EditAnywhere, Category = "Stat" , meta = (ClampMin = 0 , ClampMax = 100 , UIMin = 0 , UIMax = 100)) int currentLife = 100;
#pragma endregion

#pragma region BOOL
	UPROPERTY(EditAnywhere) bool isGhost = false;
	UPROPERTY(EditAnywhere) bool isPoisoined = false;
	UPROPERTY(EditAnywhere) bool isOnFire = false;

	bool canNotTakeDamage = true;
#pragma endregion

	UPROPERTY(EditAnywhere, Category = "Settings") TSubclassOf<ADamageIndicatorActor> damageIndicator;

public:
	UPROPERTY(EditAnywhere , BlueprintReadWrite)  bool isDead = false;
	FORCEINLINE void SetIsPoisoined(const bool _status) { isPoisoined = _status; };
	FORCEINLINE void SetIsOnFire(const bool _status) { isOnFire = _status; };
	FORCEINLINE void SetIsGhost(const bool _status) { isGhost = _status; };
	FORCEINLINE void SetInvulnerability(const bool _status) { canNotTakeDamage = _status; };
	FORCEINLINE void SetCurrentLife(const int _currentLife)  { currentLife = _currentLife; };

	FORCEINLINE bool IsDead() const { return isDead; };
	FORCEINLINE bool IsDeath() const { return  currentLife <= 0; };
	FORCEINLINE bool MaxLife() const { return currentLife >= maxLife;};
	FORCEINLINE bool MinLife() const { return currentLife <= 0;};

	FORCEINLINE int GetMaxLife() const { return maxLife; };
	FORCEINLINE float GetCurrentLifeInPercent() const { return (float)currentLife / (float) maxLife;};

	FORCEINLINE FOnAddLife& OnAddLife() { return onAddLife; }
	FORCEINLINE FOnTakeDamage& OnTakeDamage() { return onTakeDamage; }
	FORCEINLINE FOnDeath& OnDeath() { return onDeath; };

	UFUNCTION(BlueprintCallable) FORCEINLINE int GetCurrentLife() const { return currentLife; };
	UFUNCTION(BlueprintCallable) FORCEINLINE bool IsOnFire() const
	{
		return isOnFire;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE bool IsPoisoned() const
	{
		return isPoisoined;
	}
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void InitUpdates();
	void Heal(const int _heal);
	void Kill(bool _isInDeathZone);
	void TakeDamage(const int _damage, const bool _isFromPoison = false);
	void FirstDead();
	void SpawnIndicator(int _amount);

	UFUNCTION() void UpdateFireStatus();
	UFUNCTION() void UpdatePoisonStatus();
};
