// Fill out your copyright notice in the Description page of Project Settings.


#include "THLatchBase.h"
#include "Engine.h"
#include "THCharacterBase.h"
#include "THPieceBase.h"
#include "TreasureHunter.h"
#include "net/UnrealNetwork.h"

ATHLatchBase::ATHLatchBase() : ATHActorBase()
{
	Index = -1;
	AttachedPiece = nullptr;
}

void ATHLatchBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHLatchBase::InitializeIndex(int32 index)
{
	Index = index;
}

void ATHLatchBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHLatchBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHLatchBase, Index);
	DOREPLIFETIME(ATHLatchBase, AttachedPiece);
	DOREPLIFETIME(ATHLatchBase, AttachLocation);
}

void ATHLatchBase::SubmitPiece(ATHPieceBase* piece)
{
	AttachedPiece = piece;
	piece->AttachToComponent(Object, FAttachmentTransformRules::SnapToTargetIncludingScale);
	AttachedPiece->SetActorRelativeLocation(AttachLocation);
}

ATHPieceBase* ATHLatchBase::WithdrawPiece()
{
	auto temp = AttachedPiece;
	AttachedPiece->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	return temp;
}

ATHPieceBase* ATHLatchBase::GetPiece()
{
	return AttachedPiece;
}

int32 ATHLatchBase::GetIndex()
{
	return Index;
}

bool ATHLatchBase::IsCorrectPair()
{
	return (AttachedPiece != nullptr) && (AttachedPiece->GetIndex() == Index);
}

void ATHLatchBase::Activate()
{
	Object->SetVisibility(true);
	Object->SetCollisionProfileName("BlockAllDynamic");
	Area->SetCollisionProfileName("Trigger");
}

void ATHLatchBase::Deactivate()
{
	Object->SetVisibility(false);
	Object->SetCollisionProfileName("NoCollision");
	Area->SetCollisionProfileName("NoCollision");
}
