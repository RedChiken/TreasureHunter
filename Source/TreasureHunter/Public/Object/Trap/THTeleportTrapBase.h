// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Trap/THTrapBase.h"
#include "THTeleportTrapBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHTeleportTrapBase : public ATHTrapBase
{
	GENERATED_BODY()
public:
    ATHTeleportTrapBase();

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = MovementPoint)
        class ATHTeleportTrapBase* Pair;
};
