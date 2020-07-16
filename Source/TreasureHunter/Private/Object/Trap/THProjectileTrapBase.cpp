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
	if (actor)
	{
		auto projectile = Cast<ATHProjectileBase>(actor);
		Super::ActivateActor(projectile);
		projectile->CollisionComponent->Activate(true);
		projectile->ServerFireInDirection(FVector(0.f, 1.f, 0.f));
		actor->SetActorEnableCollision(true);
		actor->SetActorHiddenInGame(false);
	}
}

void ATHProjectileTrapBase::InactivateActor(AActor* actor)
{
	if (actor)
	{
		auto projectile = Cast<ATHProjectileBase>(actor);
		Super::InactivateActor(projectile);
		projectile->CollisionComponent->Deactivate();
		actor->SetActorEnableCollision(false);
		actor->SetActorHiddenInGame(true);
	}
}
