// Fill out your copyright notice in the Description page of Project Settings.


#include "THCharacterBase.h"
#include "TreasureHunter.h"
#include "ConstructorHelpers.h"
#include "Animation/THAnimInstanceBase.h"
#include "Animation/THCharacterMovementComponent.h"
#include "camera/CameraComponent.h"
#include "Object/THProjectileBase.h"
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
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(35.0f, -3.5f, -164.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetupAttachment(FPCameraComponent);
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetIsReplicated(true);

	MovementComponent = Cast<UTHCharacterMovementComponent>(GetMovementComponent());
	if (MovementComponent)
	{
		MovementComponent->UpdatedComponent = GetCapsuleComponent();
		CrouchedEyeHeight = MovementComponent->CrouchedHalfHeight * 0.8f;
		MovementComponent->SetIsReplicated(true);
	}

	InteractionTrigger = AddNewInteractionTrigger(TEXT("Interaction"), 30.f, 100.f, FVector(50.f, 0.f, 0.f));

	UpperClimbTrigger = AddUpperClimbTrigger(TEXT("UpperClimb"), 20.f, 30.f, FVector(60.f, 0.f, 150.f), FRotator(0.f, 0.f, 90.f));
	MiddleClimbTrigger = AddMiddleClimbTrigger(TEXT("MiddleClimb"), 20.f, 30.f, FVector(60.f, 0.f, 0.f), FRotator(0.f, 0.f, 90.f));
	LowerClimbTrigger = AddLowerClimbTrigger(TEXT("LowerClimb"), 20.f, 30.f, FVector(60.f, 0.f, -150.f), FRotator(0.f, 0.f, 90.f));

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

	bReplicates = true;
	SetReplicatingMovement(true);

	GetCharacterMovement()->MaxWalkSpeed = 800.0f;

	bJump = false;
	IdleType = EIdleType::STAND;
	MovementType = EMovementType::DEFAULT;
	MovingDirection = EMovingDirection::DEFAULT;
	EnterDirection = EEnterDirection::DEFAULT;
	ExitDirection = EExitDirection::BOTTOM;
	bFullBodyMotion = false;
	bUpward = false;
	bDead = false;
	bLayeredMotion = false;
	bStandToSprint = false;
	HP = 100;
	OverlappedPiece = nullptr;
	AttachedPiece = nullptr;
	OverlappedLatch = nullptr;
	FirstHitPart = nullptr;
	HitOpposite = nullptr;
	InteractionType = EInteractionType::DEFAULT;
	AttachSequence = EAttachSequence::DEFAULT;
	bUpperClimbTrigger = false;
	bMiddleClimbTrigger = false;
	bLowerClimbTrigger = false;
	InteractableClimb = EIdleType::STAND;
	GetCharacterMovement()->JumpZVelocity = 500.0f;
}

void ATHCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
//	MovementComponent = Cast<UTHCharacterMovementComponent>(Super::GetMovementComponent());
	/*
	UE_LOG(THVerbose, Verbose, TEXT("%s: Controller = %s"), *FString(__FUNCTION__), GETBOOLSTRING(Controller != nullptr));
	UE_LOG(THVerbose, Verbose, TEXT("%s: Local - Role_Authority = %s"), *FString(__FUNCTION__), GETBOOLSTRING(GetLocalRole() == ROLE_Authority));
	UE_LOG(THVerbose, Verbose, TEXT("%s: Local - Role_SimulatedProxy = %s"), *FString(__FUNCTION__), GETBOOLSTRING(GetLocalRole() == ROLE_SimulatedProxy));
	UE_LOG(THVerbose, Verbose, TEXT("%s: Local - ROLE_AutonomousProxy = %s"), *FString(__FUNCTION__), GETBOOLSTRING(GetLocalRole() == ROLE_AutonomousProxy));
	UE_LOG(THVerbose, Verbose, TEXT("%s: Remote - Role_Authority = %s"), *FString(__FUNCTION__), GETBOOLSTRING(GetRemoteRole() == ROLE_Authority));
	UE_LOG(THVerbose, Verbose, TEXT("%s: Remote - Role_SimulatedProxy = %s"), *FString(__FUNCTION__), GETBOOLSTRING(GetRemoteRole() == ROLE_SimulatedProxy));
	UE_LOG(THVerbose, Verbose, TEXT("%s: Remote - ROLE_AutonomousProxy = %s"), *FString(__FUNCTION__), GETBOOLSTRING(GetRemoteRole() == ROLE_AutonomousProxy));
	*/
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
	DOREPLIFETIME(ATHCharacterBase, EnterDirection);
	DOREPLIFETIME(ATHCharacterBase, ExitDirection);
	DOREPLIFETIME(ATHCharacterBase, bUpward);
	DOREPLIFETIME(ATHCharacterBase, LayeredAction);
	DOREPLIFETIME(ATHCharacterBase, bFullBodyMotion);
	DOREPLIFETIME(ATHCharacterBase, bLayeredMotion);
	DOREPLIFETIME(ATHCharacterBase, bDead);
	DOREPLIFETIME(ATHCharacterBase, bStandToSprint);
	DOREPLIFETIME(ATHCharacterBase, HP);
	DOREPLIFETIME(ATHCharacterBase, OverlappedPiece);
	DOREPLIFETIME(ATHCharacterBase, AttachedPiece);
	DOREPLIFETIME(ATHCharacterBase, OverlappedLatch);
	DOREPLIFETIME(ATHCharacterBase, InteractionType);
	DOREPLIFETIME(ATHCharacterBase, AttachSequence);
	DOREPLIFETIME(ATHCharacterBase, FirstHitPart);
	DOREPLIFETIME(ATHCharacterBase, HitOpposite);
	DOREPLIFETIME(ATHCharacterBase, MovementComponent);
	DOREPLIFETIME(ATHCharacterBase, bUpperClimbTrigger);
	DOREPLIFETIME(ATHCharacterBase, bMiddleClimbTrigger);
	DOREPLIFETIME(ATHCharacterBase, bLowerClimbTrigger);
	DOREPLIFETIME(ATHCharacterBase, InteractableClimb);
}

// Called every frame
void ATHCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
	UE_LOG(THVerbose, Verbose, TEXT("%s CurrentSpeed = %f"), *FString(__FUNCTION__), GetVelocity().Size());
	if (!bLowerClimbTrigger)
	{
		if (GetRemoteRole() == ROLE_AutonomousProxy)
		{
			UE_LOG(THVerbose, Verbose, TEXT("%s MovementType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementType", MovementType));
			UE_LOG(THVerbose, Verbose, TEXT("%s MovingDirection: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovingDirection", MovingDirection));
		}
		
		UE_LOG(THVerbose, Verbose, TEXT("%s IdleType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", IdleType));
		UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
	}
	*/
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

void ATHCharacterBase::SyncLocomotionAnimTrigger(float& Speed, bool& Jump, bool& Falling, bool& StandToSprint, EIdleType& Idle, EMovementType& Movement, EMovingDirection& Moving)
{
	Speed = GetVelocity().Size();
	Jump = bJump;
	Falling = MovementComponent->IsFalling();
	StandToSprint = bStandToSprint;
	Idle = IdleType;
	Movement = MovementType;
	Moving = MovingDirection;
}

void ATHCharacterBase::SyncFullBodyAnimTrigger(bool& LayeredMotion, bool& FullBodyMotion, bool& Upward, bool& Dead, bool& UpperClimb, bool& MiddleClimb, bool& LowerClimb, ELayeredAction& Layered, EInteractionType& Interaction, TEnumAsByte<enum EMovementMode>& MovementMode)
{
	LayeredMotion = bLayeredMotion;
	FullBodyMotion = bFullBodyMotion;
	Upward = bUpward;
	Dead = bDead;
	UpperClimb = bUpperClimbTrigger;
	MiddleClimb = bMiddleClimbTrigger;
	LowerClimb = bLowerClimbTrigger;
	Layered = LayeredAction;
	Interaction = InteractionType;
	MovementMode = MovementComponent->MovementMode;
}

void ATHCharacterBase::SyncStatusAnimTrigger(float& Hp)
{
	Hp = HP;
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
	else
	{
		//UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
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

void ATHCharacterBase::UpdateExitDirection(EExitDirection Exit)
{
	ServerUpdateExitDirection(Exit);
}

void ATHCharacterBase::ReceiveDamage(float damage)
{
	ServerUpdateHP(-1 * damage);
	UE_LOG(THVerbose, Verbose, TEXT("%s: Got %f Damage. HP = %f"), *FString(__FUNCTION__), damage, HP);
	if (!bDead && (HP <= 0.0f))
	{
		SetCharacterDead();
	}
}

void ATHCharacterBase::OnHitStartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp && OverlappedComp)
	{
		auto Character = Cast<ATHCharacterBase>(OtherComp->GetOwner());
		auto SelfCharacter = Cast<ATHCharacterBase>(OverlappedComp->GetOwner());
		auto Hit = Cast<UCapsuleComponent>(OtherComp);
		auto Self = Cast<UCapsuleComponent>(OverlappedComp);
		if (Character && Hit && (Character != SelfCharacter))
		{
			if (LayeredAction == ELayeredAction::MELEEATTACK)
			{
				if ((FirstHitPart == nullptr) && (HitOpposite == nullptr))
				{
					Character->ReceiveDamage(20.f);
					FirstHitPart = Self;
					HitOpposite = Hit;
					UE_LOG(THVerbose, Verbose, TEXT("%s: Hit Occur. Lock the FirstHitPart. IsLock = %s"), *FString(__FUNCTION__), ((FirstHitPart != nullptr) ? TEXT("true") : TEXT("false")));
				}
				else if ((FirstHitPart == Self) && (HitOpposite == Hit))
				{
					FirstHitPart = nullptr;
					HitOpposite = nullptr;
					UE_LOG(THVerbose, Verbose, TEXT("%s: UnLock the FirstHitPart. IsLock = %s"), *FString(__FUNCTION__), ((FirstHitPart != nullptr) ? TEXT("true") : TEXT("false")));
				}
			}
		}
	}
}

void ATHCharacterBase::OnHitEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp)
	{
		auto Character = Cast<ATHCharacterBase>(OtherComp->GetOwner());
		auto SelfCharacter = Cast<ATHCharacterBase>(OverlappedComp->GetOwner());
		auto Hit = Cast<UCapsuleComponent>(OtherComp);
		if (Character && Hit && (Character != SelfCharacter))
		{
			if (LayeredAction == ELayeredAction::MELEEATTACK)
			{
				if (Hit == FirstHitPart)
				{
					//FirstHitPart = nullptr;
				}
				//UE_LOG(THVerbose, Verbose, TEXT("%s: Hit = %s"), *FString(__FUNCTION__), ((FirstHitPart != nullptr) ? TEXT("true") : TEXT("false")));
			}
		}
	}
}

void ATHCharacterBase::OnPieceStartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ATHPieceBase* piece = Cast<ATHPieceBase>(OtherActor);
		if (piece)
		{
			OverlappedPiece = piece;
			ServerUpdateAttachSequence(EAttachSequence::ATTACHABLE);
			UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedPiece: %s"), *FString(__FUNCTION__), (OverlappedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(THVerbose, Verbose, TEXT("%s AttachedPiece: %s"), *FString(__FUNCTION__), (AttachedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedLatch: %s"), *FString(__FUNCTION__), (OverlappedLatch == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(THVerbose, Verbose, TEXT("%s On Start Overlap With Latch, AttachSequence: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EAttachSequence", AttachSequence));
			UE_LOG(THVerbose, Verbose, TEXT("%s On Start Overlap With Latch, InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
		}
	}
}

void ATHCharacterBase::OnPieceEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		ATHPieceBase* piece = Cast<ATHPieceBase>(OtherActor);
		if (piece && (piece == OverlappedPiece))
		{
			OverlappedPiece = nullptr;
			if (AttachedPiece)
			{
				ServerUpdateAttachSequence(EAttachSequence::ATTACH);
			}
			else
			{
				ServerUpdateAttachSequence(EAttachSequence::ATTACHABLE);
			}
			UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedPiece: %s"), *FString(__FUNCTION__), (OverlappedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(THVerbose, Verbose, TEXT("%s AttachedPiece: %s"), *FString(__FUNCTION__), (AttachedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedLatch: %s"), *FString(__FUNCTION__), (OverlappedLatch == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(THVerbose, Verbose, TEXT("%s On Start Overlap With Latch, AttachSequence: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EAttachSequence", AttachSequence));
			UE_LOG(THVerbose, Verbose, TEXT("%s On Start Overlap With Latch, InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
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
			if (MovementComponent->MovementMode == EMovementMode::MOVE_Walking)
			{
				ServerUpdateInteractionType(EInteractionType::CLIMB);
				//UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
				ServerUpdateInteractableClimb(Climb->GetIdleType());
				//UE_LOG(THVerbose, Verbose, TEXT("%s InteractableClimb: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", InteractableClimb));
				//UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
			}
			//UE_LOG(THVerbose, Verbose, TEXT("%s bUpperClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bUpperClimbTrigger));
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
			if (MovementComponent->MovementMode == EMovementMode::MOVE_Walking)
			{
				ServerUpdateInteractionType(EInteractionType::CLIMB);
				//UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
				ServerUpdateInteractableClimb(Climb->GetIdleType());
				//UE_LOG(THVerbose, Verbose, TEXT("%s InteractableClimb: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", InteractableClimb));
				//UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
			}
			//UE_LOG(THVerbose, Verbose, TEXT("%s bMiddleClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bMiddleClimbTrigger));
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
			if (MovementComponent->MovementMode == EMovementMode::MOVE_Walking)
			{
				ServerUpdateInteractionType(EInteractionType::CLIMB);
				//UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
				ServerUpdateInteractableClimb(Climb->GetIdleType());
				//UE_LOG(THVerbose, Verbose, TEXT("%s InteractableClimb: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", InteractableClimb));
				//UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
			}
			//UE_LOG(THVerbose, Verbose, TEXT("%s bLowerClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bLowerClimbTrigger));
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
			//UE_LOG(THVerbose, Verbose, TEXT("%s End UpperClimbTrigger Overlap!!"), *FString(__FUNCTION__));
			ServerUpdatebUpperClimbTrigger(false);
			//UE_LOG(THVerbose, Verbose, TEXT("%s bUpperClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bUpperClimbTrigger));
			if (MovementComponent->MovementMode == EMovementMode::MOVE_Flying)
			{
				if ((MovingDirection == EMovingDirection::UPSIDE) || (MovingDirection == EMovingDirection::DEFAULT))
				{
					if (bMiddleClimbTrigger && bLowerClimbTrigger)
					{	//If TopTrigger is false during MovementMode is MOVE_Flying, Character Exit to Top
						ExitClimb();
					}
				}
				UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
				UE_LOG(THVerbose, Verbose, TEXT("%s IdleType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", IdleType));
				UE_LOG(THVerbose, Verbose, TEXT("%s MovementType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementType", MovementType));
				UE_LOG(THVerbose, Verbose, TEXT("%s bFullBodyMotion: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bFullBodyMotion));
			}
			else
			{
				ServerUpdateInteractionType(EInteractionType::DEFAULT);
				UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
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
		//	UE_LOG(THVerbose, Verbose, TEXT("%s bMiddleClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bMiddleClimbTrigger)); 
			if (MovementComponent->MovementMode == EMovementMode::MOVE_Walking)
			{
				ServerUpdateInteractionType(EInteractionType::DEFAULT);
				//UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
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
			//UE_LOG(THVerbose, Verbose, TEXT("%s End LowerClimbTrigger Overlap!!"), *FString(__FUNCTION__));
			ServerUpdatebLowerClimbTrigger(false);
			//UE_LOG(THVerbose, Verbose, TEXT("%s bLowerClimbTrigger: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bLowerClimbTrigger));
			if (MovementComponent->MovementMode == EMovementMode::MOVE_Flying)
			{
				if ((MovingDirection == EMovingDirection::DOWNSIDE) || (MovingDirection == EMovingDirection::DEFAULT))
					//TODO: Need to Add Condition when MovingDirection is Default.
				{
					if (bUpperClimbTrigger && bMiddleClimbTrigger)
					{	//If LowerTrigger is false during MovementMode is MOVE_Flying, Character Exit to Bottom
						ExitClimb();
					}
				}
				UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
				UE_LOG(THVerbose, Verbose, TEXT("%s IdleType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", IdleType));
				UE_LOG(THVerbose, Verbose, TEXT("%s MovementType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementType", MovementType));
				UE_LOG(THVerbose, Verbose, TEXT("%s bFullBodyMotion: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bFullBodyMotion));
			}
			else
			{
				ServerUpdateInteractionType(EInteractionType::DEFAULT);
				UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
			}
		}
	}
}

void ATHCharacterBase::OnLatchStartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto latch = Cast<ATHLatchBase>(OtherActor);
		if (latch)
		{
			OverlappedLatch = latch;
			if (AttachedPiece)
			{
				// Overlap with Holding Piece
				ServerUpdateAttachSequence(EAttachSequence::SUBMITTABLE);
			}
			else if(latch->GetPiece())
			{
				// Overlap without Holding Piece
				ServerUpdateAttachSequence(EAttachSequence::ATTACHABLE);
			}
			UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedPiece: %s"), *FString(__FUNCTION__), (OverlappedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(THVerbose, Verbose, TEXT("%s AttachedPiece: %s"), *FString(__FUNCTION__), (AttachedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedLatch: %s"), *FString(__FUNCTION__), (OverlappedLatch == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(THVerbose, Verbose, TEXT("%s On Start Overlap With Latch, AttachSequence: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EAttachSequence", AttachSequence));
			UE_LOG(THVerbose, Verbose, TEXT("%s On Start Overlap With Latch, InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
		}
	}
}

void ATHCharacterBase::OnLatchEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		auto latch = Cast<ATHLatchBase>(OtherActor);
		if (latch && (OverlappedLatch == latch))
		{
			OverlappedLatch = nullptr;
			if (AttachedPiece)
			{
				// Holding Piece
				ServerUpdateAttachSequence(EAttachSequence::ATTACH);
			}
			else
			{
				// Not Holding Piece
				ServerUpdateAttachSequence(EAttachSequence::DEFAULT);
			}
			UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedPiece: %s"), *FString(__FUNCTION__), (OverlappedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(THVerbose, Verbose, TEXT("%s AttachedPiece: %s"), *FString(__FUNCTION__), (AttachedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedLatch: %s"), *FString(__FUNCTION__), (OverlappedLatch == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(THVerbose, Verbose, TEXT("%s On Start Overlap With Latch, AttachSequence: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EAttachSequence", AttachSequence));
			UE_LOG(THVerbose, Verbose, TEXT("%s On Start Overlap With Latch, InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
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
		//DisableInput(GetStagePlayerController());
		AnimInstance->Montage_Play(MontageToPlay, InPlayRate, ReturnValueType, InTimeToStartMontageAt, bStopAllMontages);
		//EnableInput(GetStagePlayerController());
	}
	if ((FirstHitPart != nullptr) || (HitOpposite != nullptr))
	{
		FirstHitPart = nullptr;
		HitOpposite = nullptr;
		//UE_LOG(THVerbose, Verbose, TEXT("%hs: UnLock the FirstHitPart. IsLock = %s"), __FUNCTION__, *GETBOOLSTRING((FirstHitPart != nullptr)));
		//... Why log occur error?
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

void ATHCharacterBase::ServerUpdateEnterDirection_Implementation(EEnterDirection Direction)
{
	MulticastUpdateEnterDirection(Direction);
}

bool ATHCharacterBase::ServerUpdateEnterDirection_Validate(EEnterDirection Direction)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateEnterDirection_Implementation(EEnterDirection Direction)
{
	EnterDirection = Direction;
}

void ATHCharacterBase::ServerUpdateExitDirection_Implementation(EExitDirection Direction)
{
	MulticastUpdateExitDirection(Direction);
}

bool ATHCharacterBase::ServerUpdateExitDirection_Validate(EExitDirection Direction)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateExitDirection_Implementation(EExitDirection Direction)
{
	ExitDirection = Direction;
}

void ATHCharacterBase::ServerUpdatebUpward_Implementation(bool Upward)
{
	MulticastUpdatebUpward(Upward);
}

bool ATHCharacterBase::ServerUpdatebUpward_Validate(bool Upward)
{
	return true;
}

void ATHCharacterBase::MulticastUpdatebUpward_Implementation(bool Upward)
{
	bUpward = Upward;
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
	//UE_LOG(THVerbose, Verbose, TEXT("%s before MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
	MovementComponent->SetMovementMode(Mode);
	//UE_LOG(THVerbose, Verbose, TEXT("%s after MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
}

UCapsuleComponent* ATHCharacterBase::AddNewHitTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FName& AttachedSocket, const FVector& RelativeLocation, const FRotator& RelativeRotation)
{
	auto Trigger = CreateDefaultSubobject<UCapsuleComponent>(SubobjectName);
	Trigger->InitCapsuleSize(Radius, HalfHeight);
	Trigger->SetRelativeLocation(RelativeLocation);
	Trigger->SetRelativeRotation(RelativeRotation);
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	Trigger->SetupAttachment(GetMesh(), AttachedSocket);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATHCharacterBase::OnHitStartOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ATHCharacterBase::OnHitEndOverlap);
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
		Super::Jump();
		//TODO: If possible, Jump it with MovementComponent
		//	TODO: Repeat with delay
		break;
	case EIdleType::LADDER:
	case EIdleType::ROPE:
	case EIdleType::WALL:
		ExitClimb();
		UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
		UE_LOG(THVerbose, Verbose, TEXT("%s IdleType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", IdleType));
		UE_LOG(THVerbose, Verbose, TEXT("%s MovementType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementType", MovementType));
		//ServerUpdateInteractionType(EInteractionType::CLIMB);
		//UE_LOG(THVerbose, Verbose, TEXT("%s InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
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
	if (OverlappedPiece || AttachedPiece || OverlappedLatch)
	{
		ServerUpdateInteractionType(EInteractionType::ATTACH);
	}
	switch (InteractionType)
	{
	case EInteractionType::ATTACH:
		switch (AttachSequence)
		{
		case EAttachSequence::ATTACHABLE:
			if (OverlappedLatch)
			{
				//Attach Piece from Latch to Character
				OverlappedPiece = OverlappedLatch->WithdrawPiece();
				AttachPiece(TEXT("socket_melee_r"));
				ServerUpdateAttachSequence(EAttachSequence::SUBMITTABLE);
			}
			else
			{
				//Attach Piece to Character
				AttachPiece(TEXT("socket_melee_r"));
				ServerUpdateAttachSequence(EAttachSequence::ATTACH);
			}
			break;
		case EAttachSequence::ATTACH:
			if (OverlappedPiece)
			{
				//Switch Attached Piece and NOT Attached Piece
				auto detaching = DetachPiece();
				AttachPiece(TEXT("socket_melee_r"));
				OverlappedPiece = detaching;
			}
			else if (AttachedPiece)
			{
				//Detach Piece
				OverlappedPiece = DetachPiece();
				ServerUpdateAttachSequence(EAttachSequence::ATTACHABLE);
			}
			break;
		case EAttachSequence::SUBMITTABLE:
			if (OverlappedLatch->GetPiece())
			{
				//Switch Piece from Latch and Piece from Character
				auto temp = OverlappedLatch->WithdrawPiece();
				OverlappedLatch->SubmitPiece(DetachPiece());
				OverlappedPiece = temp;
				AttachPiece(TEXT("socket_melee_r"));
			}
			else
			{
				//Attach Piece to Latch
				OverlappedLatch->SubmitPiece(DetachPiece());
				ServerUpdateAttachSequence(EAttachSequence::ATTACHABLE);
			}
			if (OverlappedLatch->IsCorrectPair())
			{
				OverlappedLatch->OnCorrectAnswer.Broadcast();
			}
			//TODO: Check Answer. If Correct, Deactivate All Latches and Keys. Than, Open Wall.
			break;
		case EAttachSequence::DEFAULT:
			break;
		}
		ServerUpdatebLayeredMotion(true);
		ServerPlayMontage(InteractionMontage);
		UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedPiece: %s"), *FString(__FUNCTION__), (OverlappedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
		UE_LOG(THVerbose, Verbose, TEXT("%s AttachedPiece: %s"), *FString(__FUNCTION__), (AttachedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
		UE_LOG(THVerbose, Verbose, TEXT("%s OverlappedLatch: %s"), *FString(__FUNCTION__), (OverlappedLatch == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
		UE_LOG(THVerbose, Verbose, TEXT("%s On Start Overlap With Latch, AttachSequence: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EAttachSequence", AttachSequence));
		UE_LOG(THVerbose, Verbose, TEXT("%s On Start Overlap With Latch, InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
		break;
		//TODO: Play New Animation
	case EInteractionType::CLIMB:
		//From Climbing to Stand
		auto MovementMode = MovementComponent->MovementMode;
		if ((MovementMode == EMovementMode::MOVE_Walking) || (MovementMode == EMovementMode::MOVE_Falling))
		{
			if ((bUpperClimbTrigger && bMiddleClimbTrigger) || bLowerClimbTrigger)
			{
				EnterClimb();
			}
		}
		else if (MovementMode == EMovementMode::MOVE_Flying)
		{
			ExitClimb();
		}
		//UE_LOG(THVerbose, Verbose, TEXT("%s bFullBodyMotion: %s"), *FString(__FUNCTION__), GETBOOLSTRING(bFullBodyMotion));
		//UE_LOG(THVerbose, Verbose, TEXT("%s MovementMode: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementMode", MovementComponent->MovementMode));
		//UE_LOG(THVerbose, Verbose, TEXT("%s IdleType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", IdleType));
		//UE_LOG(THVerbose, Verbose, TEXT("%s MovementType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovementType", MovementType));
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
	//ServerUpdateInteractionType(EInteractionType::DEFAULT);
	ServerStopMontage(0.25f, InteractionMontage);
}

void ATHCharacterBase::MoveForward(float val)
{
	//UE_LOG(THVerbose, Verbose, TEXT("%s IdleType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EIdleType", IdleType));
	if ((IdleType == EIdleType::ROPE) || (IdleType == EIdleType::WALL) || (IdleType == EIdleType::LADDER))
	{
		//UE_LOG(THVerbose, Verbose, TEXT("%s Climb Move!"), *FString(__FUNCTION__));
		if (MovementComponent->MovementMode == EMovementMode::MOVE_Flying)
		{
			ServerUpdatebUpward(val > 0);
			if (val > 0.001)
			{
				ServerUpdateMovingDirection(EMovingDirection::UPSIDE);
			}
			else if (val < -0.001)
			{
				ServerUpdateMovingDirection(EMovingDirection::DOWNSIDE);
			}
			else
			{
				ServerUpdateMovingDirection(EMovingDirection::DEFAULT);
			}
			AddMovement(GetActorUpVector(), val);
			//UE_LOG(THVerbose, Verbose, TEXT("%s MovingDirection: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovingDirection", MovingDirection));
		}
	}
	else
	{
		//UE_LOG(THVerbose, Verbose, TEXT("%s Move on Ground"), *FString(__FUNCTION__));
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
		if (GetRemoteRole() == ROLE_AutonomousProxy)
		{
			UE_LOG(THVerbose, Verbose, TEXT("%s MovingDirection: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EMovingDirection", MovingDirection));
		}
	}
}

void ATHCharacterBase::MoveRight(float val)
{
	//Temporary block move right and left during climg
	if (!((IdleType == EIdleType::ROPE) || (IdleType == EIdleType::WALL) || (IdleType == EIdleType::LADDER)))
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
	if (MovementType != EMovementType::CLIMB)
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

void ATHCharacterBase::AttachPiece(FName Socket)
{
	if (OverlappedPiece)
	{
		AttachedPiece = OverlappedPiece;
		OverlappedPiece->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, Socket);
		UE_LOG(THVerbose, Verbose, TEXT("%s: Piece Index = %d"), *FString(__FUNCTION__), AttachedPiece->GetIndex());
		OverlappedPiece = nullptr;
	}
}

ATHPieceBase* ATHCharacterBase::DetachPiece()
{
	ATHPieceBase* temp = nullptr;
	if (AttachedPiece)
	{
		temp = AttachedPiece;
		AttachedPiece->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		temp->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 50);
		AttachedPiece = nullptr;
	}
	return temp;
}

void ATHCharacterBase::ExitClimb()
{
	ServerUpdateMovingDirection(EMovingDirection::DEFAULT);
	ServerUpdateMovementMode(EMovementMode::MOVE_Walking);
	ServerUpdateIdleType(EIdleType::STAND);
	ServerUpdateMovementType(EMovementType::DEFAULT);
	ServerUpdatebFullBodyMotion(false);
}

void ATHCharacterBase::EnterClimb()
{
	ServerUpdateMovementMode(EMovementMode::MOVE_Flying);
	ServerUpdateIdleType(InteractableClimb);
	ServerUpdateMovementType(EMovementType::CLIMB);
	ServerUpdatebFullBodyMotion(true);
}
