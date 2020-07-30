// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Latch/THLatchBase.h"
#include "THWidgetLatchBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHWidgetLatchBase : public ATHLatchBase
{
	GENERATED_BODY()

public:
    ATHWidgetLatchBase();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
    // Inherited via ICheckAnswer
    virtual bool IsCorrect() override;
};
