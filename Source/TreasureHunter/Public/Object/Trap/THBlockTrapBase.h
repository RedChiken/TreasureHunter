// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Trap/THTrapBase.h"
#include "THBlockTrapBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHBlockTrapBase : public ATHTrapBase
{
    GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Block)
        TArray<class ATHWallBase*> InterpWallList;

public:
    ATHBlockTrapBase();

    virtual void Tick(float DeltaTime) override;

    UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
        void ServerActivateAllInterpWall(float duration, bool bPositionIsRelative);

    UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
        void ServerInactivateAllInterpWall(float duration, bool bPositionIsRelative);

    UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
        void ServerStopAllInterpWall();

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

    UFUNCTION(NetMulticast, Reliable)
        void MulticastActivateAllInterpWall(float duration, bool bPositionIsRelative);

    UFUNCTION(NetMulticast, Reliable)
        void MulticastInactivateAllInterpWall(float duration, bool bPositionIsRelative);

    UFUNCTION(NetMulticast, Reliable)
        void MulticastStopAllInterpWall();
};