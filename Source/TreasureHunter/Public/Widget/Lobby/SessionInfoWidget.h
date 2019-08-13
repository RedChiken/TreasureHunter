// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THOutGameDefines.h"
#include "SessionInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API USessionInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetSessionInfo(const int32& Index, const FSessionInfo& SessionInfo);
};
