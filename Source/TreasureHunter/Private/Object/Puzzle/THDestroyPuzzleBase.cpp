// Fill out your copyright notice in the Description page of Project Settings.


#include "THDestroyPuzzleBase.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "THCharacterBase.h"
#include "THPieceBase.h"

ATHDestroyPuzzleBase::ATHDestroyPuzzleBase() : ATHPuzzleBase()
{

}

void ATHDestroyPuzzleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHDestroyPuzzleBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHDestroyPuzzleBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

bool ATHDestroyPuzzleBase::CheckInput()
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

void ATHDestroyPuzzleBase::OnKeyGetHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			Answer.Add(Cast<ATHPieceBase>(HitComponent->GetOwner())->GetIndex());
			HitComponent->GetOwner()->Destroy();
		}
	}
}
