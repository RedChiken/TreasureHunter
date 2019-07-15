// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THOutGameDefines.h"
#include "RoomMemberInfoWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSelectRoomMember);

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API URoomMemberInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintCallable)
		FOnSelectRoomMember OnSelectRoomMember;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetRoomMemberInfo(const int32& Index, const FRoomMemberInfo& RoomMemberInfo);
};
