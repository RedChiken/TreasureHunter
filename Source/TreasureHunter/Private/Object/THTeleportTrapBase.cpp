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

void ATHTeleportTrapBase::OnCharacterInRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			if (bActive)
			{
				ServerUpdatebActive(false);
				Pair->ServerUpdatebActive(false);
				Character->SetActorLocation(Pair->Object->GetRelativeLocation());
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, "Overlap with Area");
			}
		}
	}
}
