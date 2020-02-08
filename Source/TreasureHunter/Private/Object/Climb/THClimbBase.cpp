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
				//������ ��ٸ� ���ٰ� �ٽ� ���� ����
				break;
			case(EEnterDirection::DEFAULT):
				//������ ��ٸ� Ÿ���� ��.
				break;
			case(EEnterDirection::BOTTOM):
				//�ؿ��� ��ٸ� ���ٰ� ���� ����
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
				//�ؿ��� ��ٸ� ���ٰ� ���� ����
				break;
			case(EEnterDirection::DEFAULT):
				//�ؿ��� ��ٸ� Ÿ���� ��.
				break;
			case(EEnterDirection::BOTTOM):
				//�ؿ��� ��ٸ� ���ٰ� �ٽ� ������ ����
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
			//��� ��Ȳ�̵� ��ٸ� �߰��� �Ŵ޸���.
		}
	}
}
