// Fill out your copyright notice in the Description page of Project Settings.


#include "THAttachPieceBase.h"
#include "Interface/AttachActivity.h"
#include "Object/THActorBase.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "Kismet/KismetSystemLibrary.h"
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
	return bActive && ((GetAttachParentActor() == nullptr) || (Cast<IAttachActivity>(GetAttachParentActor()) == Attacher));
}

void ATHAttachPieceBase::Attach(AActor* Parent, const FAttachmentTransformRules& AttachmentRules, FName SocketName)
{
	AttachToActor(Parent, AttachmentRules, SocketName);
	InActivate();
}

void ATHAttachPieceBase::Attach(USceneComponent* Parent, const FAttachmentTransformRules& AttachmentRules, FName SocketName)
{
	AttachToComponent(Parent, AttachmentRules, SocketName);
	InActivate();
}

void ATHAttachPieceBase::Detach(const FDetachmentTransformRules& DetachmentRules)
{
	DetachFromActor(DetachmentRules);
	Activate();
}
