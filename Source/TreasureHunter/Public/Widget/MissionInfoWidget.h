// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THOutGameDefines.h"
#include "MissionInfoWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSelectMission);

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API UMissionInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintCallable)
		FOnSelectMission OnSelectMission;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetMissionInfo(const FMissionInfo& MissionInfo);	
};
