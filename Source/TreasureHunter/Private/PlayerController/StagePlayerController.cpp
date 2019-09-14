// Fill out your copyright notice in the Description page of Project Settings.


#include "StagePlayerController.h"
#include "TreasureHunter.h"
#include "GameState/StageGameState.h"

#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/Pawn.h"

AStagePlayerController::AStagePlayerController()
{

}

void AStagePlayerController::BeginPlay()
{
	Super::BeginPlay();
	InitializeHUD();
}

void AStagePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TickHUD(DeltaSeconds);
}

void AStagePlayerController::SetupInputComponent()
{
	
}

bool AStagePlayerController::InitializeHUD()
{
	return false;
}

void AStagePlayerController::TickHUD(float DeltaSeconds)
{
}

void AStagePlayerController::RequestFinalizeCurrentStage()
{
}
