// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TreasureHunter.h"
#include "THCharacterBase.h"
#include "THCharacterMovementComponent.h"
#include "UObject/UObjectGlobals.h"
#include "net/UnrealNetwork.h"

UTHCharacterMovementComponent::UTHCharacterMovementComponent(const class FObjectInitializer& ObjectInitializer) : UCharacterMovementComponent(ObjectInitializer)
{
}

void UTHCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);
}

void UTHCharacterMovementComponent::OnMovementUpdated(float DeltaTime, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaTime, OldLocation, OldVelocity);
	auto character = Cast<ATHCharacterBase>(CharacterOwner);
	if (character)
	{
		character->OnMovementStop();
		//UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementMode));
	}
}

void UTHCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);
	UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementMode));
}
