// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTH_LobbyGameMode, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(ErrorTH_LobbyGameMode, Error, All);
DECLARE_LOG_CATEGORY_EXTERN(LogTH_LobbyPlayerController, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogTH_THGameInstance, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogTH_WidgetControllerComponent, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(ErrorTH_WidgetControllerComponent, Error, All);
DECLARE_LOG_CATEGORY_EXTERN(LogTH_StageGameMode, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogTH_StagePlayerController, Verbose, All);
DECLARE_LOG_CATEGORY_EXTERN(LogTH_PlayerBase_MovingDirection, Verbose, All);
DECLARE_LOG_CATEGORY_EXTERN(LogTH_PlayerBase_MovementType, Verbose, All);
DECLARE_LOG_CATEGORY_EXTERN(LogTH_PlayerBase_IdleType, Verbose, All);
DECLARE_LOG_CATEGORY_EXTERN(LogTH_PlayerBase_CheckValue, Verbose, All);
DECLARE_LOG_CATEGORY_EXTERN(LogTH_PlayerBase_CheckOverlap, Verbose, All);

DECLARE_LOG_CATEGORY_EXTERN(THError, Error, All);
DECLARE_LOG_CATEGORY_EXTERN(THWarning, Warning, All);
DECLARE_LOG_CATEGORY_EXTERN(THDisplay, Display, All);
DECLARE_LOG_CATEGORY_EXTERN(THLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(THVerbose, Verbose, All);
DECLARE_LOG_CATEGORY_EXTERN(THVeryVerbose, VeryVerbose, All);

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetNameStringByIndex((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

#define GETBOOLSTRING(bvalue) (bvalue ? TEXT("true") : TEXT("false"))