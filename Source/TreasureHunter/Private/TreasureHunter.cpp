// Fill out your copyright notice in the Description page of Project Settings.

#include "TreasureHunter.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, TreasureHunter, "TreasureHunter" );

DEFINE_LOG_CATEGORY(THError);
DEFINE_LOG_CATEGORY(THWarning);
DEFINE_LOG_CATEGORY(THDisplay);
DEFINE_LOG_CATEGORY(THLog);
DEFINE_LOG_CATEGORY(THVerbose);
DEFINE_LOG_CATEGORY(THVeryVerbose);