// Fill out your copyright notice in the Description page of Project Settings.


#include "THInterpToObstacleBase.h"
#include "TreasureHunter.h"
#include "Components/InterpToMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "net/UnrealNetwork.h"
#include "Engine.h"

ATHInterpToObstacleBase::ATHInterpToObstacleBase() : ATHActorBase()
{
	MovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("InterpolationMovement"));
	SetReplicateMovement(true);
	SetReplicatingMovement(true);
	SetReplicates(true);
}

void ATHInterpToObstacleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHInterpToObstacleBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHInterpToObstacleBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHInterpToObstacleBase, MovementComponent);
	DOREPLIFETIME(ATHInterpToObstacleBase, ActivateDirection);
	DOREPLIFETIME(ATHInterpToObstacleBase, InactivateDirection);
}

void ATHInterpToObstacleBase::ActivateWall(float duration, bool bPositionIsRelative)
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

void ATHInterpToObstacleBase::InactivateWall(float duration, bool bPositionIsRelative)
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

void ATHInterpToObstacleBase::StopWall()
{
	MovementComponent->StopMovementImmediately();
}

void ATHInterpToObstacleBase::ServerActivateWall_Implementation(float duration, bool bPositionIsRelative)
{
	UE_LOG(THVerbose, Verbose, TEXT("%s - Server ActivateWall Called"), *FString(__FUNCTION__));
	MulticastActivateWall(duration, bPositionIsRelative);
}

bool ATHInterpToObstacleBase::ServerActivateWall_Validate(float duration, bool bPositionIsRelative)
{
	return true;
}

void ATHInterpToObstacleBase::MulticastActivateWall_Implementation(float duration, bool bPositionIsRelative)
{
	UE_LOG(THVerbose, Verbose, TEXT("%s - Multicast ActivateWall Called"), *FString(__FUNCTION__));
	ActivateWall(duration, bPositionIsRelative);
}

void ATHInterpToObstacleBase::ServerInactivateWall_Implementation(float duration, bool bPositionIsRelative)
{
	MulticastInactivateWall(duration, bPositionIsRelative);
}

bool ATHInterpToObstacleBase::ServerInactivateWall_Validate(float duration, bool bPositionIsRelative)
{
	return true;
}

void ATHInterpToObstacleBase::MulticastInactivateWall_Implementation(float duration, bool bPositionIsRelative)
{
	InactivateWall(duration, bPositionIsRelative);
}

void ATHInterpToObstacleBase::ServerStopWall_Implementation()
{
	MulticastStopWall();
}

bool ATHInterpToObstacleBase::ServerStopWall_Validate()
{
	return true;
}

void ATHInterpToObstacleBase::MulticastStopWall_Implementation()
{
	StopWall();
}

void ATHInterpToObstacleBase::InitializeControlPointDirection(const TArray<FVector>& List)
{
	ActivateDirection.Add(List[0]);
	InactivateDirection.Add(List[0]);
	for (int i = 1; i < List.Num(); ++i)
	{
		ActivateDirection.Add(List[i]);
		InactivateDirection.Add(List[List.Num() - i - 1] * -1);
	}
}
