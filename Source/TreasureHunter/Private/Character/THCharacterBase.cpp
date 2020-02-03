// Fill out your copyright notice in the Description page of Project Settings.


#include "THCharacterBase.h"
#include "TreasureHunter.h"
#include "ConstructorHelpers.h"
#include "Animation/THAnimInstanceBase.h"
#include "camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "net/UnrealNetwork.h"
#include "Engine.h"

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetNameStringByIndex((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

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
	//TODO: Set TP Camera Component

	
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

	bReplicates = true;
	SetReplicatingMovement(true);

	GetCharacterMovement()->MaxWalkSpeed = 800.0f;

	bJump = false;
	IdleType = EIdleType::STAND;
	MovementType = EMovementType::DEFAULT;
	MovingDirection = EMovingDirection::DEFAULT;
	EnterDirection = EEnterDirection::DEFAULT;
	ExitDirection = EExitDirection::DEFAULT;
	bFullBodyMotion = false;
	bClimb = false;
	bUpward = false;
	bDead = false;
	bLayeredMotion = false;
	bStandToSprint = false;
	HP = 100;
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
	DOREPLIFETIME(ATHCharacterBase, MovementType);
	DOREPLIFETIME(ATHCharacterBase, MovingDirection);
	DOREPLIFETIME(ATHCharacterBase, bJump);
	DOREPLIFETIME(ATHCharacterBase, EnterDirection);
	DOREPLIFETIME(ATHCharacterBase, bUpward);
	DOREPLIFETIME(ATHCharacterBase, ExitDirection);
	DOREPLIFETIME(ATHCharacterBase, LayeredAction);
	DOREPLIFETIME(ATHCharacterBase, bFullBodyMotion);
	DOREPLIFETIME(ATHCharacterBase, bLayeredMotion);
	DOREPLIFETIME(ATHCharacterBase, bClimb);
	DOREPLIFETIME(ATHCharacterBase, bDead);
	DOREPLIFETIME(ATHCharacterBase, bStandToSprint);
	DOREPLIFETIME(ATHCharacterBase, HP);
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

bool ATHCharacterBase::getbUpward()
{
	return bUpward;
}

EExitDirection ATHCharacterBase::getExitDirection()
{
	return ExitDirection;
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

bool ATHCharacterBase::getbClimb()
{
	return bClimb;
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

void ATHCharacterBase::OnOverlapWithNormalHitBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlapWithHitBox(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult, false);
}

void ATHCharacterBase::OnOverlapWithCriticalHitBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlapWithHitBox(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult, true);
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
	MulticastUpdateMovementType(type);
}

bool ATHCharacterBase::ServerUpdateMovementType_Validate(EMovementType type)
{
	return true;
}

void ATHCharacterBase::MulticastUpdateMovementType_Implementation(EMovementType type)
{
	UE_LOG(LogTH_PlayerBase_MovementType, Verbose, TEXT("MovementType change from %s to %s"), *GETENUMSTRING("EMovementType", MovementType), *GETENUMSTRING("EMovementType", type));
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
	UE_LOG(LogTH_PlayerBase_MovingDirection, Verbose, TEXT("MovingDirection change from %s to %s"), *GETENUMSTRING("EMovingDirection", MovingDirection), *GETENUMSTRING("EMovingDirection", direction));
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
	UE_LOG(LogTH_PlayerBase_IdleType, Verbose, TEXT("IdleType change from %s to %s"), *GETENUMSTRING("EIdleType", IdleType), *GETENUMSTRING("EIdleType", type));
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

void ATHCharacterBase::ServerUpdatebClimb_Implementation(bool Climb)
{
	MulticastUpdatebClimb(Climb);
}

bool ATHCharacterBase::ServerUpdatebClimb_Validate(bool Climb)
{
	return true;
}

void ATHCharacterBase::MulticastUpdatebClimb_Implementation(bool Climb)
{
	bClimb = Climb;
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
	ServerPlayMontage(MeleeAttack);
	//TODO: Give Damage when hit enemy
}

void ATHCharacterBase::OnMeleeAttackReleased()
{
	ServerUpdatebLayeredMotion(false);
	ServerStopMontage(0.25f, MeleeAttack);
}

void ATHCharacterBase::OnInteractionPressed()
{
	ServerUpdatebLayeredMotion(true);
	//TODO: Condition - when character in proper area
	ServerPlayMontage(Interaction);
}

void ATHCharacterBase::OnInteractionReleased()
{
	ServerUpdatebLayeredMotion(false);
	ServerStopMontage(0.25f, Interaction);
	//Stop Montage Play
}

void ATHCharacterBase::MoveForward(float val)
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

void ATHCharacterBase::MoveRight(float val)
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

void ATHCharacterBase::Turn(float val)
{
	AddControllerYawInput(val);
}

void ATHCharacterBase::LookUp(float val)
{
	AddControllerPitchInput(val);
}

void ATHCharacterBase::AddMovement(const FVector vector, float val)
{
	if (val != 0)
	{
		if ((IdleType == EIdleType::LADDER) || (IdleType == EIdleType::ROPE) || (IdleType == EIdleType::WALL))
		{
			//TODO: Add Climb
		}
		else if ((IdleType == EIdleType::STAND))
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
				}
			}
			AddMovementInput(vector, val);
		}
		else if (IdleType == EIdleType::CROUCH)
		{
			bStandToSprint = false;
			ServerUpdateMovementType(EMovementType::WALK);
			AddMovementInput(vector, val);
		}
	}
}

void ATHCharacterBase::OverlapWithHitBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult, bool bCritical)
{
	if (OtherActor)
	{
		auto melee = Cast<ATHCharacterBase>(OtherActor);
		if (melee)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Hit Character"));
			//UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("Hit Character"));
			//serve damage
		}
	}
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
						GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("Hit Character"));
						UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("Hit Character"));

						ServerUpdateHP((bCritical ? -50.0f : -20.0f));
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Rest HP is %f"), HP));
						UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("Rest HP is %f"), HP);

						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("HP: %f, bDead is %s"), HP, 
							(bDead ? TEXT("True") : TEXT("False"))));
						if (!bDead && (HP <= 0.0f))
						{
							SetCharacterDead();
						}
					}
					else
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("DamageBox has collision without melee attack"));
						//UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("DamageBox has collision without melee attack"));
					}
					//serve damage
				}
				else
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("collision is not DamageBox"));
					//UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("collision is not DamageBox"));
				}
			}
			else
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("HitBox and Damage Box have same Root Component"));
				//UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("HitBox and Damage Box have same Root Component"));
			}
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("No Collision"));
			//UE_LOG(LogTH_PlayerBase_CheckOverlap, Verbose, TEXT("No Collision"));
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
