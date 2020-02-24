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
	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionRange"));

	RootComponent = Object;
	Area->SetupAttachment(RootComponent);
	Area->SetVisibility(true);
	Area->SetCollisionProfileName("Trigger");
}

// Called when the game starts or when spawned
void ATHActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATHActorBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHActorBase, Object);
	DOREPLIFETIME(ATHActorBase, Area);
}

// Called every frame
void ATHActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

