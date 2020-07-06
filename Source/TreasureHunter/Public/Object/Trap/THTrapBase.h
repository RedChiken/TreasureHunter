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

	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerAddCharacterToInRangeQueue(class ATHCharacterBase* input);

	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerRemoveCharacterFromInRangeQueue(class ATHCharacterBase* input);

	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerSaveCharacterList();

	UFUNCTION(BlueprintImplementableEvent)
		void OnCharacterInRange(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent)
		void OnCharacterBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		virtual void OnCharacterBeginOverlap_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent)
		void OnCharacterEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
		virtual void OnCharacterEndOverlap_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
		void ActivateTrap();

protected:
	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdatebInArea(bool inArea);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdatebInactive(bool Inactive);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastAddCharacterToInRangeQueue(class ATHCharacterBase* input);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastRemoveCharacterFromInRangeQueue(class ATHCharacterBase* input);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastSaveCharacterList();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Block)
		bool bInArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Block)
		bool bInactive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Condition)
		int ActivateLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Condition)
		TArray<class ATHCharacterBase*> InRangePlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Condition)
		TArray<class ATHCharacterBase*> ExperiencedParty;
};
