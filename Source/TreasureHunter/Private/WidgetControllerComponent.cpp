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
#include "Widget/SessionWidget.h"
#include "Widget/RoomMemberInfoWidget.h"

#include "LobbyGameMode.h"
#include "LobbyPlayerController.h"
#include "Kismet/GameplayStatics.h"
// Sets default values for this component's properties
UWidgetControllerComponent::UWidgetControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UWidgetControllerComponent::InitializeUI(ULobbyWidget * LobbyWidget, UGroupMemberInfoWidget * GroupMembberInfoWidget, UMissionInfoWidget * MissionInfoWidget, UChatWidget * ChatWidget, UChatInfoWidget * ChatInfoWidget, UFindSessionWidget * FindSessionWidget, USessionInfoWidget * SessionInfoWidget, UCreateSessionWidget * CreateSessionWidget, USessionWidget * SessionWidget, URoomMemberInfoWidget * RoomMemerInfoWidget)
{
}

void UWidgetControllerComponent::Client_ShowSessionWidget_Implementation()
{
}

void UWidgetControllerComponent::Client_UpdateSessionMemberDisplay_Implementation(const TArray<FRoomMemberInfo>& RoomMemberInfoArray)
{
}

void UWidgetControllerComponent::Client_SetReadyButtonVisual_Implementation(bool bisHost)
{
}

void UWidgetControllerComponent::ShowLobbyEntry()
{
}

void UWidgetControllerComponent::ShowSessionWidget()
{
}

inline bool UWidgetControllerComponent::IsReadyRoom() const
{
	return false;
}

void UWidgetControllerComponent::BindEventHandlers()
{
}

void UWidgetControllerComponent::ChangeWidget(UUserWidget * NewWidget)
{
}

ALobbyGameMode * UWidgetControllerComponent::GetLobbyGameMode() const
{
	return nullptr;
}

ALobbyPlayerController * UWidgetControllerComponent::GetLobbyPlayerController() const
{
	return nullptr;
}

void UWidgetControllerComponent::OnMenu()
{
}

void UWidgetControllerComponent::OnSkill()
{
}

void UWidgetControllerComponent::OnItem()
{
}

void UWidgetControllerComponent::OnFindMatch()
{
}

void UWidgetControllerComponent::OnNextCharacter()
{
}

void UWidgetControllerComponent::OnPreviewCharacter()
{
}

void UWidgetControllerComponent::OnNextSkin()
{
}

void UWidgetControllerComponent::OnPreviewSkin()
{
}

void UWidgetControllerComponent::OnSelectGroupMember()
{
}

void UWidgetControllerComponent::OnSelectMission()
{
}

void UWidgetControllerComponent::OnSendMessage(FString Message)
{
}

void UWidgetControllerComponent::OnTryConnect(int32 SessinIndex)
{
}

void UWidgetControllerComponent::OnOpenCreateSessionWidget()
{
}

void UWidgetControllerComponent::OnCancelConnect()
{
}

void UWidgetControllerComponent::OnSelectSession()
{
}

void UWidgetControllerComponent::OnCreateSession(FString HostName, int32 MaxPlayer)
{
}

void UWidgetControllerComponent::OnCancelCreateSession()
{
}

void UWidgetControllerComponent::OnToggleReady()
{
}

void UWidgetControllerComponent::OnCancelSession()
{
}

void UWidgetControllerComponent::OnSelectRoomMember()
{
}

void UWidgetControllerComponent::OnFindSessionsComplete(bool bWasSuccessful)
{
}

void UWidgetControllerComponent::Server_ToggleReady_Implementation()
{
}

bool UWidgetControllerComponent::Server_ToggleReady_Validate()
{
	return true;
}

void UWidgetControllerComponent::Server_TryStartGame_Implementation()
{
}

bool UWidgetControllerComponent::Server_TryStartGame_Implementation()
{
	return true;
}

void UWidgetControllerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
}
