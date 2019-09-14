// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "THExitDirection.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EExitDirection : uint8 
{
	BOTTOM	UMETA(DisplayName = "Bottom"),
	TOP		UMETA(DisplayName = "Top"),
	DEFAULT	UMETA(DisplayName = "Default")
};

UCLASS()
class TREASUREHUNTER_API UTHExitDirection : public UUserDefinedEnum
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = enum)
		EExitDirection ExitDirection;
};
