// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThirdPersonMPProjectile.generated.h"

UCLASS()
class THIRDPERSONMP_API AThirdPersonMPProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AThirdPersonMPProjectile();

	/*
	class キーワードを使ってこれらの宣言においてそれぞれの型を優先します。
	これにより、変数宣言されるだけでなく独自クラスの前方宣言にし、
	それらのクラスがヘッダ ファイル内で確実に認識されるようになります。
	*/
	// Sphere component used to test collision.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USphereComponent* SphereComponent;

	// Static Mesh used to provide a visual representation of the object.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* StaticMesh;

	// Movement component for handling projectile movement.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UProjectileMovementComponent* ProjectileMovementComponent;

	// Particle used when the projectile impacts against another object and explodes.
	UPROPERTY(EditAnywhere, Category = "Effects")
		class UParticleSystem* ExplosionEffect;

	//The damage type and damage that will be done by this projectile
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
		TSubclassOf<class UDamageType> DamageType;

	//The damage dealt by this projectile.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
		float Damage;


protected:

	UFUNCTION(Category = "Projectile")
		void OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void Destroyed() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
