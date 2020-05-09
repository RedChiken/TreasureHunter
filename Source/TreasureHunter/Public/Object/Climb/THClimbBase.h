// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/THActorBase.h"
#include "DataType/THEnterDirection.h"
#include "DataType/THExitDirection.h"
#include "DataType/THMovementType.h"
#include "DataType/THIdleType.h"
#include "THClimbBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHClimbBase : public ATHActorBase
{
	GENERATED_BODY()
public:
    ATHClimbBase();

	EIdleType GetIdleType();
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

protected:
	EIdleType IdleType;
};
