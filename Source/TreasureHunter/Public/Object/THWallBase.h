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
		void StopWall();

	UFUNCTION(BlueprintCallable)
		TArray<FInterpControlPoint> ReverseControlPoints(const TArray<FInterpControlPoint>& ControlPoints);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, REplicated, Category = Movement)
		FVector InitialPosition;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Movement)
        class UInterpToMovementComponent* MovementComponent;
};
