// Fill out your copyright notice in the Description page of Project Settings.


#include "THAnimInstanceBase.h"
#include "THCharacterBase.h"

void UTHAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		auto Character = Cast<ATHCharacterBase>(Pawn);
		if (Character)
		{
			/*
			CurrentSpeed = Character->getCurrentSpeed();
			bJump = Character->getbJump();
			bFall = Character->getIsFalling();
			bStandToSprint = Character->getbStandToSprint();
			IdleType = Character->getIdleType();
			MovementType = Character->getMovementType();
			MovingDirection = Character->getMovingDirection();

			bLayeredMotion = Character->getbLayeredMotion();
			bFullBodyMotion = Character->getbFullBodyMotion();
			bUpward = Character->getbUpward();
			bDead = Character->getbDead();
			bUpperClimb = Character->getbUpperClimbTrigger();
			bMiddleClimb = Character->getbMiddleClimbTrigger();
			bLowerClimb = Character->getbLowerClimbTrigger();
			LayeredAction = Character->getLayeredAction();
			InteractionType = Character->getInteractionType();

			HP = Character->getHP();
			*/
			Character->SyncLocomotionAnimTrigger(CurrentSpeed, bJump, bFall, bStandToSprint, IdleType, MovementType, MovingDirection);
			Character->SyncFullBodyAnimTrigger(bLayeredMotion, bFullBodyMotion, bUpward, bDead, bUpperClimb, bMiddleClimb, bLowerClimb, LayeredAction, InteractionType, MovementMode);
			Character->SyncStatusAnimTrigger(HP);
		}
	}
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
