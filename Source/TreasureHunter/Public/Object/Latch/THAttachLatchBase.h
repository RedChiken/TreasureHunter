// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Latch/THLatchBase.h"
#include "Interface/AttachActivity.h"
#include "THAttachLatchBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHAttachLatchBase : public ATHLatchBase, public IAttachActivity
{
	GENERATED_BODY()

public:
	ATHAttachLatchBase();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
	virtual bool IsAttachable(class IAttachable* Input) override;
	virtual bool IsDetachable() override;
	virtual void Attach(class IAttachable* Input) override;
	virtual class IAttachable* Detach() override;
};
