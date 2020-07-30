// Fill out your copyright notice in the Description page of Project Settings.


#include "THProjectileBase.h"
#include "Character/THCharacterBase.h"
#include "Interface/Damagable.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"

ATHProjectileBase::ATHProjectileBase() : ATHActorBase()
{
	SetReplicateMovement(true);
	SetReplicatingMovement(true);
	SetReplicates(true);
	CollisionComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	CollisionComponent->SetUpdatedComponent(Object);
	Object->SetCollisionProfileName(TEXT("Projectile"));
	Object->OnComponentHit.AddDynamic(this, &ATHProjectileBase::OnProjectileHit);
}

void ATHProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorHiddenInGame(bActive);
	//SetActorEnableCollision(!bActive);
	SetActorTickEnabled(!bActive);
}

void ATHProjectileBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHProjectileBase, CollisionComponent);
	DOREPLIFETIME(ATHProjectileBase, Damage);
}

void ATHProjectileBase::FireInDirection(FVector ShootDirection)
{
	//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, FString::Printf(TEXT("direction: %s, velocity: %s"), *ShootDirection.ToString(), *CollisionComponent->Velocity.ToString()));
	CollisionComponent->Velocity = ShootDirection * CollisionComponent->InitialSpeed;
	//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue, FString::Printf(TEXT("velocity: %s"), *CollisionComponent->Velocity.ToString()));
}

float ATHProjectileBase::GetDamageBP()
{
	return GetDamage();
}

void ATHProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Projectile Hit Actor"));
		IDamagable* Damagable = Cast<IDamagable>(OtherActor);
		if (Damagable)
		{
			Damagable->ReceiveDamage(Damage);
		}
		/*
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Projectile Hit Character"));
			Character->ReceiveDamage(Damage);
		}
		*/
	}
	ServerUpdatebActive(false);
	Destroy();
}

const float ATHProjectileBase::GetDamage()
{
	return Damage;
}

void ATHProjectileBase::UpdateDamage(const float& damage)
{
	ServerUpdateDamage(damage);
}

void ATHProjectileBase::ServerUpdateDamage_Implementation(float damage)
{
	MulticastUpdateDamage(damage);
}

bool ATHProjectileBase::ServerUpdateDamage_Validate(float damage)
{
	return true;
}

void ATHProjectileBase::MulticastUpdateDamage_Implementation(float damage)
{
	Damage = damage;
}

void ATHProjectileBase::ServerFireInDirection_Implementation(FVector ShootDirection)
{
	MulticastFireInDirection(ShootDirection);
}

bool ATHProjectileBase::ServerFireInDirection_Validate(FVector ShootDirection)
{
	return true;
}

void ATHProjectileBase::MulticastFireInDirection_Implementation(FVector ShootDirection)
{
	CollisionComponent->Velocity = ShootDirection * CollisionComponent->InitialSpeed;
}