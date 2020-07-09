// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Trap/THTrapBase.h"
#include "THSpawnTrapBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHSpawnTrapBase : public ATHTrapBase
{
	GENERATED_BODY()
public:
    ATHSpawnTrapBase();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

    virtual void ActivateActor(AActor* actor);

    virtual void InactivateActor(AActor* actor);

public:
    UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
        void ServerActivateAllActor();

    UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
        void ServerActivateActor(int index);

    UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
        void ServerInactivateAllActor();

    UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
        void ServerInactivateActor(int index);

protected:
    UFUNCTION(NetMulticast, Reliable)
        void MulticastActivateAllActor();

    UFUNCTION(NetMulticast, Reliable)
        void MulticastActivateActor(int index);

    UFUNCTION(NetMulticast, Reliable)
        void MulticastInactivateAllActor();

    UFUNCTION(NetMulticast, Reliable)
        void MulticastInactivateActor(int index);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Spawn)
        TArray<AActor*> SpawnedActor;
};
