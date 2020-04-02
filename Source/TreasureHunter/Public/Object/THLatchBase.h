// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/THActorBase.h"
#include "THLatchBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCorrectAnswer);

UCLASS()
class TREASUREHUNTER_API ATHLatchBase : public ATHActorBase
{
	GENERATED_BODY()
public:
    ATHLatchBase();

    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
        void InitializeIndex(int32 index);

    UFUNCTION(BlueprintCallable)
        void SubmitPiece(class ATHPieceBase* Piece);

    UFUNCTION(BlueprintCallable)
        ATHPieceBase* WithdrawPiece();

    UFUNCTION(BlueprintCallable)
        ATHPieceBase* GetPiece();

    UFUNCTION(BlueprintCallable)
        int32 GetIndex();

    UFUNCTION(BlueprintCallable)
        bool IsCorrectPair();

    UFUNCTION(Blueprintcallable)
        void Activate();

    UFUNCTION(Blueprintcallable)
        void Deactivate();

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
    UPROPERTY(BlueprintAssignable)
        FOnCorrectAnswer OnCorrectAnswer;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Key)
        int32 Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Key)
        class ATHPieceBase* AttachedPiece;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Key)
        FVector AttachLocation;
};
