// Fill out your copyright notice in the Description page of Project Settings.


#include "THInRangeTriggerBase.h"
#include "THCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"

ATHInRangeTriggerBase::ATHInRangeTriggerBase() : ATHTriggerBase()
{
	Area->OnComponentBeginOverlap.AddDynamic(this, &ATHInRangeTriggerBase::OnCharacterInRange);
}

void ATHInRangeTriggerBase::OnCharacterInRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Something Get In Range"));
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Character gets in to the Interaction Area"));
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
