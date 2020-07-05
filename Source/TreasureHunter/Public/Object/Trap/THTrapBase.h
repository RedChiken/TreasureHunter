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

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void InitializeTrap();

	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerUpdatebInArea(bool inArea);

	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerUpdatebInactive(bool Inactive);

	UFUNCTION(BlueprintImplementableEvent)
		void OnCharacterInRange(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdatebInArea(bool inArea);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdatebInactive(bool Inactive);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Block)
		bool bInArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Block)
		bool bInactive;
};
