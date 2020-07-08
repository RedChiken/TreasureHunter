// Fill out your copyright notice in the Description page of Project Settings.


#include "THBlockTrapBase.h"
#include "TreasureHunter.h"
#include "THCharacterBase.h"
#include "THWallBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "Engine/World.h"

ATHBlockTrapBase::ATHBlockTrapBase() : ATHTrapBase()
{
}

void ATHBlockTrapBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHBlockTrapBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHBlockTrapBase, InterpWallList);
	DOREPLIFETIME(ATHBlockTrapBase, ActivatingDirection);
	DOREPLIFETIME(ATHBlockTrapBase, DeactivatingDirection);
}

void ATHBlockTrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHBlockTrapBase::ServerActivateAllInterpWall_Implementation(float duration, bool bPositionIsRelative)
{
	UE_LOG(THVerbose, Verbose, TEXT("%s - Server ActivateAllInterpWall Called"), *FString(__FUNCTION__));
	MulticastActivateAllInterpWall(duration, bPositionIsRelative);
}

bool ATHBlockTrapBase::ServerActivateAllInterpWall_Validate(float duration, bool bPositionIsRelative)
{
	return true;
}

void ATHBlockTrapBase::MulticastActivateAllInterpWall_Implementation(float duration, bool bPositionIsRelative)
{
	UE_LOG(THVerbose, Verbose, TEXT("%s - Multicast ActivateAllInterpWall Called"), *FString(__FUNCTION__));
	for (const auto& iter : InterpWallList)
	{
		iter->ServerActivateWall(duration, bPositionIsRelative);
	}
}

void ATHBlockTrapBase::ServerInactivateAllInterpWall_Implementation(float duration, bool bPositionIsRelative)
{
	MulticastInactivateAllInterpWall(duration, bPositionIsRelative);
}

bool ATHBlockTrapBase::ServerInactivateAllInterpWall_Validate(float duration, bool bPositionIsRelative)
{
	return true;
}

void ATHBlockTrapBase::MulticastInactivateAllInterpWall_Implementation(float duration, bool bPositionIsRelative)
{
	for (const auto& iter : InterpWallList)
	{
		iter->ServerInactivateWall(duration, bPositionIsRelative);
	}
}

void ATHBlockTrapBase::ServerStopAllInterpWall_Implementation()
{
	MulticastStopAllInterpWall();
}

bool ATHBlockTrapBase::ServerStopAllInterpWall_Validate()
{
	return true;
}

void ATHBlockTrapBase::MulticastStopAllInterpWall_Implementation()
{
	for (const auto& iter : InterpWallList)
	{
		iter->ServerStopWall();
	}
}
