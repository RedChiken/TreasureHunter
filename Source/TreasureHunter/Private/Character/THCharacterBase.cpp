// Fill out your copyright notice in the Description page of Project Settings.


#include "THCharacterBase.h"
#include "TreasureHunter.h"
#include "ConstructorHelpers.h"
#include "HitBox/THCharacterHitBox.h"
#include "Animation/THAnimInstanceBase.h"
#include "Animation/THCharacterMovementComponent.h"
#include "camera/CameraComponent.h"
#include "Object/Projectile/THProjectileBase.h"
#include "Object/Piece/THAttachPieceBase.h"
#include "Object/Latch/THAttachLatchBase.h"
#include "Interface/Attachable.h"
#include "THPieceBase.h"
#include "THLatchBase.h"
#include "THWallBase.h"
#include "THLadderBase.h"
#include "THRopeBase.h"
#include "StagePlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UObjectGlobals.h"
#include "net/UnrealNetwork.h"
#include "Engine.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ATHCharacterBase::ATHCharacterBase(const class FObjectInitializer& ObjectInitializer) : ACharacter(ObjectInitializer.SetDefaultSubobjectClass<UTHCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(27.5f, 100.f);
	GetCapsuleComponent()->SetIsReplicated(true);
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	RootComponent = GetCapsuleComponent();

	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	TPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));

	FPCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	//If it's false, Character cannot look upside or downside
	FPCameraComponent->bUsePawnControlRotation = true;
	FPCameraComponent->SetFieldOfView(90.0f);

	//TODO: This is temporary location. Set TP Camera Component at proper position
	TPCameraComponent->SetupAttachment(GetCapsuleComponent());
	TPCameraComponent->SetRelativeLocation(FVector(0.0f, -100.0f, 50.0f));
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(40.5f, -3.5f, -164.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetupAttachment(FPCameraComponent);
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetIsReplicated(true);
	SetReplicateMovement(true);
	SetReplicates(true);
	SetReplicatingMovement(true);

	MovementComponent = Cast<UTHCharacterMovementComponent>(GetMovementComponent());
	if (MovementComponent)
	{
		MovementComponent->UpdatedComponent = GetCapsuleComponent();
		CrouchedEyeHeight = MovementComponent->CrouchedHalfHeight * 0.8f;
		MovementComponent->SetIsReplicated(true);
	}

	InteractionTrigger = AddNewInteractionTrigger(TEXT("Interaction"), 30.f, 100.f, FVector(30.f, 0.f, 0.f));

	UpperClimbTrigger = AddUpperClimbTrigger(TEXT("UpperClimb"), 20.f, 30.f, FVector(30.f, 0.f, 150.f), FRotator(0.f, 0.f, 90.f));
	MiddleClimbTrigger = AddMiddleClimbTrigger(TEXT("MiddleClimb"), 20.f, 30.f, FVector(30.f, 0.f, 0.f), FRotator(0.f, 0.f, 90.f));
	LowerClimbTrigger = AddLowerClimbTrigger(TEXT("LowerClimb"), 20.f, 30.f, FVector(30.f, 0.f, -150.f), FRotator(0.f, 0.f, 90.f));

	HeadHitTrigger = AddNewHitTrigger(TEXT("Head"), 13.f, 13.f, TEXT("head"), FVector(5.f, 2.5f, 0.f), FRotator(90.f, 0.f, 0.f));
	UpperBodyHitTrigger = AddNewHitTrigger(TEXT("UpperBody"), 22.5f, 27.5f, TEXT("spine_03"), FVector(-2.5f, 0.f, 0.f), FRotator(90.f, 0.f, 0.f));
	LowerBodyHitTrigger = AddNewHitTrigger(TEXT("LowerBody"), 20.f, 25.f, TEXT("spine_01"), FVector::ZeroVector, FRotator(90.f, 0.f, 0.f));
	LeftUpperArmHitTrigger = AddNewHitTrigger(TEXT("LeftUpperArm"), 12.5f, 22.5f, TEXT("upperarm_l"), FVector(15.f, 0.f, 0.f), FRotator(90.f, 0.f, 0.f));
	LeftLowerArmHitTrigger = AddNewHitTrigger(TEXT("LeftLowerArm"), 7.5f, 15.f, TEXT("lowerarm_l"), FVector(15.f, 0.f, 0.f), FRotator(90.f, 0.f, 0.f));
	LeftHandHitTrigger = AddNewHitTrigger(TEXT("LeftHand"), 7.5f, 12.5f, TEXT("middle_01_l"), FVector(0.f, -2.5f, 0.f), FRotator(90.f, 0.f, 0.f));
	RightUpperArmHitTrigger = AddNewHitTrigger(TEXT("RightUpperArm"), 12.5f, 22.5f, TEXT("upperarm_r"), FVector(-15.f, 0.f, 0.f), FRotator(90.f, 0.f, 0.f));
	RightLowerArmHitTrigger = AddNewHitTrigger(TEXT("RightLowerArm"), 7.5f, 22.5f, TEXT("lowerarm_r"), FVector(-15.f, 0.f, 0.f), FRotator(90.f, 0.f, 0.f));
	RightHandHitTrigger = AddNewHitTrigger(TEXT("RightHand"), 7.5f, 12.5f, TEXT("middle_01_r"), FVector(0.f, 2.5f, 0.f), FRotator(90.f, 0.f, 0.f));
	LeftUpperLegHitTrigger = AddNewHitTrigger(TEXT("LeftUpperLeg"), 12.5f, 30.f, TEXT("calf_l"), FVector(25.f, -6.f, 0.f), FRotator(90.f, 0.f, 20.f));
	LeftLowerLegHitTrigger = AddNewHitTrigger(TEXT("LeftLowerLeg"), 12.5f, 32.5f, TEXT("foot_l"), FVector(17.5f, 2.5f, 2.5f), FRotator(90.f, 0.f, -10.f));
	LeftFootHitTrigger = AddNewHitTrigger(TEXT("LeftFoot"), 7.5f, 17.5f, TEXT("ball_l"), FVector(-7.5f, 0.f, 0.f), FRotator(90.f, 0.f, 0.f));
	RightUpperLegHitTrigger = AddNewHitTrigger(TEXT("RightUpperLeg"), 13.5f, 30.f, TEXT("calf_r"), FVector(-25.f, 3.5f, 0.f), FRotator(90.f, 0.f, 14.f));
	RightLowerLegHitTrigger = AddNewHitTrigger(TEXT("RightLowerLeg"), 12.5f, 32.5f, TEXT("foot_r"), FVector(-17.5f, -2.5f, -2.5f), FRotator(90.f, 0.f, -10.f));
	RightFootHitTrigger = AddNewHitTrigger(TEXT("RightFoot"), 7.5f, 17.5f, TEXT("ball_r"), FVector(7.5f, 0.f, 0.f), FRotator(90.f, 0.f, 0.f));

	AddtoMemory(FString::FromInt(GetUniqueID()));

	bReplicates = true;
	SetReplicatingMovement(true);

	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	GetCharacterMovement()->JumpZVelocity = 500.0f;

	bJump = false;
	IdleType = EIdleType::STAND;
	MovementType = EMovementType::DEFAULT;
	MovingDirection = EMovingDirection::DEFAULT;
	bFullBodyMotion = false;
	bDead = false;
	bLayeredMotion = false;
	bStandToSprint = false;
	HP = 100;
	OverlappedPiece = nullptr;
	OverlappedLatch = nullptr;
	InteractionType = EInteractionType::DEFAULT;
	AttachSequence = EAttachSequence::DEFAULT;
	bUpperClimbTrigger = false;
	bMiddleClimbTrigger = false;
	bLowerClimbTrigger = false;
	InteractableClimb = EIdleType::STAND;

	MovementComponent->MaxFlySpeed = 200.0f;
	MovementComponent->BrakingDecelerationFlying = 2000.0f;
}

void ATHCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UTHAnimInstanceBase* AnimInstance = Cast<UTHAnimInstanceBase>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->OnEnterRopeTop.AddDynamic(this, &ATHCharacterBase::EnterRopeTop);
		AnimInstance->OnExitRopeTop.AddDynamic(this, &ATHCharacterBase::ExitRopeTop);
		AnimInstance->OnEnterRopeBottom.AddDynamic(this, &ATHCharacterBase::EnterRopeBottom);
		AnimInstance->OnExitRopeBottom.AddDynamic(this, &ATHCharacterBase::ExitRopeBottom);
		AnimInstance->OnEnterWallTop.AddDynamic(this, &ATHCharacterBase::EnterWallTop);
		AnimInstance->OnExitWallTop.AddDynamic(this, &ATHCharacterBase::ExitWallTop);
		AnimInstance->OnEnterWallBottom.AddDynamic(this, &ATHCharacterBase::EnterWallBottom);
		AnimInstance->OnExitWallBottom.AddDynamic(this, &ATHCharacterBase::ExitWallBottom);
		AnimInstance->OnEnterLadderTop.AddDynamic(this, &ATHCharacterBase::EnterLadderTop);
		AnimInstance->OnExitLadderTop.AddDynamic(this, &ATHCharacterBase::ExitLadderTop);
		AnimInstance->OnEnterLadderBottom.AddDynamic(this, &ATHCharacterBase::EnterLadderBottom);
		AnimInstance->OnExitLadderBottom.AddDynamic(this, &ATHCharacterBase::ExitLadderBottom);
		AnimInstance->OnJump.AddDynamic(this, &ACharacter::Jump);
		AnimInstance->OnEnableRightHandHitBox.AddDynamic(this, &ATHCharacterBase::EnableRightPunchMeleeAttack);
		AnimInstance->OnDisableRightHandHitBox.AddDynamic(this, &ATHCharacterBase::DisableRightPunchMeleeAttack);
	}
}

// Called when the game starts or when spawned
void ATHCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATHCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHCharacterBase, IdleType);
	DOREPLIFETIME(ATHCharacterBase, MovementType);
	DOREPLIFETIME(ATHCharacterBase, MovingDirection);
	DOREPLIFETIME(ATHCharacterBase, bJump);
	DOREPLIFETIME(ATHCharacterBase, LayeredAction);
	DOREPLIFETIME(ATHCharacterBase, bFullBodyMotion);
	DOREPLIFETIME(ATHCharacterBase, bLayeredMotion);
	DOREPLIFETIME(ATHCharacterBase, bDead);
	DOREPLIFETIME(ATHCharacterBase, bStandToSprint);
	DOREPLIFETIME(ATHCharacterBase, HP);
	DOREPLIFETIME(ATHCharacterBase, OverlappedPiece);
	DOREPLIFETIME(ATHCharacterBase, OverlappedLatch);
	DOREPLIFETIME(ATHCharacterBase, InteractionType);
	DOREPLIFETIME(ATHCharacterBase, AttachSequence);
	DOREPLIFETIME(ATHCharacterBase, HitObject);
	DOREPLIFETIME(ATHCharacterBase, Ally);
	DOREPLIFETIME(ATHCharacterBase, MovementComponent);
	DOREPLIFETIME(ATHCharacterBase, HoldingPiece);

	DOREPLIFETIME(ATHCharacterBase, bUpperClimbTrigger);
	DOREPLIFETIME(ATHCharacterBase, bMiddleClimbTrigger);
	DOREPLIFETIME(ATHCharacterBase, bLowerClimbTrigger);
	DOREPLIFETIME(ATHCharacterBase, InteractableClimb);
}

// Called every frame
void ATHCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATHCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ATHCharacterBase::OnToggleCrouch);
	//TODO: Add Slide
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ATHCharacterBase::OnToggleSprint);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATHCharacterBase::OnJumpPressed);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ATHCharacterBase::OnJumpReleased);
	PlayerInputComponent->BindAction("MeleeAttack", IE_Pressed, this, &ATHCharacterBase::OnMeleeAttackPressed);
	PlayerInputComponent->BindAction("MeleeAttack", IE_Released, this, &ATHCharacterBase::OnMeleeAttackReleased);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ATHCharacterBase::OnInteractionPressed);
	PlayerInputComponent->BindAction("Interaction", IE_Released, this, &ATHCharacterBase::OnInteractionReleased);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ATHCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATHCharacterBase::MoveRight);

	//TODO: Try to Make CameraComponent Rotate or Rotate Head
	PlayerInputComponent->BindAxis("Turn", this, &ATHCharacterBase::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ATHCharacterBase::LookUp);
}

void ATHCharacterBase::OnMovementStop()
{
	if (MovementComponent->MovementMode == EMovementMode::MOVE_Walking)
	{
		if (GetVelocity().Size() < 0.001)
		{
			ServerUpdateMovementType(EMovementType::DEFAULT);
			if (MovementType == EMovementType::SPRINT)
			{
				ServerUpdateSpeed(0.5f);
			}
		}
	}
}

void ATHCharacterBase::StopInteraction()
{
	OnInteractionReleased();
}

void ATHCharacterBase::UpdateIdleType(EIdleType Idle)
{
	ServerUpdateIdleType(Idle);
}

void ATHCharacterBase::OnHitStartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedComp && OtherComp)
	{
		auto MyHitBox = Cast<UTHCharacterHitBox>(OverlappedComp);
		if (MyHitBox && MyHitBox->getAbletoHit())
		{
			IDamagable* Target = Cast<IDamagable>(OtherComp->GetOwner());
			if (Target)
			{
				FString ID = FString::FromInt(OtherComp->GetOwner()->GetUniqueID());
				if (!IsValidinMemory(ID) && !IsValidinBuffer(ID))
				{
					AddtoBuffer(ID);
					Target->ReceiveDamage(Cast<IDamageActivity>(MyHitBox)->GetDamage());
				}
			}
		}
	}
}

void ATHCharacterBase::OnPieceStartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ATHPieceBase* piece = Cast<ATHPieceBase>(OtherActor);
		if (piece && (OverlappedPiece == nullptr))
		{
			ServerUpdateInteractionType(EInteractionType::ATTACH);
			ServerUpdateOverlappedPiece(piece);
			if (IsLocallyControlled())
			{
				UE_LOG(THVerbose, Verbose, TEXT("%s HoldingPiece: %s"), *FString(__FUNCTION__), GETBOOLSTRING(HoldingPiece != nullptr));
				UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedPiece: %s"), *FString(__FUNCTION__), GETBOOLSTRING(OverlappedPiece != nullptr));
				UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedLatch: %s"), *FString(__FUNCTION__), GETBOOLSTRING(OverlappedLatch != nullptr));
				UE_LOG(THVerbose, Verbose, TEXT("%s On Start Overlap With Piece, InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
			}
		}
	}
}

void ATHCharacterBase::OnPieceEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		ATHPieceBase* piece = Cast<ATHPieceBase>(OtherActor);
		if (piece && OverlappedPiece)
		{
			if (HoldingPiece == nullptr)
			{
				ServerUpdateInteractionType(EInteractionType::DEFAULT);
				UE_LOG(THVerbose, Verbose, TEXT("%s Not Hold Any Piece. InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
			}
			ServerUpdateOverlappedPiece(nullptr);
			if (IsLocallyControlled())
			{
				UE_LOG(THVerbose, Verbose, TEXT("%s HoldingPiece: %s"), *FString(__FUNCTION__), GETBOOLSTRING(HoldingPiece != nullptr));
				UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedPiece: %s"), *FString(__FUNCTION__), GETBOOLSTRING(OverlappedPiece != nullptr));
				UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedLatch: %s"), *FString(__FUNCTION__), GETBOOLSTRING(OverlappedLatch != nullptr));
			}
		}
	}
}

void ATHCharacterBase::OnUpperClimbStartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto Climb = Cast<ATHClimbBase>(OtherActor);
		if (Climb)
		{
			ServerUpdatebUpperClimbTrigger(true);
			if (!IsClimbing())
			{
				ServerUpdateInteractionType(EInteractionType::CLIMB);
				ServerUpdateInteractableClimb(Climb->GetIdleType());
			}
			if (IsLocallyControlled() && !IsAbleToClimb())
			{
				UE_LOG(THVerbose, Verbose, TEXT("%s bUpperClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bUpperClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s bMiddleClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bMiddleClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s bLowerClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bLowerClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s IdleType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", IdleType));
				UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
				UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
				UE_LOG(THVerbose, Verbose, TEXT("%s InteractableClimb: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", InteractableClimb));
			}
		}
	}
}

void ATHCharacterBase::OnMiddleClimbStartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto Climb = Cast<ATHClimbBase>(OtherActor);
		if (Climb)
		{
			ServerUpdatebMiddleClimbTrigger(true);
			if (!IsClimbing())
			{
				ServerUpdateInteractionType(EInteractionType::CLIMB);
				ServerUpdateInteractableClimb(Climb->GetIdleType());
			}
			if (IsLocallyControlled() && !IsAbleToClimb())
			{
				UE_LOG(THVerbose, Verbose, TEXT("%s bUpperClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bUpperClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s bMiddleClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bMiddleClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s bLowerClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bLowerClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s IdleType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", IdleType));
				UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
				UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
				UE_LOG(THVerbose, Verbose, TEXT("%s InteractableClimb: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", InteractableClimb));
			}
		}
	}
}

void ATHCharacterBase::OnLowerClimbStartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto Climb = Cast<ATHClimbBase>(OtherActor);
		if (Climb)
		{
			ServerUpdatebLowerClimbTrigger(true);
			if (!IsClimbing())
			{
				ServerUpdateInteractionType(EInteractionType::CLIMB);
				ServerUpdateInteractableClimb(Climb->GetIdleType());
			}
			if (IsLocallyControlled() && !IsAbleToClimb())
			{
				UE_LOG(THVerbose, Verbose, TEXT("%s bUpperClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bUpperClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s bMiddleClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bMiddleClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s bLowerClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bLowerClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s IdleType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", IdleType));
				UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
				UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
				UE_LOG(THVerbose, Verbose, TEXT("%s InteractableClimb: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", InteractableClimb));
			}
		}
	}
}

void ATHCharacterBase::OnUpperClimbEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		auto Climb = Cast<ATHClimbBase>(OtherActor);
		auto Trigger = Cast<UCapsuleComponent>(OverlappedComp);
		if (Climb)
		{
			ServerUpdatebUpperClimbTrigger(false);
			if (IsClimbing())
			{
				if ((MovingDirection == EMovingDirection::UPSIDE) && IsAttachToTop())
				{
					ServerDisableInput(Cast<AStagePlayerController>(GetController()));
					//ServerDisableCollision();
					//ServerTeleportTo(GetActorLocation() + GetActorForwardVector() * 50 + GetActorUpVector() * 150, GetActorRotation());
					ServerUpdateMovementType(EMovementType::DEFAULT);
				}
			}
			else
			{
				if (!IsAbleToClimb())
				{
					ServerUpdateInteractionType(EInteractionType::DEFAULT);
					ServerUpdateInteractableClimb(EIdleType::STAND);
				}
			}
			if (IsLocallyControlled() && IsClimbing())
			{
				UE_LOG(THVerbose, Verbose, TEXT("%s bUpperClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bUpperClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s bMiddleClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bMiddleClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s bLowerClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bLowerClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s IdleType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", IdleType));
				UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
				UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
				UE_LOG(THVerbose, Verbose, TEXT("%s InteractableClimb: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", InteractableClimb));
			}
		}
	}
}

void ATHCharacterBase::OnMiddleClimbEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		auto Climb = Cast<ATHClimbBase>(OtherActor);
		if (Climb)
		{
			ServerUpdatebMiddleClimbTrigger(false);
			if (!IsAbleToClimb() && !IsClimbing())
			{
				ServerUpdateInteractionType(EInteractionType::DEFAULT);
				ServerUpdateInteractableClimb(EIdleType::STAND);
			}
			if (IsLocallyControlled() && IsClimbing())
			{
				UE_LOG(THVerbose, Verbose, TEXT("%s bUpperClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bUpperClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s bMiddleClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bMiddleClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s bLowerClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bLowerClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s IdleType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", IdleType));
				UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
				UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
				UE_LOG(THVerbose, Verbose, TEXT("%s InteractableClimb: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", InteractableClimb));
			}
		}
	}
}

void ATHCharacterBase::OnLowerClimbEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		auto Climb = Cast<ATHClimbBase>(OtherActor);
		if (Climb)
		{
			ServerUpdatebLowerClimbTrigger(false);
			if (IsClimbing())
			{
				if ((MovingDirection == EMovingDirection::DOWNSIDE) && IsAttachToBottom())
				{
					ServerDisableInput(Cast<AStagePlayerController>(GetController()));
					//ServerDisableCollision();
					//ServerTeleportTo(GetActorLocation() - GetActorForwardVector() * 25, GetActorRotation());
					ServerUpdateMovementType(EMovementType::DEFAULT);
				}
			}
			else
			{
				if (!IsAbleToClimb())
				{
					ServerUpdateInteractionType(EInteractionType::DEFAULT);
					ServerUpdateInteractableClimb(EIdleType::STAND);
				}
			}
			if (IsLocallyControlled() && IsClimbing())
			{
				UE_LOG(THVerbose, Verbose, TEXT("%s bUpperClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bUpperClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s bMiddleClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bMiddleClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s bLowerClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bLowerClimbTrigger));
				UE_LOG(THVerbose, Verbose, TEXT("%s IdleType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", IdleType));
				UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
				UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
				UE_LOG(THVerbose, Verbose, TEXT("%s InteractableClimb: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", InteractableClimb));
			}
		}
	}
}

void ATHCharacterBase::OnLatchStartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		
		auto latch = Cast<ATHLatchBase>(OtherActor);
		if (latch && OverlappedLatch)
		{
			ServerUpdateInteractionType(EInteractionType::ATTACH);
			ServerUpdateOverlappedLatch(latch);
			if (IsLocallyControlled())
			{
				UE_LOG(THVerbose, Verbose, TEXT("%s HoldingPiece: %s"), *FString(__FUNCTION__), GETBOOLSTRING(HoldingPiece != nullptr));
				UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedPiece: %s"), *FString(__FUNCTION__), GETBOOLSTRING(OverlappedPiece != nullptr));
				UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedLatch: %s"), *FString(__FUNCTION__), GETBOOLSTRING(OverlappedLatch != nullptr));
				UE_LOG(THVerbose, Verbose, TEXT("%s On Start Overlap With Latch, InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
			}
		}
	}
}

void ATHCharacterBase::OnLatchEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		auto latch = Cast<ATHLatchBase>(OtherActor);
		if (latch && !OverlappedLatch)
		{
			ServerUpdateOverlappedLatch(nullptr);
			if (HoldingPiece == nullptr)
			{
				ServerUpdateInteractionType(EInteractionType::DEFAULT);
				UE_LOG(THVerbose, Verbose, TEXT("%s On End Overlap With Latch, InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
			}
			if (IsLocallyControlled())
			{
				UE_LOG(THVerbose, Verbose, TEXT("%s HoldingPiece: %s"), *FString(__FUNCTION__), GETBOOLSTRING(HoldingPiece != nullptr));
				UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedPiece: %s"), *FString(__FUNCTION__), GETBOOLSTRING(OverlappedPiece != nullptr));
				UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedLatch: %s"), *FString(__FUNCTION__), GETBOOLSTRING(OverlappedLatch != nullptr));
			}
		}
	}
}

void ATHCharacterBase::ServerPlayMontage_Implementation(UAnimMontage* MontageToPlay, float InPlayRate, EMontagePlayReturnType ReturnValueType, float InTimeToStartMontageAt, bool bStopAllMontages)
{
	MulticastPlayMontage(MontageToPlay, InPlayRate, ReturnValueType, InTimeToStartMontageAt, bStopAllMontages);
}

bool ATHCharacterBase::ServerPlayMontage_Validate(UAnimMontage* MontageToPlay, float InPlayRate, EMontagePlayReturnType ReturnValueType, float InTimeToStartMontageAt, bool bStopAllMontages)
{
	return true;
}

void ATHCharacterBase::MulticastPlayMontage_Implementation(UAnimMontage* MontageToPlay, float InPlayRate, EMontagePlayReturnType ReturnValueType, float InTimeToStartMontageAt, bool bStopAllMontages)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance != NULL)
	{
		if (!AnimInstance->Montage_IsPlaying(MontageToPlay))
		{
			AnimInstance->Montage_Play(MontageToPlay, InPlayRate, ReturnValueType, InTimeToStartMontageAt, bStopAllMontages);
		}
	}
}

void ATHCharacterBase::ServerStopMontage_Implementation(float blendOut, UAnimMontage* MontageToStop)
{
	MulticastStopMontage(blendOut, MontageToStop);
}

bool ATHCharacterBase::ServerStopMontage_Validate(float blendOut, UAnimMontage* MontageToStop)
{
	return true;
}

void ATHCharacterBase::MulticastStopMontage_Implementation(float blendOut, UAnimMontage* MontageToStop)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance != NULL)
	{
		AnimInstance->Montage_Stop(blendOut, InteractionMontage);
	}
}

void ATHCharacterBase::ServerUpdateOverlappedPiece_Implementation(ATHPieceBase* Piece)
{
	MulticastUpdateOverlappedPiece(Piece);
}

bool ATHCharacterBase::ServerUpdateOverlappedPiece_Validate(ATHPieceBase* Piece)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateOverlappedPiece_Implementation(ATHPieceBase* Piece)
{
	OverlappedPiece = Piece;
}

void ATHCharacterBase::ServerUpdateOverlappedLatch_Implementation(ATHLatchBase* Latch)
{
	MulticastUpdateOverlappedLatch(Latch);
}

bool ATHCharacterBase::ServerUpdateOverlappedLatch_Validate(ATHLatchBase* Latch)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateOverlappedLatch_Implementation(ATHLatchBase* Latch)
{
	OverlappedLatch = Latch;
}

void ATHCharacterBase::ServerUpdateMovementType_Implementation(EMovementType type)
{
	MulticastUpdateMovementType(type);
}

bool ATHCharacterBase::ServerUpdateMovementType_Validate(EMovementType type)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateMovementType_Implementation(EMovementType type)
{
	//UE_LOG(THVerbose, Verbose, TEXT("MovementType change from %s to %s"), *GETENUMSTRING("EMovementType", MovementType), *GETENUMSTRING("EMovementType", type));
	MovementType = type;
}

void ATHCharacterBase::ServerUpdateMovingDirection_Implementation(EMovingDirection direction)
{
	MulticastUpdateMovingDirection(direction);
}

bool ATHCharacterBase::ServerUpdateMovingDirection_Validate(EMovingDirection direction)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateMovingDirection_Implementation(EMovingDirection direction)
{
	//UE_LOG(THVerbose, Verbose, TEXT("MovingDirection change from %s to %s"), *GETENUMSTRING("EMovingDirection", MovingDirection), *GETENUMSTRING("EMovingDirection", direction));
	MovingDirection = direction;
}

void ATHCharacterBase::ServerUpdateIdleType_Implementation(EIdleType type)
{
	MulticastUpdateIdleType(type);
}

bool ATHCharacterBase::ServerUpdateIdleType_Validate(EIdleType type)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateIdleType_Implementation(EIdleType type)
{
	//UE_LOG(THVerbose, Verbose, TEXT("IdleType change from %s to %s"), *GETENUMSTRING("EIdleType", IdleType), *GETENUMSTRING("EIdleType", type));
	IdleType = type;
}

void ATHCharacterBase::ServerUpdateSpeed_Implementation(float rate)
{
	MulticastUpdateSpeed(rate);
}

bool ATHCharacterBase::ServerUpdateSpeed_Validate(float rate)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateSpeed_Implementation(float rate)
{
	GetCharacterMovement()->MaxWalkSpeed *= rate;
}

void ATHCharacterBase::ServerUpdatebJump_Implementation(bool isJump)
{
	MulticastUpdatebJump(isJump);
}

bool ATHCharacterBase::ServerUpdatebJump_Validate(bool isJump)
{
	return true;
}

void ATHCharacterBase::MulticastUpdatebJump_Implementation(bool isJump)
{
	bJump = isJump;
}

void ATHCharacterBase::ServerUpdateLayeredAction_Implementation(ELayeredAction Action)
{
	MulticastUpdateLayeredAction(Action);
}

bool ATHCharacterBase::ServerUpdateLayeredAction_Validate(ELayeredAction Action)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateLayeredAction_Implementation(ELayeredAction Action)
{
	LayeredAction = Action;
}

void ATHCharacterBase::ServerUpdatebFullBodyMotion_Implementation(bool FullBodyMotion)
{
	MulticastUpdatebFullBodyMotion(FullBodyMotion);
}

bool ATHCharacterBase::ServerUpdatebFullBodyMotion_Validate(bool FullBodyMotion)
{
	return true;
}

void ATHCharacterBase::MulticastUpdatebFullBodyMotion_Implementation(bool FullBodyMotion)
{
	bFullBodyMotion = FullBodyMotion;
}

void ATHCharacterBase::ServerUpdatebLayeredMotion_Implementation(bool LayeredMotion)
{
	MulticastUpdatebLayeredMotion(LayeredMotion);
}

bool ATHCharacterBase::ServerUpdatebLayeredMotion_Validate(bool LayeredMotion)
{
	return true;
}

void ATHCharacterBase::MulticastUpdatebLayeredMotion_Implementation(bool LayeredMotion)
{
	bLayeredMotion = LayeredMotion;
}

void ATHCharacterBase::ServerUpdatebDead_Implementation(bool Dead)
{
	MulticastUpdatebDead(Dead);
}

bool ATHCharacterBase::ServerUpdatebDead_Validate(bool Dead)
{
	return true;
}

void ATHCharacterBase::MulticastUpdatebDead_Implementation(bool Dead)
{
	bDead = Dead;
}

void ATHCharacterBase::ServerUpdateHP_Implementation(float HPChanged)
{
	MulticastUpdateHP(HPChanged);
}

bool ATHCharacterBase::ServerUpdateHP_Validate(float HPChanged)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateHP_Implementation(float HPChanged)
{
	HP += HPChanged;
}

void ATHCharacterBase::ServerUpdateInteractionType_Implementation(EInteractionType Type)
{
	MulticastUpdateInteractionType(Type);
}

bool ATHCharacterBase::ServerUpdateInteractionType_Validate(EInteractionType Type)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateInteractionType_Implementation(EInteractionType Type)
{
	InteractionType = Type;
}

void ATHCharacterBase::ServerUpdateAttachSequence_Implementation(EAttachSequence Sequence)
{
	MulticastUpdateAttachSequence(Sequence);
}

bool ATHCharacterBase::ServerUpdateAttachSequence_Validate(EAttachSequence Sequence)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateAttachSequence_Implementation(EAttachSequence Sequence)
{
	AttachSequence = Sequence;
}

void ATHCharacterBase::ServerUpdatebUpperClimbTrigger_Implementation(bool ClimbTrigger)
{
	MulticastUpdatebUpperClimbTrigger(ClimbTrigger);
}

bool ATHCharacterBase::ServerUpdatebUpperClimbTrigger_Validate(bool ClimbTrigger)
{
	return true;
}

void ATHCharacterBase::MulticastUpdatebUpperClimbTrigger_Implementation(bool ClimbTrigger)
{
	bUpperClimbTrigger = ClimbTrigger;
}

void ATHCharacterBase::ServerUpdatebMiddleClimbTrigger_Implementation(bool ClimbTrigger)
{
	MulticastUpdatebMiddleClimbTrigger(ClimbTrigger);
}

bool ATHCharacterBase::ServerUpdatebMiddleClimbTrigger_Validate(bool ClimbTrigger)
{
	return true;
}

void ATHCharacterBase::MulticastUpdatebMiddleClimbTrigger_Implementation(bool ClimbTrigger)
{
	bMiddleClimbTrigger = ClimbTrigger;
}

void ATHCharacterBase::ServerUpdatebLowerClimbTrigger_Implementation(bool ClimbTrigger)
{
	MulticastUpdatebLowerClimbTrigger(ClimbTrigger);
}

bool ATHCharacterBase::ServerUpdatebLowerClimbTrigger_Validate(bool ClimbTrigger)
{
	return true;
}

void ATHCharacterBase::MulticastUpdatebLowerClimbTrigger_Implementation(bool ClimbTrigger)
{
	bLowerClimbTrigger = ClimbTrigger;
}

void ATHCharacterBase::ServerUpdateInteractableClimb_Implementation(EIdleType ClimbType)
{
	MulticastUpdateInteractableClimb(ClimbType);
}

bool ATHCharacterBase::ServerUpdateInteractableClimb_Validate(EIdleType ClimbType)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateInteractableClimb_Implementation(EIdleType ClimbType)
{
	InteractableClimb = ClimbType;
}

void ATHCharacterBase::ServerUpdateMovementMode_Implementation(EMovementMode Mode)
{
	MulticastUpdateMovementMode(Mode);
}

bool ATHCharacterBase::ServerUpdateMovementMode_Validate(EMovementMode Mode)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateMovementMode_Implementation(EMovementMode Mode)
{
	//UE_LOG(THVerbose, Verbose, TEXT("%s before MovementMode: %s"), *const FString&(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
	MovementComponent->SetMovementMode(Mode);
	//UE_LOG(THVerbose, Verbose, TEXT("%s after MovementMode: %s"), *const FString&(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
}

void ATHCharacterBase::ServerTeleportTo_Implementation(FVector WorldLocation, FRotator Rotation)
{
	MulticastTeleportTo(WorldLocation, Rotation);
}

bool ATHCharacterBase::ServerTeleportTo_Validate(FVector WorldLocation, FRotator Rotation)
{
	return true;
}

void ATHCharacterBase::MulticastTeleportTo_Implementation(FVector WorldLocation, FRotator Rotation)
{
	TeleportTo(WorldLocation, Rotation);
}

void ATHCharacterBase::ServerEnableCollision_Implementation()
{
	MulticastEnableCollision();
}

bool ATHCharacterBase::ServerEnableCollision_Validate()
{
	return true;
}

void ATHCharacterBase::MulticastEnableCollision_Implementation()
{
	SetActorTickEnabled(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	InteractionTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	UpperClimbTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MiddleClimbTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LowerClimbTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	HeadHitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	UpperBodyHitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LowerBodyHitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftUpperArmHitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftLowerArmHitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftHandHitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightUpperArmHitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightLowerArmHitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightHandHitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftUpperLegHitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftLowerLegHitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftFootHitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightUpperArmHitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightLowerLegHitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightFootHitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetActorHiddenInGame(false);
}

void ATHCharacterBase::ServerDisableCollision_Implementation()
{
	MulticastDisableCollision();
}

bool ATHCharacterBase::ServerDisableCollision_Validate()
{
	return true;
}

void ATHCharacterBase::MulticastDisableCollision_Implementation()
{
	SetActorTickEnabled(false);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	InteractionTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UpperClimbTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MiddleClimbTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LowerClimbTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HeadHitTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UpperBodyHitTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LowerBodyHitTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftUpperArmHitTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftLowerArmHitTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandHitTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightUpperArmHitTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightLowerArmHitTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandHitTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftUpperLegHitTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftLowerLegHitTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftFootHitTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightUpperArmHitTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightLowerLegHitTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightFootHitTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorHiddenInGame(true);
}

void ATHCharacterBase::ServerEnableInput_Implementation(APlayerController* InputController)
{
	MulticastEnableInput(InputController);
}

bool ATHCharacterBase::ServerEnableInput_Validate(APlayerController* InputController)
{
	return true;
}

void ATHCharacterBase::MulticastEnableInput_Implementation(APlayerController* InputController)
{
	EnableInput(InputController);
}

void ATHCharacterBase::ServerDisableInput_Implementation(APlayerController* InputController)
{
	MulticastDisableInput(InputController);
}

bool ATHCharacterBase::ServerDisableInput_Validate(APlayerController* InputController)
{
	return true;
}

void ATHCharacterBase::MulticastDisableInput_Implementation(APlayerController* InputController)
{
	DisableInput(InputController);
}

void ATHCharacterBase::ServerActivateHitBox_Implementation(UObject* HitBox)
{
	MulticastActivateHitBox(HitBox);
}

bool ATHCharacterBase::ServerActivateHitBox_Validate(UObject* HitBox)
{
	return true;
}

void ATHCharacterBase::MulticastActivateHitBox_Implementation(UObject* HitBox)
{
	auto CharacterHitBox = Cast<UTHCharacterHitBox>(HitBox);
	CharacterHitBox->Activate();
}

void ATHCharacterBase::ServerInactivateHitBox_Implementation(UObject* HitBox)
{
	MulticastInactivateHitBox(HitBox);
}

bool ATHCharacterBase::ServerInactivateHitBox_Validate(UObject* HitBox)
{
	return true;
}

void ATHCharacterBase::MulticastInactivateHitBox_Implementation(UObject* HitBox)
{
	auto CharacterHitBox = Cast<UTHCharacterHitBox>(HitBox);
	CharacterHitBox->InActivate();
}

void ATHCharacterBase::ServerAddHitObject_Implementation(const FString& target)
{
	MulticastAddHitObject(target);
}

bool ATHCharacterBase::ServerAddHitObject_Validate(const FString& target)
{
	return true;
}

void ATHCharacterBase::ServerRemoveHitObject_Implementation(const FString& target)
{
	MulticastRemoveHitObject(target);
}

bool ATHCharacterBase::ServerRemoveHitObject_Validate(const FString& target)
{
	return true;
}

void ATHCharacterBase::ServerResetHitObject_Implementation()
{
	MulticastResetHitObject();
}

bool ATHCharacterBase::ServerResetHitObject_Validate()
{
	return true;
}

void ATHCharacterBase::ServerAddAlly_Implementation(const FString& target)
{
	MulticastAddAlly(target);
}

bool ATHCharacterBase::ServerAddAlly_Validate(const FString& target)
{
	return true;
}

void ATHCharacterBase::ServerRemoveAlly_Implementation(const FString& target)
{
	MulticastRemoveAlly(target);
}

bool ATHCharacterBase::ServerRemoveAlly_Validate(const FString& target)
{
	return true;
}

void ATHCharacterBase::ServerResetAlly_Implementation()
{
	MulticastResetAlly();
}

bool ATHCharacterBase::ServerResetAlly_Validate()
{
	return true;
}

void ATHCharacterBase::MulticastAddHitObject_Implementation(const FString& target)
{
	if (!IsValidinBuffer(target) && !IsValidinMemory(target))
	{
		HitObject.Add(target);
	}
}

void ATHCharacterBase::MulticastRemoveHitObject_Implementation(const FString& target)
{
	if (IsValidinBuffer(target))
	{
		HitObject.Remove(target);
	}
}

void ATHCharacterBase::MulticastResetHitObject_Implementation()
{
	HitObject.Empty();
}

void ATHCharacterBase::MulticastAddAlly_Implementation(const FString& target)
{
	if (!IsValidinMemory(target))
	{
		Ally.Add(target);
	}
}

void ATHCharacterBase::MulticastRemoveAlly_Implementation(const FString& target)
{
	if (IsValidinMemory(target))
	{
		Ally.Remove(target);
	}
}

void ATHCharacterBase::MulticastResetAlly_Implementation()
{
	Ally.Empty();
}

void ATHCharacterBase::ServerUpdateHoldingPiece_Implementation(ATHAttachPieceBase* Piece)
{
	MulticastUpdateHoldingPiece(Piece);
}

bool ATHCharacterBase::ServerUpdateHoldingPiece_Validate(ATHAttachPieceBase* Piece)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateHoldingPiece_Implementation(ATHAttachPieceBase* Piece)
{
	HoldingPiece = Piece;
}

void ATHCharacterBase::ServerAttach_Implementation(ATHAttachPieceBase* Input)
{
	MulticastAttach(Input);
}

bool ATHCharacterBase::ServerAttach_Validate(ATHAttachPieceBase* Input)
{
	return true;
}

void ATHCharacterBase::MulticastAttach_Implementation(ATHAttachPieceBase* Input)
{
	//Attach Piece to Character
	if (IsDetachable())
	{
		//If already has Piece, Detach it.
		UE_LOG(THVerbose, Verbose, TEXT("%s Detach HoldingPiece"), *FString(__FUNCTION__));
		Detach();
	}
	UE_LOG(THVerbose, Verbose, TEXT("%s Attach Piece to Character"), *FString(__FUNCTION__));
	Input->Attach(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("socket_melee_r"));
}

void ATHCharacterBase::ServerAttachTo_Implementation(ATHAttachLatchBase* Input, ATHAttachPieceBase* Output)
{
	MulticastAttachTo(Input, Output);
}

bool ATHCharacterBase::ServerAttachTo_Validate(ATHAttachLatchBase* Input, ATHAttachPieceBase* Output)
{
	return true;
}

void ATHCharacterBase::MulticastAttachTo_Implementation(ATHAttachLatchBase* Input, ATHAttachPieceBase* Output)
{
	if (Input->IsDetachable())
	{
		//Get Piece
		Output = Cast<ATHAttachPieceBase>(Input->Detach());
		if (IsDetachable())
		{
			//If already has Piece, Detach it.
			Input->Attach(Detach());
		}
		Attach(Output);
	}
	else
	{
		if (IsDetachable())
		{
			//Submit Piece
			Input->Attach(Detach());
			ServerUpdateInteractionType(EInteractionType::DEFAULT);
		}
	}
}

void ATHCharacterBase::ServerDetach_Implementation(ATHAttachPieceBase* Output)
{
	MulticastDetach(Output);
}

bool ATHCharacterBase::ServerDetach_Validate(ATHAttachPieceBase* Output)
{
	return true;
}

void ATHCharacterBase::MulticastDetach_Implementation(ATHAttachPieceBase* Output)
{
	Output = HoldingPiece;
	HoldingPiece->Detach(FDetachmentTransformRules::KeepRelativeTransform);
}

UTHCharacterHitBox* ATHCharacterBase::AddNewHitTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FName& AttachedSocket, const FVector& RelativeLocation, const FRotator& RelativeRotation)
{
	auto Trigger = CreateDefaultSubobject<UTHCharacterHitBox>(SubobjectName);
	Trigger->InitCapsuleSize(Radius, HalfHeight);
	Trigger->SetRelativeLocation(RelativeLocation);
	Trigger->SetRelativeRotation(RelativeRotation);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	Trigger->SetupAttachment(GetMesh(), AttachedSocket);
	Trigger->UpdateDamage(5);
	Trigger->InActivate();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATHCharacterBase::OnHitStartOverlap);
	return Trigger;
}

UCapsuleComponent* ATHCharacterBase::AddUpperClimbTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FVector& RelativeLocation, const FRotator& RelativeRotation)
{
	auto trigger = AddNewClimbTrigger(SubobjectName, Radius, HalfHeight, RelativeLocation, RelativeRotation);
	trigger->OnComponentBeginOverlap.AddDynamic(this, &ATHCharacterBase::OnUpperClimbStartOverlap);
	trigger->OnComponentEndOverlap.AddDynamic(this, &ATHCharacterBase::OnUpperClimbEndOverlap);
	return trigger;
}

UCapsuleComponent* ATHCharacterBase::AddMiddleClimbTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FVector& RelativeLocation, const FRotator& RelativeRotation)
{
	auto trigger = AddNewClimbTrigger(SubobjectName, Radius, HalfHeight, RelativeLocation, RelativeRotation);
	trigger->OnComponentBeginOverlap.AddDynamic(this, &ATHCharacterBase::OnMiddleClimbStartOverlap);
	trigger->OnComponentEndOverlap.AddDynamic(this, &ATHCharacterBase::OnMiddleClimbEndOverlap);
	return trigger;
}

UCapsuleComponent* ATHCharacterBase::AddLowerClimbTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FVector& RelativeLocation, const FRotator& RelativeRotation)
{
	auto trigger = AddNewClimbTrigger(SubobjectName, Radius, HalfHeight, RelativeLocation, RelativeRotation);
	trigger->OnComponentBeginOverlap.AddDynamic(this, &ATHCharacterBase::OnLowerClimbStartOverlap);
	trigger->OnComponentEndOverlap.AddDynamic(this, &ATHCharacterBase::OnLowerClimbEndOverlap);
	return trigger;
}

UCapsuleComponent* ATHCharacterBase::AddNewClimbTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FVector& RelativeLocation, const FRotator& RelativeRotation)
{
	auto Trigger = CreateDefaultSubobject<UCapsuleComponent>(SubobjectName);
	Trigger->InitCapsuleSize(Radius, HalfHeight);
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetRelativeLocation(RelativeLocation);
	Trigger->SetRelativeRotation(RelativeRotation);
	Trigger->SetGenerateOverlapEvents(true);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	return Trigger;
}

UCapsuleComponent* ATHCharacterBase::AddNewInteractionTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FVector& RelativeLocation, const FRotator& RelativeRotation)
{
	auto Trigger = CreateDefaultSubobject<UCapsuleComponent>(SubobjectName);
	Trigger->InitCapsuleSize(Radius, HalfHeight);
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetRelativeLocation(RelativeLocation);
	Trigger->SetRelativeRotation(RelativeRotation);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATHCharacterBase::OnPieceStartOverlap);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATHCharacterBase::OnLatchStartOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ATHCharacterBase::OnPieceEndOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ATHCharacterBase::OnLatchEndOverlap);
	return Trigger;
}

void ATHCharacterBase::EnterRopeTop()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s: Notify!"), *FString(__FUNCTION__));
	EnterClimb();
	ServerTeleportTo(GetActorLocation() + GetActorForwardVector() * 100 - GetActorUpVector() * 100, GetActorRotation().Add(0.f, 0.f, 180.f));
	ServerEnableInput(Cast<AStagePlayerController>(GetController()));
}

void ATHCharacterBase::ExitRopeTop()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s: Notify!"), *FString(__FUNCTION__));
	ServerTeleportTo(GetActorLocation() + GetActorForwardVector() * 50 + GetActorUpVector() * 150, GetActorRotation());
	ExitClimb();
	ServerEnableInput(Cast<AStagePlayerController>(GetController()));
}

void ATHCharacterBase::EnterRopeBottom()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s: Notify!"), *FString(__FUNCTION__));
	EnterClimb();
	ServerEnableInput(Cast<AStagePlayerController>(GetController()));
}

void ATHCharacterBase::ExitRopeBottom()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s: Notify!"), *FString(__FUNCTION__));
	ExitClimb();
	ServerEnableInput(Cast<AStagePlayerController>(GetController()));
}

void ATHCharacterBase::EnterWallTop()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s: Notify!"), *FString(__FUNCTION__));
	EnterClimb();
	ServerTeleportTo(GetActorLocation() + GetActorForwardVector() * 100 - GetActorUpVector() * 100, GetActorRotation().Add(0.f, 0.f, 180.f));
	ServerEnableInput(Cast<AStagePlayerController>(GetController()));
}

void ATHCharacterBase::ExitWallTop()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s: Notify!"), *FString(__FUNCTION__));
	ServerTeleportTo(GetActorLocation() + GetActorForwardVector() * 50 + GetActorUpVector() * 150, GetActorRotation());
	ExitClimb();
	ServerEnableInput(Cast<AStagePlayerController>(GetController()));
}

void ATHCharacterBase::EnterWallBottom()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s: Notify!"), *FString(__FUNCTION__));
	EnterClimb();
	ServerEnableInput(Cast<AStagePlayerController>(GetController()));
}

void ATHCharacterBase::ExitWallBottom()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s: Notify!"), *FString(__FUNCTION__));
	ExitClimb();
	ServerEnableInput(Cast<AStagePlayerController>(GetController()));
}

void ATHCharacterBase::EnterLadderTop()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s: Notify!"), *FString(__FUNCTION__));
	EnterClimb();
	ServerTeleportTo(GetActorLocation() + GetActorForwardVector() * 100 - GetActorUpVector() * 100, GetActorRotation().Add(0.f, 0.f, 180.f));
	ServerEnableInput(Cast<AStagePlayerController>(GetController()));
}

void ATHCharacterBase::ExitLadderTop()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s: Notify!"), *FString(__FUNCTION__));
	ServerTeleportTo(GetActorLocation() + GetActorForwardVector() * 50 + GetActorUpVector() * 150, GetActorRotation());
	ExitClimb();
	ServerEnableInput(Cast<AStagePlayerController>(GetController()));
}

void ATHCharacterBase::EnterLadderBottom()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s: Notify!"), *FString(__FUNCTION__));
	EnterClimb();
	ServerEnableInput(Cast<AStagePlayerController>(GetController()));
}

void ATHCharacterBase::ExitLadderBottom()
{
	UE_LOG(THVerbose, Verbose, TEXT("%s: Notify!"), *FString(__FUNCTION__));
	ExitClimb();
	ServerEnableInput(Cast<AStagePlayerController>(GetController()));
}

void ATHCharacterBase::EnableRightPunchMeleeAttack()
{
	if (IsMeleeAttack())
	{
		UE_LOG(THVerbose, Verbose, TEXT("%s: Notify!"), *FString(__FUNCTION__));
		ServerActivateHitBox(RightHandHitTrigger);
		//TODO: CHange to Right Hand and Fix
	}
}

void ATHCharacterBase::DisableRightPunchMeleeAttack()
{
	if (IsMeleeAttack())
	{
		UE_LOG(THVerbose, Verbose, TEXT("%s: Right Hand Trigger Inactivate!"), *FString(__FUNCTION__));
		ServerInactivateHitBox(RightHandHitTrigger);
		ResetBuffer();
	}
}

void ATHCharacterBase::OnToggleCrouch()
{
	if (IdleType == EIdleType::STAND)
	{
		if ((MovementType == EMovementType::DEFAULT) || (MovementType == EMovementType::WALK))
		{
			ServerUpdateIdleType(EIdleType::CROUCH);
			IdleType = EIdleType::CROUCH;
			ServerUpdateSpeed(0.5);
		}
	}
	else if(IdleType == EIdleType::CROUCH)
	{
		ServerUpdateIdleType(EIdleType::STAND);
		ServerUpdateSpeed(2.0);
	}
}

void ATHCharacterBase::OnToggleSprint()
{
	if (IdleType == EIdleType::STAND)
	{
		if (MovementType == EMovementType::WALK)
		{
			ServerUpdateMovementType(EMovementType::SPRINT);
			ServerUpdateSpeed(2.0);
		}
		else if (MovementType == EMovementType::SPRINT)
		{
			ServerUpdateMovementType(EMovementType::WALK);
			ServerUpdateSpeed(0.5);
		}
		else if (MovementType == EMovementType::DEFAULT)
		{
			ServerUpdateSpeed(2.0);
			bStandToSprint = true;
		}
	}
}

void ATHCharacterBase::OnSlide()
{
	bFullBodyMotion = true;
	if (MovementType == EMovementType::SPRINT)
	{
		//TODO: Do the Job
	}
}

void ATHCharacterBase::OnJumpPressed()
{
	switch (IdleType)
	{
	case EIdleType::DEFAULT:
	case EIdleType::STAND:
		ServerUpdatebJump(true);
		UE_LOG(THVerbose, Verbose, TEXT("bJump is %s"), (bJump ? TEXT("On") : TEXT("Off")));
		break;
	case EIdleType::LADDER:
	case EIdleType::ROPE:
	case EIdleType::WALL:
		ExitClimb();
		UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
		UE_LOG(THVerbose, Verbose, TEXT("%s IdleType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", IdleType));
		UE_LOG(THVerbose, Verbose, TEXT("%s MovementType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementType", MovementType));
		//ServerUpdateInteractionType(EInteractionType::CLIMB);
		//UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *const FString&(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
		UE_LOG(THVerbose, Verbose, TEXT("%s bFullBodyMotion: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bFullBodyMotion));
		break;
	}
}

void ATHCharacterBase::OnJumpReleased()
{
	if (IdleType != EIdleType::CROUCH)
	{
		ServerUpdatebJump(false);
		UE_LOG(THVerbose, Verbose, TEXT("bJump is %s"), (bJump ? TEXT("On") : TEXT("Off")));
		Super::StopJumping();
	}
}

void ATHCharacterBase::OnMeleeAttackPressed()
{
	ServerUpdatebLayeredMotion(true);
	ServerUpdateLayeredAction(ELayeredAction::MELEEATTACK);
	ServerPlayMontage(MeleeAttackMontage);
}

void ATHCharacterBase::OnMeleeAttackReleased()
{
	ServerUpdatebLayeredMotion(false);
	ServerUpdateLayeredAction(ELayeredAction::DEFAULT);
	ServerStopMontage(0.25f, MeleeAttackMontage);
}

void ATHCharacterBase::OnInteractionPressed()
{
	switch (InteractionType)
	{
	case EInteractionType::ATTACH:
	{
		auto AttachedPiece = Cast<ATHAttachPieceBase>(OverlappedPiece);
		auto AttachedLatch = Cast<ATHAttachLatchBase>(OverlappedLatch);
		if (AttachedPiece)
		{
			UE_LOG(THVerbose, Verbose, TEXT("%s Attach Piece to Character"), *FString(__FUNCTION__));
			Attach(AttachedPiece);
			ServerUpdateOverlappedPiece(nullptr);
		}
		else if (AttachedLatch)
		{
			UE_LOG(THVerbose, Verbose, TEXT("%s Attach Activity with AttachedLatch"), *FString(__FUNCTION__));
			Attach(AttachedLatch);
		}
		else
		{
			if (HoldingPiece)
			{
				UE_LOG(THVerbose, Verbose, TEXT("%s Detach Piece"), *FString(__FUNCTION__));
				ATHAttachPieceBase* temp = nullptr;
				ServerDetach(temp);
				ServerUpdateInteractionType(EInteractionType::DEFAULT);
			}
		}
		if (IsLocallyControlled())
		{
			UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedPiece: %s"), *FString(__FUNCTION__), GETBOOLSTRING(OverlappedPiece != nullptr));
			UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedLatch: %s"), *FString(__FUNCTION__), GETBOOLSTRING(OverlappedLatch != nullptr));
		}
	}
	break;
	case EInteractionType::CLIMB:
	{
		//From Climbing to Stand
		auto MovementMode = MovementComponent->MovementMode;
		ServerDisableInput(Cast<AStagePlayerController>(GetController()));
		if (MovementMode == EMovementMode::MOVE_Flying)
		{
			ExitClimb();
		}
		else
		{
			EnterClimb();
		}
		if (IsLocallyControlled())
		{
			UE_LOG(THVerbose, Verbose, TEXT("%s bUpperClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bUpperClimbTrigger));
			UE_LOG(THVerbose, Verbose, TEXT("%s bMiddleClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bMiddleClimbTrigger));
			UE_LOG(THVerbose, Verbose, TEXT("%s bLowerClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bLowerClimbTrigger));
			UE_LOG(THVerbose, Verbose, TEXT("%s IdleType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", IdleType));
			UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
			UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
			UE_LOG(THVerbose, Verbose, TEXT("%s InteractableClimb: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", InteractableClimb));
		}
	}
		break;
	case EInteractionType::INVESTIGATE:
		UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
		ServerUpdatebLayeredMotion(true);
		ServerPlayMontage(InteractionMontage);
		break;
	case EInteractionType::DEFAULT:
		ServerUpdatebLayeredMotion(true);
		ServerPlayMontage(InteractionMontage);
		UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
		break;
	default:
		break;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Interaction Start"));
}

void ATHCharacterBase::OnInteractionReleased()
{
	ServerUpdatebLayeredMotion(false);
	ServerStopMontage(0.25f, InteractionMontage);
}

void ATHCharacterBase::MoveForward(float val)
{
	//UE_LOG(THVerbose, Verbose, TEXT("%s IdleType: %s"), *const FString&(__FUNCTION__), *GETENUMSTRING("EIdleType", IdleType));
	if (IsClimbing())
	{
		if (val > 0.f)
		{
			if (!IsAttachToTop())
			{
				ServerUpdateMovementType(EMovementType::CLIMB);
				ServerUpdateMovingDirection(EMovingDirection::UPSIDE);
				AddMovement(GetActorUpVector(), val);
			}
		}
		else if (val < 0.f)
		{
			if (!IsAttachToBottom())
			{
				ServerUpdateMovementType(EMovementType::CLIMB);
				ServerUpdateMovingDirection(EMovingDirection::DOWNSIDE);
				AddMovement(GetActorUpVector(), val);
			}
		}
		else
		{
			ServerUpdateMovementType(EMovementType::DEFAULT);
			ServerUpdateMovingDirection(EMovingDirection::DEFAULT);
			//MovementComponent->Velocity = FVector::ZeroVector;
			MovementComponent->StopMovementImmediately();
			
		}
		//UE_LOG(THVerbose, Verbose, TEXT("%s MovingDirection: %s"), *const FString&(__FUNCTION__), *GETENUMSTRING("EMovingDirection", MovingDirection));
	}
	else
	{
		//UE_LOG(THVerbose, Verbose, TEXT("%s Move on Ground"), *const FString&(__FUNCTION__));
		AddMovement(GetActorForwardVector(), val);
		if (val > 0)
		{
			switch (MovingDirection)
			{
			case EMovingDirection::DEFAULT:
				ServerUpdateMovingDirection(EMovingDirection::FRONT);
				break;
			case EMovingDirection::RIGHT:
				ServerUpdateMovingDirection(EMovingDirection::FRONTRIGHT);
				break;
			case EMovingDirection::LEFT:
				ServerUpdateMovingDirection(EMovingDirection::FRONTLEFT);
				break;
			}
		}
		else if (val < 0)
		{
			switch (MovingDirection)
			{
			case EMovingDirection::DEFAULT:
				ServerUpdateMovingDirection(EMovingDirection::BACK);
				break;
			case EMovingDirection::RIGHT:
				ServerUpdateMovingDirection(EMovingDirection::BACKRIGHT);
				break;
			case EMovingDirection::LEFT:
				ServerUpdateMovingDirection(EMovingDirection::BACKLEFT);
				break;
			}
		}
		else
		{
			switch (MovingDirection)
			{
			case EMovingDirection::FRONT:
				ServerUpdateMovingDirection(EMovingDirection::DEFAULT);
				break;
			case EMovingDirection::FRONTRIGHT:
				ServerUpdateMovingDirection(EMovingDirection::RIGHT);
				break;
			case EMovingDirection::BACKRIGHT:
				ServerUpdateMovingDirection(EMovingDirection::RIGHT);
				break;
			case EMovingDirection::BACK:
				ServerUpdateMovingDirection(EMovingDirection::DEFAULT);
				break;
			case EMovingDirection::BACKLEFT:
				ServerUpdateMovingDirection(EMovingDirection::LEFT);
				break;
			case EMovingDirection::FRONTLEFT:
				ServerUpdateMovingDirection(EMovingDirection::LEFT);
				break;
			}
		}
	}
}

void ATHCharacterBase::MoveRight(float val)
{
	//Temporary block move right and left during climg
	if (!IsClimbing())
	{
		AddMovement(GetActorRightVector(), val);
		if (val > 0)
		{
			switch (MovingDirection)
			{
			case EMovingDirection::DEFAULT:
				ServerUpdateMovingDirection(EMovingDirection::RIGHT);
				break;
			case EMovingDirection::FRONT:
				ServerUpdateMovingDirection(EMovingDirection::FRONTRIGHT);
				break;
			case EMovingDirection::BACK:
				ServerUpdateMovingDirection(EMovingDirection::BACKRIGHT);
				break;
			}
		}
		else if (val < 0)
		{
			switch (MovingDirection)
			{
			case EMovingDirection::DEFAULT:
				ServerUpdateMovingDirection(EMovingDirection::LEFT);
				break;
			case EMovingDirection::FRONT:
				ServerUpdateMovingDirection(EMovingDirection::FRONTLEFT);
				break;
			case EMovingDirection::BACK:
				ServerUpdateMovingDirection(EMovingDirection::BACKLEFT);
				break;
			}
		}
		else
		{
			switch (MovingDirection)
			{
			case EMovingDirection::FRONTRIGHT:
				ServerUpdateMovingDirection(EMovingDirection::FRONT);
				break;
			case EMovingDirection::RIGHT:
				ServerUpdateMovingDirection(EMovingDirection::DEFAULT);
				break;
			case EMovingDirection::BACKRIGHT:
				ServerUpdateMovingDirection(EMovingDirection::BACK);
				break;
			case EMovingDirection::BACKLEFT:
				ServerUpdateMovingDirection(EMovingDirection::BACK);
				break;
			case EMovingDirection::LEFT:
				ServerUpdateMovingDirection(EMovingDirection::DEFAULT);
				break;
			case EMovingDirection::FRONTLEFT:
				ServerUpdateMovingDirection(EMovingDirection::FRONT);
				break;
			default:
				break;
			}
		}
	}
}

void ATHCharacterBase::Turn(float val)
{
	if (!IsClimbing())
	{
		//AddControllerYawInput(val);
		FRotator rot = GetActorRotation();
		MovementComponent->UpdateBasedRotation(rot, FRotator(0.f, val, 0.f));
	}
	else
	{
		// TODO: Turn Camera With Head
	}
}

void ATHCharacterBase::LookUp(float val)
{
	//AddControllerPitchInput(val);
	FRotator rot = GetActorRotation();
	MovementComponent->UpdateBasedRotation(rot, FRotator(-val, 0.f, 0.f));
}

void ATHCharacterBase::SyncSpeed(float& Speed)
{
	Speed = GetVelocity().Size();
}

void ATHCharacterBase::SyncbJump(bool& Jump)
{
	Jump = bJump;
}

void ATHCharacterBase::SyncbFalling(bool& Falling)
{
	Falling = MovementComponent->IsFalling();
}

void ATHCharacterBase::SyncStandToSparint(bool& STS)
{
	STS = bStandToSprint;
}

void ATHCharacterBase::SyncIdleType(EIdleType& Idle)
{
	Idle = IdleType;
}

void ATHCharacterBase::SyncMovementType(EMovementType& Movement)
{
	Movement = MovementType;
}

void ATHCharacterBase::SyncMovingDirection(EMovingDirection& Moving)
{
	Moving = MovingDirection;
}

void ATHCharacterBase::SyncbFullBodyMotion(bool& FullBody)
{
	FullBody = bFullBodyMotion;
}

void ATHCharacterBase::SyncbUpperClimb(bool& Upper)
{
	Upper = bUpperClimbTrigger;
}

void ATHCharacterBase::SyncbMiddleClimb(bool& Middle)
{
	Middle = bMiddleClimbTrigger;
}

void ATHCharacterBase::SyncbLowerClimb(bool& Lower)
{
	Lower = bLowerClimbTrigger;
}

void ATHCharacterBase::SyncMovementMode(TEnumAsByte<EMovementMode>& MovementMode)
{
	MovementMode = MovementComponent->MovementMode;
}

void ATHCharacterBase::SyncbLayeredMotion(bool& LayeredMotion)
{
	LayeredMotion = bLayeredMotion;
}

void ATHCharacterBase::SyncLayeredAction(ELayeredAction& Layered)
{
	Layered = LayeredAction;
}

void ATHCharacterBase::SyncInteractionType(EInteractionType& Interaction)
{
	Interaction = InteractionType;
}

void ATHCharacterBase::SyncHP(float& Hp)
{
	Hp = HP;
}

void ATHCharacterBase::SyncbDead(bool& Dead)
{
	Dead = bDead;
}

void ATHCharacterBase::ReceiveDamage(const float& damage)
{
	ServerUpdateHP(damage * -1);
	UE_LOG(THVerbose, Verbose, TEXT("%s: Got %f Damage. HP = %f"), *FString(__FUNCTION__), damage, HP);
	if (!bDead && (HP <= 0.0f))
	{
		SetCharacterDead();
	}
}

void ATHCharacterBase::ReceiveHeal(const float& heal)
{
	ServerUpdateHP(heal);
	UE_LOG(THVerbose, Verbose, TEXT("%s: Got %f Heal. HP = %f"), *FString(__FUNCTION__), heal, HP);
}

void ATHCharacterBase::AddtoBuffer(FString input)
{
	ServerAddHitObject(input);
}

void ATHCharacterBase::RemovefromBuffer(FString input)
{
	ServerRemoveHitObject(input);
}

bool ATHCharacterBase::IsValidinBuffer(const FString input)
{
	return HitObject.Contains(input);
}

void ATHCharacterBase::ResetBuffer()
{
	ServerResetHitObject();
}

void ATHCharacterBase::Flush()
{
	//Implement when it need
}

void ATHCharacterBase::AddtoMemory(FString input)
{
	ServerAddAlly(input);
}

void ATHCharacterBase::RemovefromMemory(FString input)
{
	ServerRemoveAlly(input);
}

bool ATHCharacterBase::IsValidinMemory(const FString input)
{
	return Ally.Contains(input);
}

void ATHCharacterBase::ResetMemory()
{
	ServerResetAlly();
}

void ATHCharacterBase::Activate()
{
	ServerEnableCollision();
}

FString ATHCharacterBase::GetID()
{
	return UKismetSystemLibrary::GetObjectName(this);
}

void ATHCharacterBase::InActivate()
{
	ServerDisableCollision();
}

void ATHCharacterBase::Reset()
{
	//TODO: Implement When Character Implement Success
}

bool ATHCharacterBase::IsAttachable(IAttachable* Input)
{
	auto attachPiece = Cast<ATHAttachPieceBase>(Input);
	return (HoldingPiece == nullptr) || ((HoldingPiece == attachPiece) && !(HoldingPiece->GetID().Equals(attachPiece->GetID())));
}

bool ATHCharacterBase::IsDetachable()
{
	return (HoldingPiece != nullptr);
}

void ATHCharacterBase::Attach(IAttachable* Input)
{
	if (Input->IsAttachable(this))
	{
		UE_LOG(THVerbose, Verbose, TEXT("%s Attach Occur"), *FString(__FUNCTION__));
		ATHAttachPieceBase* AttachInput = Cast<ATHAttachPieceBase>(Input);
		ServerAttach(AttachInput);
		ServerUpdateHoldingPiece(AttachInput);
		if (HoldingPiece == AttachInput)
		{
			UE_LOG(THVerbose, Verbose, TEXT("%s Successfully Set HoldingPiece to AttachInput"), *FString(__FUNCTION__));
			HoldingPiece->InActivate();
		}
		ServerUpdateInteractionType(EInteractionType::ATTACH);
		if (IsLocallyControlled())
		{
			UE_LOG(THVerbose, Verbose, TEXT("%s HoldingPiece is Cleared now: %s"), *FString(__FUNCTION__), GETBOOLSTRING(HoldingPiece == nullptr));
			UE_LOG(THVerbose, Verbose, TEXT("%s HoldingPiece: %s"), *FString(__FUNCTION__), GETBOOLSTRING(HoldingPiece == Cast<ATHAttachPieceBase>(Input)));
			UE_LOG(THVerbose, Verbose, TEXT("%s On Start Overlap With Piece, InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
		}
	}
}

void ATHCharacterBase::Attach(IAttachActivity* Input)
{
	ATHAttachPieceBase* DetachedPiece = nullptr;
	ServerAttachTo(Cast<ATHAttachLatchBase>(Input), DetachedPiece);
	if (DetachedPiece != nullptr)
	{
		DetachedPiece->InActivate();
	}
	if (IsLocallyControlled())
	{
		UE_LOG(THVerbose, Verbose, TEXT("%s HoldingPiece is Cleared now: %s"), *FString(__FUNCTION__), GETBOOLSTRING(HoldingPiece == nullptr));
		UE_LOG(THVerbose, Verbose, TEXT("%s HoldingPiece: %s"), *FString(__FUNCTION__), GETBOOLSTRING(Cast<ATHAttachPieceBase>(DetachedPiece) == HoldingPiece));
		UE_LOG(THVerbose, Verbose, TEXT("%s On Start Overlap With Piece, InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
	}
}

IAttachable* ATHCharacterBase::Detach()
{
	ATHAttachPieceBase* ret = nullptr;
	ServerDetach(ret);
	if (ret != nullptr)
	{
		ret->Activate();
		ServerUpdateHoldingPiece(nullptr);
	}
	return ret;
}

void ATHCharacterBase::AddMovement(const FVector vector, float val)
{
	if (val != 0)
	{
		switch (IdleType)
		{
		case EIdleType::STAND:
			{
				if (MovementType == EMovementType::DEFAULT)
				{
					if (bStandToSprint)
					{	// Sprint
						bStandToSprint = false;
						ServerUpdateMovementType(EMovementType::SPRINT);
					}
					else
					{	// Walk
						ServerUpdateMovementType(EMovementType::WALK);
						//UE_LOG(THVerbose, Verbose, TEXT("MovementType: %s"), *GETENUMSTRING("EMovementType", MovementType));
					}
				}
				//AddMovementInput(vector, val); 
				MovementComponent->AddInputVector(vector * val);
				
			}
			break;

		case EIdleType::CROUCH:
			{
				bStandToSprint = false;
				ServerUpdateMovementType(EMovementType::WALK);
				//AddMovementInput(vector, val); 
				MovementComponent->AddInputVector(vector * val);
			}
			break;

		case EIdleType::LADDER:
		case EIdleType::ROPE:
		case EIdleType::WALL:
			//ServerUpdateMovementType(EMovementType::CLIMB);
			MovementComponent->AddInputVector(vector * val);
			//AddMovementInput(vector, val);
			break;
		}
	}
}

void ATHCharacterBase::SetCharacterDead()
{
	ServerUpdatebFullBodyMotion(true);
	ServerUpdatebDead(true);
	SetActorEnableCollision(false);

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("bDead is %s"), (bDead ? TEXT("true") : TEXT("false"))));
	UE_LOG(THVerbose, Verbose, TEXT("bDead is %s"), (bDead ? TEXT("true") : TEXT("false")));
}

void ATHCharacterBase::ExitClimb()
{
	ServerUpdateMovingDirection(EMovingDirection::DEFAULT);
	ServerUpdateMovementType(EMovementType::DEFAULT);
	ServerUpdateMovementMode(EMovementMode::MOVE_Walking);
	ServerUpdateIdleType(EIdleType::STAND);
	ServerUpdateMovementType(EMovementType::DEFAULT);
	ServerUpdatebFullBodyMotion(false);
}

void ATHCharacterBase::EnterClimb()
{	
	ServerUpdateMovementMode(EMovementMode::MOVE_Flying);
	ServerUpdateIdleType(InteractableClimb);
	//ServerUpdateMovementType(EMovementType::CLIMB);
	ServerUpdatebFullBodyMotion(true);
}

bool ATHCharacterBase::IsClimbing()
{
	return bFullBodyMotion && (MovementComponent->MovementMode == EMovementMode::MOVE_Flying) && ((IdleType == EIdleType::ROPE) || (IdleType == EIdleType::LADDER) || (IdleType == EIdleType::WALL));
}

bool ATHCharacterBase::IsClimbUp()
{
	return IsClimbing() && (MovementComponent->Velocity.Size() > 0.f) && (MovingDirection == EMovingDirection::UPSIDE);
}

bool ATHCharacterBase::IsClimbDown()
{
	return IsClimbing() && (MovementComponent->Velocity.Size() > 0.f) && (MovingDirection == EMovingDirection::DOWNSIDE);
}

bool ATHCharacterBase::IsAttachToTop()
{
	return !bUpperClimbTrigger && !bMiddleClimbTrigger && bLowerClimbTrigger;
}

bool ATHCharacterBase::IsAttachToBottom()
{
	return bUpperClimbTrigger && bMiddleClimbTrigger && !bLowerClimbTrigger;
}

bool ATHCharacterBase::IsAbleToClimb()
{
	return bUpperClimbTrigger || bMiddleClimbTrigger || bLowerClimbTrigger;
}

bool ATHCharacterBase::IsMeleeAttack()
{
	return bLayeredMotion && (LayeredAction == ELayeredAction::MELEEATTACK);
}
