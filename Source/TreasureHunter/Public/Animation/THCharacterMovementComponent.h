// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "THCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API UTHCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UTHCharacterMovementComponent(const class FObjectInitializer& ObjectInitializer);

	virtual void UpdateFromCompressedFlags(uint8 Flags) override;

	virtual void OnMovementUpdated(float DeltaTime, const FVector& OldLocation, const FVector& OldVelocity) override;

	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;

};
