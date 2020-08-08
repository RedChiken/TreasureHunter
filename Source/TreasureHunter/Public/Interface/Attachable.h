// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/EngineTypes.h"
#include "Attachable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttachable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TREASUREHUNTER_API IAttachable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsAttachable(const class IAttachActivity* Attacher) = 0;
	virtual void Attach(AActor* ParentActor, const FAttachmentTransformRules& AttachmentRules, FName SocketName = NAME_None) = 0;
	virtual void Attach(USceneComponent* ParentActor, const FAttachmentTransformRules& AttachmentRules, FName SocketName = NAME_None) = 0;
	virtual void Detach(const FDetachmentTransformRules& DetachmentRules) = 0;
	virtual void Visualize() = 0;
	virtual void Invisualize() = 0;
	virtual void EnableCollision() = 0;
	virtual void DisableCollision() = 0;
};
