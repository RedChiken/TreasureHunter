// Fill out your copyright notice in the Description page of Project Settings.


#include "THLadderBase.h"
#include "Character/THCharacterBase.h"

void ATHLadderBase::EnterClimb(class ATHCharacterBase* Character, EEnterDirection Enter)
{
	Super::EnterClimb(Character, Enter);
	Character->UpdateIdleType(EIdleType::LADDER);
}