// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StagePlayerController.generated.h"

class UStageHUDWidget;

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API AStagePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AStagePlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

protected:
	/*UFUNCTION(BlueprintImplementableEvent)
		UStageHUDWidget* CreateHUD();*/

private:
	bool InitializeHUD();
	void TickHUD(float DeltaSeconds);

	//void CheckInteractionTriggers();

	/*
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ExcuteInteractionTrigger(AInteractionTrigger* Trigger);
	*/
	UFUNCTION()
		void RequestFinalizeCurrentStage();

protected:
	/*
	UPROPERTY()
	UStageHUDWidget* HUD;
	*/
};
