// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "THActorBase.generated.h"

UCLASS()
class TREASUREHUNTER_API ATHActorBase : public AActor
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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Actor)
		class UStaticMeshComponent* Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Range)
		class UBoxComponent* Area;
};
