// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Interface/DamageActivity.h"
#include "THCharacterHitBox.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API UTHCharacterHitBox : public UCapsuleComponent, public IDamageActivity
{
	GENERATED_BODY()

public:
	UTHCharacterHitBox();

public:
	virtual const float GetDamage() override;
	virtual void UpdateDamage(const float& Damage) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
		float damage;
};
