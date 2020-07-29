// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/THActorBase.h"
#include "THPieceBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHPieceBase : public ATHActorBase
{
	GENERATED_BODY()

public:
    ATHPieceBase();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};
