// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThirdPersonMPCharacter.generated.h"

UCLASS(config=Game)
class AThirdPersonMPCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;


public:

	/*
	GetMaxHealth �֐������ GetCurrentHealth �֐��́AC++ ����уu���[�v�����g�̗����ŁA
	AThirdPersonMPCharacter �̊O������v���C���[�̃w���X�l�ɃA�N�Z�X�ł���Q�b�^�[ (�l���擾���郁�\�b�h) ��
	�񋟂��܂��BGetMaxHealth ����� GetCurrentHealth �� const �֐��Ƃ��āA
	�����̒l��ύX�ł���悤�ɂ��邱�ƂȂ��A�l���擾�ł�����S�Ȏ�i��񋟂��܂��B
	�܂��A�v���C���[�̃w���X��ݒ肵�A�_���[�W��^���邽�߂̊֐���錾���Ă��܂��B
	*/

	/** Getter for Max Health.*/
	UFUNCTION(BlueprintPure, Category = "Health")
		FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	/** Getter for Current Health.*/
	UFUNCTION(BlueprintPure, Category = "Health")
		FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	/** Setter for Current Health. Clamps the value between 0 and MaxHealth and calls OnHealthUpdate. 
	Should only be called on the server.*/
	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetCurrentHealth(float healthValue);

	/** Event for taking damage. Overridden from APawn.*/
	UFUNCTION(BlueprintCallable, Category = "Health")
		float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, 
						 AController* EventInstigator, AActor* DamageCauser) override;


	AThirdPersonMPCharacter();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;


protected:


	/*
	�v���C���[�̃w���X�̕ύX���@�������ɐ��䂷��K�v�����邽�߁A�����̃w���X�l�ɂ͎��̐��񂪂���܂��B

	+ `MaxHealth` �ł̓��v���P�[�g�͍s�킸�A�f�t�H���g�ł͕ҏW�̂݉\�B
	���̒l�͂��ׂẴv���C���[�ɑ΂��Ď��O�Ɍv�Z����Ă���A�ύX����邱�Ƃ͂���܂���B

	+ `CurrentHealth` �ł̓��v���P�[�g�͍s�����̂́A�u���[�v�����g�̂ǂ̕������ҏW�܂��̓A�N�Z�X�ł��Ȃ��B

	+ `MaxHealth` ����� `CurrentHealth` �͂ǂ���� `protected` �ł��邽�߁A
	�O���� C++ �N���X���炱���ɃA�N�Z�X���邱�Ƃ͂ł��Ȃ��BMaxHealth ����� CurrentHealth �́A
	`AThirdPersonMPCharacter` ���ŁA�܂��� AThirdPersonMPCharacter ����h���������̃N���X�ł̂ݕύX�ł��܂��B

�@	 ����ɂ��A���C�u�̃Q�[���v���C���Ƀv���C���[�� `CurrentHealth` �܂��� `MaxHealth` �ւ�
	�s�v�ȕύX�������N�������X�N���ŏ����ɗ}���܂��B
	�����̒l���擾����ѕύX���邽�߂̂��̑��̃p�u���b�N�֐��ɂ��Đ������܂��B

�@	 `Replicated` �w��q���g�p����ƁA�T�[�o�[��̃A�N�^�̃R�s�[�́A�ϐ��̒l���ύX����邽�тɁA
	�ڑ�����Ă��邷�ׂẴN���C�A���g�ɕϐ��̒l�����v���P�[�g�ł��܂��B
	`ReplicatedUsing` ���������������s���܂����A���̎w��q���g�p����ƁA**RepNotify** �֐���ݒ�ł��܂��B
	�N���C�A���g�����v���P�[�g���ꂽ�f�[�^�𐳏�Ɏ�M�����ꍇ�ɁA���̊֐����g���K�[����܂��B
	`OnRep_CurrentHealth` ���g�p���āA���̕ϐ��ւ̕ύX�Ɋ�Â��āA�e�N���C�A���g�ɑ΂���X�V�����s���܂��B
	*/

	/** Response to health being updated. 
	Called on the server immediately after modification, and on clients in response to a RepNotify*/
	void OnHealthUpdate();

	/** The player's maximum health. This is the highest value of their health can be. 
	This value is a value of the player's health, which starts at when spawned.*/
	UPROPERTY(EditDefaultsOnly, Category = "Health")
		float MaxHealth;

	/** The player's current health. When reduced to 0, they are considered dead.*/
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
		float CurrentHealth;

	/** RepNotify for changes made to current health.*/
	UFUNCTION()
		void OnRep_CurrentHealth();

	/*
	�����́A���˕��𔭎˂��邽�߂Ɏg�p����ϐ��Ɗ֐��ł��B
	HandleFire �͂��̃`���[�g���A���Ŏ�������B��� RPC �ł���A�T�[�o�[�ł̔��˕��̃X�|�[�����s���܂��B
	HandleFire �ɂ� Server �w��q���܂܂�Ă��邽�߁A�N���C�A���g��� HandleFire ���Ăяo�����Ƃ���ƁA
	�Ăяo�����l�b�g���[�N�o�R�ŃT�[�o�[��̌����̂���L�����N�^�[�Ɍ������܂��B

	HandleFire �ɂ� Reliable �w��q���܂܂�Ă��邽�߁AHandleFire �͌Ăяo����邽�т�
	�M���ł��� RPC �̃L���[�ɔz�u����܂��B�܂��A�T�[�o�[�� HandleFire �𐳏�Ɏ�M����ƃL���[����폜����܂��B
	����ɂ��A�T�[�o�[�����̊֐��Ăяo�����m���Ɏ�M���邱�Ƃ��ۏ؂���܂��B
	�������A�폜���邱�ƂȂ���x�ɑ����� RPC ��z�u����ƁA�M�����̍��� RPC �̃L���[��
	�I�[�o�[�t���[���鋰�ꂪ����܂��B���̏ꍇ�A���[�U�[�͋����I�ɐڑ�����������܂��B
	���̂��߁A�v���C���[�����̊֐����Ăяo�����Ƃ̂ł���p�x�ɒ��ӂ���K�v������܂��B
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay|Projectile")
		TSubclassOf<class AThirdPersonMPProjectile> ProjectileClass;

	/** Delay between shots in seconds.Used to control fire rate for our test projectile, but also to prevent an overflow of server functions from binding SpawnProjectile directly to input.*/
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		float FireRate;

	/** If true, we are in the process of firing projectiles. */
	bool bIsFiringWeapon;

	/** Function for beginning weapon fire.*/
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void StartFire();

	/** Function for ending weapon fire.Once this is called, the player can use StartFire again.*/
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void StopFire();

	/** Server function for spawning projectiles.*/
	UFUNCTION(Server, Reliable)
		void HandleFire();

	/** A timer handle used for providing the fire rate delay in-between spawns.*/
	FTimerHandle FiringTimer;


	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);


protected:

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface


public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

