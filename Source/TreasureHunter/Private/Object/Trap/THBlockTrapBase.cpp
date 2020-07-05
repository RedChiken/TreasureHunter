// Fill out your copyright notice in the Description page of Project Settings.


#include "THBlockTrapBase.h"
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

void ATHBlockTrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
