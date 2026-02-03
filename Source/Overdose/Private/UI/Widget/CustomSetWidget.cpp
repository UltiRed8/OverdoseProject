// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/CustomSetWidget.h"

void UCustomSetWidget::NativeConstruct()
{
	Super::NativeConstruct();
	lowButton->OnClicked.AddDynamic(this, &UCustomSetWidget::OnLowClick);
	mediumButton->OnClicked.AddDynamic(this, &UCustomSetWidget::OnMediumClick);
	epicButton->OnClicked.AddDynamic(this, &UCustomSetWidget::OnEpicClick);
	ultraButton->OnClicked.AddDynamic(this, &UCustomSetWidget::OnUltraClick);
}

void UCustomSetWidget::OnLowClick()
{
	if (!behaviour) return;
	behaviour->Behaviour(0);
}

void UCustomSetWidget::OnMediumClick()
{
	if (!behaviour) return;
	behaviour->Behaviour(1);
}

void UCustomSetWidget::OnEpicClick()
{
	if (!behaviour) return;
	behaviour->Behaviour(2);
}

void UCustomSetWidget::OnUltraClick()
{
	if (!behaviour) return;
	behaviour->Behaviour(3);
}

void UCustomSetWidget::Init(const FString& _name)
{
	nameSettings->SetText(FText::FromString(_name));
}

void UCustomSetWidget::SetBehaviour(TObjectPtr<UGameSetBehaviour> _behaviour)
{
	behaviour = _behaviour;
}