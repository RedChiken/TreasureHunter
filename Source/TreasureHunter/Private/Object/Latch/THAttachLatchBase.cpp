// Fill out your copyright notice in the Description page of Project Settings.


#include "THAttachLatchBase.h"
#include "Interface/Attachable.h"
#include "Piece/THAttachPieceBase.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "Kismet/KismetSystemLibrary.h"
#include "..\..\..\Public\Object\Latch\THAttachLatchBase.h"

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

void ATHAttachLatchBase::ServerAttachPiece_Implementation(ATHAttachPieceBase* AttachPiece)
{
	MulticastAttachPiece(AttachPiece);
}

bool ATHAttachLatchBase::ServerAttachPiece_Validate(ATHAttachPieceBase* AttachPiece)
{
	return true;
}

void ATHAttachLatchBase::MulticastAttachPiece_Implementation(ATHAttachPieceBase* AttachPiece)
{
	AttachPiece->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	Piece = AttachPiece;
}

void ATHAttachLatchBase::ServerDetachPiece_Implementation(ATHPieceBase* AttPiece, ATHAttachPieceBase* RetPiece)
{
	MulticastDetachPiece(AttPiece, RetPiece);
}

bool ATHAttachLatchBase::ServerDetachPiece_Validate(ATHPieceBase* AttPiece, ATHAttachPieceBase* RetPiece)
{
	return true;
}

void ATHAttachLatchBase::MulticastDetachPiece_Implementation(ATHPieceBase* AttPiece, ATHAttachPieceBase* RetPiece)
{
	AttPiece->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	RetPiece = Cast<ATHAttachPieceBase>(AttPiece);
	AttPiece = nullptr;
}

bool ATHAttachLatchBase::IsAttachable(IAttachable* attach)
{
	auto attachPiece = Cast<ATHAttachPieceBase>(attach);
	return (Piece != attachPiece) && (Input.Compare(attachPiece->GetID()) != 0);
}

bool ATHAttachLatchBase::IsDetachable()
{
	return Piece && (Input.IsEmpty());
}

void ATHAttachLatchBase::Attach(IAttachable* attach)
{
	auto AttachPiece = Cast<ATHAttachPieceBase>(attach);
	if (bActive && IsAttachable(attach))
	{
		ServerAttachPiece(AttachPiece);
		Submit(AttachPiece->GetID());
	}
}

IAttachable* ATHAttachLatchBase::Detach()
{
	ATHAttachPieceBase* ret = nullptr;
	if (bActive && IsDetachable())
	{
		ServerDetachPiece(Piece, ret);
		ResetInput();
	}
	return ret;
}
