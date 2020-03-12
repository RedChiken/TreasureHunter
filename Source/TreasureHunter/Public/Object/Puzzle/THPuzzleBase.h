// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/THActorBase.h"
#include "THPuzzleBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHPuzzleBase : public ATHActorBase
{
	GENERATED_BODY()
public:
    ATHPuzzleBase();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

    UFUNCTION(BlueprintCallable)
        void InitializeKey(int index, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator, FVector Scale = FVector(1.0f, 1.0f, 1.0f));

    UFUNCTION(BlueprintCallable)
        bool CheckAnswer();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Key)
        TArray<class ATHPieceBase*> KeyObject;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Key)
        TArray<int32> Input;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Key)
        TArray<int32> Answer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Key)
        UChildActorComponent* Trap;
};
