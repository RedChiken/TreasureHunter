// Fill out your copyright notice in the Description page of Project Settings.


#include "THAttachPieceBase.h"
#include "Interface/AttachActivity.h"
#include "Object/THActorBase.h"

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

bool ATHAttachPieceBase::IsAttachable()
{
	return GetAttachParentActor() == nullptr;
}

bool ATHAttachPieceBase::HasAuthorize(const IAttachActivity* Attacher)
{
	return (Cast<IAttachActivity>(GetAttachParentActor()) == Attacher);
}
