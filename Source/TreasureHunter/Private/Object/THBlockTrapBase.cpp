// Fill out your copyright notice in the Description page of Project Settings.


#include "THBlockTrapBase.h"
#include "THCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "Engine/World.h"

ATHBlockTrapBase::ATHBlockTrapBase() : ATHActorBase()
{
	InArea = false;
	InteractionRange->OnComponentBeginOverlap.AddDynamic(this, &ATHBlockTrapBase::OnCharacterInRange);
}

void ATHBlockTrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHBlockTrapBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHBlockTrapBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHBlockTrapBase, WallList);
	DOREPLIFETIME(ATHBlockTrapBase, DestinationList);
	DOREPLIFETIME(ATHBlockTrapBase, InArea);
}

void ATHBlockTrapBase::MoveAllWall(float DeltaTime)
{
	for (int i = 0; i < WallList.Num(); i++)
	{
		if (IsWallNearTheEnd(i))
		{
			nowLocation = WallList[i]->GetRelativeLocation();
			nowLocation += DestinationList[i] * DeltaTime;
			WallList[i]->SetRelativeLocation(nowLocation);
		}
	}
}

void ATHBlockTrapBase::ServerUpdateInArea_Implementation(bool area)
{
	MulticastUpdateInArea(area);
}

bool ATHBlockTrapBase::ServerUpdateInArea_Validate(bool area)
{
	return true;
}

void ATHBlockTrapBase::MulticastUpdateInArea_Implementation(bool area)
{
	InArea = area;
}

void ATHBlockTrapBase::OnCharacterInRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			ServerUpdateInArea(true);
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("InArea : %s"), InArea ? TEXT("true") : TEXT("false")));
		}
	}
}
