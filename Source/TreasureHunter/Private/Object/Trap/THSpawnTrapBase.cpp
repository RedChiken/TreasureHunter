// Fill out your copyright notice in the Description page of Project Settings.


#include "THSpawnTrapBase.h"
#include "TreasureHunter.h"
#include "THCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "Engine/World.h"

ATHSpawnTrapBase::ATHSpawnTrapBase() : ATHTrapBase()
{
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

void ATHSpawnTrapBase::ActivateActor(AActor* actor)
{
	UE_LOG(THVerbose, Verbose, TEXT("%s - ActivateActor"), *FString(__FUNCTION__));
	if (actor)
	{
		actor->SetActorTickEnabled(true);
		actor->SetActorEnableCollision(true);	// different with actor by actor
		actor->SetActorHiddenInGame(false);		// different with actor by actor
	}
}

void ATHSpawnTrapBase::InactivateActor(AActor* actor)
{
	UE_LOG(THVerbose, Verbose, TEXT("%s - InactivateActor"), *FString(__FUNCTION__));
	if (actor)
	{
		actor->SetActorTickEnabled(false);
		actor->SetActorEnableCollision(false);	// different with actor by actor
		actor->SetActorHiddenInGame(true);		// different with actor by actor
	}
}

void ATHSpawnTrapBase::ServerActivateAllActor_Implementation()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s - ServerActivateAllActor"), *FString(__FUNCTION__));
	MulticastActivateAllActor();
}

bool ATHSpawnTrapBase::ServerActivateAllActor_Validate()
{
	return true;
}

void ATHSpawnTrapBase::MulticastActivateAllActor_Implementation()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s - MulticastActivateAllActor"), *FString(__FUNCTION__));
	/*for (int i = 0; i < SpawnedActor.Num(); ++i)
	{
		ServerActivateActor(i);
	}*/
	
	for (auto& iter : SpawnedActor)
	{
		ActivateActor(iter);
	}
}

void ATHSpawnTrapBase::ServerActivateActor_Implementation(int index)
{
	MulticastActivateActor(index);
}

bool ATHSpawnTrapBase::ServerActivateActor_Validate(int index)
{
	return true;
}

void ATHSpawnTrapBase::MulticastActivateActor_Implementation(int index)
{
	ActivateActor(SpawnedActor[index]);
}

void ATHSpawnTrapBase::ServerInactivateAllActor_Implementation()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s - ServerInactivateAllActor"), *FString(__FUNCTION__));
	MulticastInactivateAllActor();
}

bool ATHSpawnTrapBase::ServerInactivateAllActor_Validate()
{
	return true;
}

void ATHSpawnTrapBase::MulticastInactivateAllActor_Implementation()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s -MulticastInactivateAllActor"), *FString(__FUNCTION__));
	/*for (int i = 0; i < SpawnedActor.Num(); ++i)
	{
		ServerInactivateActor(i);
	}
	*/
	for (auto& iter : SpawnedActor)
	{
		InactivateActor(iter);
	}
}

void ATHSpawnTrapBase::ServerInactivateActor_Implementation(int index)
{
	MulticastInactivateActor(index);
}

bool ATHSpawnTrapBase::ServerInactivateActor_Validate(int index)
{
	return true;
}

void ATHSpawnTrapBase::MulticastInactivateActor_Implementation(int index)
{
	InactivateActor(SpawnedActor[index]);
}

void ATHSpawnTrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
