// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/THActorBase.h"
#include "THProjectileBase.generated.h"

/**
 * 
 */
UCLASS()
class TREASUREHUNTER_API ATHProjectileBase : public ATHActorBase
{
	GENERATED_BODY()

public:
    ATHProjectileBase();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
    UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
        void ServerUpdateDamage(float damage);

    UFUNCTION(NetMulticast, Reliable)
        void MulticastUpdateDamage(float damage);

    UFUNCTION(BlueprintCallable)
        void FireInDirection(FVector ShootDirection);

    UFUNCTION(BlueprintCallable)
        float GetDamage();

protected:
    UFUNCTION(BlueprintCallable)
        void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Projectile)
        class UProjectileMovementComponent* CollisionComponent;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Damage)
        float Damage;
    
};
