// Fill out your copyright notice in the Description page of Project Settings.

#include "Limbus.h"
#include "../Public/PawnArchetype.h"
#include "../Public/Skillarchetype.h"

// Sets default values
APawnArchetype::APawnArchetype()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APawnArchetype::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnArchetype::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnArchetype::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// TODO : need to add map as a parameter
// Called when player want to move
TArray<FVector> APawnArchetype::MovableArea(const FVector& target, const FVector& me) const {
	TArray<FVector> ret;
	for (auto i : moveRange) {
		if (Movable(target, me)) {
			ret.AddUnique(i);
		}
	}
	return ret;
}


// TODO : need to add map as a parameter
// Called when player want to attack
TArray<FVector> APawnArchetype::AttackableArea(const FVector& target, const FVector& me) const {
	TArray<FVector> ret;
	for (auto i : moveRange) {
		if (Attackable(target, me)) {
			ret.AddUnique(i);
		}
	}
	return ret;
}


// Called in movableArea
bool APawnArchetype::Movable(const FVector& target, const FVector& me) const {
	bool ret = false;
	for (auto i : moveRange) {
		if (i == (target + me))
		break;
	}
	return ret;
}


// Called in attackableArea
bool APawnArchetype::Attackable(const FVector& target, const FVector& me) const {
	bool ret = false;
	for (auto i : attackRange) {
		if (i == (target + me))
		break;
	}
	return ret;
}

void APawnArchetype::Intensify() {

}