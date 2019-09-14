// Fill out your copyright notice in the Description page of Project Settings.


#include "StageGameMode.h"
#include "PlayerState/StagePlayerStateBase.h"
#include "TreasureHunter.h"

#include "GameFramework/Pawn.h"
#include "GameState/StageGameState.h"
#include "Kismet/GameplayStatics.h"

AStageGameMode::AStageGameMode()
{
	GameStateClass = AStageGameState::StaticClass();
	PlayerStateClass = AStagePlayerStateBase::StaticClass();
}

void AStageGameMode::PostLogin(APlayerController* NewController)
{
	Super::PostLogin(NewController);

	if (NewController->GetPawn() == nullptr)
	{
		int32 ID = UGameplayStatics::GetPlayerControllerID(NewController);
		UE_LOG(LogTH_StageGameMode, Log, TEXT("%hs: Spawning a player pawn for PlayerControllerID=%d"), __FUNCTION__, ID);

		AActor* StartSpot = FindPlayerStart(NewController);
		APawn* Character = SpawnDefaultPawnFor(NewController, StartSpot);
		NewController->Possess(Character);
	}
}
