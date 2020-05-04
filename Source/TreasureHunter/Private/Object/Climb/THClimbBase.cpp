// Fill out your copyright notice in the Description page of Project Settings.


#include "THClimbBase.h"
#include "THCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"

ATHClimbBase::ATHClimbBase() : ATHActorBase()
{
}

void ATHClimbBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
