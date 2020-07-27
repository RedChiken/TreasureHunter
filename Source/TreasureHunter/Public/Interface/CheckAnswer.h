// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CheckAnswer.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCheckAnswer : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TREASUREHUNTER_API ICheckAnswer
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsCorrect() = 0;
	virtual void Submit(UObject* Input) = 0;
	virtual void Accept(UObject* Input) = 0;
	virtual void Reject(UObject* Input) = 0;
};