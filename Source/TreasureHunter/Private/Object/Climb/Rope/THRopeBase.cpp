// Fill out your copyright notice in the Description page of Project Settings.


#include "THRopeBase.h"
#include "Character/THCharacterBase.h"

void ATHRopeBase::EnterClimb(class ATHCharacterBase* Character, EEnterDirection Enter)
{
	Super::EnterClimb(Character, Enter);
	Character->UpdateIdleType(EIdleType::ROPE);
}