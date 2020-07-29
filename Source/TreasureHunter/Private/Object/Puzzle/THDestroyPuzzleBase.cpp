// Fill out your copyright notice in the Description page of Project Settings.


#include "THDestroyPuzzleBase.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "THCharacterBase.h"

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

void ATHDestroyPuzzleBase::OnKeyGetHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			//Answer.Add(Cast<ATHPieceBase>(HitComponent->GetOwner())->GetIndex());
			//HitComponent->GetOwner()->Destroy();
		}
	}
}
