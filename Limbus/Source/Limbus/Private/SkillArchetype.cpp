// Fill out your copyright notice in the Description page of Project Settings.

#include "Limbus.h"
#include "../Public/SkillArchetype.h"
#include "../Public/Board.h"

// Sets default values for this component's properties
USkillArchetype::USkillArchetype()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	this->usable = false;
	// ...
}


// Called when the game starts
void USkillArchetype::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USkillArchetype::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



// TODO : need to add map as a parameter
// Called when a player want to use this skill
TArray<FVector> USkillArchetype::ActableArea(const FVector& target, const FVector& me) const {
	TArray<FVector> ret;
	for (auto i : range) {
		if (ActableDistance(target, me)) {
			ret.AddUnique(i);
		}
	}
	return ret;
}


//Called in ActableArea
bool USkillArchetype::ActableDistance(const FVector& target, const FVector& me) const {
	bool ret = false;
	for (auto i : range) {
		if (i == (target + me)) {
			ret = true;
			break;
		}
	}
	return ret;
}
