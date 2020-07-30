// Fill out your copyright notice in the Description page of Project Settings.


#include "THLatchBase.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "THCharacterBase.h"
#include "THPieceBase.h"
#include "TreasureHunter.h"

ATHLatchBase::ATHLatchBase() : ATHActorBase()
{
	Object->SetCollisionProfileName("BlockAll");
}

void ATHLatchBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHLatchBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHLatchBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHLatchBase, Input);
	DOREPLIFETIME(ATHLatchBase, Answer);
}

void ATHLatchBase::ServerUpdateInput_Implementation(const FString& input)
{
	MulticastUpdateInput(input);
}

bool ATHLatchBase::ServerUpdateInput_Validate(const FString& input)
{
	return true;
}

void ATHLatchBase::MulticastUpdateInput_Implementation(const FString& input)
{
	Input = input;
}

void ATHLatchBase::ServerUpdateAnswer_Implementation(const FString& input)
{
	MulticastUpdateAnswer(input);
}

bool ATHLatchBase::ServerUpdateAnswer_Validate(const FString& input)
{
	return true;
}

void ATHLatchBase::MulticastUpdateAnswer_Implementation(const FString& input)
{
	Answer = input;
}

bool ATHLatchBase::IsCorrect()
{
	return Input.Compare(Answer) == 0;
}

void ATHLatchBase::Submit(const FString& input)
{
	ServerUpdateInput(input);
}

void ATHLatchBase::ResetInput()
{
	ServerUpdateInput(FString());
}

void ATHLatchBase::ResetAnswer()
{
	ServerUpdateAnswer(FString());
}

void ATHLatchBase::InitializeAnswer(const FString& input)
{
	ServerUpdateAnswer(input);
}
