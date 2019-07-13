// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "THClassType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EClassType : uint8 {
	DEFAULT			UMETA(DisplayName = "Default"),
	ARMY			UMETA(DisplayName = "Army"),
	BEASTTAMER		UMETA(DisplayName = "BeastTamer"),
	BREEDER			UMETA(DisplayName = "Breeder"),
	CARTOGRAPHER	UMETA(DisplayName = "Cartographer"),
	DEFENDER		UMETA(DisplayName = "Defender"),
	DIGGER			UMETA(DisplayName = "Digger"),
	HALLUCINATOR	UMETA(DisplayName = "Hallucinator"),
	HOWLER			UMETA(DisplayName = "Howler"),
	POINTMOVER		UMETA(DisplayName = "PointMover"),
	RAMPLIGHTER		UMETA(DisplayName = "RampLighter"),
	RESURRECTIONIST	UMETA(DisplayName = "Resurrectionist"),
	SHOOTER			UMETA(DisplayName = "Shooter"),
	STALKER			UMETA(DisplayName = "Stalker"),
	TRAPPER			UMETA(DisplayName = "Trapper")
};

UCLASS()
class TREASUREHUNTER_API UTHClassType : public UUserDefinedEnum
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = Enum)
		EClassType ClassType;
};
