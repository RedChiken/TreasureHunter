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
	UE_LOG(THVerbose, Verbose, TEXT("%s attach is Valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(attach != nullptr));
	UE_LOG(THVerbose, Verbose, TEXT("%s attach is Attachable: %s"), *FString(__FUNCTION__), GETBOOLSTRING(IsAttachable(attach)));
	auto AttachPiece = Cast<ATHAttachPieceBase>(attach);
	if (bActive && IsAttachable(attach))
	{
		UE_LOG(THVerbose, Verbose, TEXT("%s Attach bActive and isAttachable"), *FString(__FUNCTION__));
		UE_LOG(THVerbose, Verbose, TEXT("%s AttachPiece is Valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(AttachPiece != nullptr));
		FAttachmentTransformRules AttachmentRule(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
		AttachPiece->Attach(Object, AttachmentRule);
		AttachPiece->SetActorRelativeLocation(GetActorLocation() + GetActorUpVector() * 300.f);
		UE_LOG(THVerbose, Verbose, TEXT("%s Attach Done"), *FString(__FUNCTION__));
		//Set Transform
		Submit(AttachPiece->GetID());
		UE_LOG(THVerbose, Verbose, TEXT("%s Submit Done"), *FString(__FUNCTION__));
	}
}

IAttachable* ATHAttachLatchBase::Detach()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s attach is Detachable: %s"), *FString(__FUNCTION__), GETBOOLSTRING(IsDetachable()));
	ATHAttachPieceBase* ret = nullptr;
	if (bActive && IsDetachable())
	{
		FDetachmentTransformRules DetachRule(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, false);
		Piece->Detach(DetachRule);
		ret = Piece;
		Piece = nullptr;
		//Set Transform
		ResetInput();
	}
	UE_LOG(THVerbose, Verbose, TEXT("%s ret is Valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(ret != nullptr));
	UE_LOG(THVerbose, Verbose, TEXT("%s Piece is Valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(Piece != nullptr));
	UE_LOG(THVerbose, Verbose, TEXT("%s Compare ret and Piece: %s"), *FString(__FUNCTION__), GETBOOLSTRING(ret == Piece));
	return ret;
}
