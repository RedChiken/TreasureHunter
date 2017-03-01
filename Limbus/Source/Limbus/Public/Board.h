// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "Board.generated.h"

/**
 * 
 */
UCLASS(BlueprintCallable)
class LIMBUS_API ABoard : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	ABoard();
	// Called when map Spawned
	UFUNCTION(BlueprintCallable)

	void InitializePawn(FString& file);

	// Move Pawn
	void MovePawn(FVector now, FVector target);

	//TODO : attack pawn, skill pawn
protected:
	// Spawn Pawn. Called when pawn spawned.
	void SpawnPawn(FVector position, class APawnArchetype* pawn);

private:
	TMap<FVector, APawnArchetype*> pawnMap;
	TSet<APawnArchetype*> deadPawn;
	//TODO : need to make trap(int yet) class
	TMap<FVector, int*> trapMap;

};
