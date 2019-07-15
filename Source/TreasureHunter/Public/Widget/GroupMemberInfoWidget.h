// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THOutGameDefines.h"
#include "GroupMemberInfoWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSelectGroupMember);
/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API UGroupMemberInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintCallable)
		FOnSelectGroupMember OnSelectGroupMember;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetGroupMemberInfo(const FGroupMemberInfo& GroupMemberInfo);	
};
