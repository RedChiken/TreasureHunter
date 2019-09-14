// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DataType/THIdleType.h"
#include "DataType/THMovementType.h"
#include "DataType/THEnterDirection.h"
#include "DataType/THExitDirection.h"
#include "THAnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API UTHAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
public:

protected:
	UPROPERTY(BlueprintReadOnly, Category = Locomotion)
		EIdleType IdleType;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		EEnterDirection EnterDirection;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		EEnterDirection ExitDirection;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		bool bFullBodyMotion;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		bool bSlide;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		bool bClimb;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		bool bUpward;

	UPROPERTY(BlueprintReadOnly, Category = Locomotion)
		EMovementType MovementType;

	UPROPERTY(BlueprintReadOnly, Category = Locomotion)
		bool bJump;

	UPROPERTY(BlueprintReadOnly, Category = Locomotion)
		bool bFall;

	UPROPERTY(BlueprintReadOnly, Category = Layered)
		bool bAttack;

	UPROPERTY(BlueprintReadOnly, Category = Layered)
		bool bInteraction;
};
