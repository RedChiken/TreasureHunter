// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../DataType/THIdleType.h"
#include "../DataType/THMovementType.h"
#include "../DataType/THMovingDirection.h"
#include "LocomotionSync.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULocomotionSync : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TREASUREHUNTER_API ILocomotionSync
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SyncSpeed(float& Speed) = 0;
	virtual void SyncbJump(bool& Jump) = 0;
	virtual void SyncbFalling(bool& Falling) = 0;
	virtual void SyncStandToSparint(bool& STS) = 0;
	virtual void SyncIdleType(EIdleType& Idle) = 0;
	virtual void SyncMovementType(EMovementType& Movement) = 0;
	virtual void SyncMovingDirection(EMovingDirection& Moving) = 0;
};
