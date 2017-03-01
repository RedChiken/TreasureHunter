// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SkillArchetype.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIMBUS_API USkillArchetype : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillArchetype();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Called when the Piece use Skill
	virtual void ActSkill(FVector target);
	virtual void ActSkill(FVector target1, FVector target2);
	
	// TODO : need to add map as a parameter
	// Called when a player want to use this skill
	TArray<FVector> ActableArea(const FVector& target, const FVector& me) const;

private:
	// Called in ActableArea
	bool ActableDistance(const FVector& target, const FVector& me) const;
	
public:
	bool usable;

protected:
	TArray<FVector> range;

	
};
