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
#include "DataType/THInteractionType.h"
#include "Engine/EngineTypes.h"
#include "Containers/EnumAsByte.h"
#include "THAnimInstanceBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnterRopeTop);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitRopeTop);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnterRopeBottom);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitRopeBottom);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnterWallTop);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitWallTop);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnterWallBottom);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitWallBottom);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnterLadderTop);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitLadderTop);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnterLadderBottom);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitLadderBottom);

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API UTHAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(Blueprintcallable)
		void AnimNotify_EnterRopeTop();

	UFUNCTION(Blueprintcallable)
		void AnimNotify_ExitRopeTop();

	UFUNCTION(Blueprintcallable)
		void AnimNotify_EnterRopeBottom();

	UFUNCTION(Blueprintcallable)
		void AnimNotify_ExitRopeBottom();

	UFUNCTION(Blueprintcallable)
		void AnimNotify_EnterWallTop();

	UFUNCTION(Blueprintcallable)
		void AnimNotify_ExitWallTop();

	UFUNCTION(Blueprintcallable)
		void AnimNotify_EnterWallBottom();

	UFUNCTION(Blueprintcallable)
		void AnimNotify_ExitWallBottom();

	UFUNCTION(Blueprintcallable)
		void AnimNotify_EnterLadderTop();

	UFUNCTION(Blueprintcallable)
		void AnimNotify_ExitLadderTop();

	UFUNCTION(Blueprintcallable)
		void AnimNotify_EnterLadderBottom();

	UFUNCTION(Blueprintcallable)
		void AnimNotify_ExitLadderBottom();

public:
	UPROPERTY(BlueprintAssignable)
		FOnEnterRopeTop OnEnterRopeTop;

	UPROPERTY(BlueprintAssignable)
		FOnExitRopeTop OnExitRopeTop;

	UPROPERTY(BlueprintAssignable)
		FOnEnterRopeBottom OnEnterRopeBottom;

	UPROPERTY(BlueprintAssignable)
		FOnExitRopeBottom OnExitRopeBottom;

	UPROPERTY(BlueprintAssignable)
		FOnEnterWallTop OnEnterWallTop;

	UPROPERTY(BlueprintAssignable)
		FOnExitWallTop OnExitWallTop;

	UPROPERTY(BlueprintAssignable)
		FOnEnterWallBottom OnEnterWallBottom;

	UPROPERTY(BlueprintAssignable)
		FOnExitWallBottom OnExitWallBottom;

	UPROPERTY(BlueprintAssignable)
		FOnEnterLadderTop OnEnterLadderTop;

	UPROPERTY(BlueprintAssignable)
		FOnExitLadderTop OnExitLadderTop;

	UPROPERTY(BlueprintAssignable)
		FOnEnterLadderBottom OnEnterLadderBottom;

	UPROPERTY(BlueprintAssignable)
		FOnExitLadderBottom OnExitLadderBottom;

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
