// Fill out your copyright notice in the Description page of Project Settings.

#include "TreasureHunter.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, TreasureHunter, "TreasureHunter" );

DEFINE_LOG_CATEGORY(LogTH_LobbyGameMode);
DEFINE_LOG_CATEGORY(ErrorTH_LobbyGameMode);
DEFINE_LOG_CATEGORY(LogTH_LobbyPlayerController);
DEFINE_LOG_CATEGORY(LogTH_THGameInstance);
DEFINE_LOG_CATEGORY(LogTH_WidgetControllerComponent);
DEFINE_LOG_CATEGORY(ErrorTH_WidgetControllerComponent);
DEFINE_LOG_CATEGORY(LogTH_StageGameMode);
DEFINE_LOG_CATEGORY(LogTH_StagePlayerController); 
DEFINE_LOG_CATEGORY(LogTH_PlayerBase_MovingDirection);
DEFINE_LOG_CATEGORY(LogTH_PlayerBase_MovementType);
DEFINE_LOG_CATEGORY(LogTH_PlayerBase_IdleType);
DEFINE_LOG_CATEGORY(LogTH_PlayerBase_CheckValue);
DEFINE_LOG_CATEGORY(LogTH_PlayerBase_CheckOverlap);

DEFINE_LOG_CATEGORY(THError);
DEFINE_LOG_CATEGORY(THWarning);
DEFINE_LOG_CATEGORY(THDisplay);
DEFINE_LOG_CATEGORY(THLog);
DEFINE_LOG_CATEGORY(THVerbose);
DEFINE_LOG_CATEGORY(THVeryVerbose);