// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UObject/Object.h"
#include "CheckInRangeCharacter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCheckInRangeCharacter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TREASUREHUNTER_API ICheckInRangeCharacter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AddtoBuffer(FString input) = 0;
	virtual void RemovefromBuffer(FString input) = 0;
	virtual bool IsValidinBuffer(const FString input) = 0;
	virtual void ResetBuffer() = 0;
	virtual void Flush() = 0;
	virtual void AddtoMemory(FString input) = 0;
	virtual void RemovefromMemory(FString input) = 0;
	virtual bool IsValidinMemory(const FString input) = 0;
	virtual void ResetMemory() = 0;

};
