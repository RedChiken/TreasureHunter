// Fill out your copyright notice in the Description page of Project Settings.


#include "THProjectileTrapBase.h"
#include "Object/THProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ATHProjectileTrapBase::ATHProjectileTrapBase() : ATHSpawnTrapBase()
{
}

void ATHProjectileTrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHProjectileTrapBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHProjectileTrapBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ATHProjectileTrapBase::ActivateActor(AActor* actor)
{
	Super::ActivateActor(actor);
	auto projectile = Cast<ATHProjectileBase>(actor);
	projectile->CollisionComponent->Activate(true);
}

void ATHProjectileTrapBase::DeactivateActor(AActor* actor)
{
	Super::DeactivateActor(actor);
	auto projectile = Cast<ATHProjectileBase>(actor);
	projectile->CollisionComponent->Deactivate();
}
