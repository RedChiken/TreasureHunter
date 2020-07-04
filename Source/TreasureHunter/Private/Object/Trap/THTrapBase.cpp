// Fill out your copyright notice in the Description page of Project Settings.


#include "THTrapBase.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "Engine/World.h"

ATHTrapBase::ATHTrapBase()
{

}

void ATHTrapBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHTrapBase, bInArea);
	DOREPLIFETIME(ATHTrapBase, bInactive);
}
