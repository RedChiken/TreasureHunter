// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "THChatType.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EChatType : uint8 {
	NORMAL	UMETA(DisplayName = "Normal"),
	GROUP	UMETA(DisplayName = "Group"),
	WHISPER	UMETA(DisplayName = "Whisper")
};

UCLASS()
class TREASUREHUNTER_API UTHChatType : public UUserDefinedEnum
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = Enum)
		EChatType ChatType;
	
};
