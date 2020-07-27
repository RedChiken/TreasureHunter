// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/CheckInRangeCharacter.h"
#include "Interface/ObjectActivity.h"
#include "THActorBase.generated.h"

UCLASS()
class TREASUREHUNTER_API ATHActorBase : public AActor, public ICheckInRangeCharacter, public IObjectActivity
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATHActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerUpdatebActive(bool active);
	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerAddtoBuffer(UObject* input);
	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerRemovefromBuffer(UObject* input);
	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerResetBuffer();
	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerFlush();
	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerAddtoMemory(UObject* input);
	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerRemovefromMemory(UObject* input);
	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerResetMemory();

protected:
	UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
		void MulticastUpdatebActive(bool active);
	UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
		void MulticastAddtoBuffer(UObject* input);
	UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
		void MulticastRemovefromBuffer(UObject* input);
	UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
		void MulticastResetBuffer();
	UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
		void MulticastFlush();
	UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
		void MulticastAddtoMemory(UObject* input);
	UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
		void MulticastRemovefromMemory(UObject* input);
	UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
		void MulticastResetMemory();

public:
	virtual void AddtoBuffer(UObject* input) override;
	virtual void RemovefromBuffer(UObject* input) override;
	virtual bool IsValidinBuffer(const UObject* input) override;
	virtual void ResetBuffer() override;
	virtual void Flush() override;
	virtual void AddtoMemory(UObject* input) override;
	virtual void RemovefromMemory(UObject* input) override;
	virtual bool IsValidinMemory(const UObject* input) override;
	virtual void ResetMemory() override;

	virtual void Activate() override;
	virtual void InActivate() override;
	virtual void Reset() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Actor)
		class UStaticMeshComponent* Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Range)
		class UBoxComponent* Area;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Spawn)
		bool bActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = InRange)
		TArray<UObject*> Entry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = InRange)
		TArray<UObject*> Record;
};
