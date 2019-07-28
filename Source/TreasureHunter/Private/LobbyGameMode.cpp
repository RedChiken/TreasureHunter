// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"
#include "TreasureHunter.h"
#include "LobbyPlayerController.h"
#include "PlayerController/LobbyPlayerController.h"

#include "Kismet/GameplayStatics.h"

ALobbyGameMode::ALobbyGameMode() {

}

bool ALobbyGameMode::HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxPlayers)
{
	return false;
}

void ALobbyGameMode::FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool IsLAN, bool bIsPresencec)
{
}

bool ALobbyGameMode::JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult & Result)
{
	return false;
}

void ALobbyGameMode::UpdateSessionMemberInfo()
{
}

void ALobbyGameMode::TryStartGame(const FString & MapName)
{
}

inline FOnFindSessionsComplete & ALobbyGameMode::GetOnFindSessionsComplete() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
}

inline FOnlineSessionSearch * ALobbyGameMode::GetSessionSearch() const
{
	return nullptr;
}

void ALobbyGameMode::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
}

void ALobbyGameMode::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
}

void ALobbyGameMode::OnFindSessionsComplete(bool bWasSuccessful)
{
}

void ALobbyGameMode::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}

void ALobbyGameMode::CollectSessionMemberInfo(TArray<FRoomMemberInfo>& OutSessionMemberInfoArray, AController * Ignore)
{
}

void ALobbyGameMode::PostLogin(APlayerController * NewPlayer)
{
}

void ALobbyGameMode::Logout(AController * Exiting)
{
}
