// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../DataType/THIdleType.h"
#include "../DataType/THMovementType.h"
#include "../DataType/THMovingDirection.h"
#include "FullBodyMotionSync.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFullBodyMotionSync : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TREASUREHUNTER_API IFullBodyMotionSync
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SyncSpeed(float& Speed);
	virtual void SyncbJump(bool& Jump);
	virtual void SyncbFalling(bool& Falling);
	virtual void SyncStandToSparint(bool& STS);
	virtual void SyncIdleType(EIdleType& Idle);
	virtual void SyncMovementType(EMovementType& Movement);
	virtual void SyncMovingDirection(EMovingDirection& Moving);
};
