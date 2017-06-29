// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "LimbusGameState.generated.h"

/**
 * 
 */
UCLASS()
class LIMBUS_API ALimbusGameState : public AGameState
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int stageLevel;
	// 폰 리스트, 맵 객체들 리스트 관리 어떻게 할까?
protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<int> mapSize = { 11, 13, 13, 17, 17, 17, 19 };
	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> mapArray = {
		FVector(46870.371094, 58651.636719, 0.0),
		FVector(11423.077148, 52063.960938, 100.0),
		FVector(-43961.539063, -51551.167969, 100.0),
		FVector(9125.0, -53995.886719, 200.0),
		FVector(-33062.5, 35860.753906, 200.0),
		FVector(-47125.0, 22648.058594, 200.0),
		FVector(-19750.0, -52071.0625, 300.0)
	};
};
