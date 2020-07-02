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
#include "Engine/EngineTypes.h"
#include "Containers/EnumAsByte.h"
#include "THCharacterBase.generated.h"

UCLASS()
class TREASUREHUNTER_API ATHCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATHCharacterBase(const class FObjectInitializer& ObjectInitializer);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, REplicated, Category = Movement)
		class UTHCharacterMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction)
		class UCapsuleComponent* InteractionTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ClimbTrigger)
		class UCapsuleComponent* UpperClimbTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ClimbTrigger)
		class UCapsuleComponent* MiddleClimbTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ClimbTrigger)
		class UCapsuleComponent* LowerClimbTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UCapsuleComponent* HeadHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UCapsuleComponent* UpperBodyHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UCapsuleComponent* LowerBodyHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UCapsuleComponent* LeftUpperArmHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UCapsuleComponent* LeftLowerArmHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UCapsuleComponent* LeftHandHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UCapsuleComponent* RightUpperArmHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UCapsuleComponent* RightLowerArmHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UCapsuleComponent* RightHandHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UCapsuleComponent* LeftUpperLegHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UCapsuleComponent* LeftLowerLegHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UCapsuleComponent* LeftFootHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UCapsuleComponent* RightUpperLegHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UCapsuleComponent* RightLowerLegHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UCapsuleComponent* RightFootHitTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* MeleeAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* InteractionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* LandFromJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* RopeExitBottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* RopeExitTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* LadderExitBottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* LadderExitTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* WallExitBottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* WallExitTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Interaction)
		class ATHPieceBase* OverlappedPiece;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Interaction)
		class ATHPieceBase* AttachedPiece;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Interaction)
		class ATHLatchBase* OverlappedLatch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Hit)
		class UCapsuleComponent* FirstHitPart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Hit)
		class UCapsuleComponent* HitOpposite;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		EIdleType IdleType;

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
		EInteractionType InteractionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		EAttachSequence AttachSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bUpperClimbTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bMiddleClimbTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		bool bLowerClimbTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Action, meta = (AllowPrivateAccess = "true"))
		EIdleType InteractableClimb;


public:
	void SyncLocomotionAnimTrigger(float& Speed, bool& Jump, bool& Fall, bool& StandToSprint, EIdleType& Idle, EMovementType& Movement, EMovingDirection& Moving);
	void SyncFullBodyAnimTrigger(bool& LayeredMotion, bool& FullBodyMotion, bool& Upward, bool& Dead, bool& UpperClimb, bool& MiddleClimb, bool& LowerClimb, ELayeredAction& Layered, EInteractionType& Interaction, TEnumAsByte<enum EMovementMode>& MovementMode);
	void SyncStatusAnimTrigger(float& HP);

	void OnMovementStop();

	void StopInteraction();
	void UpdateIdleType(EIdleType Idle);
	void UpdateExitDirection(EExitDirection Exit);

	void ReceiveDamage(float damage);

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
		void ServerUpdateLayeredAction(ELayeredAction Action);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdateInteractionType(EInteractionType Type);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdateAttachSequence(EAttachSequence Sequence);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdatebUpperClimbTrigger(bool ClimbTrigger);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdatebMiddleClimbTrigger(bool ClimbTrigger);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdatebLowerClimbTrigger(bool ClimbTrigger);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdateInteractableClimb(EIdleType ClimbType);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerUpdateMovementMode(EMovementMode Mode);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerTeleportTo(FVector WorldLocation, FRotator Rotation);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerEnableCollision();

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerDisableCollision();

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerEnableInput(class APlayerController* InputController);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerDisableInput(class APlayerController* InputController);


protected:
	UFUNCTION(BlueprintCallable)
		void OnHitStartOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void OnHitEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void OnPieceStartOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void OnPieceEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void OnUpperClimbStartOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void OnMiddleClimbStartOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void OnLowerClimbStartOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void OnUpperClimbEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void OnMiddleClimbEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void OnLowerClimbEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void OnLatchStartOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void OnLatchEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void OnMontageEnded(class UAnimMontage* Montage, bool bInterrupted);

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
		void MulticastUpdateInteractionType(EInteractionType Type);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateAttachSequence(EAttachSequence Sequence);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdatebUpperClimbTrigger(bool ClimbTrigger);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdatebMiddleClimbTrigger(bool ClimbTrigger);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdatebLowerClimbTrigger(bool ClimbTrigger);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateInteractableClimb(EIdleType ClimbType);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastUpdateMovementMode(EMovementMode Mode);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastTeleportTo(FVector WorldLocation, FRotator Rotation);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastEnableCollision();

	UFUNCTION(NetMulticast, Reliable)
		void MulticastDisableCollision();

	UFUNCTION(NetMulticast, Reliable)
		void MulticastEnableInput(class APlayerController* InputController);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastDisableInput(class APlayerController* InputController);

	UFUNCTION(BlueprintCallable)
		class UCapsuleComponent* AddNewHitTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FName& AttachedSocket = NAME_None, const FVector& RelativeLocation = FVector::ZeroVector, const FRotator& RelativeRotation = FRotator::ZeroRotator);

	UFUNCTION(Blueprintcallable)
		class UCapsuleComponent* AddUpperClimbTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FVector& RelativeLocation = FVector::ZeroVector, const FRotator& RelativeRotation = FRotator::ZeroRotator);

	UFUNCTION(Blueprintcallable)
		class UCapsuleComponent* AddMiddleClimbTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FVector& RelativeLocation = FVector::ZeroVector, const FRotator& RelativeRotation = FRotator::ZeroRotator);

	UFUNCTION(Blueprintcallable)
		class UCapsuleComponent* AddLowerClimbTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FVector& RelativeLocation = FVector::ZeroVector, const FRotator& RelativeRotation = FRotator::ZeroRotator);

		class UCapsuleComponent* AddNewClimbTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FVector& RelativeLocation = FVector::ZeroVector, const FRotator& RelativeRotation = FRotator::ZeroRotator);

	UFUNCTION(Blueprintcallable)
		class UCapsuleComponent* AddNewInteractionTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FVector& RelativeLocation = FVector::ZeroVector, const FRotator& RelativeRotation = FRotator::ZeroRotator);

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

	void SetCharacterDead();

	void AttachPiece(FName Socket = NAME_None);

	class ATHPieceBase* DetachPiece();

	void ExitClimb();
	void EnterClimb();

};
