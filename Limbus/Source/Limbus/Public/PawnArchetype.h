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
	UFUNCTION(BlueprintCallable)
	TArray<FVector> MovableArea(const FVector& target, const FVector& me) const;

	// Called when player want to attack
	UFUNCTION(BlueprintCallable)
	TArray<FVector> AttackableArea(const FVector& target, const FVector& me) const;

	// Called when pawn Intensified
	//UFUNCTION(BlueprintNativeEvent)
	virtual void Intensify();

protected:
	// Called in movableArea
	UFUNCTION(BlueprintCallable)
	bool Movable(const FVector& target, const FVector& me) const;
	
	// Called in attackableArea
	UFUNCTION(BlueprintCallable)
	bool Attackable(const FVector& target, const FVector& me) const;

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<class USkillArchetype *> skillset;
	UPROPERTY(BlueprintReadWrite)
	int HEALTH;
	UPROPERTY(BlueprintReadWrite)
	int ATK;
	UPROPERTY(BlueprintReadWrite)
	int SACRED;
	UPROPERTY(BlueprintReadWrite)
	bool player;

protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> moveRange;
	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> attackRange;
	
};
