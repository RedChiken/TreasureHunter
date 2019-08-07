// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetControllerComponent.h"
#include "Widget/LobbyWidget.h"
#include "Widget/GroupMemberInfoWidget.h"
#include "Widget/MissionInfoWidget.h"
#include "Widget/ChatWidget.h"
#include "Widget/ChatInfoWidget.h"
#include "Widget/FindSessionWidget.h"
#include "Widget/SessionWidget.h"
#include "Widget/CreateSessionWidget.h"
#include "Widget/SessionInfoWidget.h"
#include "Widget/RoomMemberInfoWidget.h"
#include "THGameInstance.h"
#include "TreasureHunter.h"

#include "LobbyGameMode.h"
#include "LobbyPlayerController.h"
#include "Kismet/GameplayStatics.h"
// Sets default values for this component's properties
UWidgetControllerComponent::UWidgetControllerComponent() : ActiveWidget(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
}

void UWidgetControllerComponent::InitializeUI(
	ULobbyWidget *				InLobbyWidget, 
	UGroupMemberInfoWidget *	InGroupMemberInfoWidget,
	UMissionInfoWidget *		InMissionInfoWidget,
	UChatWidget *				InChatWidget,
	UChatInfoWidget *			InChatInfoWidget,
	UFindSessionWidget *		InFindSessionWidget,
	USessionInfoWidget *		InSessionInfoWidget,
	UCreateSessionWidget *		InCreateSessionWidget,
	USessionWidget *			InSessionWidget,
	URoomMemberInfoWidget *		InRoomMemerInfoWidget)
{
	ensure(bInitialized == false);
	bInitialized = true;

	ensureMsgf(InLobbyWidget, TEXT("LobbyWidget is null"));
	ensureMsgf(InGroupMemberInfoWidget, TEXT("GroupMembberInfoWidget is null"));
	ensureMsgf(InMissionInfoWidget, TEXT("MissionInfoWidget is null"));
	ensureMsgf(InChatWidget, TEXT("ChatWidget is null"));
	ensureMsgf(InChatInfoWidget, TEXT("ChatInfoWidget is null"));
	ensureMsgf(InFindSessionWidget, TEXT("FindSessionWidget is null"));
	ensureMsgf(InSessionInfoWidget, TEXT("SessionInfoWidget is null"));
	ensureMsgf(InCreateSessionWidget, TEXT("CreateSessionWidget is null"));
	ensureMsgf(InSessionWidget, TEXT("SessionWidget is null"));
	ensureMsgf(InRoomMemerInfoWidget, TEXT("RoomMemberInfoWidget is null"));

	LobbyWidget = InLobbyWidget;
	GroupMemberInfoWidget = InGroupMemberInfoWidget;
	MissionInfoWidget = InMissionInfoWidget;
	ChatWidget = InChatWidget;
	ChatInfoWidget = InChatInfoWidget;
	FindSessionWidget = InFindSessionWidget;
	SessionInfoWidget = InSessionInfoWidget;
	CreateSessionWidget = InCreateSessionWidget;
	SessionWidget = InSessionWidget;
	RoomMemberInfoWidget = InRoomMemerInfoWidget;

	BindEventHandlers();
	ChangeWidget(LobbyWidget);
}

void UWidgetControllerComponent::Client_ShowSessionWidget_Implementation()
{
	ShowSessionWidget();
}

void UWidgetControllerComponent::Client_UpdateSessionMemberDisplay_Implementation(const TArray<FSessionMemberInfo>& RoomMemberInfoArray)
{
	SessionWidget->UpdateRoomMemberList(RoomMemberInfoArray);
}

void UWidgetControllerComponent::Client_SetReadyButtonVisual_Implementation(bool bisHost)
{
	SessionWidget->SetReadyButtonVisual(bisHost);
}

void UWidgetControllerComponent::ShowLobbyWidget()
{
	ChangeWidget(LobbyWidget);
}

void UWidgetControllerComponent::ShowSessionWidget()
{
	ChangeWidget(SessionWidget);
}

inline bool UWidgetControllerComponent::IsReadyInSession() const
{
	return bReadyInSession;
}

void UWidgetControllerComponent::BindEventHandlers()
{
	if (LobbyWidget) {
		LobbyWidget->OnMenu.AddDynamic(this, &UWidgetControllerComponent::OnMenu);
		LobbyWidget->OnSkill.AddDynamic(this, &UWidgetControllerComponent::OnSkill);
		LobbyWidget->OnItem.AddDynamic(this, &UWidgetControllerComponent::OnItem);
		LobbyWidget->OnFindMatch.AddDynamic(this, &UWidgetControllerComponent::OnFindMatch);
		LobbyWidget->OnNextCharacter.AddDynamic(this, &UWidgetControllerComponent::OnNextCharacter);
		LobbyWidget->OnPreviewCharacter.AddDynamic(this, &UWidgetControllerComponent::OnPreviewCharacter);
		LobbyWidget->OnNextSkin.AddDynamic(this, &UWidgetControllerComponent::OnNextSkin);
		LobbyWidget->OnPreviewSkin.AddDynamic(this, &UWidgetControllerComponent::OnPreviewSkin);

		GroupMemberInfoWidget->OnSelectGroupMember.AddDynamic(this, &UWidgetControllerComponent::OnSelectGroupMember);

		MissionInfoWidget->OnSelectMission.AddDynamic(this, &UWidgetControllerComponent::OnSelectMission);

		ChatWidget->OnSendMessage.AddDynamic(this, &UWidgetControllerComponent::OnSendMessage);
	}
	if (FindSessionWidget) {
		FindSessionWidget->OnTryConnect.AddDynamic(this, &UWidgetControllerComponent::OnTryConnect);
		FindSessionWidget->OnOpenCreateSessionWidget.AddDynamic(this, &UWidgetControllerComponent::OnOpenCreateSessionWidget);
		FindSessionWidget->OnCancelConnect.AddDynamic(this, &UWidgetControllerComponent::OnCancelConnect);
	}
	if (CreateSessionWidget) {
		CreateSessionWidget->OnCreateSession.AddDynamic(this, &UWidgetControllerComponent::OnCreateSession);
		CreateSessionWidget->OnCancelCreateSession.AddDynamic(this, &UWidgetControllerComponent::OnCancelCreateSession);
	}
	if (SessionWidget) {
		SessionWidget->OnToggleReady.AddDynamic(this, &UWidgetControllerComponent::OnToggleReady);
		SessionWidget->OnCancelSession.AddDynamic(this, &UWidgetControllerComponent::OnCancelSession);
		RoomMemberInfoWidget->OnSelectSessionMember.AddDynamic(this, &UWidgetControllerComponent::OnSelectSessionMember);
	}
}

void UWidgetControllerComponent::ChangeWidget(UUserWidget * NewWidget)
{
	if (ActiveWidget) {
		ActiveWidget->RemoveFromParent();
		ActiveWidget->SetIsEnabled(false);
	}

	NewWidget->AddToPlayerScreen();
	NewWidget->SetIsEnabled(true);
	
	ActiveWidget = NewWidget;
}

ALobbyGameMode * UWidgetControllerComponent::GetLobbyGameMode() const
{
	return Cast<ALobbyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

ALobbyPlayerController * UWidgetControllerComponent::GetLobbyPlayerController() const
{
	return Cast<ALobbyPlayerController>(GetOwner());
}

void UWidgetControllerComponent::OnMenu()
{
	UE_LOG(LogTemp, Log, TEXT("%hs: Open Menu"), __FUNCTION__);
}

void UWidgetControllerComponent::OnSkill()
{
	UE_LOG(LogTemp, Log, TEXT("%hs: Open Skill Widget"), __FUNCTION__);
}

void UWidgetControllerComponent::OnItem()
{
	UE_LOG(LogTemp, Log, TEXT("%hs: Open Item Widget"), __FUNCTION__);
}

void UWidgetControllerComponent::OnFindMatch()
{
	//OnSelectConnect
	auto* GameMode = GetLobbyGameMode();
	auto* PC = GetLobbyPlayerController();

	if (GameMode && PC) {
		GameMode->GetOnFindSessionsComplete().AddUObject(this, &UWidgetControllerComponent::OnFindSessionsComplete);

		constexpr bool bIsLAN = false;
		constexpr bool bIsPresence = false;
		GameMode->FindSessions(PC->GetLocalPlayer()->GetPreferredUniqueNetId().GetUniqueNetId(), bIsLAN, bIsPresence);

		FindSessionWidget->DisplaySearchingState();
		ChangeWidget(FindSessionWidget);
	}
	else{
		UE_LOG(LogTemp, Log, TEXT("%hs: GameMode or PlayerController is invalid"), __FUNCTION__);
	}
}

void UWidgetControllerComponent::OnNextCharacter()
{
	UE_LOG(LogTemp, Log, TEXT("%hs: Change to Next Character"), __FUNCTION__);
}

void UWidgetControllerComponent::OnPreviewCharacter()
{
	UE_LOG(LogTemp, Log, TEXT("%hs: Change to Preview Character"), __FUNCTION__);
}

void UWidgetControllerComponent::OnNextSkin()
{
	UE_LOG(LogTemp, Log, TEXT("%hs: Change to Next Skin"), __FUNCTION__);
}

void UWidgetControllerComponent::OnPreviewSkin()
{
	UE_LOG(LogTemp, Log, TEXT("%hs: Change to Preview Skin"), __FUNCTION__);
}

void UWidgetControllerComponent::OnSelectGroupMember()
{
	UE_LOG(LogTemp, Log, TEXT("%hs: Open Character Info Widget"), __FUNCTION__);
}

void UWidgetControllerComponent::OnSelectMission()
{
	UE_LOG(LogTemp, Log, TEXT("%hs: Open Mission Info WIdget"), __FUNCTION__);
}

void UWidgetControllerComponent::OnSendMessage(FString Message)
{
	UE_LOG(LogTemp, Log, TEXT("%hs: Send message"), __FUNCTION__);
}

void UWidgetControllerComponent::OnTryConnect(int32 SessionIndex)
{
	auto GameMode = GetLobbyGameMode();
	auto PC = GetLobbyPlayerController();
	const auto& Results = GameMode->GetSessionSearch()->SearchResults;

	if (GameMode && PC && Results.IsValidIndex(SessionIndex)) {
		const auto& NetId = PC->GetLocalPlayer()->GetPreferredUniqueNetId().GetUniqueNetId();
		GameMode->JoinSession(NetId, GameSessionName, Results[SessionIndex]);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%hs: Invalid SessionIndex (%d)"), __FUNCTION__, SessionIndex);
	}
}

void UWidgetControllerComponent::OnOpenCreateSessionWidget()
{
	ChangeWidget(CreateSessionWidget);
}

void UWidgetControllerComponent::OnCancelConnect()
{
	ChangeWidget(LobbyWidget);
}

void UWidgetControllerComponent::OnCreateSession(FString HostName, int32 MaxPlayer)
{
	auto* GameMode = GetLobbyGameMode();
	auto* PC = GetLobbyPlayerController();

	if (GameMode && PC) {
		const auto& NetId = PC->GetLocalPlayer()->GetPreferredUniqueNetId().GetUniqueNetId();
		constexpr bool bIsLAN = false;
		constexpr bool bIsPresence = false;
		GameMode->HostSession(NetId, GameSessionName, bIsLAN, bIsPresence, MaxPlayer);
	}
}

void UWidgetControllerComponent::OnCancelCreateSession()
{
	ChangeWidget(FindSessionWidget);
}

void UWidgetControllerComponent::OnToggleReady()
{
	if (GetNetMode() == NM_Client) {
		Server_ToggleReady();
	}
	else {
		Server_TryStartGame();
	}
}

void UWidgetControllerComponent::OnCancelSession()
{
	auto GI = GetWorld()->GetGameInstance<UTHGameInstance>();
	GI->DestroySessionAndLeaveGame();
}

void UWidgetControllerComponent::OnSelectSessionMember()
{
	UE_LOG(LogTemp, Log, TEXT("%hs: Show Session Member"), __FUNCTION__);
}

void UWidgetControllerComponent::OnFindSessionsComplete(bool bWasSuccessful)
{
	auto* GameMode = GetLobbyGameMode();
	if (GameMode) {
		TArray<FSessionInfo> SessionInfo;
		UE_LOG(LogTemp, Log, TEXT("%hs: Success to Find Sessions"), __FUNCTION__);

		for (const auto& Result : GameMode->GetSessionSearch()->SearchResults) {
			FSessionInfo Info;
			Info.HostName = Result.Session.OwningUserName;
			SessionInfo.Emplace(Info);
		}

		FindSessionWidget->UpdateRoomList(SessionInfo);
	}
	else{
		UE_LOG(LogTemp, Log, TEXT("%hs: Fail to Find Sessions"), __FUNCTION__);
	}
}

void UWidgetControllerComponent::Server_ToggleReady_Implementation()
{
	bReadyInSession = !bReadyInSession;
	if (auto GameMode = GetLobbyGameMode()) {
		GameMode->UpdateSessionMemberInfo();
	}
}

bool UWidgetControllerComponent::Server_ToggleReady_Validate()
{
	return true;
}

void UWidgetControllerComponent::Server_TryStartGame_Implementation()
{
	if (auto GameMode = GetLobbyGameMode()) {
		//TODO: Change temp_Name to Game Level
		GameMode->TryStartGame(FString("StageLevel"));
	}
}

bool UWidgetControllerComponent::Server_TryStartGame_Validate()
{
	return true;
}

void UWidgetControllerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWidgetControllerComponent, bReadyInSession);
}
