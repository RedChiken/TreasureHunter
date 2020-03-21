// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "THAttachSequence.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAttachSequence : uint8
{
	ATTACHABLE		UMETA(DisplayName = "Attachable"),
	ATTACH			UMETA(DisplayName = "Attach"),
	SUBMITTABLE		UMETA(DisplayName = "Submittable"),
	DEFAULT			UMETA(DisplayName = "Default")
};

UCLASS()
class TREASUREHUNTER_API UTHAttachSequence : public UUserDefinedEnum
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = Enum)
		EAttachSequence AttachSequence;
	
};
