// Fill out your copyright notice in the Description page of Project Settings.


#include "THLadderBase.h"
#include "Character/THCharacterBase.h"

ATHLadderBase::ATHLadderBase() : ATHClimbBase()
{
	type = EIdleType::LADDER;
}