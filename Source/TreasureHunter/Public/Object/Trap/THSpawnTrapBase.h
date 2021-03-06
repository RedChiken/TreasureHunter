// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/THActorBase.h"
#include "THSpawnTrapBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHSpawnTrapBase : public ATHActorBase
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

    UFUNCTION(BlueprintImplementableEvent)
        void OnCharacterInRange(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Spawn)
        TArray<AActor*> SpawnedActor;
};
