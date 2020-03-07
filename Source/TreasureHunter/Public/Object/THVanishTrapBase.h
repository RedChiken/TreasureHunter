// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/THActorBase.h"
#include "THVanishTrapBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHVanishTrapBase : public ATHActorBase
{
	GENERATED_BODY()

public:
	ATHVanishTrapBase();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
    
    UFUNCTION(BlueprintCallable)
        void VanishBrushByIndex(int index);

    UFUNCTION(BlueprintCallable)
        void VanishAllBrush();

    UFUNCTION(BlueprintCallable)
        void AppearBrushByIndex(int index);

    UFUNCTION(BlueprintCallable)
        void AppearAllBrush();

    UFUNCTION(BlueprintImplementableEvent)
        void OnCharacterInRange(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintCallable)
        void SpawnBrush();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Brush)
        TArray<class ABrush*> BrushList;

};
