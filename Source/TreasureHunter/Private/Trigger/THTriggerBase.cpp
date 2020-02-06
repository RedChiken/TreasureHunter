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
	Width = 500.0f;
	Depth = 500.0f;
	Height = 500.0f;

	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("InRangeTrigger"));
	Core = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Core"));
	RootComponent = Area;
	Core->SetupAttachment(Area);
	Area->InitBoxExtent(FVector(Width, Depth, Height));
	Area->AddRelativeLocation(Location);
	Area->BodyInstance.SetCollisionProfileName("Trigger");
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
	DOREPLIFETIME(ATHTriggerBase, Width);
	DOREPLIFETIME(ATHTriggerBase, Depth);
	DOREPLIFETIME(ATHTriggerBase, Height);
	DOREPLIFETIME(ATHTriggerBase, Location);
}

// Called every frame
void ATHTriggerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

