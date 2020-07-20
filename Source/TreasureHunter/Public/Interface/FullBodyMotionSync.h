// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/EngineTypes.h"
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
	virtual void SyncbFullBodyMotion(bool& FullBody) = 0;
	virtual void SyncbUpperClimb(bool& Upper) = 0;
	virtual void SyncbMiddleClimb(bool& Middle) = 0;
	virtual void SyncbLowerClimb(bool& Lower) = 0;
	virtual void SyncMovementMode(TEnumAsByte<EMovementMode>& MovementMode) = 0;
};
