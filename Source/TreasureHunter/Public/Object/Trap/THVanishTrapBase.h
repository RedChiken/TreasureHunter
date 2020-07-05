// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Trap/THTrapBase.h"
#include "THVanishTrapBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHVanishTrapBase : public ATHTrapBase
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

    UFUNCTION(BlueprintCallable)
        void SpawnBrush();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Brush)
        TArray<class ABrush*> BrushList;

};
