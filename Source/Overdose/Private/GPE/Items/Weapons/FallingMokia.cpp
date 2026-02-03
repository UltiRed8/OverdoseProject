#include "GPE/Items/Weapons/FallingMokia.h"
#include <Actor/Characters/AntCharacter.h>
#include <Kismet/GameplayStatics.h>

AFallingMokia::AFallingMokia()
{
	name = "Falling Mokia";
}

float AFallingMokia::Use(TObjectPtr<AActor> _user)
{
	if (TObjectPtr<AAntCharacter> _ant = Cast<AAntCharacter>(_user))
	{
		FVector _posTopView = _ant->GetCamera()->GetTopViewCamera()->GetComponentLocation();
		FVector _targetPos = _posTopView;
		_targetPos.Z -= 4000;
		FHitResult _result;
		if (_ant->GetCamera()->IsTopView())
		{
			if (GetWorld()->LineTraceSingleByChannel(_result, _posTopView, _targetPos, ECollisionChannel::ECC_MAX))
			{
				FVector _resultLocation = _result.Location;
				_resultLocation.Z += 1500;
				_resultLocation.X -= 175;

				for (int _x = 0; _x <= 3; _x++)
				{
						//_finalLocation.X += 350 * _x;
						FVector _finalLocation = _resultLocation;
						_finalLocation.X += 350 * _x;
						TObjectPtr<AProjectile> _projectile = GetWorld()->SpawnActor<AProjectile>(projectile, _finalLocation, FRotator());
						if (_projectile)
						{
							_projectile->SetProjectileOwner(_user);
						}
				/*	for (int _y = 0; _y <= 1; _y++)
					{
					}*/
				}
				Super::Use(_user);
			
			}
			_ant->GetCamera()->BaseView();
			return removeDelay;
		}
		_ant->GetCamera()->TopView();
		return -1.0f;
	}
	return -1.0f;
}

//void AFallingMokia::Activate(TObjectPtr<AActor> _user)
//{
//	
//}
