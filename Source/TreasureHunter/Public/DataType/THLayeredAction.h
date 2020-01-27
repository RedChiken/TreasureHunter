// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "THLayeredAction.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ELayeredAction : uint8
{
	MELEEATTACK		UMETA(DisplayName = "MeleeAttack"), 
	INTERACTION		UMETA(DisplayName = "Interaction"), 
	DEFAULT			UMETA(DisplayName = "Default")
};

UCLASS()
class TREASUREHUNTER_API UTHLayeredAction : public UUserDefinedEnum
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = Enum)
		ELayeredAction LayeredAction;
};
