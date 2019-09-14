// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "THMovementType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMovementType : uint8
{
	WALK	UMETA(DisplayName = "Walk"),
	SPRINT	UMETA(DisplayName = "Sprint"),
	CLIMB	UMETA(DisplayName = "Climb"),
	DEFAULT	UMETA(DisplayName = "Default")
};

UCLASS()
class TREASUREHUNTER_API UTHMovementType : public UUserDefinedEnum
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Enum)
		EMovementType MovementType;
};
