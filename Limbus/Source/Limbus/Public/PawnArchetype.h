// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PawnArchetype.generated.h"

UCLASS()
class LIMBUS_API APawnArchetype : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APawnArchetype();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when player want to move
	TArray<FVector>* MovableArea(const FVector& target, const FVector& me) const;

	// Called when player want to attack
	TArray<FVector>* AttackableArea(const FVector& target, const FVector& me) const;

	// Called when pawn Intensified
	virtual void Intensify() = 0;

protected:
	// Called in movableArea
	bool Movable(const FVector& target, const FVector& me) const;
	
	// Called in attackableArea
	bool Attackable(const FVector& target, const FVector& me) const;

public:
	TArray<UActorComponent *> skillset;
	int HEALTH;
	int ATK;
	int SACRED;
	bool player;

protected:
	TArray<FVector> moveRange;
	TArray<FVector> attackRange;
	
};
