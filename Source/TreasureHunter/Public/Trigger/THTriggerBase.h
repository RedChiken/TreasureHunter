// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "THTriggerBase.generated.h"

UCLASS()
class TREASUREHUNTER_API ATHTriggerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATHTriggerBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = InteractionArea)
		class UStaticMeshComponent* Core;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = InteractionArea)
		class UBoxComponent* Area;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = AreaSize, meta = (AllowPrivateAccess = "true"))
		float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = AreaSize, meta = (AllowPrivateAccess = "true"))
		float Depth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = AreaSize, meta = (AllowPrivateAccess = "true"))
		float Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = AreaSize, meta = (AllowPrivateAccess = "true"))
		FVector Location;
};
