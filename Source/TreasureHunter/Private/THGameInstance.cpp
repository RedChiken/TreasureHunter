// Fill out your copyright notice in the Description page of Project Settings.

#include "THGameInstance.h"
#include "TreasureHunter.h"
#include "Kismet/GameplayStatics.h"

void UTHGameInstance::Init()
{
	Super::Init();
	
	OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UTHGameInstance::OnDestroySessionComplete);
}

void UTHGameInstance::Shutdown()
{
	DestroySessionAndLeaveGame();

	Super::Shutdown();
}

void UTHGameInstance::DestroySessionAndLeaveGame()
{
	UE_LOG(LogTemp, Log, TEXT("%hs: Trying to destroy the session..."), __FUNCTION__);

	IOnlineSubsystem* const OnlineSystem = IOnlineSubsystem::Get();
	if (OnlineSystem) {
		IOnlineSessionPtr Sessions = OnlineSystem->GetSessionInterface();
		if (Sessions.IsValid()) {
			Sessions->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);
			Sessions->DestroySession(GameSessionName);
		}
	}
}

void UTHGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("%hs: SessionName=%s, bWasSuccessful=%d"), __FUNCTION__, *SessionName.ToString(), bWasSuccessful);

	IOnlineSubsystem* const OnlineSystem = IOnlineSubsystem::Get();
	if (OnlineSystem) {
		IOnlineSessionPtr Sessions = OnlineSystem->GetSessionInterface();
		if (Sessions.IsValid()) {
			Sessions->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
			if (bWasSuccessful) {
				//TODO: Change level to lobby level
				UGameplayStatics::OpenLevel(GetWorld(), "LobbyLevel", true);
			}
		}
	}
}
