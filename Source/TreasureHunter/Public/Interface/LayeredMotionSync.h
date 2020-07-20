// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../DataType/THLayeredAction.h"
#include "../DataType/THInteractionType.h"
#include "LayeredMotionSync.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULayeredMotionSync : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TREASUREHUNTER_API ILayeredMotionSync
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SyncbLayeredMotion(bool& LayeredMotion);
	virtual void SyncLayeredAction(ELayeredAction& Layered);
	virtual void SyncInteractionType(EInteractionType& Interaction);
};
