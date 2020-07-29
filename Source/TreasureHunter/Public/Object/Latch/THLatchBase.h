// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/THActorBase.h"
#include "Interface/CheckAnswer.h"
#include "THLatchBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCorrectAnswer);

UCLASS()
class TREASUREHUNTER_API ATHLatchBase : public ATHActorBase, public ICheckAnswer
{
	GENERATED_BODY()
public:
    ATHLatchBase();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
    UPROPERTY(BlueprintAssignable)
        FOnCorrectAnswer OnCorrectAnswer;

public:

    // Inherited via ICheckAnswer
    virtual bool IsCorrect();
};
