// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Piece/THPieceBase.h"
#include "Interface/Damagable.h"
#include "THHitPieceBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHHitPieceBase : public ATHPieceBase, public IDamagable
{
	GENERATED_BODY()

public:
    ATHHitPieceBase();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
    virtual void ReceiveDamage(const float& damage) override;
    virtual void ReceiveHeal(const float& heal) override;
};
