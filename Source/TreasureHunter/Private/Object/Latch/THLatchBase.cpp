// Fill out your copyright notice in the Description page of Project Settings.


#include "THLatchBase.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "THCharacterBase.h"
#include "THPieceBase.h"
#include "TreasureHunter.h"

ATHLatchBase::ATHLatchBase() : ATHActorBase()
{
	Object->SetCollisionProfileName("BlockAll");
}

void ATHLatchBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHLatchBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHLatchBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

bool ATHLatchBase::IsCorrect()
{
	return false;
}
