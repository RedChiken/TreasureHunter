// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "THOutGameDefines.h"
#include "WidgetControllerComponent.generated.h"

class UUserWidget;
class ULobbyWidget;
class UGroupMemberInfoWidget;
class UMissionInfoWidget;
class UChatWidget;
class UChatInfoWidget;
class UFindSessionWidget;
class USessionInfoWidget;
class UCreateSessionWidget;
class USessionWidget;
class URoomMemberInfoWidget;
class ALobbyGameMode;
class ALobbyPlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TREASUREHUNTER_API UWidgetControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWidgetControllerComponent();

	UFUNCTION(BlueprintCallable)
		void InitializeUI(
			ULobbyWidget*			LobbyWidget,
			UGroupMemberInfoWidget*	GroupMembberInfoWidget, 
			UMissionInfoWidget*		MissionInfoWidget, 
			UChatWidget*			ChatWidget, 
			UChatInfoWidget*		ChatInfoWidget, 
			UFindSessionWidget*		FindSessionWidget, 
			USessionInfoWidget*		SessionInfoWidget, 
			UCreateSessionWidget*	CreateSessionWidget, 
			USessionWidget*			SessionWidget, 
			URoomMemberInfoWidget*	RoomMemerInfoWidget);

	UFUNCTION(Client, Reliable)
		void Client_ShowSessionWidget();

	UFUNCTION(Client, Reliable)
		void Client_UpdateSessionMemberDisplay(const TArray<FSessionMemberInfo>& RoomMemberInfoArray);

	UFUNCTION(Client, Reliable)
		void Client_SetReadyButtonVisual(bool bisHost);

	void ShowLobbyWidget();
	void ShowSessionWidget();

	inline bool IsReadyInSession() const;

private:
	void BindEventHandlers();
	void ChangeWidget(UUserWidget* NewWidget);

	ALobbyGameMode* GetLobbyGameMode() const;
	ALobbyPlayerController* GetLobbyPlayerController() const;

	UFUNCTION()
		void OnMenu();

	UFUNCTION()
		void OnSkill();

	UFUNCTION()
		void OnItem();

	UFUNCTION()
		void OnFindMatch();

	UFUNCTION()
		void OnNextCharacter();

	UFUNCTION()
		void OnPreviewCharacter();

	UFUNCTION()
		void OnNextSkin();

	UFUNCTION()
		void OnPreviewSkin();

	UFUNCTION()
		void OnSelectGroupMember();

	UFUNCTION()
		void OnSelectMission();

	UFUNCTION()
		void OnSendMessage(FString Message);

	UFUNCTION()
		void OnTryConnect(int32 SessinIndex);

	UFUNCTION()
		void OnOpenCreateSessionWidget();

	UFUNCTION()
		void OnCancelConnect();

	UFUNCTION()
		void OnCreateSession(FString HostName, int32 MaxPlayer);

	UFUNCTION()
		void OnCancelCreateSession();

	UFUNCTION()
		void OnToggleReady();

	UFUNCTION()
		void OnCancelSession();

	UFUNCTION()
		void OnSelectSessionMember();

	UFUNCTION()
		void OnFindSessionsComplete(bool bWasSuccessful);

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_ToggleReady();

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_TryStartGame();

public:	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	bool bInitialized;

	UPROPERTY(Replicated)
		bool bReadyInSession;

	UUserWidget* ActiveWidget;

	UPROPERTY()
		ULobbyWidget* LobbyWidget;

	UPROPERTY()
		UGroupMemberInfoWidget* GroupMemberInfoWidget;

	UPROPERTY()
		UMissionInfoWidget* MissionInfoWidget;

	UPROPERTY()
		UChatWidget* ChatWidget;

	UPROPERTY()
		UChatInfoWidget* ChatInfoWidget;

	UPROPERTY()
		UFindSessionWidget* FindSessionWidget;

	UPROPERTY()
		USessionInfoWidget* SessionInfoWidget;

	UPROPERTY()
		UCreateSessionWidget* CreateSessionWidget;

	UPROPERTY()
		USessionWidget* SessionWidget;

	UPROPERTY()
		URoomMemberInfoWidget* RoomMemberInfoWidget;
};
