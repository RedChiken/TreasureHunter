// Fill out your copyright notice in the Description page of Project Settings.


#include "THSpawnTrapBase.h"
#include "THCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "Engine/World.h"

ATHSpawnTrapBase::ATHSpawnTrapBase() : ATHActorBase()
{
	Area->OnComponentBeginOverlap.AddDynamic(this, &ATHSpawnTrapBase::OnCharacterInRange);
}

void ATHSpawnTrapBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHSpawnTrapBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHSpawnTrapBase, SpawnedActor);
}

void ATHSpawnTrapBase::ActivateActor(int index)
{
	auto actor = SpawnedActor[index];
	actor->SetActorHiddenInGame(false);
	actor->SetActorEnableCollision(true);
	actor->SetActorTickEnabled(true);
}

void ATHSpawnTrapBase::ActivateAllActor()
{
	for (int i = 0; i < SpawnedActor.Num(); ++i)
	{
		ActivateActor(i);
	}
}

void ATHSpawnTrapBase::DeactivateActor(int index)
{
	auto actor = SpawnedActor[index];
	actor->SetActorHiddenInGame(true);
	actor->SetActorEnableCollision(false);
	actor->SetActorTickEnabled(false);
}

void ATHSpawnTrapBase::DeactivateAllActor()
{
	for (int i = 0; i < SpawnedActor.Num(); ++i)
	{
		DeactivateActor(i);
	}
}

void ATHSpawnTrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
