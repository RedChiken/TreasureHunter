// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Interface/DamageActivity.h"
#include "Interface/ObjectActivity.h"
#include "THCharacterHitBox.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API UTHCharacterHitBox : public UCapsuleComponent, public IDamageActivity, public IObjectActivity
{
	GENERATED_BODY()

public:
	UTHCharacterHitBox();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
	bool getAbletoHit();

public:
	virtual const float GetDamage() override;
	virtual void UpdateDamage(const float& Damage) override;

	virtual void Activate() override;
	virtual void InActivate() override;
	virtual void Reset() override;
	virtual FString GetID() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Damage)
		float damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Damage)
		bool bAbletoHit;
};
