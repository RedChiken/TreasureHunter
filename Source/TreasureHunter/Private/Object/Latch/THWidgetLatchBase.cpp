// Fill out your copyright notice in the Description page of Project Settings.


#include "THWidgetLatchBase.h"

ATHWidgetLatchBase::ATHWidgetLatchBase() : ATHLatchBase()
{

}

void ATHWidgetLatchBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHWidgetLatchBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHWidgetLatchBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

bool ATHWidgetLatchBase::IsCorrect()
{
	return false;
}
