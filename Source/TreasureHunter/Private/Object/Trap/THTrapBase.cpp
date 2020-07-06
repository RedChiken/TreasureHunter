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
	bInArea = false;
	bInactive = false;
	ActivateLimit = 3;
	//Area->OnComponentBeginOverlap.AddDynamic(this, &ATHTrapBase::OnCharacterInRange);
	Area->OnComponentBeginOverlap.AddDynamic(this, &ATHTrapBase::OnCharacterBeginOverlap);
	Area->OnComponentEndOverlap.AddDynamic(this, &ATHTrapBase::OnCharacterEndOverlap);
}

void ATHTrapBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHTrapBase, bInArea);
	DOREPLIFETIME(ATHTrapBase, bInactive);
	DOREPLIFETIME(ATHTrapBase, ActivateLimit);
	DOREPLIFETIME(ATHTrapBase, InRangePlayers);
	DOREPLIFETIME(ATHTrapBase, ExperiencedParty);
}

void ATHTrapBase::ServerUpdatebInactive_Implementation(bool Inactive)
{
	MulticastUpdatebInactive(Inactive);
}

bool ATHTrapBase::ServerUpdatebInactive_Validate(bool Inactive)
{
	return true;
}

void ATHTrapBase::MulticastUpdatebInactive_Implementation(bool Inactive)
{
	bInactive = Inactive;
}

void ATHTrapBase::ServerUpdatebInArea_Implementation(bool inArea)
{
	MulticastUpdatebInArea(inArea);
}

bool ATHTrapBase::ServerUpdatebInArea_Validate(bool inArea)
{
	return true;
}

void ATHTrapBase::MulticastUpdatebInArea_Implementation(bool inArea)
{
	bInArea = inArea;
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
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			//it works to here.
			if (!ExperiencedParty.Contains(Character) && !InRangePlayers.Contains(Character))
			{
				//InRangePlayers.Add(Character);
				if (!ExperiencedParty.Contains(Character))
				{
					ServerAddCharacterToInRangeQueue(Character);
				}
				if (InRangePlayers.Num() >= ActivateLimit)
				{
					ActivateTrap();
					UE_LOG(THVerbose, Verbose, TEXT("%s - Trap Activated"), *FString(__FUNCTION__));
					/*
					for (const auto& iter : InRangePlayers)
					{
						ExperiencedParty.Add(iter);
					}*/
					ServerSaveCharacterList();
				}
				UE_LOG(THVerbose, Verbose, TEXT("%s - Number of InRangePlayers: %d"), *FString(__FUNCTION__), InRangePlayers.Num());
				UE_LOG(THVerbose, Verbose, TEXT("%s - Number of ExperiencedPlayer: %d"), *FString(__FUNCTION__), ExperiencedParty.Num());
			}
		}
	}
}

void ATHTrapBase::OnCharacterEndOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			ServerRemoveCharacterFromInRangeQueue(Character);
			UE_LOG(THVerbose, Verbose, TEXT("%s - Number of InRangePlayers: %d"), *FString(__FUNCTION__), InRangePlayers.Num());
			UE_LOG(THVerbose, Verbose, TEXT("%s - Number of ExperiencedPlayer: %d"), *FString(__FUNCTION__), ExperiencedParty.Num());
			/*
			if (InRangePlayers.Contains(Character))
			{
				InRangePlayers.Remove(Character);
				UE_LOG(THVerbose, Verbose, TEXT("%s - Players out of range: %d"), *FString(__FUNCTION__), InRangePlayers.Num());
			}*/
		}
	}
}
