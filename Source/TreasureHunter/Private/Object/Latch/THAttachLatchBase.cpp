// Fill out your copyright notice in the Description page of Project Settings.


#include "THAttachLatchBase.h"
#include "Interface/Attachable.h"
#include "Piece/THAttachPieceBase.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
#include "net/UnrealNetwork.h"
#include "Kismet/KismetSystemLibrary.h"

ATHAttachLatchBase::ATHAttachLatchBase() : ATHLatchBase(), Piece(nullptr)
{

}

void ATHAttachLatchBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHAttachLatchBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHAttachLatchBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHAttachLatchBase, Piece);
	DOREPLIFETIME(ATHAttachLatchBase, AttachedPosition);
}

bool ATHAttachLatchBase::IsAttachable(IAttachable* attach)
{
	auto attachPiece = Cast<ATHAttachPieceBase>(attach);
	return (Piece == nullptr) || ((Piece != nullptr) && !(attachPiece->GetID().Equals(Piece->GetID())));
}

bool ATHAttachLatchBase::IsDetachable()
{
	return (Piece != nullptr);
}

void ATHAttachLatchBase::Attach(IAttachable* attach)
{
	auto AttachPiece = Cast<ATHAttachPieceBase>(attach);
	if (bActive && IsAttachable(attach))
	{
		AttachPiece->Attach(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		//Set Transform
		Submit(AttachPiece->GetID());
	}
}

IAttachable* ATHAttachLatchBase::Detach()
{
	ATHAttachPieceBase* ret = nullptr;
	if (bActive && IsDetachable())
	{
		Piece->Detach(FDetachmentTransformRules::KeepRelativeTransform);
		ret = Piece;
		Piece = nullptr;
		//Set Transform
		ResetInput();
	}
	return ret;
}
