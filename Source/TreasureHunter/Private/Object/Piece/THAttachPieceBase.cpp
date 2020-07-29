// Fill out your copyright notice in the Description page of Project Settings.


#include "THAttachPieceBase.h"
#include "Interface/AttachActivity.h"

ATHAttachPieceBase::ATHAttachPieceBase() : ATHPieceBase()
{

}

void ATHAttachPieceBase::Tick(float DeltaTime)
{
}

void ATHAttachPieceBase::BeginPlay()
{
}

void ATHAttachPieceBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
}

bool ATHAttachPieceBase::IsAttachable()
{
	return false;
}

bool ATHAttachPieceBase::HasAuthorize(const IAttachActivity* Attacher)
{
	return false;
}
