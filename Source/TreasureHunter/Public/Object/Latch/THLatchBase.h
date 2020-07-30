// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/THActorBase.h"
#include "Interface/CheckAnswer.h"
#include "THLatchBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCorrectAnswer);

UCLASS()
class TREASUREHUNTER_API ATHLatchBase : public ATHActorBase, public ICheckAnswer
{
	GENERATED_BODY()
public:
    ATHLatchBase();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
    UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
        void ServerUpdateInput(const FString& input);

    UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
        void ServerUpdateAnswer(const FString& input);

protected:
    UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
        void MulticastUpdateInput(const FString& input);

    UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
        void MulticastUpdateAnswer(const FString& input);


public:
    // Inherited via ICheckAnswer
    virtual bool IsCorrect() override;
    virtual void Submit(const FString& input) override;
    virtual void ResetInput() override;
    virtual void ResetAnswer() override;
    virtual void InitializeAnswer(const FString& input) override;

public:
    UPROPERTY(BlueprintAssignable)
        FOnCorrectAnswer OnCorrectAnswer;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = InRange)
        FString Input;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = InRange)
        FString Answer;
};
