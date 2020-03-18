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
	bInArea = false;
	Area->OnComponentBeginOverlap.AddDynamic(this, &ATHBlockTrapBase::OnCharacterInRange);
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
	DOREPLIFETIME(ATHBlockTrapBase, ActivatedLocation);
	DOREPLIFETIME(ATHBlockTrapBase, DeactivatedLocation);
	DOREPLIFETIME(ATHBlockTrapBase, bInArea);
}

void ATHBlockTrapBase::ActivateAllWall(float DeltaTime)
{
	for (int i = 0; i < WallList.Num(); i++)
	{
		if (IsWallNearTheEnd(i, ActivatedLocation))
		{
			nowLocation = WallList[i]->GetRelativeLocation();
			nowLocation += (ActivatedLocation[i] - nowLocation) * DeltaTime;
			WallList[i]->SetRelativeLocation(nowLocation);
		}
	}
}

void ATHBlockTrapBase::DeactivateAllWall(float DeltaTime)
{
	for (int i = 0; i < WallList.Num(); i++)
	{
		if (IsWallNearTheEnd(i, DeactivatedLocation))
		{
			nowLocation = WallList[i]->GetRelativeLocation();
			nowLocation += (DeactivatedLocation[i] - nowLocation) * DeltaTime;
			WallList[i]->SetRelativeLocation(nowLocation);
		}
	}
}

void ATHBlockTrapBase::ServerUpdatebInArea_Implementation(bool inArea)
{
	MulticastUpdatebInArea(inArea);
}

bool ATHBlockTrapBase::ServerUpdatebInArea_Validate(bool inArea)
{
	return true;
}

void ATHBlockTrapBase::MulticastUpdatebInArea_Implementation(bool inArea)
{
	bInArea = inArea;
}
