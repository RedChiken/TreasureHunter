// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THOutGameDefines.h"
#include "RoomMemberInfoWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSelectSessionMember);

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API URoomMemberInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintCallable)
		FOnSelectSessionMember OnSelectSessionMember;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetRoomMemberInfo(const int32& Index, const FSessionMemberInfo& RoomMemberInfo);
};
