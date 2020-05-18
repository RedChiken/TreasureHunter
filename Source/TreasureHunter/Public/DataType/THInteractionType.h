// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "THInteractionType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	ATTACH			UMETA(DisplayName = "Attach"),
	CLIMB			UMETA(DisplayName = "Climb"),
	INVESTIGATE		UMETA(DisplayName = "Investigate"),
	DEFAULT			UMETA(DisplayName = "Default")
};

UCLASS()
class TREASUREHUNTER_API UTHInteractionType : public UUserDefinedEnum
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = Enum)
		EInteractionType InteractionType;
};
