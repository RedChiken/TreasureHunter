// Fill out your copyright notice in the Description page of Project Settings.


#include "THInRangeExample.h"
#include "THCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"

ATHInRangeExample::ATHInRangeExample() : ATHActorBase()
{
	Area->OnComponentBeginOverlap.AddDynamic(this, &ATHInRangeExample::OnCharacterInRange);
}

void ATHInRangeExample::OnCharacterInRange(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Character gets in to the Interaction Area"));
		}
	}
}