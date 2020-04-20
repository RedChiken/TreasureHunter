// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "THCharacterMovementComponent.h"
#include "UObject/UObjectGlobals.h"
#include "net/UnrealNetwork.h"

UTHCharacterMovementComponent::UTHCharacterMovementComponent(const class FObjectInitializer& ObjectInitializer) : UCharacterMovementComponent(ObjectInitializer)
{
	int i = 0;
}

void UTHCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);
}

void UTHCharacterMovementComponent::OnMovementUpdated(float DeltaTime, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaTime, OldLocation, OldVelocity);
}

void UTHCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);
}
