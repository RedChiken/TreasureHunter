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
	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerAttachPiece(class ATHAttachPieceBase* AttachPiece);

	UFUNCTION(Server, BlueprintCallable, Reliable, WithValidation)
		void ServerDetachPiece(class ATHPieceBase* AttPiece, class ATHAttachPieceBase* RetPiece);

protected:
	UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
		void MulticastAttachPiece(class ATHAttachPieceBase* AttachPiece);

	UFUNCTION(NetMulticast, BlueprintCallable, Reliable)
		void MulticastDetachPiece(class ATHPieceBase* AttPiece, class ATHAttachPieceBase* RetPiece);
	
public:
	virtual bool IsAttachable(class IAttachable* attach) override;
	virtual bool IsDetachable() override;
	virtual void Attach(class IAttachable* attach, IAttachActivity* Attacher) override;
	virtual class IAttachable* Detach() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Piece)
		class ATHPieceBase* Piece;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Piece)
		FVector AttachedPosition;
};
