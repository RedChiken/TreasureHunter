// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DataType/THIdleType.h"
#include "DataType/THMovementType.h"
#include "DataType/THEnterDirection.h"
#include "DataType/THExitDirection.h"
#include "DataType/THLayeredAction.h"
#include "THCharacterBase.generated.h"

UCLASS()
class TREASUREHUNTER_API ATHCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATHCharacterBase();

	virtual void PostInitializeComponents() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* TP_Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FPCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TPCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitBox)
		class UCapsuleComponent* HitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* MeleeAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* Interaction;

private:
	//TODO: Add Getter Function
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		float SpeedRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		EIdleType IdleType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		EMovementType MovementType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		EEnterDirection EnterDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bUpward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		EExitDirection ExitDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		ELayeredAction LayeredAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bFullBodyMotion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bLayeredMotion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bClimb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bStandToSprint;

public:
	float getCurrentSpeed();
	EIdleType getIdleType();
	EMovementType getMovementType();
	bool getbJump();
	bool getIsFalling();
	EEnterDirection getEnterDirection();
	bool getbUpward();
	EExitDirection getExitDirection();
	ELayeredAction getLayeredAction();
	bool getbFullBodyMotion();
	bool getbLayeredMotion();
	bool getbClimb();
	bool getbDead();
	bool getbStandToSprint();

protected:
	UFUNCTION()
		void OnOverlapWithHitBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerPlayMontage(UAnimMontage* MontageToPlay, float InPlayRate = 1.0f, EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength, float InTimeToStartMontageAt = 0.0f, bool bStopAllMontages = true);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastPlayMontage(UAnimMontage* MontageToPlay, float InPlayRate = 1.0f, EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength, float InTimeToStartMontageAt = 0.0f, bool bStopAllMontages = true);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerUpdateMovementType(EMovementType type);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateMovementType(EMovementType type);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerUpdateIdleType(EIdleType type);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateIdleType(EIdleType type);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerUpdateSpeedRate(float rate);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateSpeedRate(float rate);


	//TODO: Replicate update HP

	void OnToggleCrouch();
	void OnToggleSprint();
	void OnSlide();
	void OnJump();

	void OnMeleeAttack();
	void OnInteraction();

	void MoveForward(float val);
	void MoveRight(float val);
	void Turn(float val);
	void LookUp(float val);

private:
	void AddMovement(const FVector vector, float val);
};
