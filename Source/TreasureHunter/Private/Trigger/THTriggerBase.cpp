// Fill out your copyright notice in the Description page of Project Settings.


#include "THTriggerBase.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "THCharacterBase.h"

// Sets default values
ATHTriggerBase::ATHTriggerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionArea"));
	Area->BodyInstance.SetCollisionProfileName("InteractionArea");
	Area->SetBoxExtent(Extent);
	Area->AddRelativeLocation(Location);
	Area->SetBoundsScale(5.0f);
	Area->OnComponentBeginOverlap.AddDynamic(this, &ATHTriggerBase::OnComponentBeginOverlap);
	RootComponent = Area;
}

// Called when the game starts or when spawned
void ATHTriggerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATHTriggerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATHTriggerBase, Extent);
	DOREPLIFETIME(ATHTriggerBase, Location);
}

// Called every frame
void ATHTriggerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATHTriggerBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Character gets in to the Interaction Area"));
		}
	}
}

