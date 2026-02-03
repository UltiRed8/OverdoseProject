// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/GraphicsMenuWidget.h"
#include <Components/SizeBox.h>

void UGraphicsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GenerateSettings();
}

void UGraphicsMenuWidget::GenerateSettings()
{
	TArray<UWidget*> _widgets = verticalBox->GetAllChildren();

	for (int _index = 0; _index < _widgets.Num(); _index++)
	{
		TObjectPtr<USizeBox> _sizeBox = Cast<USizeBox>(_widgets[_index]);
		TObjectPtr<UCustomSetWidget> _custom = Cast<UCustomSetWidget>(_sizeBox->GetChildAt(0));
		if (!_custom) continue;

		TObjectPtr<UGameSetBehaviour> _set = NewObject<UGameSetBehaviour>(this, settings[_index]);
		_set->Init();
		_custom->Init(_set->GetLabel());
		_custom->SetBehaviour(_set);


	}
}