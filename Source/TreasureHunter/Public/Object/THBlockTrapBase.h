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
        TArray<class UStaticMeshComponent*> WallList;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Block)
        TArray<FVector> DestinationList;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Block)
        bool InArea;

private:
    FVector nowLocation;

public:
    ATHBlockTrapBase();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

    UFUNCTION(BlueprintCallable)
        void MoveAllWall(float DeltaTime);

    UFUNCTION(Server, Reliable, WithValidation)
        void ServerUpdateInArea(bool area);

    UFUNCTION(NetMulticast, Reliable)
        void MulticastUpdateInArea(bool area);

    UFUNCTION(BlueprintImplementableEvent)
        bool IsWallNearTheEnd(int index);

private:
    UFUNCTION()
        void OnCharacterInRange(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
