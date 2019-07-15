// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THOutGameDefines.h"
#include "SessionWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnToggleReady);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCancelSession);
/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API USessionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintCallable)
		FOnToggleReady OnToggleReady;

	UPROPERTY(BlueprintCallable)
		FOnCancelSession OnCancelSession;

	UFUNCTION(BlueprintImplementableEvent)
		void SetReadyButtonVisual(bool bIsHost);

	UFUNCTION(BlueprintImplementableEvent)
		void SetReadyState(bool bReady);

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateRoomMemberList(const TArray<FRoomMemberInfo>& RoomMemberInfoArray);
};
