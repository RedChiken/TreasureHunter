// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/THActorBase.h"
#include "THClimbBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHClimbBase : public ATHActorBase
{
	GENERATED_BODY()
public:
    ATHClimbBase();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Range)
		class UBoxComponent* UpsideArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Range)
		class UBoxComponent* DownsideArea;

private:
	UFUNCTION()
		void OnClimbAtTop(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnClimbAtBottom(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
		void OnClimbAtMiddle(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
