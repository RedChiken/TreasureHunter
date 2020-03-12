// Fill out your copyright notice in the Description page of Project Settings.


#include "THPuzzleBase.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "THPieceBase.h"

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

void ATHPuzzleBase::InitializeKey(int index, FVector Location, FRotator Rotation, FVector Scale)
{
	KeyObject[index]->InitializeIndex(index);
	KeyObject[index]->SetActorLocationAndRotation(Location, Rotation);
	KeyObject[index]->SetActorScale3D(Scale);
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
