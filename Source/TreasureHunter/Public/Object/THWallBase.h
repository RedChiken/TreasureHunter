// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Climb/THClimbBase.h"
#include "Components/InterpToMovementComponent.h"
#include "THWallBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHWallBase : public ATHClimbBase
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
		void InactivateWall(float duration, bool bPositionIsRelative);

	UFUNCTION(BlueprintCallable)
		void StopWall();

	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerActivateWall(float duration, bool bPositionIsRelative);

	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerInactivateWall(float duration, bool bPositionIsRelative);

	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerStopWall();

protected:
	UFUNCTION(BlueprintCallable)
		void InitializeControlPointDirection(const TArray<FVector>& List);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastActivateWall(float duration, bool bPositionIsRelative);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastInactivateWall(float duration, bool bPositionIsRelative);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastStopWall();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = ControlPoints)
		TArray<FVector> ActivateDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = ControlPoints)
		TArray<FVector> InactivateDirection;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Movement)
        class UInterpToMovementComponent* MovementComponent;
};
