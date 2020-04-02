// Fill out your copyright notice in the Description page of Project Settings.


#include "ThAttachPuzzleBase.h"
#include "THLatchBase.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "THCharacterBase.h"

AThAttachPuzzleBase::AThAttachPuzzleBase() : ATHPuzzleBase()
{

}

void AThAttachPuzzleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AThAttachPuzzleBase::BeginPlay()
{
	Super::BeginPlay();
}

void AThAttachPuzzleBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AThAttachPuzzleBase, LatchList);
}

bool AThAttachPuzzleBase::CheckInput()
{
	bool ret = (Input.Num() == Answer.Num());
	if (ret)
	{
		for (int index = 0; ret && (index < LatchList.Num()); ++index)
		{
			ret = Cast<ATHLatchBase>(LatchList[index]->GetChildActor())->IsCorrectPair();
		}
	}
	return ret;
}

void AThAttachPuzzleBase::OnCharacterNearKey(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void AThAttachPuzzleBase::ActivateAllLatch()
{
	for (int i = 0; i < LatchList.Num(); ++i)
	{
		Cast<ATHLatchBase>(LatchList[i]->GetChildActor())->Activate();
	}
}

void AThAttachPuzzleBase::DeactivateAllLatch()
{
	for (int i = 0; i < LatchList.Num(); ++i)
	{
		Cast<ATHLatchBase>(LatchList[i]->GetChildActor())->Deactivate();
	}
}
