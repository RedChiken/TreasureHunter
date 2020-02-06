// Fill out your copyright notice in the Description page of Project Settings.


#include "THInteractionTriggerBase.h"
#include "THInRangeTriggerBase.h"
#include "THCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"

ATHInteractionTriggerBase::ATHInteractionTriggerBase() : ATHTriggerBase()
{
	Width = 150.0f;
	Depth = 150.0f;
	Height = 150.0f;
	Area->SetBoxExtent(FVector(Width, Depth, Height));
	Area->OnComponentBeginOverlap.AddDynamic(this, &ATHInteractionTriggerBase::OnCharacterNearbyObject);
	Area->OnComponentEndOverlap.AddDynamic(this, &ATHInteractionTriggerBase::OnCharacterOutofObject);
}

void ATHInteractionTriggerBase::OnCharacterNearbyObject(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Something Overlapped with Interaction Trigger"));
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			Character->setbInInteractionRange(true);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("bInInteractionRange in Character: %s"), Character->getbInInteractionRange() ? TEXT("true") : TEXT("false")));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("overlapped Actor is not ATHCharacterBase"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("No Collision"));
	}
}

void ATHInteractionTriggerBase::OnCharacterOutofObject(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Something Out of Range"));
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			Character->setbInInteractionRange(false);
			Character->StopInteraction();
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("bInInteractionRange in Character: %s"), Character->getbInInteractionRange() ? TEXT("true") : TEXT("false")));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("overlapped Actor is not ATHCharacterBase"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("No Collision"));
	}
}
