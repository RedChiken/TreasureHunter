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
    virtual bool IsAttachable(const class IAttachActivity* Attacher) override;
    virtual void Attach(AActor* Parent, const FAttachmentTransformRules& AttachmentRules, FName SocketName = NAME_None) override;
    virtual void Attach(USceneComponent* Parent, const FAttachmentTransformRules& AttachmentRules, FName SocketName = NAME_None) override;
    virtual void Detach(const FDetachmentTransformRules& DetachmentRules) override;
};
