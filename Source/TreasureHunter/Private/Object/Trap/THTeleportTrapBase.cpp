// Fill out your copyright notice in the Description page of Project Settings.

#include "THTeleportTrapBase.h"
#include "THCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "Engine/World.h"

ATHTeleportTrapBase::ATHTeleportTrapBase() : ATHActorBase()
{
	bActive = true;
	Area->OnComponentBeginOverlap.AddDynamic(this, &ATHTeleportTrapBase::OnCharacterInRange);
}

void ATHTeleportTrapBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHTeleportTrapBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHTeleportTrapBase, Pair);
}
