// Fill out your copyright notice in the Description page of Project Settings.


#include "THInteractionExample.h"
#include "THCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"

ATHInteractionExample::ATHInteractionExample() : ATHActorBase()
{
	AreaSize = FVector(125.0f, 125.0f, 100.0f);
	AreaLocation = FVector(0.f, 0.f, 100.0f);
	SetRangeLocation(AreaLocation);
	SetRangeSize(AreaSize);
	InteractionRange->OnComponentBeginOverlap.AddDynamic(this, &ATHInteractionExample::OnCharacterNearbyObject);
	InteractionRange->OnComponentEndOverlap.AddDynamic(this, &ATHInteractionExample::OnCharacterOutofObject);
}

void ATHInteractionExample::OnCharacterNearbyObject(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			Character->UpdatebInInteractionRange(true);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("bInInteractionRange in Character: %s"), Character->getbInInteractionRange() ? TEXT("true") : TEXT("false")));
		}
	}
}

void ATHInteractionExample::OnCharacterOutofObject(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			Character->UpdatebInInteractionRange(false);
			Character->StopInteraction();
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("bInInteractionRange in Character: %s"), Character->getbInInteractionRange() ? TEXT("true") : TEXT("false")));
		}
	}
}