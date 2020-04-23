// Fill out your copyright notice in the Description page of Project Settings.


#include "THWallBase.h"
#include "TreasureHunter.h"
#include "Kismet/GameplayStatics.h"
#include "net/UnrealNetwork.h"
#include "Components/InterpToMovementComponent.h"
#include "Engine.h"

ATHWallBase::ATHWallBase() : ATHActorBase()
{
	MovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("InterpolationMovement"));
}

void ATHWallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHWallBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHWallBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHWallBase, MovementComponent);
}

void ATHWallBase::ActivateWall(TArray<FVector> Point, bool bPositionIsRelative)
{
	for (int i = 0; i < Point.Num(); ++i)
	{
		MovementComponent->AddControlPointPosition(Point[i], bPositionIsRelative);
	}

	UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s: ControlPoint = %d"), *FString(__FUNCTION__), MovementComponent->ControlPoints.Num());
	MovementComponent->RestartMovement();
}
