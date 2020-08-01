// Fill out your copyright notice in the Description page of Project Settings.


#include "THAttachPieceBase.h"
#include "Interface/AttachActivity.h"
#include "Object/THActorBase.h"
#include "..\..\..\Public\Object\Piece\THAttachPieceBase.h"

ATHAttachPieceBase::ATHAttachPieceBase() : ATHPieceBase()
{

}

void ATHAttachPieceBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHAttachPieceBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHAttachPieceBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

bool ATHAttachPieceBase::IsAttachable(const IAttachActivity* Attacher)
{
	return (GetAttachParentActor() == nullptr) || (Cast<IAttachActivity>(GetAttachParentActor()) == Attacher);
}
