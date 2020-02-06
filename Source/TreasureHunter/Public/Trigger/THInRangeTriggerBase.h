// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trigger/THTriggerBase.h"
#include "THInRangeTriggerBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHInRangeTriggerBase : public ATHTriggerBase
{
	GENERATED_BODY()
public:
    ATHInRangeTriggerBase();

private:
    UFUNCTION()
        void OnCharacterInRange(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
