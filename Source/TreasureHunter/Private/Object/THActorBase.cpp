// Fill out your copyright notice in the Description page of Project Settings.


#include "THActorBase.h"
#include "THCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"

// Sets default values
ATHActorBase::ATHActorBase() : AActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Object = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object"));
	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionRange"));

	RootComponent = Object;
	Area->SetupAttachment(RootComponent);
	Area->SetVisibility(true);
	Area->SetCollisionProfileName("Trigger");
	bActive = true;
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
	DOREPLIFETIME(ATHActorBase, bActive);
	DOREPLIFETIME(ATHActorBase, Entry);
	DOREPLIFETIME(ATHActorBase, Record);
}

// Called every frame
void ATHActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATHActorBase::ServerUpdatebActive_Implementation(bool active)
{
	MulticastUpdatebActive(active);
}

bool ATHActorBase::ServerUpdatebActive_Validate(bool active)
{
	return true;
}

void ATHActorBase::MulticastUpdatebActive_Implementation(bool active)
{
	bActive = active;
}

void ATHActorBase::ServerAddtoBuffer_Implementation(UObject* input)
{
	MulticastAddtoBuffer(input);
}

bool ATHActorBase::ServerAddtoBuffer_Validate(UObject* input)
{
	return true;
}

void ATHActorBase::MulticastAddtoBuffer_Implementation(UObject* input)
{
	if (bActive && !IsValidinBuffer(input) && !IsValidinMemory(input))
	{
		Entry.AddUnique(input);
	}
}

void ATHActorBase::ServerRemovefromBuffer_Implementation(UObject* input)
{
	MulticastRemovefromBuffer(input);
}

bool ATHActorBase::ServerRemovefromBuffer_Validate(UObject* input)
{
	return true;
}

void ATHActorBase::MulticastRemovefromBuffer_Implementation(UObject* input)
{
	if (bActive && IsValidinBuffer(input))
	{
		Entry.Remove(input);
	}
}

void ATHActorBase::ServerResetBuffer_Implementation()
{
	MulticastResetBuffer();
}

bool ATHActorBase::ServerResetBuffer_Validate()
{
	return true;
}

void ATHActorBase::MulticastResetBuffer_Implementation()
{
	Entry.Empty();
}

void ATHActorBase::ServerFlush_Implementation()
{
	MulticastFlush();
}

bool ATHActorBase::ServerFlush_Validate()
{
	return true;
}

void ATHActorBase::MulticastFlush_Implementation()
{
	for (const auto& iter : Entry)
	{
		Record.AddUnique(iter);
	}
	Entry.Empty();
}

void ATHActorBase::ServerAddtoMemory_Implementation(UObject* input)
{
	MulticastAddtoMemory(input);
}

bool ATHActorBase::ServerAddtoMemory_Validate(UObject* input)
{
	return true;
}

void ATHActorBase::MulticastAddtoMemory_Implementation(UObject* input)
{
	if (bActive && !IsValidinMemory(input))
	{
		Record.AddUnique(input);
	}
}

void ATHActorBase::ServerRemovefromMemory_Implementation(UObject* input)
{
	MulticastRemovefromMemory(input);
}

bool ATHActorBase::ServerRemovefromMemory_Validate(UObject* input)
{
	return true;
}

void ATHActorBase::MulticastRemovefromMemory_Implementation(UObject* input)
{
	if (bActive && IsValidinMemory(input))
	{
		Record.Remove(input);
	}
}

void ATHActorBase::ServerResetMemory_Implementation()
{
	MulticastResetMemory();
}

bool ATHActorBase::ServerResetMemory_Validate()
{
	return true;
}

void ATHActorBase::MulticastResetMemory_Implementation()
{
	Record.Empty();
}

void ATHActorBase::AddtoBuffer(UObject* input)
{
	ServerAddtoBuffer(input);
}

void ATHActorBase::RemovefromBuffer(UObject* input)
{
	ServerRemovefromBuffer(input);
}

bool ATHActorBase::IsValidinBuffer(const UObject* input)
{
	return Entry.Contains(input);
}

void ATHActorBase::ResetBuffer()
{
	ServerResetBuffer();
}

void ATHActorBase::Flush()
{
	ServerFlush();
}

void ATHActorBase::AddtoMemory(UObject* input)
{
	ServerAddtoMemory(input);
}

void ATHActorBase::RemovefromMemory(UObject* input)
{
	ServerRemovefromMemory(input);
}

bool ATHActorBase::IsValidinMemory(const UObject* input)
{
	return Record.Contains(input);
}

void ATHActorBase::ResetMemory()
{
	ServerResetMemory();
}
