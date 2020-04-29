// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/THActorBase.h"
#include "THBlockTrapBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHBlockTrapBase : public ATHActorBase
{
	GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Block)
        TArray<class ATHWallBase*> InterpWallList;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Block)
        TArray<FVector> ActivatingDirection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Block)
        TArray<FVector> DeactivatingDirection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Block)
        bool bInArea;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Block)
        bool bInactive;

public:
    ATHBlockTrapBase();

    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintImplementableEvent)
        void OnCharacterInRange(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
        void InitializeTrap();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
        void SetRelativeControlPoint(class ATHWallBase* Wall, const TArray<FVector>& ControlPointList);

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
        void ActivateAllInterpWall();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
        void StopAllInterpWall();

    UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
        void ServerUpdatebInArea(bool inArea);

    UFUNCTION(NetMulticast, Reliable)
        void MulticastUpdatebInArea(bool inArea);

    UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
        void ServerUpdatebInactive(bool Inactive);

    UFUNCTION(NetMulticast, Reliable)
        void MulticastUpdatebInactive(bool Inactive);
};
