// Fill out your copyright notice in the Description page of Project Settings.


#include "THPieceBase.h"
#include "Engine.h"
#include "THCharacterBase.h"
#include "TreasureHunter.h"
#include "net/UnrealNetwork.h"

ATHPieceBase::ATHPieceBase() : ATHActorBase()
{
}

void ATHPieceBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHPieceBase::InitializeIndex(int32 index)
{
	Index = index;
}

int32 ATHPieceBase::GetIndex()
{
	return Index;
}

void ATHPieceBase::ActivateKey()
{
	Object->SetVisibility(true);
	Object->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ATHPieceBase::DeactivateKey()
{
	Object->SetVisibility(false);
	Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATHPieceBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHPieceBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHPieceBase, Index);
}