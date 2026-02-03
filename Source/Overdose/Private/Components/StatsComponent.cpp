#include "Components/StatsComponent.h"
#include <Utils/DevUtils.h>
#include <Actor/Characters/AntCharacter.h>
#include <Gamemodes/AntGameModeBase.h>
#include <Kismet/GameplayStatics.h>
#include <Subsystem/GameSubsystem.h>
#include <Subsystem/StatSubsystem.h>
#include <Subsystem/ChatSubsystem.h>


void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	if (TObjectPtr<AAntCharacter> _ant = Cast<AAntCharacter>(GetOwner()))
	{
		onAddLife.Broadcast(GetCurrentLifeInPercent(), _ant);
	}
	InitUpdates();
}

void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStatsComponent::Heal(const int _heal)
{
	if (MaxLife())
		return;
	currentLife += _heal;
	if (currentLife > 100)
		currentLife = 100;
	if (TObjectPtr<AAntCharacter> _ant = Cast<AAntCharacter>(GetOwner()))
	{
		onAddLife.Broadcast(GetCurrentLifeInPercent(), _ant);
		SpawnIndicator(_heal);
	}
}

void UStatsComponent::Kill(bool _isInDeathZone)
{
	if (canNotTakeDamage) return;
	currentLife = 0;

	if (TObjectPtr<AAntCharacter> _ant = Cast<AAntCharacter>(GetOwner()))
	{
		onDeath.Broadcast(_isInDeathZone, _ant);
		onTakeDamage.Broadcast(GetCurrentLifeInPercent(), _ant);
		if (_ant->IsControlled() || _ant->GetGhost())
		{
			LOG("DEADD");
			_ant->GetTeamController()->EndOfTurn();
		}
	}
	isDead = true;
	FirstDead();
}

void UStatsComponent::TakeDamage(const int _damage, const bool _fromStatus)
{
	if (canNotTakeDamage) return;

	if (_damage == 0) return;
	TObjectPtr<UStatSubsystem> _statSub = GetWorld()->GetGameInstance()->GetSubsystem<UStatSubsystem>();
	if (!_statSub) return;

	TObjectPtr<AAntCharacter> _ant = Cast<AAntCharacter>(GetOwner());

	SpawnIndicator(-_damage);

	if (_ant)
	{
		_statSub->GetStatData(_ant->GetTeamController()->GetTeamID() - 1).damages += _damage;

		if (_ant->GetTeamController()->GetWidget()->GetInventoryWidget()->IsVisible())
		{
			ESlateVisibility _visibility = ESlateVisibility::Hidden;
			_ant->GetTeamController()->GetWidget()->GetInventoryWidget()->SetVisibility(_visibility);
		}
	}

	if (MinLife() || IsDeath())
	{
		isDead = true;
		return;
	}

	currentLife -= _damage;

	TObjectPtr<AAntCharacter> _chara = Cast<AAntCharacter>(GetOwner());

	if (_chara)
	{
		onTakeDamage.Broadcast(GetCurrentLifeInPercent(), _chara);
		if (MinLife()) { onDeath.Broadcast(false, _chara); };
		if (!_chara->IsControlled()) return;
		if (!_fromStatus)
		{
			_chara->GetTeamController()->EndOfTurn();
			LOG("ENNNNNNND");
		}
	}
}

void UStatsComponent::UpdateFireStatus()
{
	if (isGhost) return;
	if (isOnFire)
	{
		TakeDamage(15, true);
		if (TObjectPtr<AAntCharacter> _ant = Cast<AAntCharacter>(GetOwner()))
		{
			GetWorld()->GetGameInstance()->GetSubsystem<UChatSubsystem>()->DamageByFlame(_ant->GetName());
			UGameplayStatics::PlaySoundAtLocation(this, _ant->GetFireSoundStatus(), _ant->GetActorLocation());
		}
	}
}

void UStatsComponent::UpdatePoisonStatus()
{
	if (isGhost) return;
	if (currentLife == 1) return;
	if (isPoisoined)
	{
		int _damages = 10;
		_damages = currentLife - _damages <= 0 ? _damages + (currentLife - _damages) - 1 : _damages;
		TakeDamage(_damages, true);
		if (TObjectPtr<AAntCharacter> _ant = Cast<AAntCharacter>(GetOwner()))
		{
			GetWorld()->GetGameInstance()->GetSubsystem<UChatSubsystem>()->DamageByPoison(_ant->GetName());
			UGameplayStatics::PlaySoundAtLocation(this, _ant->GetPoisonSoundStatus(), _ant->GetActorLocation());
		}
	}
}

void UStatsComponent::SpawnIndicator(int _amount)
{
	FActorSpawnParameters _param;
	_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	TObjectPtr<ADamageIndicatorActor> _actor = GetWorld()->SpawnActor<ADamageIndicatorActor>(damageIndicator, _param);
	FVector _location = GetOwner()->GetActorLocation();
	_location.Z += 100;
	_actor->SetActorLocation(_location);
	_actor->SetDamagesAmount(_amount);
	_actor->UpdateText();
}

void UStatsComponent::FirstDead()
{
	TObjectPtr<UStatSubsystem> _statSub = GetWorld()->GetGameInstance()->GetSubsystem<UStatSubsystem>();
	if (!_statSub) return;
	for (FStatData& _stats : _statSub->GetStatDatas())
	{
		if (_stats.hasFirstKill)
		{
			return;
		}
	}
	TObjectPtr<AAntCharacter> _ant = Cast<AAntCharacter>(GetOwner());
	_statSub->GetStatData(_ant->GetTeamController()->GetTeamID() - 1).hasFirstKill = true;
}

void UStatsComponent::InitUpdates()
{
	TObjectPtr<UGameSubsystem> _subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameSubsystem>();
	if (_subsystem)
	{
		_subsystem->OnTurnEnded().AddDynamic(this, &UStatsComponent::UpdatePoisonStatus);
		_subsystem->OnTurnEnded().AddDynamic(this, &UStatsComponent::UpdateFireStatus);
	}
}