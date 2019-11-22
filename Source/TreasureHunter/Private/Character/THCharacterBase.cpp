// Fill out your copyright notice in the Description page of Project Settings.


#include "THCharacterBase.h"
#include "ConstructorHelpers.h"
#include "Animation/THAnimInstanceBase.h"
#include "camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "net/UnrealNetwork.h"
#include "Engine.h"

// Sets default values
ATHCharacterBase::ATHCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);
	CrouchedEyeHeight = 32.f;
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	
	HitBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitBox"));
	HitBox->BodyInstance.SetCollisionProfileName("NormalHitBox");
	//TODO: Add Collision
	HitBox->InitCapsuleSize(55.f, 96.f);
	//TODO: Add OnOverlapWithitBox Dynamic
	HitBox->SetupAttachment(RootComponent);

	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	FPCameraComponent->bUsePawnControlRotation = true;
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetupAttachment(FPCameraComponent);
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetIsReplicated(true);

	SpeedRate = 1.0f;
	bJump = false;
	IdleType = EIdleType::STAND;
	EMovementType::DEFAULT;
	EnterDirection = EEnterDirection::DEFAULT;
	ExitDirection = EExitDirection::DEFAULT;
	bFullBodyMotion = false;
	bClimb = false;
	bUpward = false;
	bDead = false;
	bLayeredMotion = false;
	bStandToSprint = false;
	GetCharacterMovement()->JumpZVelocity = 800.0f;
}

// Called when the game starts or when spawned
void ATHCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATHCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATHCharacterBase, SpeedRate);
	DOREPLIFETIME(ATHCharacterBase, IdleType);
	DOREPLIFETIME(ATHCharacterBase, MovementType);
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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATHCharacterBase::OnJump);
	PlayerInputComponent->BindAction("MeleeAttack", IE_Pressed, this, &ATHCharacterBase::OnMeleeAttack);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ATHCharacterBase::OnInteraction);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ATHCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATHCharacterBase::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	
	PlayerInputComponent->BindAxis("UpDown", this, &ATHCharacterBase::TurnAtRate);
	PlayerInputComponent->BindAxis("LeftRight", this, &ATHCharacterBase::LookUpAtRate);
}

float ATHCharacterBase::getCurrentSpeed()
{
	return this->GetVelocity().Size() * SpeedRate;
}

EIdleType ATHCharacterBase::getIdleType()
{
	return IdleType;
}

EMovementType ATHCharacterBase::getMovementType()
{
	return MovementType;
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

void ATHCharacterBase::OnOverlapWithHitBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherComp)
	{
		auto melee = Cast<ATHCharacterBase>(OtherActor);
		if (melee)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Hit Character"));
			//serve damage
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
}

void ATHCharacterBase::OnToggleCrouch()
{
	if (IdleType == EIdleType::STAND)
	{
		if ((MovementType == EMovementType::DEFAULT) || (MovementType == EMovementType::WALK))
		{
			IdleType = EIdleType::CROUCH;
			SpeedRate *= 0.5;
		}
	}
	else if(IdleType == EIdleType::CROUCH)
	{
		IdleType = EIdleType::STAND;
		SpeedRate *= 2.0;
	}
}

void ATHCharacterBase::OnToggleSprint()
{
	if (MovementType == EMovementType::WALK)
	{
		MovementType = EMovementType::SPRINT;
		SpeedRate *= 2.0;
	}
	else if (MovementType == EMovementType::SPRINT)
	{
		MovementType = EMovementType::WALK;
		SpeedRate *= 0.5;
	}
	else if (MovementType == EMovementType::DEFAULT)
	{
		SpeedRate *= 2.0;
		bStandToSprint = true;
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

void ATHCharacterBase::OnJump()
{
	bFullBodyMotion = true;
	bJump = true;
	Super::Jump();
}

void ATHCharacterBase::OnMeleeAttack()
{
	bLayeredMotion = true;
	ServerPlayMontage(MeleeAttack);
	//TODO: Give Damage when hit enemy
}

void ATHCharacterBase::OnInteraction()
{
	bLayeredMotion = true;
	//TODO: Condition - when character in proper area
	ServerPlayMontage(Interaction);
}

void ATHCharacterBase::MoveForward(float val)
{
	if ((IdleType == EIdleType::LADDER) || (IdleType == EIdleType::ROPE) || (IdleType == EIdleType::WALL))
	{
		//TODO: Add Climb
	}
	else if (IdleType == EIdleType::STAND)
	{
		if (bStandToSprint)
		{	// Sprint
			bStandToSprint = false;
			MovementType = EMovementType::SPRINT;
		}
		else
		{	// Walk
			MovementType = EMovementType::WALK;
		}
		AddMovementInput(GetActorForwardVector(), val);
	}
	else if (IdleType == EIdleType::CROUCH)
	{
		bStandToSprint = false;
		MovementType = EMovementType::WALK;
		AddMovementInput(GetActorForwardVector(), val);
	}
}

void ATHCharacterBase::MoveRight(float val)
{
	if ((IdleType == EIdleType::STAND) || (IdleType == EIdleType::CROUCH))
	{
		AddMovementInput(GetActorForwardVector(), val);
	}
}

void ATHCharacterBase::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATHCharacterBase::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
