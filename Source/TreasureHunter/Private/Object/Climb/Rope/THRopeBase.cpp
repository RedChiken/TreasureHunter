// Fill out your copyright notice in the Description page of Project Settings.


#include "THRopeBase.h"
#include "Character/THCharacterBase.h"

ATHRopeBase::ATHRopeBase() : ATHClimbBase()
{
	IdleType = EIdleType::ROPE;
}