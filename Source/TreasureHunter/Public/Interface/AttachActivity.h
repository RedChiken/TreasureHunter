// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttachActivity.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttachActivity : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TREASUREHUNTER_API IAttachActivity
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsAttachable(class IAttachable* Input) = 0;
	virtual bool IsDetachable() = 0;
	virtual void Attach(class IAttachable* Input, IAttachActivity* Attacher) = 0;
	virtual class IAttachable* Detach() = 0;
};
