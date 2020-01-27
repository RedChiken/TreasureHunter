// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "StageGameState.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API AStageGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AStageGameState();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:

protected:
	FString NextLevelOnExit;
};
