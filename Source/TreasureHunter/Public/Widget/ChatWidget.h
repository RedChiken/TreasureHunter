// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THOutGameDefines.h"
#include "ChatWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSendMessage, FString, Message);

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API UChatWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintCallable)
		FOnSendMessage OnSendMessage;

	UFUNCTION(BlueprintImplementableEvent)
		void OnUpdateChat(const TArray<FChatInfo>& ChatInfoArray);
};
