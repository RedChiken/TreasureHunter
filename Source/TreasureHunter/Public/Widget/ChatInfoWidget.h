// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THOutGameDefines.h"
#include "ChatInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API UChatInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetChatInfo(const FChatInfo& ChatInfo);
};
