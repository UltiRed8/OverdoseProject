#include "GPE/Items/Tools/Teleporter.h"
#include <Actor/Characters/AntCharacter.h>
#include <Utils/DevUtils.h>
#include <Kismet/GameplayStatics.h>

ATeleporter::ATeleporter()
{
	name = "Teleporter";
}

float ATeleporter::Use(TObjectPtr<AActor> _user)
{
	if (TObjectPtr<AAntCharacter> _ant = Cast<AAntCharacter>(_user))
	{
		FVector _posAnt = _ant->GetActorLocation();
		FVector _posTopView = _ant->GetCamera()->GetTopViewCamera()->GetComponentLocation();
		FVector _targetPos = _posTopView;
		FHitResult _result;
		_targetPos.Z -= 4000;
		if (_ant->GetCamera()->IsTopView())
		{
			if (GetWorld()->LineTraceSingleByChannel(_result, _posTopView, _targetPos, ECollisionChannel::ECC_MAX))
			{
				FVector _resultLocation = _result.Location;
				_resultLocation.Z += 40;
				TObjectPtr<UNavigationSystemV1> _nav = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
				if (!_nav)
					return -1.0f;
				FNavLocation _targetLocationFinal;
				_nav->ProjectPointToNavigation(_resultLocation, _targetLocationFinal, FVector(500, 500, 100));
				if (_targetLocationFinal.Location == FVector(0) || FVector::Distance(_targetLocationFinal.Location, _resultLocation) >= 500)
					return -1.0f;
				_targetLocationFinal.Location.Z += 80;
				_ant->SetActorLocation(_targetLocationFinal.Location);
				UGameplayStatics::PlaySoundAtLocation(this, teleportSound, _result.Location);
				Super::Use(_user);
				//_ant->Stop(5.0f);
				_ant->GetCamera()->BaseView();
				return removeDelay;
			}
			return -1.0f;
		}
		_ant->GetCamera()->TopView();
	}
	return -1.0f;
}

void ATeleporter::TeleportActor(TObjectPtr<AActor> _user)
{
	
}

