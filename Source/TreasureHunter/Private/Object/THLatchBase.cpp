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
	Index = -1;
	AttachedPiece = nullptr;
	Object->SetCollisionProfileName("BlockAll");
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
	if (piece)
	{
		AttachedPiece = piece;
		piece->AttachToComponent(Object, FAttachmentTransformRules::KeepRelativeTransform);
		UE_LOG(THVerbose, Verbose, TEXT("%s piece is %s"), *FString(__FUNCTION__), ((piece == nullptr) ? TEXT("InValid!") : TEXT("Valid!")));
		UE_LOG(THVerbose, Verbose, TEXT("%s: Latch Index = %d"), *FString(__FUNCTION__), Index);
		UE_LOG(THVerbose, Verbose, TEXT("%s: Piece Index = %d"), *FString(__FUNCTION__), AttachedPiece->GetIndex());
		UE_LOG(THVerbose, Verbose, TEXT("%s: Correctness = %s"), *FString(__FUNCTION__), (IsCorrectPair() ? TEXT("Correct!") : TEXT("Wrong!")));
		AttachedPiece->SetActorRelativeLocation(AttachLocation);
		piece = AttachedPiece;
	}
	else
	{
		UE_LOG(THVerbose, Verbose, TEXT("%s piece is nullptr"), *FString(__FUNCTION__));
	}
}

ATHPieceBase* ATHLatchBase::WithdrawPiece()
{
	if (AttachedPiece)
	{
		auto temp = AttachedPiece;
		AttachedPiece->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		UE_LOG(THVerbose, Verbose, TEXT("%s temp is %s"), *FString(__FUNCTION__), ((temp == nullptr) ? TEXT("InValid!") : TEXT("Valid!")));
		AttachedPiece = temp;
		AttachedPiece->SetActorRotation(FRotator::ZeroRotator);
	}
	else
	{
		UE_LOG(THVerbose, Verbose, TEXT("%s AttachedPiece is nullptr"), *FString(__FUNCTION__));
	}
	return AttachedPiece;
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
	Object->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ATHLatchBase::Deactivate()
{
	Object->SetVisibility(false);
	Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
