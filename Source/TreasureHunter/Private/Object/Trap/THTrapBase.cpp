// Fill out your copyright notice in the Description page of Project Settings.


#include "THTrapBase.h"
#include "TreasureHunter.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "Engine/World.h"
#include "Character/THCharacterBase.h"
#include "..\..\..\Public\Object\Trap\THTrapBase.h"

ATHTrapBase::ATHTrapBase() : ATHActorBase()
{
	bTrapActive = true;
	SetReplicateMovement(true);
	SetReplicatingMovement(true);
	SetReplicates(true);
	Area->OnComponentBeginOverlap.AddDynamic(this, &ATHTrapBase::OnCharacterBeginOverlap);
	Area->OnComponentEndOverlap.AddDynamic(this, &ATHTrapBase::OnCharacterEndOverlap);
}

void ATHTrapBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHTrapBase, bTrapActive);
	DOREPLIFETIME(ATHTrapBase, ActivateLimit);
	DOREPLIFETIME(ATHTrapBase, InRangePlayers);
	DOREPLIFETIME(ATHTrapBase, ExperiencedParty);
}

void ATHTrapBase::ServerAddCharacterToInRangeQueue_Implementation(ATHCharacterBase* input)
{
	MulticastAddCharacterToInRangeQueue(input);
}

bool ATHTrapBase::ServerAddCharacterToInRangeQueue_Validate(ATHCharacterBase* input)
{
	return true;
}

void ATHTrapBase::MulticastAddCharacterToInRangeQueue_Implementation(ATHCharacterBase* input)
{
	InRangePlayers.AddUnique(input);
}

void ATHTrapBase::ServerRemoveCharacterFromInRangeQueue_Implementation(ATHCharacterBase* input)
{
	MulticastRemoveCharacterFromInRangeQueue(input);
}

bool ATHTrapBase::ServerRemoveCharacterFromInRangeQueue_Validate(ATHCharacterBase* input)
{
	return true;
}

void ATHTrapBase::MulticastRemoveCharacterFromInRangeQueue_Implementation(ATHCharacterBase* input)
{
	if (InRangePlayers.Contains(input))
	{
		InRangePlayers.Remove(input);
	}
}

void ATHTrapBase::ServerSaveCharacterList_Implementation()
{
	MulticastSaveCharacterList();
}

bool ATHTrapBase::ServerSaveCharacterList_Validate()
{
	return true;
}

void ATHTrapBase::MulticastSaveCharacterList_Implementation()
{
	for (const auto& iter : InRangePlayers)
	{
		ExperiencedParty.AddUnique(iter);
	}
}

void ATHTrapBase::OnCharacterBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(THVerbose, Verbose, TEXT("%s - ActivateLimit: %d"), *FString(__FUNCTION__), ActivateLimit);
	if (bTrapActive && OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			if (!ExperiencedParty.Contains(Character) && !InRangePlayers.Contains(Character))
			{
				if (!ExperiencedParty.Contains(Character))
				{
					//UE_LOG(THVerbose, Verbose, TEXT("%s - NewCharacter"), *FString(__FUNCTION__));
					ServerAddCharacterToInRangeQueue(Character);
				}
				//UE_LOG(THVerbose, Verbose, TEXT("%s - Number of InRangePlayers: %d"), *FString(__FUNCTION__), InRangePlayers.Num());
				if (InRangePlayers.Num() >= ActivateLimit)
				{
					ServerActivateTrap();
					//UE_LOG(THVerbose, Verbose, TEXT("%s - Trap Activated"), *FString(__FUNCTION__));
					ServerSaveCharacterList();
				}
				//UE_LOG(THVerbose, Verbose, TEXT("%s - Number of ExperiencedPlayer: %d"), *FString(__FUNCTION__), ExperiencedParty.Num());
			}
		}
	}
}

void ATHTrapBase::OnCharacterEndOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bTrapActive && OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			ServerRemoveCharacterFromInRangeQueue(Character);
			//UE_LOG(THVerbose, Verbose, TEXT("%s - Number of InRangePlayers: %d"), *FString(__FUNCTION__), InRangePlayers.Num());
			//UE_LOG(THVerbose, Verbose, TEXT("%s - Number of ExperiencedPlayer: %d"), *FString(__FUNCTION__), ExperiencedParty.Num());
		}
	}
}

void ATHTrapBase::ServerActivateTrap_Implementation()
{
	MulticastActivateTrap();
}

bool ATHTrapBase::ServerActivateTrap_Validate()
{
	return true;
}

void ATHTrapBase::MulticastActivateTrap_Implementation()
{
	ActivateTrap();
}

void ATHTrapBase::ServerInactivateTrap_Implementation()
{
	MulticastInactivateTrap();
}

bool ATHTrapBase::ServerInactivateTrap_Validate()
{
	return true;
}

void ATHTrapBase::MulticastInactivateTrap_Implementation()
{
	InactivateTrap();
}
