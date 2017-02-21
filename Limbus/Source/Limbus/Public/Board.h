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
	ABoard(int mapSize);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when map Spawned
	void SpawnMap(int x, int y);

	// Spawn Pawn. Called when pawn spawned.
	void SpawnPawn(FVector position, APawnArchetype* pawn);

	// Move Pawn
	void MovePawn(FVector now, FVector target);

	//TODO : attack pawn, skill pawn

protected:
	//testcodes
	TArray< TArray<UStaticMeshComponent*> > PlaneVisualComponentMap;
	UStaticMeshComponent* PlaneVisualComponent;

private:
	TMap<FVector, APawnArchetype*> pawnMap;
	TSet<APawnArchetype*> deadPawn;
	//TODO : need to make trap(int yet) clas
	TMap<FVector, int*> trapMap;
	const int MAPNUMBER;
	const TArray<FVector> MAPPOSITION = {
		FVector(46870.37037f, 58651.63545f, 0.0f),
		FVector(11423.07692f, 52063.9598f, 100.0f), 
		FVector(-43961.53846f, -51551.16784f, 100.0f), 
		FVector(9125.0f, -53995.88798f, 200.0f), 
		FVector(-33062.5f, 35860.75535f, 200.0f), 
		FVector(-47125.0f, 22648.05954f, 200.0f), 
		FVector(-19750.0f, -52071.06264f, 300.0f)
	};
	const TArray<int> MAPSIZE = { 11, 13, 13, 17, 17, 17, 19 };
};
