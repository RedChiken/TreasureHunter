// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DataType/THIdleType.h"
#include "DataType/THMovementType.h"
#include "DataType/THEnterDirection.h"
#include "DataType/THExitDirection.h"
#include "DataType/THLayeredAction.h"
#include "DataType/THMovingDirection.h"
#include "DataType/THLayeredAction.h"
#include "DataType/THInteractionType.h"
#include "DataType/THAttachSequence.h"
#include "Animation/AnimInstance.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BodyHitBox)
		class UCapsuleComponent* BodyHitBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BodyHitBox)
		class UCapsuleComponent* HeadHitBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BodyHitBox)
		class UCapsuleComponent* MeleeLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BodyHitBox)
		class UCapsuleComponent* MeleeRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction)
		TArray<class UCapsuleComponent*> FrontTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* MeleeAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* Interaction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* LandFromJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Interaction)
		class ATHPieceBase* Piece;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Interaction)
		class ATHLatchBase* Latch;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		EIdleType IdleType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		EIdleType NearbyIdleType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		EMovementType MovementType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		EMovingDirection MovingDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		EEnterDirection EnterDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		EExitDirection ExitDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bUpward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		ELayeredAction LayeredAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bFullBodyMotion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bLayeredMotion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bStandToSprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bInInteractionRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bAbleToClimb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bClimbing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		EInteractionType InteractionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		EAttachSequence AttachSequence; 

public:
	float getCurrentSpeed();
	EIdleType getIdleType();
	EMovementType getMovementType();
	EMovingDirection getMovingDirection();
	bool getbJump();
	bool getIsFalling();
	EEnterDirection getEnterDirection();
	EExitDirection getExitDirection();
	bool getbUpward();
	ELayeredAction getLayeredAction();
	bool getbFullBodyMotion();
	bool getbLayeredMotion();
	bool getbDead();
	bool getbStandToSprint();
	float getHP();
	bool getbInInteractionRange();
	bool getbAbleToClimb();
	bool getbClimbing();
	EInteractionType getInteractionType();

	void StopInteraction();

	void UpdatebInInteractionRange(bool InInteractionRange);
	void UpdateIdleType(EIdleType Idle);
	void UpdateNearbyIdleType(EIdleType Idle);
	void UpdateExitDirection(EExitDirection Exit);
	void ExitFromClimb(EExitDirection Exit);
	void EnterToClimb(EEnterDirection Enter, EIdleType Nearby);
	void GetOutofClimbArea();

	void ReceiveDamage(float damage, bool bCritical = false);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerPlayMontage(UAnimMontage* MontageToPlay, float InPlayRate = 1.0f, EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength, float InTimeToStartMontageAt = 0.0f, bool bStopAllMontages = true);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerStopMontage(float blendOut, UAnimMontage* MontageToStop);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdateMovementType(EMovementType type);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdateMovingDirection(EMovingDirection direction);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdateIdleType(EIdleType type);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdateNearbyIdleType(EIdleType type);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdateSpeed(float rate);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdatebJump(bool isJump);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdateEnterDirection(EEnterDirection Direction);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdateExitDirection(EExitDirection Direction);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdatebUpward(bool Upward);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdatebFullBodyMotion(bool FullBodyMotion);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdatebLayeredMotion(bool LayeredMotion);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdatebDead(bool Dead);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdateHP(float HPChanged);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdatebInInteractionRange(bool InInteractionRange);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdatebAbleToClimb(bool Climb);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdatebClimbing(bool Climb);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdateLayeredAction(ELayeredAction Action);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdateInteractionType(EInteractionType Type);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdateAttachSequence(EAttachSequence Sequence);


protected:
	UFUNCTION()
		void OnOverlapWithNormalHitBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapWithCriticalHitBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void OnPieceStartOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void OnPieceEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void OnLatchStartOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void OnLatchEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastPlayMontage(UAnimMontage* MontageToPlay, float InPlayRate = 1.0f, EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength, float InTimeToStartMontageAt = 0.0f, bool bStopAllMontages = true);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastStopMontage(float blendOut, UAnimMontage* MontageToStop);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateMovementType(EMovementType type);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateMovingDirection(EMovingDirection direction);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateIdleType(EIdleType type);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateNearbyIdleType(EIdleType type);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateSpeed(float rate);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdatebJump(bool isJump);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateEnterDirection(EEnterDirection Direction);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateExitDirection(EExitDirection Direction);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdatebUpward(bool Upward);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateLayeredAction(ELayeredAction Action);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdatebFullBodyMotion(bool FullBodyMotion);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdatebLayeredMotion(bool LayeredMotion);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdatebDead(bool Dead);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateHP(float HPChanged);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdatebInInteractionRange(bool InInteractionRange);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdatebAbleToClimb(bool Climb);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdatebClimbing(bool Climb);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateInteractionType(EInteractionType Type);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateAttachSequence(EAttachSequence Sequence);

	void OnToggleCrouch();
	void OnToggleSprint();
	void OnSlide();
	void OnJumpPressed();
	void OnJumpReleased();

	void OnMeleeAttackPressed();
	void OnMeleeAttackReleased();
	void OnInteractionPressed();
	void OnInteractionReleased();

	void MoveForward(float val);
	void MoveRight(float val);
	void Turn(float val);
	void LookUp(float val);

private:
	void AddMovement(const FVector vector, float val); 
	
	void OverlapWithHitBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult, bool bCritical);

	void SetCharacterDead();

	void AttachPiece(FName Socket = NAME_None);

	class ATHPieceBase* DetachPiece();


};
