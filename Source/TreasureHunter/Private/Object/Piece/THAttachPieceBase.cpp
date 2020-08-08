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

void ATHAttachPieceBase::ServerEnableCollision_Implementation()
{
	MulticastEnableCollision();
}

bool ATHAttachPieceBase::ServerEnableCollision_Validate()
{
	return true;
}

void ATHAttachPieceBase::MulticastEnableCollision_Implementation()
{
	//Object->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetActorEnableCollision(true);
}

void ATHAttachPieceBase::ServerDisableCollision_Implementation()
{
	MulticastDisableCollision();
}

bool ATHAttachPieceBase::ServerDisableCollision_Validate()
{
	return true;
}

void ATHAttachPieceBase::MulticastDisableCollision_Implementation()
{
	//Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorEnableCollision(false);
}

void ATHAttachPieceBase::ServerVisualize_Implementation()
{
	MulticastVisualize();
}

bool ATHAttachPieceBase::ServerVisualize_Validate()
{
	return true;
}

void ATHAttachPieceBase::MulticastVisualize_Implementation()
{
	Object->SetVisibility(true);
}

void ATHAttachPieceBase::ServerInvisualize_Implementation()
{
	MulticastInvisualize();
}

bool ATHAttachPieceBase::ServerInvisualize_Validate()
{
	return true;
}

void ATHAttachPieceBase::MulticastInvisualize_Implementation()
{
	Object->SetVisibility(true);
}

bool ATHAttachPieceBase::IsAttachable(const IAttachActivity* Attacher)
{
	return bActive && (GetAttachParentActor() == nullptr); 
}

void ATHAttachPieceBase::Attach(AActor* Parent, const FAttachmentTransformRules& AttachmentRules, FName SocketName)
{
	UE_LOG(THVerbose, Verbose, TEXT("%s Parent Input is valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(Parent != nullptr));
	DisableCollision();
	AttachToActor(Parent, AttachmentRules, SocketName);
	UE_LOG(THVerbose, Verbose, TEXT("%s AttachToActor Success"), *FString(__FUNCTION__));
	UE_LOG(THVerbose, Verbose, TEXT("%s ParentActor is valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(GetAttachParentActor() != nullptr));
	SetReplicateMovement(false);
	bActive = false;
	UE_LOG(THVerbose, Verbose, TEXT("%s Attached Piece ID: %s"), *FString(__FUNCTION__), *GetID());
}

void ATHAttachPieceBase::Attach(USceneComponent* Parent, const FAttachmentTransformRules& AttachmentRules, FName SocketName)
{
	UE_LOG(THVerbose, Verbose, TEXT("%s Parent Input is valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(Parent != nullptr));
	DisableCollision();
	SetReplicateMovement(false);
	bActive = false;
	AttachToComponent(Parent, AttachmentRules, SocketName);
	UE_LOG(THVerbose, Verbose, TEXT("%s AttachToComponent Successs"), *FString(__FUNCTION__));
	UE_LOG(THVerbose, Verbose, TEXT("%s ParentActor is valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(GetAttachParentActor() != nullptr));
	UE_LOG(THVerbose, Verbose, TEXT("%s Attached Piece ID: %s"), *FString(__FUNCTION__), *GetID());
}

void ATHAttachPieceBase::Detach(const FDetachmentTransformRules& DetachmentRules)
{
	SetReplicateMovement(true);
	bActive = true;
	DetachFromActor(DetachmentRules);
	UE_LOG(THVerbose, Verbose, TEXT("%s DetachFromActor Success"), *FString(__FUNCTION__));
	UE_LOG(THVerbose, Verbose, TEXT("%s ParentActor is valid: %s"), *FString(__FUNCTION__), GETBOOLSTRING(GetAttachParentActor() != nullptr));
	UE_LOG(THVerbose, Verbose, TEXT("%s Detached Piece ID: %s"), *FString(__FUNCTION__), *GetID());
}

void ATHAttachPieceBase::Visualize()
{
	ServerVisualize();
}

void ATHAttachPieceBase::Invisualize()
{
	ServerInvisualize();
}

void ATHAttachPieceBase::EnableCollision()
{
	ServerEnableCollision();
}

void ATHAttachPieceBase::DisableCollision()
{
	ServerDisableCollision();
}
