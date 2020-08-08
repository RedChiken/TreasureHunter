// Fill out your copyright notice in the Description page of Project Settings.

#include "THAttachLatchBase.h"
#include "TreasureHunter.h"
#include "Interface/Attachable.h"
#include "Piece/THAttachPieceBase.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
#include "net/UnrealNetwork.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

ATHAttachLatchBase::ATHAttachLatchBase() : ATHLatchBase(), Piece(nullptr)
{
	bActive = true;
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

void ATHAttachLatchBase::ServerUpdatePiece_Implementation(ATHAttachPieceBase* InputPiece)
{
	MulticastUpdatePiece(InputPiece);
}

bool ATHAttachLatchBase::ServerUpdatePiece_Validate(ATHAttachPieceBase* InputPiece)
{
	return true;
}

void ATHAttachLatchBase::MulticastUpdatePiece_Implementation(ATHAttachPieceBase* InputPiece)
{
	Piece = InputPiece;
}

bool ATHAttachLatchBase::IsAttachable(IAttachable* attach)
{
	return (attach != nullptr);
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
		UE_LOG(THVerbose, Verbose, TEXT("%s Attach bActive and isAttachable"), *FString(__FUNCTION__));
		FAttachmentTransformRules AttachmentRule(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
		AttachPiece->Attach(Object, AttachmentRule);
		AttachPiece->SetActorRelativeLocation(GetActorUpVector() * 75.f);
		UE_LOG(THVerbose, Verbose, TEXT("%s Attach Done"), *FString(__FUNCTION__));
		//Set Transform
		Submit(AttachPiece->GetID());
		MulticastUpdatePiece(AttachPiece);
		UE_LOG(THVerbose, Verbose, TEXT("%s Compare ID of Piece and AttachPiece: %s"), *FString(__FUNCTION__), GETBOOLSTRING(Piece->GetID() == AttachPiece->GetID()));
	}
	UE_LOG(THVerbose, Verbose, TEXT("%s AttachPiece is Valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(AttachPiece != nullptr));
	UE_LOG(THVerbose, Verbose, TEXT("%s Piece is Valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(Piece != nullptr));
	UE_LOG(THVerbose, Verbose, TEXT("%s Compare Piece and AttachPiece: %s"), *FString(__FUNCTION__), GETBOOLSTRING(Piece == AttachPiece));
}

IAttachable* ATHAttachLatchBase::Detach()
{
	ATHAttachPieceBase* ret = nullptr;
	if (bActive && IsDetachable())
	{
		FDetachmentTransformRules DetachRule(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, false);
		Piece->Detach(DetachRule);
		ret = Piece;
		MulticastUpdatePiece(nullptr);
		//Set Transform
		ResetInput();
	}
	UE_LOG(THVerbose, Verbose, TEXT("%s ret is Valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(ret != nullptr));
	UE_LOG(THVerbose, Verbose, TEXT("%s Piece is Valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(Piece != nullptr));
	return ret;
}
