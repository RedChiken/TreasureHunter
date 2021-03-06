// Fill out your copyright notice in the Description page of Project Settings.


#include "THCharacterBase.h"
#include "TreasureHunter.h"
#include "ConstructorHelpers.h"
#include "Animation/THAnimInstanceBase.h"
#include "camera/CameraComponent.h"
#include "Object/THProjectileBase.h"
#include "THPieceBase.h"
#include "THLatchBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "net/UnrealNetwork.h"
#include "Engine.h"

// Sets default values
ATHCharacterBase::ATHCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(20.f, 96.f);
	CrouchedEyeHeight = 32.f;
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

	BodyHitBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BodyHitBox"));
	BodyHitBox->BodyInstance.SetCollisionProfileName("NormalHitBox");
	BodyHitBox->InitCapsuleSize(21.f, 80.f);
	BodyHitBox->SetRelativeLocation(FVector(-10.f, 0.f, -22.5f));
	BodyHitBox->OnComponentBeginOverlap.AddDynamic(this, &ATHCharacterBase::OnOverlapWithNormalHitBox);
	BodyHitBox->SetupAttachment(RootComponent);

	HeadHitBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HeadHitBox"));
	HeadHitBox->BodyInstance.SetCollisionProfileName("CriticalHitBox");
	HeadHitBox->InitCapsuleSize(10.f, 12.f);
	HeadHitBox->AddRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	HeadHitBox->OnComponentBeginOverlap.AddDynamic(this, &ATHCharacterBase::OnOverlapWithCriticalHitBox);
	HeadHitBox->SetupAttachment(RootComponent);
	
	MeleeLeft = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LeftMeleeHitBox"));
	MeleeLeft->BodyInstance.SetCollisionProfileName(TEXT("DamageBox"));
	MeleeLeft->InitCapsuleSize(6.f, 8.f);
	MeleeLeft->SetupAttachment(GetMesh(), TEXT("socket_melee_l"));

	MeleeRight = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RightMeleeHitBox"));
	//MeleeRight->BodyInstance.SetCollisionProfileName(TEXT("DamageBox"));
	//Right hand is not used to melee attack. so 
	MeleeRight->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeleeRight->InitCapsuleSize(6.f, 8.f);
	MeleeRight->SetupAttachment(GetMesh(), TEXT("socket_melee_r"));

	FrontTrigger.Add(CreateDefaultSubobject<UCapsuleComponent>(TEXT("Upper")));
	FrontTrigger.Add(CreateDefaultSubobject<UCapsuleComponent>(TEXT("Middle")));
	FrontTrigger.Add(CreateDefaultSubobject<UCapsuleComponent>(TEXT("Under")));

	for (int i = 0; i < 3; ++i)
	{
		FrontTrigger[i]->InitCapsuleSize(12.f, 24.f);
		FrontTrigger[i]->SetupAttachment(GetMesh());
		FrontTrigger[i]->BodyInstance.SetCollisionProfileName(TEXT("Trigger"));
		FrontTrigger[i]->SetRelativeLocation(FVector(0.f, 70.f, (2 - i) * 100.f));
		FrontTrigger[i]->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
		FrontTrigger[i]->OnComponentBeginOverlap.AddDynamic(this, &ATHCharacterBase::OnPieceStartOverlap);
		FrontTrigger[i]->OnComponentBeginOverlap.AddDynamic(this, &ATHCharacterBase::OnLatchStartOverlap);
		FrontTrigger[i]->OnComponentEndOverlap.AddDynamic(this, &ATHCharacterBase::OnPieceEndOverlap);
		FrontTrigger[i]->OnComponentEndOverlap.AddDynamic(this, &ATHCharacterBase::OnLatchEndOverlap);
	}
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
	bInInteractionRange = false;
	bAbleToClimb = false;
	HP = 100;
	OverlappedPiece = nullptr;
	AttachedPiece = nullptr;
	OverlappedLatch = nullptr;
	GetCharacterMovement()->JumpZVelocity = 500.0f;
}

void ATHCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
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
	DOREPLIFETIME(ATHCharacterBase, NearbyIdleType);
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
	DOREPLIFETIME(ATHCharacterBase, bInInteractionRange);
	DOREPLIFETIME(ATHCharacterBase, bAbleToClimb);
	DOREPLIFETIME(ATHCharacterBase, HP);
	DOREPLIFETIME(ATHCharacterBase, bClimbing);
	DOREPLIFETIME(ATHCharacterBase, OverlappedPiece);
	DOREPLIFETIME(ATHCharacterBase, AttachedPiece);
	DOREPLIFETIME(ATHCharacterBase, OverlappedLatch);
	DOREPLIFETIME(ATHCharacterBase, InteractionType);
	DOREPLIFETIME(ATHCharacterBase, AttachSequence);
}

// Called every frame
void ATHCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if ((MovementType != EMovementType::DEFAULT) && (getCurrentSpeed() < 0.001))
	{
		if (MovementType == EMovementType::SPRINT)
		{
			ServerUpdateSpeed(0.5f);
		}
		ServerUpdateMovementType(EMovementType::DEFAULT);
	}
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

float ATHCharacterBase::getCurrentSpeed()
{
	return this->GetVelocity().Size();
}

EIdleType ATHCharacterBase::getIdleType()
{
	return IdleType;
}

EMovementType ATHCharacterBase::getMovementType()
{
	return MovementType;
}

EMovingDirection ATHCharacterBase::getMovingDirection()
{
	return MovingDirection;
}

bool ATHCharacterBase::getbJump()
{
	return bJump;
}

bool ATHCharacterBase::getIsFalling()
{
	return GetMovementComponent()->IsFalling();
}

EEnterDirection ATHCharacterBase::getEnterDirection()
{
	return EnterDirection;
}

EExitDirection ATHCharacterBase::getExitDirection()
{
	return ExitDirection;
}

bool ATHCharacterBase::getbUpward()
{
	return bUpward;
}

ELayeredAction ATHCharacterBase::getLayeredAction()
{
	return LayeredAction;
}

bool ATHCharacterBase::getbFullBodyMotion()
{
	return bFullBodyMotion;
}

bool ATHCharacterBase::getbLayeredMotion()
{
	return bLayeredMotion;
}

bool ATHCharacterBase::getbDead()
{
	return bDead;
}

bool ATHCharacterBase::getbStandToSprint()
{
	return bStandToSprint;
}

float ATHCharacterBase::getHP()
{
	return HP;
}

bool ATHCharacterBase::getbInInteractionRange()
{
	return bInInteractionRange;
}

bool ATHCharacterBase::getbAbleToClimb()
{
	return bAbleToClimb;
}

bool ATHCharacterBase::getbClimbing()
{
	return bClimbing;
}

EInteractionType ATHCharacterBase::getInteractionType()
{
	return InteractionType;
}

void ATHCharacterBase::StopInteraction()
{
	OnInteractionReleased();
}

void ATHCharacterBase::UpdatebInInteractionRange(bool InInteractionRange)
{
	ServerUpdatebInInteractionRange(InInteractionRange);
}

void ATHCharacterBase::UpdateIdleType(EIdleType Idle)
{
	ServerUpdateIdleType(Idle);
}

void ATHCharacterBase::UpdateNearbyIdleType(EIdleType Idle)
{
	ServerUpdateNearbyIdleType(Idle);
}

void ATHCharacterBase::UpdateExitDirection(EExitDirection Exit)
{
	ServerUpdateExitDirection(Exit);
}

void ATHCharacterBase::ExitFromClimb(EExitDirection Exit)
{
	ServerUpdatebFullBodyMotion(false);
	ServerUpdatebClimbing(false);
	ServerUpdateIdleType(EIdleType::STAND);
	ServerUpdateEnterDirection(EEnterDirection::DEFAULT);
	ServerUpdateExitDirection(Exit);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	/*
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("bFullBodyMotion: %s"), (GETBOOLSTRING(bFullBodyMotion))));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("bClimbing: %s"), (GETBOOLSTRING(bClimbing))));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("IdleType: %s"), *GETENUMSTRING("EIdleType", IdleType)));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("EnterDirection: %s"), *GETENUMSTRING("EEnterDirection", EnterDirection)));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue,	FString::Printf(TEXT("ExitDirection: %s"),*GETENUMSTRING("EExitDirection", ExitDirection)));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("MovementMode: %s"), *GetCharacterMovement()->GetMovementName()));
	*/
}

void ATHCharacterBase::EnterToClimb(EEnterDirection Enter, EIdleType Nearby)
{
	ServerUpdatebInInteractionRange(true);
	ServerUpdatebAbleToClimb(true);
	ServerUpdateEnterDirection(Enter);
	ServerUpdateNearbyIdleType(Nearby);
	
	/*
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("bInInteractionRange: %s"), (GETBOOLSTRING(bInInteractionRange))));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("bClimbing: %s"), (GETBOOLSTRING(bClimbing))));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("NearbyIdleType: %s"), *GETENUMSTRING("EIdleType", NearbyIdleType)));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("EnterDirection: %s"), *GETENUMSTRING("EEnterDirection", EnterDirection)));
	*/
}

void ATHCharacterBase::GetOutofClimbArea()
{
	ServerUpdatebInInteractionRange(false);
	ServerUpdatebAbleToClimb(false);
	ServerUpdateEnterDirection(EEnterDirection::DEFAULT);
	ServerUpdateNearbyIdleType(EIdleType::DEFAULT);

	/*
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("bInInteractionRange: %s"), (GETBOOLSTRING(bInInteractionRange))));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("bAbleToClimb: %s"), (GETBOOLSTRING(bAbleToClimb))));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("EnterDirection: %s"), *GETENUMSTRING("EEnterDirection", EnterDirection)));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("NearbyIdleType: %s"), *GETENUMSTRING("EIdleType", NearbyIdleType)));*/
}

void ATHCharacterBase::ReceiveDamage(float damage, bool bCritical)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("Hit Character"));
	UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("Hit Character"));

	ServerUpdateHP((bCritical ? 2.5f : 1.0f) * damage);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("hit bullet! Rest HP is %f"), HP));
	UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("hit bullet! Rest HP is %f"), HP);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("HP: %f, bDead is %s"), HP,
		(bDead ? TEXT("True") : TEXT("False"))));
	if (!bDead && (HP <= 0.0f))
	{
		SetCharacterDead();
	}
}

void ATHCharacterBase::OnOverlapWithNormalHitBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlapWithHitBox(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult, false);
}

void ATHCharacterBase::OnOverlapWithCriticalHitBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlapWithHitBox(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult, true);
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
			UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s OverlappedPiece: %s"), *FString(__FUNCTION__), (OverlappedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s AttachedPiece: %s"), *FString(__FUNCTION__), (AttachedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s OverlappedLatch: %s"), *FString(__FUNCTION__), (OverlappedLatch == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("%s On Start Overlap With Latch, AttachSequence: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EAttachSequence", AttachSequence));
			UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("%s On Start Overlap With Latch, InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
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
			UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s OverlappedPiece: %s"), *FString(__FUNCTION__), (OverlappedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s AttachedPiece: %s"), *FString(__FUNCTION__), (AttachedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s OverlappedLatch: %s"), *FString(__FUNCTION__), (OverlappedLatch == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("%s On Start Overlap With Latch, AttachSequence: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EAttachSequence", AttachSequence));
			UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("%s On Start Overlap With Latch, InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
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
			UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s OverlappedPiece: %s"), *FString(__FUNCTION__), (OverlappedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s AttachedPiece: %s"), *FString(__FUNCTION__), (AttachedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s OverlappedLatch: %s"), *FString(__FUNCTION__), (OverlappedLatch == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("%s On Start Overlap With Latch, AttachSequence: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EAttachSequence", AttachSequence));
			UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("%s On Start Overlap With Latch, InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
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
			UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s OverlappedPiece: %s"), *FString(__FUNCTION__), (OverlappedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s AttachedPiece: %s"), *FString(__FUNCTION__), (AttachedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s OverlappedLatch: %s"), *FString(__FUNCTION__), (OverlappedLatch == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
			UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("%s On Start Overlap With Latch, AttachSequence: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EAttachSequence", AttachSequence));
			UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("%s On Start Overlap With Latch, InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
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
		AnimInstance->Montage_Stop(blendOut, Interaction);
	}
}

void ATHCharacterBase::ServerUpdateMovementType_Implementation(EMovementType type)
{
	//UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("Server before MovementType: %s"), *GETENUMSTRING("EMovementType", MovementType));
	MulticastUpdateMovementType(type);
	//UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("Server after MovementType: %s"), *GETENUMSTRING("EMovementType", MovementType));
}

bool ATHCharacterBase::ServerUpdateMovementType_Validate(EMovementType type)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateMovementType_Implementation(EMovementType type)
{
	//UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("Multicast before MovementType: %s"), *GETENUMSTRING("EMovementType", MovementType));
	MovementType = type;
	//UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("Multicast after MovementType: %s"), *GETENUMSTRING("EMovementType", MovementType));
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
	//UE_LOG(LogTH_PlayerBase_MovingDirection, Verbose, TEXT("MovingDirection change from %s to %s"), *GETENUMSTRING("EMovingDirection", MovingDirection), *GETENUMSTRING("EMovingDirection", direction));
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
	//UE_LOG(LogTH_PlayerBase_IdleType, Verbose, TEXT("IdleType change from %s to %s"), *GETENUMSTRING("EIdleType", IdleType), *GETENUMSTRING("EIdleType", type));
	IdleType = type;
}

void ATHCharacterBase::ServerUpdateNearbyIdleType_Implementation(EIdleType type)
{
	MulticastUpdateNearbyIdleType(type);
}

bool ATHCharacterBase::ServerUpdateNearbyIdleType_Validate(EIdleType type)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateNearbyIdleType_Implementation(EIdleType type)
{
	NearbyIdleType = type;
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

void ATHCharacterBase::ServerUpdatebInInteractionRange_Implementation(bool InInteractionRange)
{
	MulticastUpdatebInInteractionRange(InInteractionRange);
}

bool ATHCharacterBase::ServerUpdatebInInteractionRange_Validate(bool InInteractionRange)
{
	return true;
}

void ATHCharacterBase::MulticastUpdatebInInteractionRange_Implementation(bool InInteractionRange)
{
	bInInteractionRange = InInteractionRange;
}

void ATHCharacterBase::ServerUpdatebAbleToClimb_Implementation(bool Climb)
{
	MulticastUpdatebAbleToClimb(Climb);
}

bool ATHCharacterBase::ServerUpdatebAbleToClimb_Validate(bool Climb)
{
	return true;
}

void ATHCharacterBase::MulticastUpdatebAbleToClimb_Implementation(bool Climb)
{
	bAbleToClimb = Climb;
}

void ATHCharacterBase::ServerUpdatebClimbing_Implementation(bool Climb)
{
	MulticastUpdatebClimbing(Climb);
}

bool ATHCharacterBase::ServerUpdatebClimbing_Validate(bool Climb)
{
	return true;
}

void ATHCharacterBase::MulticastUpdatebClimbing_Implementation(bool Climb)
{
	bClimbing = Climb;
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
	if (IdleType != EIdleType::CROUCH)
	{
		if (ExitDirection == EExitDirection::DEFAULT)
		{
			ExitFromClimb(EExitDirection::MIDDLE);
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("MovementMode: %s"), *GetCharacterMovement()->GetMovementName()));
		}
		ServerUpdatebJump(true);
		UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("bJump is %s"), (bJump ? TEXT("On") : TEXT("Off")));

		Super::Jump();
		//	TODO: Repeat with delay
	}
}

void ATHCharacterBase::OnJumpReleased()
{
	if (IdleType != EIdleType::CROUCH)
	{
		ServerUpdatebJump(false);
		UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("bJump is %s"), (bJump ? TEXT("On") : TEXT("Off")));
		Super::StopJumping();
	}
}

void ATHCharacterBase::OnMeleeAttackPressed()
{
	ServerUpdatebLayeredMotion(true);
	ServerUpdateLayeredAction(ELayeredAction::MELEEATTACK);
	ServerPlayMontage(MeleeAttack);
}

void ATHCharacterBase::OnMeleeAttackReleased()
{
	ServerUpdatebLayeredMotion(false);
	ServerUpdateLayeredAction(ELayeredAction::DEFAULT);
	ServerStopMontage(0.25f, MeleeAttack);
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
		UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s OverlappedPiece: %s"), *FString(__FUNCTION__), (OverlappedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
		UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s AttachedPiece: %s"), *FString(__FUNCTION__), (AttachedPiece == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
		UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("%s OverlappedLatch: %s"), *FString(__FUNCTION__), (OverlappedLatch == nullptr) ? TEXT("InValid!") : TEXT("Valid!"));
		UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("%s On Start Overlap With Latch, AttachSequence: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EAttachSequence", AttachSequence));
		UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("%s On Start Overlap With Latch, InteractionType: %s"), *FString(__FUNCTION__), *GETENUMSTRING("EInteractionType", InteractionType));
		//TODO: Play New Animation
	case EInteractionType::CLIMB:
		break;
	case EInteractionType::INVESTIGATE:
		ServerPlayMontage(Interaction);
		break;
	case EInteractionType::DEFAULT:
		break;
	default:
		break;
	}
	if (bInInteractionRange)
	{
		ServerUpdatebLayeredMotion(true);
		ServerPlayMontage(Interaction);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Interaction Start"));

		//TODO: Add Interaction when Interact with Key
		//AttachedPiece->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("socket_melee_r"));

	}
}

void ATHCharacterBase::OnInteractionReleased()
{
	ServerUpdatebLayeredMotion(false);
	ServerUpdateInteractionType(EInteractionType::DEFAULT);
	ServerStopMontage(0.25f, Interaction);
	/*
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("bFullBodyMotion: %s"), (GETBOOLSTRING(bFullBodyMotion))));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("IdleType: %s"), *GETENUMSTRING("EIdleType", IdleType)));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("ExitDirection: %s"), *GETENUMSTRING("EExitDirection", ExitDirection)));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("bClimbing: %s"), (GETBOOLSTRING(bClimbing))));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("MovementMode: %s"), *GetCharacterMovement()->GetMovementName()));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("bLayeredMotion: %s"), (GETBOOLSTRING(bLayeredMotion))));
	*/
	//Stop Montage Play
}

void ATHCharacterBase::MoveForward(float val)
{
	if (bClimbing)
	{
		ServerUpdatebUpward(val > 0);
		AddMovement(GetActorUpVector(), val);
	}
	else
	{
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
	if (!bClimbing)
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
	if (!bClimbing)
	{
		AddControllerYawInput(val);
	}
	else
	{
		// TODO: Turn Camera With Head
	}
}

void ATHCharacterBase::LookUp(float val)
{
	AddControllerPitchInput(val);
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
						//UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("MovementType: %s"), *GETENUMSTRING("EMovementType", MovementType));
					}
				}
				AddMovementInput(vector, val); 
			}
			break;

		case EIdleType::CROUCH:
			{
				bStandToSprint = false;
				ServerUpdateMovementType(EMovementType::WALK);
				AddMovementInput(vector, val);
			}
			break;

		case EIdleType::LADDER:
			if (bClimbing)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("before MovementType: %s"), *GETENUMSTRING("EMovementType", MovementType)));
				//UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("before MovementType: %s"), *GETENUMSTRING("EMovementType", MovementType));
				if (MovementType == EMovementType::CLIMB)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("before value is Climb!"));
					UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("before value is Climb!"));
				}
				UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("AddMovement after MovementType: %s"), *GETENUMSTRING("EMovementType", MovementType));
				ServerUpdateMovementType(EMovementType::CLIMB);
				UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("AddMovement before MovementType: %s"), *GETENUMSTRING("EMovementType", MovementType));
				//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString::Printf(TEXT("after MovementType: %s"), *GETENUMSTRING("EMovementType", MovementType)));
				//UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("after MovementType: %s"), *GETENUMSTRING("EMovementType", MovementType));
				//TODO: Make Character go UP and DOWN
				if (MovementType == EMovementType::CLIMB)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("after value is Climb!"));
					UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("after value is Climb!"));
				}
				AddMovementInput(vector, val);
			}
			break;
		case EIdleType::ROPE:
			if (bClimbing)
			{
				AddMovementInput(vector, val);
			}
			break;
		case EIdleType::WALL:
			if (bClimbing)
			{
				AddMovementInput(vector, val);
			}
			break;
		}
	}
}

void ATHCharacterBase::OverlapWithHitBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult, bool bCritical)
{
	if (OtherComp)
	{
		auto melee = Cast<UCapsuleComponent>(OtherComp);
		if (melee)
		{
			auto hitboxParents = BodyHitBox->GetAttachmentRoot();
			auto damageboxParents = melee->GetAttachmentRoot();
			if (hitboxParents != damageboxParents)
			{
				auto collision = melee->GetCollisionProfileName();
				if (collision == FName(TEXT("DamageBox")))
				{
					if (!bLayeredMotion)
					{
						ReceiveDamage(-20.0f, bCritical);
					}
				}
			}
		}
	}
}

void ATHCharacterBase::SetCharacterDead()
{
	ServerUpdatebFullBodyMotion(true);
	ServerUpdatebDead(true);
	SetActorEnableCollision(false);
	BodyHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HeadHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeleeLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeleeRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("bDead is %s"), (bDead ? TEXT("true") : TEXT("false"))));
	UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("bDead is %s"), (bDead ? TEXT("true") : TEXT("false")));
}

void ATHCharacterBase::AttachPiece(FName Socket)
{
	if (OverlappedPiece)
	{
		AttachedPiece = OverlappedPiece;
		OverlappedPiece->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, Socket);
		UE_LOG(LogTH_PlayerBase_CheckValue, Verbose, TEXT("%s: Piece Index = %d"), *FString(__FUNCTION__), AttachedPiece->GetIndex());
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
