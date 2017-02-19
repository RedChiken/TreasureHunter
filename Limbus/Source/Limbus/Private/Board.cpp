// Fill out your copyright notice in the Description page of Project Settings.

#include "Limbus.h"
#include "../Public/Board.h"
#include "../Public/PawnArchetype.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Set static mesh, shader.
void ABoard::SpawnMap(int mapSize) {

}

// Spawn Pawn
void ABoard::SpawnPawn(FVector position, APawnArchetype* pawn) {
	if (pawnMap.Contains(position)) {
		//something on the map already
	}
	else {
		pawnMap.Add(position, pawn);
	}
}

// Move Pawn
void ABoard::MovePawn(FVector now, FVector target) {
	if (pawnMap.Contains(target)) {
		//something on the map already
	}
	else {
		pawnMap.Add(target, pawnMap.FindAndRemoveChecked(now));
	}
}
