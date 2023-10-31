// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonMPProjectile.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"		//基本的なゲームプレイ関数へのアクセス
#include "UObject/ConstructorHelpers.h"	//コンポーネントを設定するためのコンストラクタ関数へのアクセス

// Sets default values
AThirdPersonMPProjectile::AThirdPersonMPProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	bReplicates 変数では、このアクタがレプリケートを行う必要があることをゲームに伝えます。
	アクタは、デフォルトでは、そのアクタをスポーンするマシン上にのみ存在します。
	bReplicates が True に設定されている場合、アクタの権限のあるコピーがサーバー上に存在する限り、
	アクタは接続されているすべてのクライアントにアクタをレプリケートしようとします。
	*/
	bReplicates = true;

	/*
	これにより、オブジェクトの構築時に SphereComponent が定義され、Projectile コリジョンが提供されます。
	*/
	//Definition for the SphereComponent that will serve as the Root component for the projectile and its collision.
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	SphereComponent->InitSphereRadius(37.5f);
	SphereComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = SphereComponent;

	/*
	これにより、Sphere コンポーネント上の OnComponentHit イベントを使用して OnProjectileImpact 関数が登録されます。
	これは、発射物の主なコリジョン コンポーネントとして機能します。
	特に、このゲームプレイ ロジックがサーバーのみで実行されることを確実にするためには、
	OnProjectileImpact を登録する前に GetLocalRole() == ROLE_Authority と指定されていることを確認します。
	*/
	//Registering the Projectile Impact function on a Hit event.
	if (GetLocalRole() == ROLE_Authority)
	{
		SphereComponent->OnComponentHit.AddDynamic(this, &AThirdPersonMPProjectile::OnProjectileImpact);
	}

	/*
	これは、視覚的表現として使用している StaticMeshComponent を定義します。
	このコンポーネントでは、StarterContent 内で Shape_Sphere メッシュを自動的に検索して取り込みます。
	また、球体もサイズが SphereComponent に合うようにスケーリングされます。
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
	StarterContent 内の P_Explosion アセットになるように ExplosionEffect のアセットの参照が設定されます
	*/
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultExplosionEffect(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (DefaultExplosionEffect.Succeeded())
	{
		ExplosionEffect = DefaultExplosionEffect.Object;
	}

	/*
	発射物の Projectile Movement コンポーネントが定義されます。このコンポーネントはレプリケートされ、
	サーバー上でこのコンポーネントが実行するすべての動きがクライアント上で再現されます。
	*/
	//Definition for the Projectile Movement Component.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->SetUpdatedComponent(SphereComponent);
	ProjectileMovementComponent->InitialSpeed = 1500.0f;
	ProjectileMovementComponent->MaxSpeed = 1500.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	/*
	発射物がアクタに与えるダメージの量と、ダメージ イベントで使用されるダメージ タイプの両方を初期化します。
	この例では、新しいダメージ タイプをまだ定義していないため、基本の UDamageType で初期化します。
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
これはアクタが破棄されるたびに呼び出されます。
パーティクル エミッタ自体は通常はレプリケートされませんが、アクタの破壊はレプリケートされるため、
サーバー上のこの発射物を破壊すると、接続された各クライアント上で自身のコピーを破壊する際に、
この関数が各クライアントで呼び出されることがわかります。
その結果、発射物が破壊されると、すべてのプレイヤーに爆発エフェクトが表示されます。
*/
void AThirdPersonMPProjectile::Destroyed()
{
	FVector spawnLocation = GetActorLocation();
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, spawnLocation, 
		FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
}

/*
発射物がオブジェクトに衝突したときに呼び出す関数です。発射物が衝突するオブジェクトが有効なアクタである場合、
コリジョンが発生したポイントで、そのオブジェクトにダメージを与える ApplyPointDamage 関数を呼び出します。
一方、衝突したサーフェスにかかわらず、あらゆるコリジョンでこのアクタが破壊され、爆発エフェクトが表示されます。
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