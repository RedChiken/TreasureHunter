// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THOutGameDefines.h"
#include "LobbyWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMenu);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSkill);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFindMatch);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreviewCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextSkin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreviewSkin);

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintCallable)
		FOnMenu OnMenu;

	UPROPERTY(BlueprintCallable)
		FOnSkill OnSkill;

	UPROPERTY(BlueprintCallable)
		FOnItem OnItem;

	UPROPERTY(BlueprintCallable)
		FOnFindMatch OnFindMatch;

	UPROPERTY(BlueprintCallable)
		FOnNextCharacter OnNextCharacter;

	UPROPERTY(BlueprintCallable)
		FOnPreviewCharacter OnPreviewCharacter;

	UPROPERTY(BlueprintCallable)
		FOnNextSkin OnNextSkin;

	UPROPERTY(BlueprintCallable)
		FOnPreviewSkin OnPreviewSkin;

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateMissionList(const TArray<FMissionInfo>& MissionInfoArray);

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateGroupMemberList(const TArray<FGroupMemberInfo>& GroupMemberInfoArray);
};
