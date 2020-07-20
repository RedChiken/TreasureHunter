// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StatusSync.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStatusSync : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TREASUREHUNTER_API IStatusSync
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SyncHP(float& Hp);
	virtual void SyncbDead(bool& Dead);
};
