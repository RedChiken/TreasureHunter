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
			CurrentSpeed = Character->getCurrentSpeed();
			IdleType = Character->getIdleType();
			MovementType = Character->getMovementType();
			MovingDirection = Character->getMovingDirection();
			bJump = Character->getbJump();
			bFall = Character->getIsFalling();
			EnterDirection = Character->getEnterDirection();
			bFullBodyMotion = Character->getbFullBodyMotion();
			bDead = Character->getbDead();
			bLayeredMotion = Character->getbLayeredMotion();
			bStandToSprint = Character->getbStandToSprint();
			bInInteractionRange = Character->getbInInteractionRange();
			bAbleToClimb = Character->getbAbleToClimb();
			bClimbing = Character->getbClimbing();
			HP = Character->getHP();
		}
	}
}
