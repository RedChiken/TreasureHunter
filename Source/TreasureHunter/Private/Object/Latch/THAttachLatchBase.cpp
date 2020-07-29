// Fill out your copyright notice in the Description page of Project Settings.


#include "THAttachLatchBase.h"
#include "Interface/Attachable.h"

ATHAttachLatchBase::ATHAttachLatchBase() : ATHLatchBase()
{

}

void ATHAttachLatchBase::Tick(float DeltaTime)
{
}

void ATHAttachLatchBase::BeginPlay()
{
}

void ATHAttachLatchBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
}

bool ATHAttachLatchBase::IsAttachable(IAttachable* Input)
{
	return false;
}

bool ATHAttachLatchBase::IsDetachable()
{
	return false;
}

void ATHAttachLatchBase::Attach(IAttachable* Input)
{
}

IAttachable* ATHAttachLatchBase::Detach()
{
	return nullptr;
}
