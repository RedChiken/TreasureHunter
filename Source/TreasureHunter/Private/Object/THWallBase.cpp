// Fill out your copyright notice in the Description page of Project Settings.


#include "THWallBase.h"
#include "TreasureHunter.h"
#include "Kismet/GameplayStatics.h"
#include "net/UnrealNetwork.h"
#include "Engine.h"

ATHWallBase::ATHWallBase() : ATHClimbBase()
{
	MovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("InterpolationMovement"));
	IdleType = EIdleType::WALL;
	SetReplicateMovement(true);
	SetReplicatingMovement(true);
	SetReplicates(true);
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
	DOREPLIFETIME(ATHWallBase, ActivateDirection);
	DOREPLIFETIME(ATHWallBase, InactivateDirection);
}

void ATHWallBase::ActivateWall(float duration, bool bPositionIsRelative)
{
	UE_LOG(THVerbose, Verbose, TEXT("%s - ActivateWall Called"), *FString(__FUNCTION__));
	MovementComponent->FinaliseControlPoints();
	MovementComponent->ControlPoints.Empty();
	MovementComponent->ResetControlPoints();
	for (const auto& iter : ActivateDirection)
	{
		MovementComponent->AddControlPointPosition(iter);
	}
	MovementComponent->Duration = duration;
	MovementComponent->RestartMovement();
}

void ATHWallBase::InactivateWall(float duration, bool bPositionIsRelative)
{
	MovementComponent->FinaliseControlPoints();
	MovementComponent->ControlPoints.Empty();
	MovementComponent->ResetControlPoints();
	for (const auto& iter : InactivateDirection)
	{
		MovementComponent->AddControlPointPosition(iter);
	}
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

void ATHWallBase::ServerActivateWall_Implementation(float duration, bool bPositionIsRelative)
{
	UE_LOG(THVerbose, Verbose, TEXT("%s - Server ActivateWall Called"), *FString(__FUNCTION__));
	MulticastActivateWall(duration, bPositionIsRelative);
}

bool ATHWallBase::ServerActivateWall_Validate(float duration, bool bPositionIsRelative)
{
	return true;
}

void ATHWallBase::MulticastActivateWall_Implementation(float duration, bool bPositionIsRelative)
{
	UE_LOG(THVerbose, Verbose, TEXT("%s - Multicast ActivateWall Called"), *FString(__FUNCTION__));
	ActivateWall(duration, bPositionIsRelative);
}

void ATHWallBase::ServerInactivateWall_Implementation(float duration, bool bPositionIsRelative)
{
	MulticastInactivateWall(duration, bPositionIsRelative);
}

bool ATHWallBase::ServerInactivateWall_Validate(float duration, bool bPositionIsRelative)
{
	return true;
}

void ATHWallBase::MulticastInactivateWall_Implementation(float duration, bool bPositionIsRelative)
{
	InactivateWall(duration, bPositionIsRelative);
}

void ATHWallBase::ServerStopWall_Implementation()
{
	MulticastStopWall();
}

bool ATHWallBase::ServerStopWall_Validate()
{
	return true;
}

void ATHWallBase::MulticastStopWall_Implementation()
{
	StopWall();
}

void ATHWallBase::InitializeControlPointDirection(const TArray<FVector>& List)
{
	for (int i = 0; i < List.Num(); ++i)
	{
		ActivateDirection.Add(List[i]);
		InactivateDirection.Add(List[List.Num() - i - 1] * -1);
	}
}
