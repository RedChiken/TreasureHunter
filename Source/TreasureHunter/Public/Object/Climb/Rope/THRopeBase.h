// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Climb/THClimbBase.h"
#include "THRopeBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHRopeBase : public ATHClimbBase
{
	GENERATED_BODY()

protected:
	virtual void EnterClimb(class ATHCharacterBase* Character, EEnterDirection Enter);
};
