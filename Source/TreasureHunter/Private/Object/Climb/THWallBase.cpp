// Fill out your copyright notice in the Description page of Project Settings.


#include "THWallBase.h"
#include "TreasureHunter.h"
#include "Kismet/GameplayStatics.h"
#include "net/UnrealNetwork.h"
#include "Engine.h"

ATHWallBase::ATHWallBase() : ATHClimbBase()
{
	IdleType = EIdleType::WALL;
}