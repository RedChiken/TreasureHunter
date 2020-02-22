// Fill out your copyright notice in the Description page of Project Settings.


#include "THActorBase.h"
#include "THCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"

// Sets default values
ATHActorBase::ATHActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Object = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object"));
	InteractionRange = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionRange"));

	RootComponent = InteractionRange;
	Object->SetupAttachment(RootComponent);
	InteractionRange->SetVisibility(true);
	InteractionRange->SetCollisionProfileName("Trigger");

	AreaSize = FVector(300.0f, 300.0f, 200.0f);
	AreaLocation = FVector(0.f, 0.f, 200.0f);
	SetRangeSize(AreaSize);
	SetRangeLocation(AreaLocation);
}

// Called when the game starts or when spawned
void ATHActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATHActorBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHActorBase, AreaSize);
	DOREPLIFETIME(ATHActorBase, AreaLocation);
	DOREPLIFETIME(ATHActorBase, Object);
	DOREPLIFETIME(ATHActorBase, InteractionRange);
}

// Called every frame
void ATHActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATHActorBase::SetRangeSize(const FVector& size)
{
	InteractionRange->SetBoxExtent(AreaSize);
}

void ATHActorBase::SetRangeLocation(const FVector& size)
{
	InteractionRange->SetRelativeLocation(AreaLocation);
}

