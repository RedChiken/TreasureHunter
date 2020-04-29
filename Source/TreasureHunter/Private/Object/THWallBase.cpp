// Fill out your copyright notice in the Description page of Project Settings.


#include "THWallBase.h"
#include "TreasureHunter.h"
#include "Kismet/GameplayStatics.h"
#include "net/UnrealNetwork.h"
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
	DOREPLIFETIME(ATHWallBase, InitialPosition);
}

void ATHWallBase::ActivateWall(float duration, bool bPositionIsRelative)
{
	MovementComponent->Duration = duration;
	MovementComponent->RestartMovement();
}

void ATHWallBase::StopWall()
{
	MovementComponent->StopMovementImmediately();
}

TArray<FInterpControlPoint> ATHWallBase::ReverseControlPoints(const TArray<FInterpControlPoint>& ControlPoints)
{
	TArray<FInterpControlPoint> Reverse;
	Reverse.Add(ControlPoints[0]);
	int length = ControlPoints.Num();
	for (int i = 0; i < length - 1; ++i)
	{
		auto relativeDestination = ControlPoints[length - i - 1].PositionControlPoint * -1;
		Reverse.Add(FInterpControlPoint(relativeDestination, true));
	}
	return Reverse;
}
