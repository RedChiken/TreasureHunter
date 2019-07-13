// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "THChatType.h"
#include "THClassType.h"
#include "THOutGameDefines.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSessionInfo {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		FString SessionName;

	UPROPERTY(BlueprintReadOnly)
		FString HostName;
};

USTRUCT(BlueprintType)
struct FRoomMemberInfo {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		FString PlayerName;

	UPROPERTY(BlueprintReadOnly)
		bool bReady;
};

USTRUCT(BlueprintType)
struct FGroupMemberInfo {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		EClassType ClassType;

	UPROPERTY(BlueprintReadOnly)
		FString PlayerName;
};

USTRUCT(BlueprintType)
struct FChatInfo {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		EChatType ChatType;

	UPROPERTY(BlueprintReadOnly)
		FString PlayerName;

	UPROPERTY(BlueprintReadOnly)
		FString ChatText;
};

USTRUCT(BlueprintType)
struct FMissionInfo {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		FString MissionName;
};