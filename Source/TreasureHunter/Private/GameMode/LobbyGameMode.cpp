// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"
#include "TreasureHunter.h"
#include "WidgetControllerComponent.h"
#include "PlayerController/LobbyPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameState.h"
#include "GameFramework/GameStateBase.h"
#include "Engine.h"

static IOnlineSessionPtr GetSessionInterface() {
	IOnlineSubsystem* const OnlineSystem = IOnlineSubsystem::Get();
	if (OnlineSystem) {
		IOnlineSessionPtr Sessions = OnlineSystem->GetSessionInterface();
		if (Sessions.IsValid()) {
			return Sessions;
		}
	}
	return nullptr;
}

ALobbyGameMode::ALobbyGameMode() {
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &ALobbyGameMode::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &ALobbyGameMode::OnStartOnlineGameComplete);
	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &ALobbyGameMode::OnFindSessionsComplete);
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &ALobbyGameMode::OnJoinSessionComplete);
}

bool ALobbyGameMode::HostSession(
	TSharedPtr<const FUniqueNetId>	UserId, 
	FName							SessionName, 
	bool							bIsLAN, 
	bool							bIsPresence,
	int32							MaxPlayers)
{
	IOnlineSessionPtr Sessions = GetSessionInterface();

	if (Sessions && UserId.IsValid()) {
		SessionSettings = MakeShareable(new FOnlineSessionSettings());
		
		SessionSettings->bIsDedicated =						false;
		SessionSettings->bIsLANMatch =						bIsLAN;
		SessionSettings->bUsesPresence =					bIsPresence;
		SessionSettings->NumPublicConnections =				MaxPlayers;
		SessionSettings->NumPrivateConnections =			0;
		SessionSettings->bAllowInvites =					true;
		SessionSettings->bAllowJoinInProgress =				true;
		SessionSettings->bShouldAdvertise =					true;
		SessionSettings->bAllowJoinViaPresence =			true;
		SessionSettings->bAllowJoinViaPresenceFriendsOnly =	false;
		
		SessionSettings->Set(SETTING_MAPNAME, FString("LobbyLevel"), EOnlineDataAdvertisementType::ViaOnlineService);

		OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

		return Sessions->CreateSession(*UserId, SessionName, *SessionSettings);
	}
	else {
		UE_LOG(ErrorTH_LobbyGameMode, Error, TEXT("%hs: Invalid OnlineSubsystem"), __FUNCTION__);
	}

	return false;
}

void ALobbyGameMode::FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresencec)
{
	IOnlineSessionPtr Sessions = GetSessionInterface();

	if (Sessions && UserId.IsValid()) {
		SessionSearch = MakeShareable(new FOnlineSessionSearch());

		SessionSearch->bIsLanQuery = bIsLAN;
		SessionSearch->MaxSearchResults = 10;
		SessionSearch->PingBucketSize = 50;

		if (bIsPresencec) {
			SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, bIsPresencec, EOnlineComparisonOp::Equals);
		}

		TSharedRef<FOnlineSessionSearch> SearchSettingsRef = SessionSearch.ToSharedRef();

		OnJoinSessionCompleteDelegateHandle = Sessions->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);

		Sessions->FindSessions(*UserId, SearchSettingsRef);
	}
	else {
		OnFindSessionsComplete(false);
	}
}

bool ALobbyGameMode::JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult & Result)
{
	bool bSuccessful = false;

	IOnlineSessionPtr Sessions = GetSessionInterface();

	if (Sessions && UserId.IsValid()) {
		OnJoinSessionCompleteDelegateHandle = Sessions->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);

		bSuccessful = Sessions->JoinSession(*UserId, SessionName, Result);
	}
	return bSuccessful;
}

void ALobbyGameMode::UpdateSessionMemberInfo()
{
	TArray<FSessionMemberInfo> SessionMemberInfoArray;
	CollectSessionMemberInfo(SessionMemberInfoArray);

	for (auto PS : GameState->PlayerArray) {
		if (auto PC = Cast<APlayerController>(PS->GetOwner())) {
			if (auto LWC = PC->FindComponentByClass<UWidgetControllerComponent>()) {
				LWC->Client_UpdateSessionMemberDisplay(SessionMemberInfoArray);
			}
		}
	}
}

void ALobbyGameMode::TryStartGame(const FString & MapName)
{
	bool bAllReady = true;
	for (auto PS : GameState->PlayerArray) {
		auto LWC = PS->GetOwner()->FindComponentByClass<UWidgetControllerComponent>();
		if (!LWC) {
			UE_LOG(ErrorTH_LobbyGameMode, Error, TEXT("%hs: LWC not found"), __FUNCTION__);
			bAllReady = false;
			break;
		}

		const bool bIsHostPC = (PS->GetOwner()->Role == ROLE_Authority) && (PS->GetOwner()->GetRemoteRole() == ROLE_SimulatedProxy);

		if ((bIsHostPC == false) && LWC->IsReadyInSession() == false) {
			UE_LOG(ErrorTH_LobbyGameMode, Error, TEXT("%hs: This client is not ready"), __FUNCTION__);
			bAllReady = false;
			break;
		}
	}

	if (bAllReady) {
		UE_LOG(LogTH_LobbyGameMode, Log, TEXT("%hs: Starting the game... MapName=%s"), __FUNCTION__, *MapName);
		GetWorld()->ServerTravel(MapName);
	}
	else {
		UE_LOG(ErrorTH_LobbyGameMode, Error, TEXT("%hs: Not all players are ready. The game will not start..."), __FUNCTION__);
	}
}

inline FOnFindSessionsComplete & ALobbyGameMode::GetOnFindSessionsComplete() const
{
	return GetSessionInterface()->OnFindSessionsCompleteDelegates;
}

inline FOnlineSessionSearch * ALobbyGameMode::GetSessionSearch() const
{
	return SessionSearch.Get();
}

void ALobbyGameMode::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTH_LobbyGameMode, Log, TEXT("%hs: SessionName=%s, WasSuccessful=%d"), __FUNCTION__, *SessionName.ToString(), bWasSuccessful);

	IOnlineSessionPtr Sessions = GetSessionInterface();
	if (Sessions) {
		Sessions->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
		if (bWasSuccessful) {
			OnStartSessionCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
			Sessions->StartSession(SessionName);
		}
	}
}

void ALobbyGameMode::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTH_LobbyGameMode, Log, TEXT("%hs: SessionName=%s, bWasSuccessful=%d"), __FUNCTION__, *SessionName.ToString(), bWasSuccessful);

	IOnlineSessionPtr Sessions = GetSessionInterface();
	if (Sessions) {
		Sessions->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
	}
	if (bWasSuccessful) {
		UGameplayStatics::OpenLevel(GetWorld(), FName("LobbyLevel"), true, TEXT("listen"));
	}
}

void ALobbyGameMode::OnFindSessionsComplete(bool bWasSuccessful)
{
	UE_LOG(LogTH_LobbyGameMode, Log, TEXT("%hs: bSuccess=%d"), __FUNCTION__, bWasSuccessful);

	IOnlineSessionPtr Sessions = GetSessionInterface();
	if (Sessions) {
		Sessions->ClearOnEndSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);

		UE_LOG(LogTH_LobbyGameMode, Log, TEXT("%hs: Num search results: %d"), __FUNCTION__, SessionSearch->SearchResults.Num());

		if (SessionSearch->SearchResults.Num() > 0) {
			for (int32 i = 0; i < SessionSearch->SearchResults.Num(); ++i) {
				const auto& Result = SessionSearch->SearchResults[i];

				UE_LOG(LogTH_LobbyGameMode, Log, TEXT("%hs: SessionNumber=%d, SessionName=%s"), __FUNCTION__, i + 1, *(Result.Session.OwningUserName));
			}
		}
	}
}

void ALobbyGameMode::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTH_LobbyGameMode, Log, TEXT("%hs: SessionName=%s, ResultType=%d"), __FUNCTION__, *SessionName.ToString(), static_cast<int32>(Result));

	IOnlineSessionPtr Sessions = GetSessionInterface();

	if (Sessions) {
		Sessions->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);

		APlayerController* const PlayerController = GetGameInstance()->GetFirstLocalPlayerController();

		FString TravelURL;

		if (PlayerController && Sessions->GetResolvedConnectString(SessionName, TravelURL)) {
			UE_LOG(LogTH_LobbyGameMode, Log, TEXT("%hs: ClientTravel to %s"), __FUNCTION__, *TravelURL);

			PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);
		}
	}
}

void ALobbyGameMode::CollectSessionMemberInfo(TArray<FSessionMemberInfo>& OutSessionMemberInfoArray, AController * Ignore)
{
	OutSessionMemberInfoArray.Empty();

	for (APlayerState* PS : GameState->PlayerArray) {
		bool bReady = false;

		if (PS->GetOwner() == Ignore) {
			continue;
		}
		
		if (auto LWC = PS->GetOwner()->FindComponentByClass<UWidgetControllerComponent>()) {
			bReady = LWC->IsReadyInSession();
		}

		FSessionMemberInfo MemberInfo;
		MemberInfo.PlayerName	= PS->GetPlayerName();
		MemberInfo.bReady		= bReady;

		OutSessionMemberInfoArray.Emplace(MemberInfo);
	}
}

void ALobbyGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	TArray<FString> NetModeStrings = { TEXT("NM_Standalone"), TEXT("NM_DedicatedServer"), TEXT("NM_ListenServer") TEXT("NM_Client") };
	int32 NetModeId = (int32)GetNetMode();
	UE_LOG(LogTH_LobbyGameMode, Log, TEXT("%hs: NetMode=%s(%d)"), __FUNCTION__, *NetModeStrings[NetModeId], NetModeId);

	if (auto LPC = Cast<ALobbyPlayerController>(NewPlayer)) {
		LPC->Client_InitializeLobbyUI();
	}

	const bool bIsHostPC = (NewPlayer->Role == ROLE_Authority) && (NewPlayer->GetRemoteRole() == ROLE_SimulatedProxy);

	UWidgetControllerComponent* WidgetController = NewPlayer->FindComponentByClass<UWidgetControllerComponent>();
	if (WidgetController) {
		if (GetNetMode() == NM_ListenServer) {
			WidgetController->Client_ShowSessionWidget();
			WidgetController->Client_SetReadyButtonVisual(bIsHostPC);
			UpdateSessionMemberInfo();
		}
	}
	else {
		UE_LOG(ErrorTH_LobbyGameMode, Error, TEXT("%hs: Can't fnid a lobby widget controller from the new PC"), __FUNCTION__);
	}
}

void ALobbyGameMode::Logout(AController * Exiting)
{
	Super::Logout(Exiting);

	TArray<FSessionMemberInfo> SessionMemberInfoArray;
	CollectSessionMemberInfo(SessionMemberInfoArray, Exiting);

	for (APlayerState* PS : GameState->PlayerArray) {
		auto PC = Cast<APlayerController>(PS->GetOwner());
		if (PC != Exiting) {
			if (auto LWC = PC->FindComponentByClass<UWidgetControllerComponent>()) {
				LWC->Client_UpdateSessionMemberDisplay(SessionMemberInfoArray);
			}
		}
	}
}
