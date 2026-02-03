#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Components/SplineComponent.h>

#include <GPE/Components/ExplosableComponent.h>
#include "Projectile.generated.h"

class AAntCharacter;

UCLASS()
class OVERDOSE_API AProjectile : public AActor
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawn);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndMovement);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHitActor, AActor*, _actor);

	UPROPERTY(BlueprintAssignable) FOnSpawn onSpawn;
	UPROPERTY(BlueprintAssignable) FOnEndMovement onEndMovement;
	UPROPERTY(BlueprintAssignable) FOnHitActor onHitActor;


	UPROPERTY(EditAnywhere , Category = "Stat") float percent = 0.0f;

	UPROPERTY(EditAnywhere , Category = "Component") TObjectPtr<USplineComponent> splineLine = nullptr;

	UPROPERTY(VisibleAnywhere) FVector currentProjectilePosition = FVector();
	UPROPERTY(VisibleAnywhere) TObjectPtr<AActor> projectileOwner = nullptr;


	UPROPERTY(EditAnywhere, Category = "Settings") float speed = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Settings") bool shouldHaveOwner = true;


	bool isExplode = true;

public:
	UPROPERTY(EditAnywhere, Category = "Mesh", BlueprintReadWrite) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Component" , BlueprintReadWrite) TObjectPtr<UExplosableComponent> explosableComponent = nullptr;

public:
	UFUNCTION(BlueprintCallable) FORCEINLINE AActor* GetProjectileOwner() { return projectileOwner; }
	FORCEINLINE void SetProjectileOwner(TObjectPtr<AActor> _actor)
	{
		projectileOwner = _actor;
	}
	FORCEINLINE void SetShouldHaveOwner(const bool _shouldHaveOwner)
	{
		shouldHaveOwner = _shouldHaveOwner;
	}
	FORCEINLINE bool IsExplode()
	{
		return isExplode;
	}
	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetMesh()
	{
		return mesh;
	}
	FORCEINLINE FVector GetPosition()
	{
		return currentProjectilePosition;
	}
	FORCEINLINE FOnSpawn& OnSpawn()
	{
		return onSpawn;
	}
	FORCEINLINE FOnEndMovement& OnEndMovement()
	{
		return onEndMovement;
	}
	FORCEINLINE FOnHitActor& OnHitActor()
	{
		return onHitActor;
	}

public:
	AProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void UpdatePosition();

	void Explosion();

	void NotifyActorBeginOverlap(AActor* _other);
	void CheckHitActor(TObjectPtr<AActor> _actor);
public:
	void AddIgnoredActor(TObjectPtr<AActor> _actor);
};