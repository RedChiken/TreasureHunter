// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/THActorBase.h"
#include "THInteractionExample.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHInteractionExample : public ATHActorBase
{
	GENERATED_BODY()
public:
    ATHInteractionExample();

private: 
    UFUNCTION()
        void OnCharacterNearbyObject(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
        void OnCharacterOutofObject(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
