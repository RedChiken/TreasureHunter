// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THOutGameDefines.h"
#include "FindSessionWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTryConnect, int32, SessionIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCancelConnect);

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API UFindSessionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintCallable)
		FOnTryConnect OnTryConnect;

	UPROPERTY(BlueprintCallable)
		FOnCancelConnect OnCancelConnect;

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateRoomList(const TArray<FSessionInfo>& SessionsInfoArray);
};
