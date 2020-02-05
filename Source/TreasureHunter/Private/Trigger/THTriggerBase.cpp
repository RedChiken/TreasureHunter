// Fill out your copyright notice in the Description page of Project Settings.


#include "THTriggerBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "THCharacterBase.h"

// Sets default values
ATHTriggerBase::ATHTriggerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("InRangeTrigger"));
	Core = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Core"));
	RootComponent = Area;
	Core->SetupAttachment(Area);
	Area->InitBoxExtent(FVector(500.0f, 500.0f, 500.0f));
	Area->AddRelativeLocation(Location);
	Area->BodyInstance.SetCollisionProfileName("Trigger");
	Area->OnComponentBeginOverlap.AddDynamic(this, &ATHTriggerBase::OnBeginOverlap);
	Area->SetVisibility(true);
}

// Called when the game starts or when spawned
void ATHTriggerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATHTriggerBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATHTriggerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATHTriggerBase, Location);
}

// Called every frame
void ATHTriggerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATHTriggerBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Something Overlapped"));
	if (OtherActor)
	{
		auto Character = Cast<ATHCharacterBase>(OtherActor);
		if (Character)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Character gets in to the Interaction Area"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("overlapped Actor is not ATHCharacterBase"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("No Collision"));
	}
}

