// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trigger/THTriggerBase.h"
#include "THInteractionTriggerBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHInteractionTriggerBase : public ATHTriggerBase
{
	GENERATED_BODY()
public:
    ATHInteractionTriggerBase();

private:
    UFUNCTION()
        void OnCharacterNearbyObject(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
        void OnCharacterOutofObject(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
