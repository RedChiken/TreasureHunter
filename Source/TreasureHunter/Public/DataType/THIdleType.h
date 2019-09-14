// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "THIdleType.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EIdleType : uint8
{
	STAND	UMETA(DisplayName = "Stand"),
	CROUCH	UMETA(DisplayName = "Crouch"), 
	LADDER	UMETA(DisplayName = "Ladder"),
	ROPE	UMETA(DisplayName = "Rope"),
	WALL	UMETA(DisplayName = "Wall"), 
	DEFAULT	UMETA(DisplayName = "Default")
};

UCLASS()
class TREASUREHUNTER_API UTHIdleType : public UUserDefinedEnum
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = Enum)
		EIdleType IdleType;
};
