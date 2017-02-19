// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Board.generated.h"

UCLASS()
class LIMBUS_API ABoard : public AActor
{
	GENERATED_BODY()
		class APawnArchetype;
public:	
	// Sets default values for this actor's properties
	ABoard();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when map Spawned
	void SpawnMap(int mapSize);

	// Spawn Pawn. Called when pawn spawned.
	void SpawnPawn(FVector position, APawnArchetype* pawn);

	// Move Pawn
	void MovePawn(FVector now, FVector target);

	//TODO : attack pawn, skill pawn
private:
	TMap<FVector, APawnArchetype*> pawnMap;
	TSet<APawnArchetype*> deadPawn;
	//TODO : need to make trap(int yet) clas
	TMap<FVector, int*> trapMap;
	
};
