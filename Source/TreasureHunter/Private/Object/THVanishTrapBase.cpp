// Fill out your copyright notice in the Description page of Project Settings.


#include "THVanishTrapBase.h"
#include "THCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "net/UnrealNetwork.h"
#include "Engine/World.h"
#include "Components/BrushComponent.h"
#include "Engine/Brush.h"
#include "Engine/BrushBuilder.h"
#include "Builders/CubeBuilder.h"
#include "Editor/EditorEngine.h"
#include "UnrealEd.h"

ATHVanishTrapBase::ATHVanishTrapBase() : ATHActorBase()
{
	Area->OnComponentBeginOverlap.AddDynamic(this, &ATHVanishTrapBase::OnCharacterInRange);
}

void ATHVanishTrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHVanishTrapBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHVanishTrapBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHVanishTrapBase, BrushList);
}

void ATHVanishTrapBase::VanishBrushByIndex(int index)
{
	BrushList[index]->BrushType = EBrushType::Brush_Subtract;
}

void ATHVanishTrapBase::VanishAllBrush()
{
	for (int i = 0; i < BrushList.Num(); ++i)
	{
		VanishBrushByIndex(i);
	}
}

void ATHVanishTrapBase::AppearBrushByIndex(int index)
{
	BrushList[index]->BrushType = EBrushType::Brush_Add;
}

void ATHVanishTrapBase::AppearAllBrush()
{
	for (int i = 0; i < BrushList.Num(); ++i)
	{
		AppearBrushByIndex(i);
	}
}

void ATHVanishTrapBase::SpawnBrush()
{
	/*
	ABrush* NewBrush = GetWorld()->SpawnBrush();
	NewBrush->BrushBuilder = NewObject<UBrushBuilder>(NewBrush, UCubeBuilder::StaticClass(), NAME_None, RF_Transactional);
	NewBrush->Brush = NewObject<UModel>(NewBrush, NAME_None, RF_Transactional);
	NewBrush->Brush->Initialize(NewBrush, false);
	NewBrush->BrushType = EBrushType::Brush_Add;
	NewBrush->BrushBuilder->Build(NewBrush->GetWorld(), NewBrush);
	NewBrush->SetNeedRebuild(NewBrush->GetLevel());
	NewBrush->GetBrushComponent()->Activate();
	
	GEditor->RebuildAlteredBSP();
	BrushList.Add(NewBrush);
	*/
}
