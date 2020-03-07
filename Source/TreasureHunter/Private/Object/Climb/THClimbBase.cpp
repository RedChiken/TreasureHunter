// Fill out your copyright notice in the Description page of Project Settings.


#include "THClimbBase.h"
#include "THCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"

ATHClimbBase::ATHClimbBase() : ATHActorBase()
{
	UpsideArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Upside"));
	DownsideArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Downside"));
	UpsideArea->SetupAttachment(RootComponent);
	DownsideArea->SetupAttachment(RootComponent);
	UpsideArea->SetBoxExtent(FVector(120.0f, 120.0f, 30.0f));
	DownsideArea->SetBoxExtent(FVector(120.0f, 120.0f, 30.0f));
	UpsideArea->SetCollisionProfileName("Trigger");
	DownsideArea->SetCollisionProfileName("Trigger");
	UpsideArea->OnComponentBeginOverlap.AddDynamic(this, &ATHClimbBase::OnClimbAtTop);
	UpsideArea->OnComponentEndOverlap.AddDynamic(this, &ATHClimbBase::OnCharacterOutofClimbArea);
	DownsideArea->OnComponentBeginOverlap.AddDynamic(this, &ATHClimbBase::OnClimbAtBottom);
	DownsideArea->OnComponentEndOverlap.AddDynamic(this, &ATHClimbBase::OnCharacterOutofClimbArea);
	Area->OnComponentBeginOverlap.AddDynamic(this, &ATHClimbBase::OnClimbAtMiddle);
	Area->OnComponentEndOverlap.AddDynamic(this, &ATHClimbBase::OnCharacterOutofClimbArea);
	type = EIdleType::DEFAULT;
}

void ATHClimbBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ATHClimbBase::OnClimbAtTop(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			if (Character->getbClimbing())
			{
				ExitClimb(Character, EExitDirection::TOP);
			}
			else
			{
				EnterClimb(Character, EEnterDirection::TOP);
			}
		}
	}
}

void ATHClimbBase::OnClimbAtBottom(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			if (Character->getbClimbing())
			{
				ExitClimb(Character, EExitDirection::BOTTOM);
			}
			else
			{
				EnterClimb(Character, EEnterDirection::BOTTOM);
			}
		}
	}
}

void ATHClimbBase::OnClimbAtMiddle(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			if (Character->getbClimbing())
			{
				Character->UpdateExitDirection(EExitDirection::MIDDLE);
			}
			else
			{
				EnterClimb(Character, EEnterDirection::TOP);
			}
		}
	}
}

void ATHClimbBase::OnCharacterOutofClimbArea(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			if (Character->getEnterDirection() == EEnterDirection::DEFAULT)
			{
				Character->GetOutofClimbArea();
			}
		}
	}
}

void ATHClimbBase::ExitClimb(ATHCharacterBase* Character, EExitDirection Exit)
{
	Character->ExitFromClimb(Exit);
}

void ATHClimbBase::EnterClimb(ATHCharacterBase* Character, EEnterDirection Enter)
{
	Character->EnterToClimb(Enter, type);
}
