// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Puzzle/THPuzzleBase.h"
#include "ThAttachPuzzleBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API AThAttachPuzzleBase : public ATHPuzzleBase
{
	GENERATED_BODY()

public:
	AThAttachPuzzleBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION(BlueprintCallable)
		void OnCharacterNearKey(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:

};
