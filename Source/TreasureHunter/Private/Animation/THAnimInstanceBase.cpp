// Fill out your copyright notice in the Description page of Project Settings.


#include "THAnimInstanceBase.h"
#include "Interface/LocomotionSync.h"
#include "Interface/FullBodyMotionSync.h"
#include "Interface/LayeredMotionSync.h"
#include "Interface/StatusSync.h"

void UTHAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		ILocomotionSync* Locomotion = Cast<ILocomotionSync>(Pawn);
		if (Locomotion)
		{
			Locomotion->SyncSpeed(CurrentSpeed);
			Locomotion->SyncbJump(bJump);
			Locomotion->SyncbFalling(bFall);
			Locomotion->SyncIdleType(IdleType);
			Locomotion->SyncMovementType(MovementType);
			Locomotion->SyncMovingDirection(MovingDirection);
		}

		IFullBodyMotionSync* FullBodyMotion = Cast<IFullBodyMotionSync>(Pawn);
		if (FullBodyMotion)
		{
			FullBodyMotion->SyncbFullBodyMotion(bFullBodyMotion);
			FullBodyMotion->SyncbUpperClimb(bUpperClimb);
			FullBodyMotion->SyncbMiddleClimb(bMiddleClimb);
			FullBodyMotion->SyncbLowerClimb(bLowerClimb);
			FullBodyMotion->SyncMovementMode(MovementMode);
		}

		ILayeredMotionSync* LayeredMotion = Cast<ILayeredMotionSync>(Pawn);
		if (LayeredMotion)
		{
			LayeredMotion->SyncbLayeredMotion(bLayeredMotion);
			LayeredMotion->SyncLayeredAction(LayeredAction);
			LayeredMotion->SyncInteractionType(InteractionType);
		}

		IStatusSync* Status = Cast<IStatusSync>(Pawn);
		if (Status)
		{
			Status->SyncHP(HP);
			Status->SyncbDead(bDead);
		}
	}
}

void UTHAnimInstanceBase::AnimNotify_Jump()
{
	OnJump.Broadcast();
}

void UTHAnimInstanceBase::AnimNotify_EnterRopeTop()
{
	OnEnterRopeTop.Broadcast();
}

void UTHAnimInstanceBase::AnimNotify_ExitRopeTop()
{
	OnExitRopeTop.Broadcast();
}

void UTHAnimInstanceBase::AnimNotify_EnterRopeBottom()
{
	OnEnterRopeBottom.Broadcast();
}

void UTHAnimInstanceBase::AnimNotify_ExitRopeBottom()
{
	OnExitRopeBottom.Broadcast();
}

void UTHAnimInstanceBase::AnimNotify_EnterWallTop()
{
	OnEnterWallTop.Broadcast();
}

void UTHAnimInstanceBase::AnimNotify_ExitWallTop()
{
	OnExitWallTop.Broadcast();
}

void UTHAnimInstanceBase::AnimNotify_EnterWallBottom()
{
	OnEnterWallBottom.Broadcast();
}

void UTHAnimInstanceBase::AnimNotify_ExitWallBottom()
{
	OnExitWallBottom.Broadcast();
}

void UTHAnimInstanceBase::AnimNotify_EnterLadderTop()
{
	OnEnterLadderTop.Broadcast();
}

void UTHAnimInstanceBase::AnimNotify_ExitLadderTop()
{
	OnExitLadderTop.Broadcast();
}

void UTHAnimInstanceBase::AnimNotify_EnterLadderBottom()
{
	OnEnterLadderBottom.Broadcast();
}

void UTHAnimInstanceBase::AnimNotify_ExitLadderBottom()
{
	OnExitLadderBottom.Broadcast();
}

void UTHAnimInstanceBase::AnimNotify_EnableLeftHandHitBox()
{
	OnEnableLeftHandHitBox.Broadcast();
}

void UTHAnimInstanceBase::AnimNotify_DisableLeftHandHitBox()
{
	OnDisableLeftHandHitBox.Broadcast();
}
