// Fill out your copyright notice in the Description page of Project Settings.


#include "THClimbBase.h"
#include "THCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"

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
				ExitClimb(Character, EExitDirection::BOTTOM);
				break;
			case(EEnterDirection::DEFAULT):
				//������ ��ٸ� Ÿ���� ��.
				Character->UpdatebAbleToClimb(true);
				EnterClimb(Character, EEnterDirection::TOP);
				break;
			case(EEnterDirection::BOTTOM):
				//�ؿ��� ��ٸ� ���ٰ� ���� ����
				ExitClimb(Character, EExitDirection::TOP);
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
				ExitClimb(Character, EExitDirection::TOP);
				break;
			case(EEnterDirection::DEFAULT):
				//�ؿ��� ��ٸ� Ÿ���� ��.
				Character->UpdatebAbleToClimb(true);
				EnterClimb(Character, EEnterDirection::BOTTOM);
				break;
			case(EEnterDirection::BOTTOM):
				//�ؿ��� ��ٸ� ���ٰ� �ٽ� ������ ����
				ExitClimb(Character, EExitDirection::BOTTOM);
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
			Character->UpdatebAbleToClimb(true);
			EnterClimb(Character, EEnterDirection::MIDDLE);
		}
	}
}

void ATHClimbBase::OnCharacterOutofClimbArea(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		auto character = Cast<ATHCharacterBase>(OtherActor);
		if (character)
		{
			character->UpdatebAbleToClimb(false);
		}
	}
}

void ATHClimbBase::ExitClimb(ATHCharacterBase* Character, EExitDirection Exit)
{
	Character->ExitFromClimb(Exit);
}

void ATHClimbBase::EnterClimb(ATHCharacterBase* Character, EEnterDirection Enter)
{
	Character->EnterToClimb(Enter);
}
