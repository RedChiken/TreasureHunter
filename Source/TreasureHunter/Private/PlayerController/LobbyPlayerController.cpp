// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyPlayerController.h"
#include "WidgetControllerComponent.h"
#include "TreasureHunter.h"
#include "UnrealNetwork.h"

ALobbyPlayerController::ALobbyPlayerController() {
	WidgetController = CreateDefaultSubobject<UWidgetControllerComponent>(TEXT("WidgetController"));
	bShowMouseCursor = true;
	//AutoReceiveInput = EAutoReceiveInput::Player0;
}

void ALobbyPlayerController::Client_InitializeLobbyUI_Implementation()
{
	InitializeLobbyUI();
}

void ALobbyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALobbyPlayerController, WidgetController);
}

void ALobbyPlayerController::InitializeLobbyUI()
{
	if (bLobbyUIInitialized) {
		UE_LOG(THLog, Log, TEXT("%hs: Already initialized"), __FUNCTION__);
		return;
	}
	ReceiveInitializeLobbyUI();
}
