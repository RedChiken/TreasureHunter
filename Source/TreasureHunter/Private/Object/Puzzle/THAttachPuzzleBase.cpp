// Fill out your copyright notice in the Description page of Project Settings.


#include "THAttachPuzzleBase.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "THCharacterBase.h"

ATHAttachPuzzleBase::ATHAttachPuzzleBase() : ATHPuzzleBase()
{

}

void ATHAttachPuzzleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHAttachPuzzleBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHAttachPuzzleBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHAttachPuzzleBase, LatchList);
}

void ATHAttachPuzzleBase::OnCharacterNearKey(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			OverlappedComp->GetOwner()->AttachToComponent(Character->GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale ,TEXT("socket_melee_l"));
		}
	}
}
