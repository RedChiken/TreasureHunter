// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

class UWidgetControllerComponent;

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALobbyPlayerController();

	UFUNCTION(Client, Reliable)
		void Client_InitializeLobbyUI();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	void InitializeLobbyUI();

	UFUNCTION(BlueprintImplementableEvent)
		void ReceiveInitializeLobbyUI();

protected:
	UPROPERTY(Replicated, BlueprintReadOnly)
		UWidgetControllerComponent* WidgetController;

	bool bLobbyUIInitialized;
};
