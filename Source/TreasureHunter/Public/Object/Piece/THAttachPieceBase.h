// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Piece/THPieceBase.h"
#include "Interface/Attachable.h"
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
    virtual bool IsAttachable() override;
    virtual bool HasAuthorize(const class IAttachActivity* Attacher) override;
};
