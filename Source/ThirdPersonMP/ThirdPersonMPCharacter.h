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
	GetMaxHealth 関数および GetCurrentHealth 関数は、C++ およびブループリントの両方で、
	AThirdPersonMPCharacter の外部からプレイヤーのヘルス値にアクセスできるゲッター (値を取得するメソッド) を
	提供します。GetMaxHealth および GetCurrentHealth は const 関数として、
	これらの値を変更できるようにすることなく、値を取得できる安全な手段を提供します。
	また、プレイヤーのヘルスを設定し、ダメージを与えるための関数を宣言しています。
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
	プレイヤーのヘルスの変更方法を厳密に制御する必要があるため、これらのヘルス値には次の制約があります。

	+ `MaxHealth` ではレプリケートは行わず、デフォルトでは編集のみ可能。
	この値はすべてのプレイヤーに対して事前に計算されており、変更されることはありません。

	+ `CurrentHealth` ではレプリケートは行うものの、ブループリントのどの部分も編集またはアクセスできない。

	+ `MaxHealth` および `CurrentHealth` はどちらも `protected` であるため、
	外部の C++ クラスからこれらにアクセスすることはできない。MaxHealth および CurrentHealth は、
	`AThirdPersonMPCharacter` 内で、または AThirdPersonMPCharacter から派生した他のクラスでのみ変更できます。

　	 これにより、ライブのゲームプレイ中にプレイヤーの `CurrentHealth` または `MaxHealth` への
	不要な変更を引き起こすリスクを最小限に抑えます。
	これらの値を取得および変更するためのその他のパブリック関数について説明します。

　	 `Replicated` 指定子を使用すると、サーバー上のアクタのコピーは、変数の値が変更されるたびに、
	接続されているすべてのクライアントに変数の値をレプリケートできます。
	`ReplicatedUsing` も同じ処理を実行しますが、この指定子を使用すると、**RepNotify** 関数を設定できます。
	クライアントがレプリケートされたデータを正常に受信した場合に、この関数がトリガーされます。
	`OnRep_CurrentHealth` を使用して、この変数への変更に基づいて、各クライアントに対する更新を実行します。
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
	これらは、発射物を発射するために使用する変数と関数です。
	HandleFire はこのチュートリアルで実装する唯一の RPC であり、サーバーでの発射物のスポーンを行います。
	HandleFire には Server 指定子が含まれているため、クライアント上で HandleFire を呼び出そうとすると、
	呼び出しがネットワーク経由でサーバー上の権限のあるキャラクターに向けられます。

	HandleFire には Reliable 指定子も含まれているため、HandleFire は呼び出されるたびに
	信頼できる RPC のキューに配置されます。また、サーバーが HandleFire を正常に受信するとキューから削除されます。
	これにより、サーバーがこの関数呼び出しを確実に受信することが保証されます。
	ただし、削除することなく一度に多くの RPC を配置すると、信頼性の高い RPC のキューが
	オーバーフローする恐れがあります。その場合、ユーザーは強制的に接続を解除されます。
	そのため、プレイヤーがこの関数を呼び出すことのできる頻度に注意する必要があります。
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

