// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "THMovingDirection.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EMovingDirection : uint8 
{
	DEFAULT		UMETA(DisplayName = "Default"),
	FRONT		UMETA(DisplayName = "Front"),
	FRONTRIGHT	UMETA(DisplayName = "FrontRight"),
	RIGHT		UMETA(DisplayName = "Right"),
	BACKRIGHT	UMETA(DisplayName = "BackRight"),
	BACK		UMETA(DisplayName = "Back"), 
	BACKLEFT	UMETA(DisplayName = "BackLeft"),
	LEFT		UMETA(DisplayName = "Left"), 
	FRONTLEFT	UMETA(DisplayName = "FrontLeft"),
	UPSIDE		UMETA(DisplayName = "Up"),
	DOWNSIDE	UMETA(DisplayName = "Down")
};

UCLASS()
class TREASUREHUNTER_API UTHMovingDirection : public UUserDefinedEnum
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = enum)
		EMovingDirection MovingDirection;
};
