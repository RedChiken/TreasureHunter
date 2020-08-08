// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Piece/THPieceBase.h"
#include "Interface/Attachable.h"
#include "Engine/EngineTypes.h"
#include "THAttachPieceBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHAttachPieceBase : public ATHPieceBase, public IAttachable
{
	GENERATED_BODY()

public:
    ATHAttachPieceBase();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
    UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
        void ServerEnableCollision();

    UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
        void ServerDisableCollision();

    UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
        void ServerVisualize();

    UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
        void ServerInvisualize();

    UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
        void MulticastEnableCollision();

    UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
        void MulticastDisableCollision();

    UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
        void MulticastVisualize();

    UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
        void MulticastInvisualize();

public:
    virtual bool IsAttachable(const class IAttachActivity* Attacher) override;
    virtual void Attach(AActor* Parent, const FAttachmentTransformRules& AttachmentRules, FName SocketName = NAME_None) override;
    virtual void Attach(USceneComponent* Parent, const FAttachmentTransformRules& AttachmentRules, FName SocketName = NAME_None) override;
    virtual void Detach(const FDetachmentTransformRules& DetachmentRules) override;
    virtual void Visualize() override;
    virtual void Invisualize() override;
    virtual void EnableCollision() override;
    virtual void DisableCollision() override;
};
