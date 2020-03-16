// Fill out your copyright notice in the Description page of Project Settings.


#include "THPuzzleBase.h"
#include "THPieceBase.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"

ATHPuzzleBase::ATHPuzzleBase() : ATHActorBase()
{
	Trap = CreateDefaultSubobject<UChildActorComponent>(TEXT("Trap"));
	Trap->SetupAttachment(RootComponent);
}

void ATHPuzzleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHPuzzleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATHPuzzleBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHPuzzleBase, KeyObject);
	DOREPLIFETIME(ATHPuzzleBase, Input);
	DOREPLIFETIME(ATHPuzzleBase, Answer);
	DOREPLIFETIME(ATHPuzzleBase, Trap);
}

void ATHPuzzleBase::ActivateAllKey()
{
	for (int i = 0; i < KeyObject.Num(); ++i)
	{
		KeyObject[i]->ActivateKey();
	}
}

void ATHPuzzleBase::DeactivateAllKey()
{
	for (int i = 0; i < KeyObject.Num(); ++i)
	{
		KeyObject[i]->DeactivateKey();
	}
}

bool ATHPuzzleBase::CheckAnswer()
{
	bool ret = (Input.Num() == Answer.Num());
	if (ret)
	{
		for (int index = 0; ret && (index < Input.Num()); ++index)
		{
			ret = (Input[index] == Answer[index]);
		}
	}
	return ret;
}
