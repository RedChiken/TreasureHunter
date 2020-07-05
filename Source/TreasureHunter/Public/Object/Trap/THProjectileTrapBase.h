// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Trap/THSpawnTrapBase.h"
#include "THProjectileTrapBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHProjectileTrapBase : public ATHSpawnTrapBase
{
	GENERATED_BODY()
public:
    ATHProjectileTrapBase();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

    virtual void ActivateActor(AActor* actor) override;

    virtual void DeactivateActor(AActor* actor) override;
};
