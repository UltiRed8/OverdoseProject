#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <UI/Widget/ChatWidget.h>
#include "ChatSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class OVERDOSE_API UChatSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNeedToShow);

	UPROPERTY(EditAnywhere) FString name;
	float timeChatDisplay = 5.0f;

public:
	UPROPERTY(BlueprintAssignable) FOnNeedToShow onNeedToShow;
	UPROPERTY(BlueprintReadWrite) TArray<FString> textList = {};
	UPROPERTY() TObjectPtr<UChatWidget> chatWidget = nullptr;

	UChatSubsystem();

	UFUNCTION(BlueprintCallable) void GetTextToDisplay();

public:
	UFUNCTION() FORCEINLINE FOnNeedToShow& OnNeedToShow() { return onNeedToShow; }
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetChatWidget(UChatWidget* _chat) { chatWidget = _chat; }
	UFUNCTION(BlueprintCallable) void CleanChatText();

	UFUNCTION(BlueprintCallable) void DamageByRubiksCube(FString _name); 
	UFUNCTION(BlueprintCallable) void DamageByBazooka(FString _sender, FString _receiver);
	UFUNCTION(BlueprintCallable) void DamageByFall(FString _name);
	UFUNCTION(BlueprintCallable) void DamageByRasputin(FString _name);
	UFUNCTION(BlueprintCallable) void DamageByMokia(FString _name);
	UFUNCTION(BlueprintCallable) void DamageByPoison(FString _name);
	UFUNCTION(BlueprintCallable) void DamageByFlame(FString _name);
	UFUNCTION(BlueprintCallable) void Death(FString _name);
	UFUNCTION(BlueprintCallable) void Ghost(FString _name);
	void AddText(FString _text);
};