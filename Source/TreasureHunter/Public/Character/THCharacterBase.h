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
#include "Interface/LocomotionSync.h"
#include "Interface/FullBodyMotionSync.h"
#include "Interface/LayeredMotionSync.h"
#include "Interface/StatusSync.h"
#include "Interface/Damagable.h"
#include "Interface/CheckInRangeCharacter.h"
#include "Interface/ObjectActivity.h"
#include "Animation/AnimInstance.h"
#include "Engine/EngineTypes.h"
#include "Containers/EnumAsByte.h"
#include "THCharacterBase.generated.h"

UCLASS()
class TREASUREHUNTER_API ATHCharacterBase : public ACharacter, 
	public ILocomotionSync, public IFullBodyMotionSync, public ILayeredMotionSync, public IStatusSync, 
	public IDamagable, public ICheckInRangeCharacter, public IObjectActivity
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
		class UTHCharacterHitBox* UpperBodyHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UTHCharacterHitBox* LowerBodyHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UTHCharacterHitBox* LeftUpperArmHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UTHCharacterHitBox* LeftLowerArmHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UTHCharacterHitBox* LeftHandHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UTHCharacterHitBox* RightUpperArmHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UTHCharacterHitBox* RightLowerArmHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UTHCharacterHitBox* RightHandHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UTHCharacterHitBox* LeftUpperLegHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UTHCharacterHitBox* LeftLowerLegHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UTHCharacterHitBox* LeftFootHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UTHCharacterHitBox* RightUpperLegHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UTHCharacterHitBox* RightLowerLegHitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitTrigger)
		class UTHCharacterHitBox* RightFootHitTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* MeleeAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* InteractionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
		class UAnimMontage* LandFromJump;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Hit)
		TArray<FString> HitObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Hit)
		TArray<FString> Ally;

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
	void OnMovementStop();

	void StopInteraction();
	void UpdateIdleType(EIdleType Idle);
	void UpdateExitDirection(EExitDirection Exit);

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

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerAddHitObject(const FString& target);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerRemoveHitObject(const FString& target);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerResetHitObject();

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerAddAlly(const FString& target);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerRemoveAlly(const FString& target);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerResetAlly();

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerActivateHitBox(UObject* HitBox);

	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
		void ServerInactivateHitBox(UObject* HitBox);


protected:
	UFUNCTION(BlueprintCallable)
		void OnHitStartOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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

	UFUNCTION(NetMulticast, Reliable)
		void MulticastAddHitObject(const FString& target);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastRemoveHitObject(const FString& target);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastResetHitObject();

	UFUNCTION(NetMulticast, Reliable)
		void MulticastAddAlly(const FString& target);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastRemoveAlly(const FString& target);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastResetAlly();

	UFUNCTION(NetMulticast, Reliable)
		void MulticastActivateHitBox(UObject* HitBox);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastInactivateHitBox(UObject* HitBox);

	UFUNCTION(BlueprintCallable)
		class UTHCharacterHitBox* AddNewHitTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FName& AttachedSocket = NAME_None, const FVector& RelativeLocation = FVector::ZeroVector, const FRotator& RelativeRotation = FRotator::ZeroRotator);

	UFUNCTION(Blueprintcallable)
		class UCapsuleComponent* AddUpperClimbTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FVector& RelativeLocation = FVector::ZeroVector, const FRotator& RelativeRotation = FRotator::ZeroRotator);

	UFUNCTION(Blueprintcallable)
		class UCapsuleComponent* AddMiddleClimbTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FVector& RelativeLocation = FVector::ZeroVector, const FRotator& RelativeRotation = FRotator::ZeroRotator);

	UFUNCTION(Blueprintcallable)
		class UCapsuleComponent* AddLowerClimbTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FVector& RelativeLocation = FVector::ZeroVector, const FRotator& RelativeRotation = FRotator::ZeroRotator);

	UFUNCTION(Blueprintcallable)
		class UCapsuleComponent* AddNewClimbTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FVector& RelativeLocation = FVector::ZeroVector, const FRotator& RelativeRotation = FRotator::ZeroRotator);

	UFUNCTION(Blueprintcallable)
		class UCapsuleComponent* AddNewInteractionTrigger(const FName& SubobjectName, const int32& Radius, const int32& HalfHeight, const FVector& RelativeLocation = FVector::ZeroVector, const FRotator& RelativeRotation = FRotator::ZeroRotator);

	UFUNCTION()
		void EnterRopeTop();

	UFUNCTION()
		void ExitRopeTop();

	UFUNCTION()
		void EnterRopeBottom();

	UFUNCTION()
		void ExitRopeBottom();

	UFUNCTION()
		void EnterWallTop();

	UFUNCTION()
		void ExitWallTop();

	UFUNCTION()
		void EnterWallBottom();

	UFUNCTION()
		void ExitWallBottom();

	UFUNCTION()
		void EnterLadderTop();

	UFUNCTION()
		void ExitLadderTop();

	UFUNCTION()
		void EnterLadderBottom();

	UFUNCTION()
		void ExitLadderBottom();

	UFUNCTION()
		void EnableRightPunchMeleeAttack();

	UFUNCTION()
		void DisableRightPunchMeleeAttack();



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

public:
	virtual void SyncSpeed(float& Speed) override;
	virtual void SyncbJump(bool& Jump) override;
	virtual void SyncbFalling(bool& Falling) override;
	virtual void SyncStandToSparint(bool& STS) override;
	virtual void SyncIdleType(EIdleType& Idle) override;
	virtual void SyncMovementType(EMovementType& Movement) override;
	virtual void SyncMovingDirection(EMovingDirection& Moving) override;

	virtual void SyncbFullBodyMotion(bool& FullBody) override;
	virtual void SyncbUpperClimb(bool& Upper) override;
	virtual void SyncbMiddleClimb(bool& Middle) override;
	virtual void SyncbLowerClimb(bool& Lower) override;
	virtual void SyncMovementMode(TEnumAsByte<EMovementMode>& MovementMode) override;

	virtual void SyncbLayeredMotion(bool& LayeredMotion) override;
	virtual void SyncLayeredAction(ELayeredAction& Layered) override;
	virtual void SyncInteractionType(EInteractionType& Interaction) override;

	virtual void SyncHP(float& Hp);
	virtual void SyncbDead(bool& Dead);

	virtual void ReceiveDamage(const float& damage) override;
	virtual void ReceiveHeal(const float& heal) override;

	virtual void AddtoBuffer(FString input) override;
	virtual void RemovefromBuffer(FString input) override;
	virtual bool IsValidinBuffer(const FString input) override;
	virtual void ResetBuffer() override;
	virtual void Flush() override;
	virtual void AddtoMemory(FString input) override;
	virtual void RemovefromMemory(FString input) override;
	virtual bool IsValidinMemory(const FString input) override;
	virtual void ResetMemory() override;

	// Inherited via IObjectActivity
	virtual void InActivate() override;
	virtual void Reset() override;
	virtual void Activate() override;
	virtual FString GetID() override;

private:
	void AddMovement(const FVector vector, float val); 

	void SetCharacterDead();

	void AttachPiece(FName Socket = NAME_None);

	class ATHPieceBase* DetachPiece();

	void ExitClimb();
	void EnterClimb();

	bool IsClimbing();
	bool IsClimbUp();
	bool IsClimbDown();
	bool IsAttachToTop();
	bool IsAttachToBottom();
	bool IsAbleToClimb();

	bool IsMeleeAttack();
};
