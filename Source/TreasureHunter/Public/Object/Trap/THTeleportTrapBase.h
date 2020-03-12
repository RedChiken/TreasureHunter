// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/THActorBase.h"
#include "THTeleportTrapBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHTeleportTrapBase : public ATHActorBase
{
	GENERATED_BODY()
public:
    ATHTeleportTrapBase();

    UFUNCTION(BlueprintImplementableEvent)
        void OnCharacterInRange(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Actor)
        class ATHTeleportTrapBase* Pair;
};
