// Fill out your copyright notice in the Description page of Project Settings.

#include "TreasureHunter.h"
#include "THAttachPieceBase.h"
#include "Interface/AttachActivity.h"
#include "Object/THActorBase.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
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
	return bActive && (GetAttachParentActor() == nullptr); 
}

void ATHAttachPieceBase::Attach(AActor* Parent, const FAttachmentTransformRules& AttachmentRules, FName SocketName)
{
	AttachToActor(Parent, AttachmentRules, SocketName);
	UE_LOG(THVerbose, Verbose, TEXT("%s AttachToActor Success"), *FString(__FUNCTION__));
	UE_LOG(THVerbose, Verbose, TEXT("%s ParentActor is valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(GetAttachParentActor() != nullptr));
	SetReplicateMovement(false);
}

void ATHAttachPieceBase::Attach(USceneComponent* Parent, const FAttachmentTransformRules& AttachmentRules, FName SocketName)
{
	AttachToComponent(Parent, AttachmentRules, SocketName);
	UE_LOG(THVerbose, Verbose, TEXT("%s AttachToComponent Successs"), *FString(__FUNCTION__));
	//UE_LOG(THVerbose, Verbose, TEXT("%s ParentActor is valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(GetAttachParentActor() != nullptr));
	SetReplicateMovement(false);
}

void ATHAttachPieceBase::Detach(const FDetachmentTransformRules& DetachmentRules)
{
	DetachFromActor(DetachmentRules);
	UE_LOG(THVerbose, Verbose, TEXT("%s DetachFromActor Success"), *FString(__FUNCTION__));
	UE_LOG(THVerbose, Verbose, TEXT("%s ParentActor is valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(GetAttachParentActor() != nullptr));
	SetReplicateMovement(true);
}
