// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Puzzle/THPuzzleBase.h"
#include "THDestroyPuzzleBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHDestroyPuzzleBase : public ATHPuzzleBase
{
	GENERATED_BODY()

public:
    ATHDestroyPuzzleBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual bool CheckInput() override;

	UFUNCTION(BlueprintCallable)
		void OnKeyGetHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:

};
