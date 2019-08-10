// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Online.h"
#include "UnrealNetwork.h"
#include "TreasureHunter.h"
#include "THGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API UTHGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	void DestroySessionAndLeaveGame();

protected:
	
private:
	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;
};
