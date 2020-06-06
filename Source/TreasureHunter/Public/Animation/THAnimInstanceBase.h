// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DataType/THIdleType.h"
#include "DataType/THMovementType.h"
#include "DataType/THMovingDirection.h"
#include "DataType/THEnterDirection.h"
#include "DataType/THExitDirection.h"
#include "DataType/THLayeredAction.h"
#include "DataType/THInteractionType.h"
#include "Engine/EngineTypes.h"
#include "Containers/EnumAsByte.h"
#include "THAnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API UTHAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = Locomotion)
		float CurrentSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Locomotion)
		bool bJump;

	UPROPERTY(BlueprintReadOnly, Category = Locomotion)
		bool bFall;

	UPROPERTY(BlueprintReadOnly, Category = Locomotion)
		bool bStandToSprint;

	UPROPERTY(BlueprintReadOnly, Category = Locomotion)
		EIdleType IdleType;

	UPROPERTY(BlueprintReadOnly, Category = Locomotion)
		EMovementType MovementType;

	UPROPERTY(BlueprintReadOnly, Category = Locomotion)
		EMovingDirection MovingDirection;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		TEnumAsByte<enum EMovementMode> MovementMode;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		EEnterDirection EnterDirection;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		EExitDirection ExitDirection;

	UPROPERTY(BlueprintReadOnly, Category = LayeredMotion)
		bool bLayeredMotion;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		bool bFullBodyMotion;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		bool bUpward;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		bool bDead;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		bool bUpperClimb;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		bool bMiddleClimb;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		bool bLowerClimb;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		ELayeredAction LayeredAction;

	UPROPERTY(BlueprintReadOnly, Category = FullBodyMotion)
		EInteractionType InteractionType;

	UPROPERTY(BlueprintReadOnly, Category = Status)
		float HP;

};
