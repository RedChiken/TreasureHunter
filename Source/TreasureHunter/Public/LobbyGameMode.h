// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online.h"
#include "UnrealNetwork.h"
#include "GameFramework/GameModeBase.h"
#include "THOutGameDefines.h"
#include "LobbyGameMode.generated.h"

class UWidgetControllerComponent;
class FOnlineSessionSettings;

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALobbyGameMode();

	bool HostSession(
		TSharedPtr<const FUniqueNetId>	UserId,
		FName							SessionName,
		bool							bIsLAN,
		bool							bIsPresence,
		int32							MaxPlayers);

	void FindSessions(
		TSharedPtr<const FUniqueNetId>	UserId,
		bool							IsLAN,
		bool							bIsPresencec);

	bool JoinSession(
		TSharedPtr<const FUniqueNetId>		UserId,
		FName								SessionName,
		const FOnlineSessionSearchResult&	Result);

	void UpdateSessionMemberInfo();
	void TryStartGame(const FString& MapName);

	inline FOnFindSessionsComplete& GetOnFindSessionsComplete() const;
	inline FOnlineSessionSearch* GetSessionSearch() const;

private:
	////////////////////////////////////////////////////////////////////////////////
	// CreateSession
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);
	
	//////////////////////////////////////////////////////////////////////////////////
	// FindSessions
	void OnFindSessionsComplete(bool bWasSuccessful);
	
	////////////////////////////////////////////////////////////////////////////////
	// JoinSession
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

private:
	void CollectSessionMemberInfo(TArray<FSessionMemberInfo>& OutSessionMemberInfoArray, AController* Ignore = nullptr);

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

private:
	////////////////////////////////////////////////////////////////////////////////
	// CreateSession
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	TSharedPtr<FOnlineSessionSettings> SessionSettings;

	//////////////////////////////////////////////////////////////////////////////////
	// FindSessions
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FDelegateHandle OnFindSessionsCompleteDelegatehandle;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	////////////////////////////////////////////////////////////////////////////////
	// JoinSession
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
};
