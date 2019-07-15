// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THOutGameDefines.h"
#include "CreateSessionWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCreateSession, FString, HostName, int32, MaxPlayer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCancelCreateSession);
/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API UCreateSessionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintCallable)
		FOnCreateSession OnCreateSession;

	UPROPERTY(BlueprintCallable)
		FOnCancelCreateSession OnCancelCreateSession;
};
