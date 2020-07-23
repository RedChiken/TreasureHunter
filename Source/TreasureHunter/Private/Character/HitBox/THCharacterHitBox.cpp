// Fill out your copyright notice in the Description page of Project Settings.


#include "THCharacterHitBox.h"
#include "net/UnrealNetwork.h"
#include "Engine.h"

UTHCharacterHitBox::UTHCharacterHitBox() : UCapsuleComponent()
{
	SetIsReplicated(true);
	damage = 0;
	bAbletoHit = false;
}

void UTHCharacterHitBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UTHCharacterHitBox, damage);
	DOREPLIFETIME(UTHCharacterHitBox, bAbletoHit);
}

bool UTHCharacterHitBox::getAbletoHit()
{
	return bAbletoHit;
}

const float UTHCharacterHitBox::GetDamage()
{
	return damage;
}

void UTHCharacterHitBox::UpdateDamage(const float& Damage)
{
	damage = Damage;
}

void UTHCharacterHitBox::Activate()
{
	bAbletoHit = true;
}

void UTHCharacterHitBox::InActivate()
{
	bAbletoHit = false;
}

void UTHCharacterHitBox::Reset()
{
}
