// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "Board.generated.h"

/**
 * 
 */
UCLASS()
class LIMBUS_API ABoard : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	ABoard();
	// Called when map Spawned
	UFUNCTION(BlueprintCallable)
	void InitializePawn(FString& file);

	// Move Pawn
	UFUNCTION(BlueprintCallable)
	void MovePawn(FVector now, FVector target);

	//TODO : attack pawn, skill pawn, Spawn pawn in blueprints

	UPROPERTY(BlueprintReadWrite)
	TMap<FVector, class APawnArchetype* > pawnMap;
	UPROPERTY(BlueprintReadWrite)
	TSet<APawnArchetype* > deadPawn;
	//TODO : need to make trap(int yet) class
	UPROPERTY(BlueprintReadWrite)
	TMap<FVector, int> trapMap;

};
