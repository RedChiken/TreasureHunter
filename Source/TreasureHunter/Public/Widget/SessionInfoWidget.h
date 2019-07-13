// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THOutGameDefines.h"
#include "SessionInfoWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSelectSession);

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API USessionInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintCallable)
		FOnSelectSession OnSelectSession;

	UFUNCTION(BlueprintImplementableEvent)
		void SetSessionInfo(const FSessionInfo& SessionInfo);
};
