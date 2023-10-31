// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonMPProjectile.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"		//��{�I�ȃQ�[���v���C�֐��ւ̃A�N�Z�X
#include "UObject/ConstructorHelpers.h"	//�R���|�[�l���g��ݒ肷�邽�߂̃R���X�g���N�^�֐��ւ̃A�N�Z�X

// Sets default values
AThirdPersonMPProjectile::AThirdPersonMPProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	bReplicates �ϐ��ł́A���̃A�N�^�����v���P�[�g���s���K�v�����邱�Ƃ��Q�[���ɓ`���܂��B
	�A�N�^�́A�f�t�H���g�ł́A���̃A�N�^���X�|�[������}�V����ɂ̂ݑ��݂��܂��B
	bReplicates �� True �ɐݒ肳��Ă���ꍇ�A�A�N�^�̌����̂���R�s�[���T�[�o�[��ɑ��݂������A
	�A�N�^�͐ڑ�����Ă��邷�ׂẴN���C�A���g�ɃA�N�^�����v���P�[�g���悤�Ƃ��܂��B
	*/
	bReplicates = true;

	/*
	����ɂ��A�I�u�W�F�N�g�̍\�z���� SphereComponent ����`����AProjectile �R���W�������񋟂���܂��B
	*/
	//Definition for the SphereComponent that will serve as the Root component for the projectile and its collision.
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	SphereComponent->InitSphereRadius(37.5f);
	SphereComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = SphereComponent;

	/*
	����ɂ��ASphere �R���|�[�l���g��� OnComponentHit �C�x���g���g�p���� OnProjectileImpact �֐����o�^����܂��B
	����́A���˕��̎�ȃR���W���� �R���|�[�l���g�Ƃ��ċ@�\���܂��B
	���ɁA���̃Q�[���v���C ���W�b�N���T�[�o�[�݂̂Ŏ��s����邱�Ƃ��m���ɂ��邽�߂ɂ́A
	OnProjectileImpact ��o�^����O�� GetLocalRole() == ROLE_Authority �Ǝw�肳��Ă��邱�Ƃ��m�F���܂��B
	*/
	//Registering the Projectile Impact function on a Hit event.
	if (GetLocalRole() == ROLE_Authority)
	{
		SphereComponent->OnComponentHit.AddDynamic(this, &AThirdPersonMPProjectile::OnProjectileImpact);
	}

	/*
	����́A���o�I�\���Ƃ��Ďg�p���Ă��� StaticMeshComponent ���`���܂��B
	���̃R���|�[�l���g�ł́AStarterContent ���� Shape_Sphere ���b�V���������I�Ɍ������Ď�荞�݂܂��B
	�܂��A���̂��T�C�Y�� SphereComponent �ɍ����悤�ɃX�P�[�����O����܂��B
	*/
	//Definition for the Mesh that will serve as our visual representation.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	//Set the Static Mesh and its position/scale if we successfully found a mesh asset to use.
	if (DefaultMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(DefaultMesh.Object);
		StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -37.5f));
		StaticMesh->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
	}

	/*
	StarterContent ���� P_Explosion �A�Z�b�g�ɂȂ�悤�� ExplosionEffect �̃A�Z�b�g�̎Q�Ƃ��ݒ肳��܂�
	*/
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultExplosionEffect(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (DefaultExplosionEffect.Succeeded())
	{
		ExplosionEffect = DefaultExplosionEffect.Object;
	}

	/*
	���˕��� Projectile Movement �R���|�[�l���g����`����܂��B���̃R���|�[�l���g�̓��v���P�[�g����A
	�T�[�o�[��ł��̃R���|�[�l���g�����s���邷�ׂĂ̓������N���C�A���g��ōČ�����܂��B
	*/
	//Definition for the Projectile Movement Component.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->SetUpdatedComponent(SphereComponent);
	ProjectileMovementComponent->InitialSpeed = 1500.0f;
	ProjectileMovementComponent->MaxSpeed = 1500.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	/*
	���˕����A�N�^�ɗ^����_���[�W�̗ʂƁA�_���[�W �C�x���g�Ŏg�p�����_���[�W �^�C�v�̗��������������܂��B
	���̗�ł́A�V�����_���[�W �^�C�v���܂���`���Ă��Ȃ����߁A��{�� UDamageType �ŏ��������܂��B
	*/
	DamageType = UDamageType::StaticClass();
	Damage = 10.0f;

}

// Called when the game starts or when spawned
void AThirdPersonMPProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThirdPersonMPProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
����̓A�N�^���j������邽�тɌĂяo����܂��B
�p�[�e�B�N�� �G�~�b�^���̂͒ʏ�̓��v���P�[�g����܂��񂪁A�A�N�^�̔j��̓��v���P�[�g����邽�߁A
�T�[�o�[��̂��̔��˕���j�󂷂�ƁA�ڑ����ꂽ�e�N���C�A���g��Ŏ��g�̃R�s�[��j�󂷂�ۂɁA
���̊֐����e�N���C�A���g�ŌĂяo����邱�Ƃ��킩��܂��B
���̌��ʁA���˕����j�󂳂��ƁA���ׂẴv���C���[�ɔ����G�t�F�N�g���\������܂��B
*/
void AThirdPersonMPProjectile::Destroyed()
{
	FVector spawnLocation = GetActorLocation();
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, spawnLocation, 
		FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
}

/*
���˕����I�u�W�F�N�g�ɏՓ˂����Ƃ��ɌĂяo���֐��ł��B���˕����Փ˂���I�u�W�F�N�g���L���ȃA�N�^�ł���ꍇ�A
�R���W���������������|�C���g�ŁA���̃I�u�W�F�N�g�Ƀ_���[�W��^���� ApplyPointDamage �֐����Ăяo���܂��B
����A�Փ˂����T�[�t�F�X�ɂ�����炸�A������R���W�����ł��̃A�N�^���j�󂳂�A�����G�t�F�N�g���\������܂��B
*/
void AThirdPersonMPProjectile::OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		UGameplayStatics::ApplyPointDamage(OtherActor, Damage, NormalImpulse, Hit,
			GetInstigator()->Controller, this, DamageType);
	}

	Destroy();
}