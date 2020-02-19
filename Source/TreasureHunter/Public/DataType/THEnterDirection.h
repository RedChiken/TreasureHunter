// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "THEnterDirection.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EEnterDirection : uint8
{
	TOP		UMETA(DisplayName = "Top"),
	MIDDLE	UMETA(DisplayName = "Middle"),
	BOTTOM	UMETA(DisplayName = "Bottom"),
	DEFAULT	UMETA(DisplayName = "Default")
};

UCLASS()
class TREASUREHUNTER_API UTHEnterDirection : public UUserDefinedEnum
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = enum)
		EEnterDirection EnterDirection;
};
