// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonMPCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//�}���`�v���C�̎���
//https://docs.unrealengine.com/5.1/ja/multiplayer-programming-quick-start-for-unreal-engine/
/*
�����́A�ϐ��̃��v���P�[�V�����ɕK�v�ȋ@�\�ƁA
GEngine �� AddOnscreenDebugMessage �֐��ւ̃A�N�Z�X��񋟂��܂��B
������g�p���āA��ʂɃ��b�Z�[�W���o�͂��܂��B
*/
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
/*
���˕��̃^�C�v��F�����Ĕ��˕����X�|�[���ł���悤�ɂȂ�܂��B
*/
#include "ThirdPersonMPProjectile.h"

//////////////////////////////////////////////////////////////////////////
// AThirdPersonMPCharacter

AThirdPersonMPCharacter::AThirdPersonMPCharacter()
{
	//Initialize the player's Health
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	/*
	�����ɂ��A���˕��̔��˂��������邽�߂ɕK�v�ȕϐ�������������܂��B
	*/
	//Initialize projectile class
	ProjectileClass = AThirdPersonMPProjectile::StaticClass();
	//Initialize fire rate
	FireRate = 0.25f;
	bIsFiringWeapon = false;
}

//////////////////////////////////////////////////////////////////////////
// Replicated Properties

void AThirdPersonMPCharacter::GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const
{
	/* GetLifetimeReplicatedProps �֐��́AReplicated �w��q�Ŏw�肵�����ׂẴv���p�e�B�����v���P�[�g���܂��B
	�܂��A���̊֐����g�p����ƁA�v���p�e�B�̃��v���P�[�g���@��ݒ�ł��܂��B
	���̗�ł́ACurrentHealth �̍ł���{�I�Ȏ������g�p���Ă��܂��B
	���v���P�[�g����K�v�̂���v���p�e�B��ǉ�����ꍇ�͏�ɁA
	���̃v���p�e�B�����̊֐��ɂ��ǉ�����K�v������܂��B
	
	*WARNING*
	GetLifetimeReplicatedProps �� Super �o�[�W�������Ăяo���K�v������܂��B
	������s��Ȃ��ƁA�A�N�^�̐e�N���X����p�����ꂽ�v���p�e�B���A
	�e�N���X�ł����̃v���p�e�B�����v���P�[�g����悤�Ɏw�肳��Ă���ꍇ�ł����v���P�[�g����܂���B*/
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	//Replicate current health.
	DOREPLIFETIME(AThirdPersonMPCharacter, CurrentHealth);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AThirdPersonMPCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersonMPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdPersonMPCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AThirdPersonMPCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AThirdPersonMPCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AThirdPersonMPCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AThirdPersonMPCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AThirdPersonMPCharacter::OnResetVR);

	/*
	StartFire �����̃Z�N�V�����̍ŏ��̎菇�ō쐬���� Fire ���̓A�N�V�����Ƀo�C���h����A
	���[�U�[�� StartFire ��L���ɂł��܂��B
	*/
	// Handle firing projectiles
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AThirdPersonMPCharacter::StartFire);
}


void AThirdPersonMPCharacter::OnResetVR()
{
	// If ThirdPersonMP is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in ThirdPersonMP.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AThirdPersonMPCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AThirdPersonMPCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AThirdPersonMPCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersonMPCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersonMPCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AThirdPersonMPCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

/*
���̊֐����g�p���āA�v���C���[�� CurrentHealth �ւ̕ύX�ɉ����čX�V�����s���܂��B
���݁A���̋@�\�͉�ʏ�̃f�o�b�O ���b�Z�[�W�ɐ�������Ă��܂����A�ǉ��̋@�\�͒ǉ����邱�Ƃ��ł��܂��B
���Ƃ��΁AOnDeath �֐��́A���S�A�j���[�V�������g���K�[���邽�߂ɁA���ׂẴ}�V���ŌĂяo����܂��B
�Ȃ��AOnHealthUpdate �̓��v���P�[�g����Ȃ����߁A���ׂẴf�o�C�X�Ŏ蓮�ŌĂяo���K�v������܂��B
*/
void AThirdPersonMPCharacter::OnHealthUpdate()
{
	//Client-specific functionality
	if (IsLocallyControlled())
	{
		FString healthMessage = FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);

		if (CurrentHealth <= 0)
		{
			FString deathMessage = FString::Printf(TEXT("You have been killed."));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);
		}
	}

	//Server-specific functionality
	if (GetLocalRole() == ROLE_Authority)
	{
		FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString(), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
	}

	//Functions that occur on all machines. 
	/*
		Any special functionality that should occur as a result of damage or death should be placed here.
	*/
}

/*
�ϐ��͏펞���v���P�[�g�����̂ł͂Ȃ��A�l���ύX���邽�тɃ��v���P�[�g����܂��B
�܂��ARepNotifies �̓N���C�A���g���ϐ��̃��v���P�[�g���ꂽ�l�𐳏�Ɏ󂯎�邽�тɎ��s����܂��B
���̂��߁A�T�[�o�[��̃v���C���[�� CurrentHealth ��ύX����Ƃ��͂��ł��A
�ڑ����ꂽ�e�N���C�A���g�� OnRep_CurrentHealth �����s���邱�Ƃ����҂���܂��B
���̂��߁AOnRep_CurrentHealth ���N���C�A���g�̃}�V���� OnHealthUpdate ���Ăяo���̂ɍœK�ł��B
*/
void AThirdPersonMPCharacter::OnRep_CurrentHealth()
{
	OnHealthUpdate();
}

/*
SetCurrentHealth �́AAThirdPersonMPCharacter �̊O������
�v���C���[�� CurrentHealth ��ύX���鐧�䂳�ꂽ��i��񋟂��܂��B
����̓��v���P�[�g���ꂽ�֐��ł͂Ȃ����̂́A�A�N�^�̃l�b�g���[�N ���[���� ROLE_Authority �ł��邱�Ƃ�
�m�F���邱�ƂŁA�z�X�g���ꂽ�Q�[�� �T�[�o�[�ŌĂяo���ꂽ�ꍇ�ɂ̂ݎ��s�����悤�ɂ��̊֐��𐧌����܂��B
����́ACurrentHealth �� 0 �ƃv���C���[�� MaxHealth �Ԃ̒l�ɌŒ肷�邱�ƂŁA
CurrentHealth �𖳌��Ȓl�ɐݒ�ł��Ȃ��悤�ɂ��܂��B
�܂��A�T�[�o�[�ƃN���C�A���g�̗��������̊֐��𓯎��ɌĂяo�����Ƃ�ۏ؂��邽�߂� OnHealthUpdate ���Ăяo���܂��B
�T�[�o�[�� RepNotify ���󂯎��Ȃ����߁A���ꂪ�K�v�ɂȂ�܂��B

*TIP*
���̂悤�ȁu�Z�b�^�[�v�֐��͂��ׂĂ̕ϐ��ɕK�v�Ȃ킯�ł͂���܂��񂪁A
���ɑ����̈قȂ�\�[�X����ύX�����\��������ꍇ�ɁA
�v���C���ɕp�ɂɕύX����锽�����̍����Q�[���v���C�ϐ��ɓK���Ă��܂��B
����́A���̂悤�ȕϐ��̃��C�u�ł̕ύX�̈�ѐ������߁A�f�o�b�O��e�Ղɂ��A
�V�����@�\�ɂ��g�������ȒP�ɂ��邽�߁A
�V���O���v���C���[ �Q�[������у}���`�v���C���[ �Q�[���Ŏg�p���邱�Ƃ������߂��܂��B
*/
void AThirdPersonMPCharacter::SetCurrentHealth(float healthValue)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		CurrentHealth = FMath::Clamp(healthValue, 0.f, MaxHealth);
		OnHealthUpdate();
	}
}

/*
�A�N�^�Ƀ_���[�W��K�p���邽�߂̃r���g�C���֐��ŁA
���̃A�N�^�̊�{�� TakeDamage �֐����Ăяo���܂��B
���̏ꍇ�ASetCurrentHealth ���g�p���ăV���v���ȃw���X�̍팸���������܂��B
*/
float AThirdPersonMPCharacter::TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent
	, AController* EventInstigator, AActor* DamageCauser)
{
	float damageApplied = CurrentHealth - DamageTaken;
	SetCurrentHealth(damageApplied);
	return damageApplied;
}

/*
StartFire �̓v���C���[���A���˃v���Z�X���J�n���邽�߂Ƀ��[�J�� �}�V���ŌĂяo���֐��ł��B
���̊֐��́A���̏����Ɋ�Â��ă��[�U�[�� HandleFire ���Ăяo�����Ƃ��ł���p�x�𐧌����܂��B

	1.���łɔ��˒��̏ꍇ�A���[�U�[�͔��˕��𔭎˂ł��Ȃ��B
		����́AStartFire �̌Ăяo������ bFiringWeapon �� true �ɐݒ肳��Ă��邱�ƂŎw�肳��܂��B
	2.StopFire �̌Ăяo�����ɂ́AbFiringWeapon �� false �ɂ̂ݐݒ肳���B
	3.������ FireRate �ł���^�C�}�[����������� StopFire ���Ăяo�����B

�܂�A���[�U�[�����˕��𔭎˂���ۂ́A�ēx���˂ł���܂ł� FireRate �b�ȏ�ҋ@����K�v������܂��B
����́AStartFire �̃o�C���h��̓��͂̎�ނɂ�����炸�����悤�ɋ@�\���܂��B
�Ⴆ�΁A���[�U�[���uFire�v�R�}���h���X�N���[�� �z�C�[���₻�̑��̕s�K�؂ȓ��͂Ƀo�C���h������A
���[�U�[���J��Ԃ��{�^�����������肵�Ă��A���̊֐��͋��e�\�ȊԊu�ň����������s����A
HandleFire �ւ̌Ăяo���ɂ��M�����̍����֐��̃��[�U�[�̃L���[�̓I�[�o�[�t���[���܂���B

HandleFire �� Server RPC �ł��邽�߁ACPP �ł̎����ɂ́A
�֐����Ɂu_Implementation�v�T�t�B�b�N�X��t����K�v������܂��B
���̎����ł́A�L�����N�^�[�̉�]�R���g���[�����g�p���ăJ�����������Ă���������擾���Ă���
���˕����X�|�[�����邱�ƂŁA�v���C���[���Ə������킹�邱�Ƃ��ł���悤�ɂ��Ă��܂��B
���̂��߁A���˕��� Projectile Movement �R���|�[�l���g�����̕����ł̔��˕��̓��������������܂��B
*/
void AThirdPersonMPCharacter::StartFire()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Fire"));

	if (!bIsFiringWeapon)
	{
		bIsFiringWeapon = true;
		UWorld* World = GetWorld();
		World->GetTimerManager().SetTimer(FiringTimer, this, &AThirdPersonMPCharacter::StopFire, FireRate, false);
		HandleFire();
	}
}

void AThirdPersonMPCharacter::StopFire()
{
	bIsFiringWeapon = false;
}

void AThirdPersonMPCharacter::HandleFire_Implementation()
{
	FVector spawnLocation = GetActorLocation() + (GetControlRotation().Vector() * 100.0f) + (GetActorUpVector() * 50.0f);
	FRotator spawnRotation = GetControlRotation();

	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = GetInstigator();
	spawnParameters.Owner = this;

	AThirdPersonMPProjectile* spawnedProjectile = GetWorld()->SpawnActor<AThirdPersonMPProjectile>(spawnLocation, spawnRotation, spawnParameters);
}
