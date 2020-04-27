// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/THActorBase.h"
#include "THWallBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHWallBase : public ATHActorBase
{
	GENERATED_BODY()
public:
    ATHWallBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
	UFUNCTION(BlueprintCallable)
		void ActivateWall(float duration, bool bPositionIsRelative);

	UFUNCTION(BlueprintCallable)
		void StopWall();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Movement)
        class UInterpToMovementComponent* MovementComponent;
};
