// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonMPCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//マルチプレイの実装
//https://docs.unrealengine.com/5.1/ja/multiplayer-programming-quick-start-for-unreal-engine/
/*
これらは、変数のレプリケーションに必要な機能と、
GEngine の AddOnscreenDebugMessage 関数へのアクセスを提供します。
これを使用して、画面にメッセージを出力します。
*/
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
/*
発射物のタイプを認識して発射物をスポーンできるようになります。
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
	これらにより、発射物の発射を処理するために必要な変数が初期化されます。
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
	/* GetLifetimeReplicatedProps 関数は、Replicated 指定子で指定したすべてのプロパティをレプリケートします。
	また、この関数を使用すると、プロパティのレプリケート方法を設定できます。
	この例では、CurrentHealth の最も基本的な実装を使用しています。
	レプリケートする必要のあるプロパティを追加する場合は常に、
	そのプロパティをこの関数にも追加する必要があります。
	
	*WARNING*
	GetLifetimeReplicatedProps の Super バージョンを呼び出す必要があります。
	これを行わないと、アクタの親クラスから継承されたプロパティが、
	親クラスでこれらのプロパティをレプリケートするように指定されている場合でもレプリケートされません。*/
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
	StartFire がこのセクションの最初の手順で作成した Fire 入力アクションにバインドされ、
	ユーザーが StartFire を有効にできます。
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
この関数を使用して、プレイヤーの CurrentHealth への変更に応じて更新を実行します。
現在、この機能は画面上のデバッグ メッセージに制限されていますが、追加の機能は追加することができます。
たとえば、OnDeath 関数は、死亡アニメーションをトリガーするために、すべてのマシンで呼び出されます。
なお、OnHealthUpdate はレプリケートされないため、すべてのデバイスで手動で呼び出す必要があります。
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
変数は常時レプリケートされるのではなく、値が変更するたびにレプリケートされます。
また、RepNotifies はクライアントが変数のレプリケートされた値を正常に受け取るたびに実行されます。
そのため、サーバー上のプレイヤーの CurrentHealth を変更するときはいつでも、
接続された各クライアントで OnRep_CurrentHealth を実行することが期待されます。
このため、OnRep_CurrentHealth がクライアントのマシンで OnHealthUpdate を呼び出すのに最適です。
*/
void AThirdPersonMPCharacter::OnRep_CurrentHealth()
{
	OnHealthUpdate();
}

/*
SetCurrentHealth は、AThirdPersonMPCharacter の外部から
プレイヤーの CurrentHealth を変更する制御された手段を提供します。
これはレプリケートされた関数ではないものの、アクタのネットワーク ロールが ROLE_Authority であることを
確認することで、ホストされたゲーム サーバーで呼び出された場合にのみ実行されるようにこの関数を制限します。
これは、CurrentHealth を 0 とプレイヤーの MaxHealth 間の値に固定することで、
CurrentHealth を無効な値に設定できないようにします。
また、サーバーとクライアントの両方がこの関数を同時に呼び出すことを保証するために OnHealthUpdate を呼び出します。
サーバーは RepNotify を受け取らないため、これが必要になります。

*TIP*
このような「セッター」関数はすべての変数に必要なわけではありませんが、
特に多くの異なるソースから変更される可能性がある場合に、
プレイ中に頻繁に変更される反応性の高いゲームプレイ変数に適しています。
これは、このような変数のライブでの変更の一貫性を高め、デバッグを容易にし、
新しい機能による拡張をより簡単にするため、
シングルプレイヤー ゲームおよびマルチプレイヤー ゲームで使用することをお勧めします。
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
アクタにダメージを適用するためのビルトイン関数で、
そのアクタの基本の TakeDamage 関数を呼び出します。
この場合、SetCurrentHealth を使用してシンプルなヘルスの削減を実装します。
*/
float AThirdPersonMPCharacter::TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent
	, AController* EventInstigator, AActor* DamageCauser)
{
	float damageApplied = CurrentHealth - DamageTaken;
	SetCurrentHealth(damageApplied);
	return damageApplied;
}

/*
StartFire はプレイヤーが、発射プロセスを開始するためにローカル マシンで呼び出す関数です。
この関数は、次の条件に基づいてユーザーが HandleFire を呼び出すことができる頻度を制限します。

	1.すでに発射中の場合、ユーザーは発射物を発射できない。
		これは、StartFire の呼び出し時に bFiringWeapon が true に設定されていることで指定されます。
	2.StopFire の呼び出し時には、bFiringWeapon は false にのみ設定される。
	3.長さが FireRate であるタイマーが完了すると StopFire が呼び出される。

つまり、ユーザーが発射物を発射する際は、再度発射できるまでに FireRate 秒以上待機する必要があります。
これは、StartFire のバインド先の入力の種類にかかわらず同じように機能します。
例えば、ユーザーが「Fire」コマンドをスクロール ホイールやその他の不適切な入力にバインドしたり、
ユーザーが繰り返しボタンを押したりしても、この関数は許容可能な間隔で引き続き実行され、
HandleFire への呼び出しによる信頼性の高い関数のユーザーのキューはオーバーフローしません。

HandleFire は Server RPC であるため、CPP での実装には、
関数名に「_Implementation」サフィックスを付ける必要があります。
この実装では、キャラクターの回転コントロールを使用してカメラが向いている方向を取得してから
発射物をスポーンすることで、プレイヤーが照準を合わせることができるようにしています。
そのため、発射物の Projectile Movement コンポーネントがその方向での発射物の動きを処理をします。
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
