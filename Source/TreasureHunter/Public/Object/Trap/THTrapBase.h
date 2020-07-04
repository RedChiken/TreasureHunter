// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/THActorBase.h"
#include "THTrapBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHTrapBase : public ATHActorBase
{
	GENERATED_BODY()
	
public:
	ATHTrapBase();

	UFUNCTION(BlueprintImplementableEvent)
		void OnCharacterInRange(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void InitializeTrap();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Block)
		bool bInArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Block)
		bool bInactive;
};
