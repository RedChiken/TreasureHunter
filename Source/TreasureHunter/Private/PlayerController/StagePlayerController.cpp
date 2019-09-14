// Fill out your copyright notice in the Description page of Project Settings.


#include "StagePlayerController.h"
#include "TreasureHunter.h"
#include "Widget/Stage/StageHUDWidget.h"
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
	Super::SetupInputComponent();
	//TODO: BindAction
}

bool AStagePlayerController::InitializeHUD()
{
	UE_LOG(LogTH_StagePlayerController, Verbose, TEXT("%hs: NetMode=%d Role=%d RemoteRole=%d"), __FUNCTION__, (int32)GetNetMode(), (int32)Role, (int32)GetRemoteRole());
	if ((GetNetMode() == NM_DedicatedServer) || ((GetNetMode() == NM_ListenServer) && (GetRemoteRole() != ROLE_SimulatedProxy)))
	{
		return false;
	}
	HUD = CreateHUD();
	check(HUD);
	return true;
}

void AStagePlayerController::TickHUD(float DeltaSeconds)
{
	if (!HUD)
	{
		return;
	}

	{
		//TODO: HUD Visibility
	}

	
}
