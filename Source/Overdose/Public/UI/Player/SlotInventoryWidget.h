#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <GPE/Items/Item.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "SlotInventoryWidget.generated.h"

UCLASS()
class OVERDOSE_API USlotInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<AItem> item = nullptr;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite, Category = "Debugs") TObjectPtr<UTextBlock> name = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite, Category = "Debugs") TObjectPtr<UImage> slotImage = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugs") TObjectPtr<UTextBlock> parentAmmoText = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite, Category = "Settings") int ammo = 0;
	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadWrite, Category = "Settings") int lockedTurns = 0;
	UPROPERTY(EditAnywhere, Category = "Settings") TObjectPtr<USoundWave> soundOnClick = nullptr;

public:
	UFUNCTION(BlueprintCallable) FORCEINLINE TSubclassOf<AItem> GetItem()
	{
		return item;
	}
	FORCEINLINE void SetNameSlot(const FText& _name)
	{
		name->SetText(_name);
	}
	UFUNCTION(BlueprintCallable) void PlaySoundOnClick();
	UFUNCTION(BlueprintCallable) void CloseMenu();
};