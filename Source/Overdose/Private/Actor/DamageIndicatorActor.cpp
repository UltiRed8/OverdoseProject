#include "../../Public/Actor/DamageIndicatorActor.h"
#include "Actor/DamageIndicatorActor.h"

ADamageIndicatorActor::ADamageIndicatorActor()
{
	PrimaryActorTick.bCanEverTick = true;
	text = CreateDefaultSubobject<UTextRenderComponent>("Text");
	RootComponent = text;
}

void ADamageIndicatorActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADamageIndicatorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADamageIndicatorActor::UpdateText()
{
	text->SetText(FText::FromString(amount >= 1 ? "+" : "" + FString::FromInt(amount)));
	text->SetTextRenderColor(amount >= 1 ? FColor::Green : FColor::White);
}