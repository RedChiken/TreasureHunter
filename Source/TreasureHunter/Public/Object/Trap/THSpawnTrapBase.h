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

    virtual void DeactivateActor(AActor* actor);

public:
    UFUNCTION(BlueprintCallable)
        void ActivateActorByIndex(int index);

    UFUNCTION(BlueprintCallable)
        void ActivateAllActor();

    UFUNCTION(BlueprintCallable)
        void DeactivateActorByIndex(int index);

    UFUNCTION(BlueprintCallable)
        void DeactivateAllActor();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Spawn)
        TArray<AActor*> SpawnedActor;
};
