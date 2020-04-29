// Fill out your copyright notice in the Description page of Project Settings.


#include "THBlockTrapBase.h"
#include "THCharacterBase.h"
#include "THWallBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "Engine/World.h"

ATHBlockTrapBase::ATHBlockTrapBase() : ATHActorBase()
{
	bInArea = false;
	bInactive = false;
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
	DOREPLIFETIME(ATHBlockTrapBase, InterpWallList);
	DOREPLIFETIME(ATHBlockTrapBase, ActivatingDirection);
	DOREPLIFETIME(ATHBlockTrapBase, DeactivatingDirection);
	DOREPLIFETIME(ATHBlockTrapBase, bInArea);
	DOREPLIFETIME(ATHBlockTrapBase, bInactive);
}

void ATHBlockTrapBase::ServerUpdatebInactive_Implementation(bool Inactive)
{
	MulticastUpdatebInactive(Inactive);
}

bool ATHBlockTrapBase::ServerUpdatebInactive_Validate(bool Inactive)
{
	return true;
}

void ATHBlockTrapBase::MulticastUpdatebInactive_Implementation(bool Inactive)
{
	bInactive = Inactive;
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
