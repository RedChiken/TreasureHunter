// Fill out your copyright notice in the Description page of Project Settings.


#include "StageGameState.h"

AStageGameState::AStageGameState() : NextLevelOnExit(TEXT("EntryLevel"))
{

}

void AStageGameState::BeginPlay()
{
	Super::BeginPlay();
}

void AStageGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
