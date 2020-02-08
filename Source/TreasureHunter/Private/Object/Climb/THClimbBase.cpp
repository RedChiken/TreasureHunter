// Fill out your copyright notice in the Description page of Project Settings.


#include "THClimbBase.h"
#include "THCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "DataType/THEnterDirection.h"
#include "DataType/THExitDirection.h"
#include "DataType/THMovementType.h"

ATHClimbBase::ATHClimbBase() : ATHActorBase()
{
	UpsideArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Upside"));
	DownsideArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Downside"));
	UpsideArea->SetupAttachment(RootComponent);
	DownsideArea->SetupAttachment(RootComponent);
	UpsideArea->SetBoxExtent(FVector(120.0f, 120.0f, 30.0f));
	DownsideArea->SetBoxExtent(FVector(120.0f, 120.0f, 30.0f));
	UpsideArea->SetCollisionProfileName("Trigger");
	DownsideArea->SetCollisionProfileName("Trigger");
	UpsideArea->OnComponentBeginOverlap.AddDynamic(this, &ATHClimbBase::OnClimbAtTop);
	DownsideArea->OnComponentBeginOverlap.AddDynamic(this, &ATHClimbBase::OnClimbAtBottom);
	InteractionRange->OnComponentBeginOverlap.AddDynamic(this, &ATHClimbBase::OnClimbAtMiddle);
}

void ATHClimbBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ATHClimbBase::OnClimbAtTop(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherComp)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		auto Comp = Cast<UBoxComponent>(OtherComp);
		auto Collision = OtherComp->GetCollisionProfileName();
		if (Character && (Collision == FName(TEXT("NormalHitBox"))))
		{
			switch (Character->getEnterDirection())
			{
			case(EEnterDirection::TOP):
				//위에서 사다리 탔다가 다시 위로 나옴
				break;
			case(EEnterDirection::DEFAULT):
				//위에서 사다리 타려고 함.
				break;
			case(EEnterDirection::BOTTOM):
				//밑에서 사다리 탔다가 위로 나옴
				break;
			}
		}
	}
}

void ATHClimbBase::OnClimbAtBottom(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherComp)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		auto Comp = Cast<UBoxComponent>(OtherComp);
		auto Collision = OtherComp->GetCollisionProfileName();
		if (Character && (Collision == FName(TEXT("NormalHitBox"))))
		{
			switch (Character->getEnterDirection())
			{
			case(EEnterDirection::TOP):
				//밑에서 사다리 탔다가 위로 나옴
				break;
			case(EEnterDirection::DEFAULT):
				//밑에서 사다리 타려고 함.
				break;
			case(EEnterDirection::BOTTOM):
				//밑에서 사다리 탔다가 다시 밑으로 나옴
				break;
			}

		}
	}
}

void ATHClimbBase::OnClimbAtMiddle(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherComp)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		auto Comp = Cast<UBoxComponent>(OtherComp);
		auto Collision = OtherComp->GetCollisionProfileName();
		if (Character && (Collision == FName(TEXT("NormalHitBox"))))
		{
			//어느 상황이든 사다리 중간에 매달리기.
		}
	}
}
