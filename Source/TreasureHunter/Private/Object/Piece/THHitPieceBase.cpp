// Fill out your copyright notice in the Description page of Project Settings.


#include "THHitPieceBase.h"
#include "..\..\..\Public\Object\Piece\THHitPieceBase.h"

ATHHitPieceBase::ATHHitPieceBase() : ATHPieceBase()
{

}

void ATHHitPieceBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHHitPieceBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHHitPieceBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ATHHitPieceBase::ReceiveDamage(const float& damage)
{
}

void ATHHitPieceBase::ReceiveHeal(const float& heal)
{
}
