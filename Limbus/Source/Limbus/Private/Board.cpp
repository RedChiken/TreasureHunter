// Fill out your copyright notice in the Description page of Project Settings.

#include "Limbus.h"
#include "../Public/Board.h"
#include "../Public/PawnArchetype.h"

// Sets default values
ABoard::ABoard(int mNum) : MAPNUMBER(mNum)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	for (int i = 0; i < MAPSIZE[MAPNUMBER]; i++) {
		for (int j = 0; j < MAPSIZE[MAPNUMBER]; j++) {
			SpawnMap(i, j);
		}
	}
	/*test codes
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMeshAsset
	(TEXT("staticMesh'/Content/StarterContent/Shapes/Shape_Plane.uasset"));		//static mesh ��θ� �޾� UStaticMesh ��ü ����
	if (PlaneMeshAsset.Succeeded()) {
		//this code should be remain
		PrimaryActorTick.bCanEverTick = true;
		PlaneVisualComponent = CreateDefaultSubobject<UStaticMeshComponent>
			(TEXT("PlaneVisualComponent"));										//UStaticMeshComponent�� ��ü ����?
		PlaneVisualComponent->SetStaticMesh(PlaneMeshAsset.Object);				//static mesh ��ü�� UStaticMeshComponet�� �ִ´�.
		RootComponent = PlaneVisualComponent;									//�ʿ��� �߽��� �� ��ü ����
		SetActorEnableCollision(true);											//�� ��ü�� collision�� �ǵ��� ����
	}
	testcodes*/
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
void ABoard::SpawnMap(int x, int y) {
	static ConstructorHelpers::FObjectFinder<UStaticMesh> planeMeshAsset
	(TEXT("staticMesh'/Content/StarterContent/Shapes/Shape_Plane.uasset"));
	if (planeMeshAsset.Succeeded()) {
		PrimaryActorTick.bCanEverTick = true;
		PlaneVisualComponentMap[x][y] = CreateDefaultSubobject<UStaticMeshComponent>
			(TEXT("PlaneVisualComponent"));
		PlaneVisualComponentMap[x][y]->SetRelativeLocation
		(this->MAPPOSITION[MAPNUMBER] + FVector(x * 100.0f, y * 100.0f, 0.0f));
		if ((x == (MAPSIZE[MAPNUMBER] + 1) / 2) && (y == (MAPSIZE[MAPNUMBER] / 2))) {
			RootComponent = PlaneVisualComponentMap[x][y];
		}
		SetActorEnableCollision(true);
	}
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
