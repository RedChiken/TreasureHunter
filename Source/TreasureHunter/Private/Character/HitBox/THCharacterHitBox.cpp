// Fill out your copyright notice in the Description page of Project Settings.


#include "THCharacterHitBox.h"

UTHCharacterHitBox::UTHCharacterHitBox() : UCapsuleComponent()
{
	damage = 0;
	SetIsReplicated(true);
	//TODO: add getreplicatedprops and replicate damage
}

const float UTHCharacterHitBox::GetDamage()
{
	return damage;
}

void UTHCharacterHitBox::UpdateDamage(const float& Damage)
{
	damage = Damage;
}
