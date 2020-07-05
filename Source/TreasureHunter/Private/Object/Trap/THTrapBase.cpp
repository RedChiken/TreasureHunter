// Fill out your copyright notice in the Description page of Project Settings.


#include "THTrapBase.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "Engine/World.h"

ATHTrapBase::ATHTrapBase() : ATHActorBase()
{
	bInArea = false;
	bInactive = false;
	Area->OnComponentBeginOverlap.AddDynamic(this, &ATHTrapBase::OnCharacterInRange);
}

void ATHTrapBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHTrapBase, bInArea);
	DOREPLIFETIME(ATHTrapBase, bInactive);
}

void ATHTrapBase::ServerUpdatebInactive_Implementation(bool Inactive)
{
	MulticastUpdatebInactive(Inactive);
}

bool ATHTrapBase::ServerUpdatebInactive_Validate(bool Inactive)
{
	return true;
}

void ATHTrapBase::MulticastUpdatebInactive_Implementation(bool Inactive)
{
	bInactive = Inactive;
}

void ATHTrapBase::ServerUpdatebInArea_Implementation(bool inArea)
{
	MulticastUpdatebInArea(inArea);
}

bool ATHTrapBase::ServerUpdatebInArea_Validate(bool inArea)
{
	return true;
}

void ATHTrapBase::MulticastUpdatebInArea_Implementation(bool inArea)
{
	bInArea = inArea;
}
