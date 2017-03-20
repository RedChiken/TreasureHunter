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
	
	// Called in ActableArea
	UFUNCTION(BlueprintCallable)
	bool ActableDistance(const FVector& target, const FVector& me) const;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
	UFUNCTION(BlueprintCallable)
	virtual void ActSkill(class ABoard* list, const TArray<FVector>& targets) {}

	// TODO : need to add map as a parameter
	// Called when a player want to use this skill
	UFUNCTION(BlueprintCallable)
	TArray<FVector> ActableArea(const FVector& target, const FVector& me) const;

public:
	UPROPERTY(BlueprintReadWrite)
	bool usable;

protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> range;

	
};
