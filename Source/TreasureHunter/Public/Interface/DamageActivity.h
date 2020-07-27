// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageActivity.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageActivity : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TREASUREHUNTER_API IDamageActivity
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual const float GetDamage() = 0;
	virtual void UpdateDamage(const float& Damage) = 0;
};