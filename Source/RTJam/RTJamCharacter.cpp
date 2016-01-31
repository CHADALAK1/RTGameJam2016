// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "RTJam.h"
#include "Actors/PickupBase.h"
#include "RTJamCharacter.h"

ARTJamCharacter::ARTJamCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ARTJamCharacter::OnHit);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	bIsDead = false;

	NormalImpulse = 600.f;
	MaxImpulse = 1200.f;
	ForceLength.Z = NormalImpulse;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARTJamCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAxis("MoveRight", this, &ARTJamCharacter::MoveRight);

	InputComponent->BindTouch(IE_Pressed, this, &ARTJamCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ARTJamCharacter::TouchStopped);
}

void ARTJamCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARTJamCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsInvincible())
	{
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	}
	else
	{
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	}

}

void ARTJamCharacter::Jump()
{
	Super::Jump();

	//compute force length by limiting max height to avoid player going off screen
	float LV_LevelHeight = 1650.f;
	float LV_CharacterHeight = GetMesh()->GetComponentLocation().Z;

	float LV_ForceStrength = LerpFloat(0.f, ForceLength.Size(), 1.f - ((LV_CharacterHeight - LV_LevelHeight) / MaxHeight));

	this->LaunchCharacter(ForceLength.GetSafeNormal() * LV_ForceStrength, false, true);
}

void ARTJamCharacter::GravityTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "GravityBoosted");
	ForceLength.Z = MaxImpulse;
	GetWorldTimerManager().SetTimer(GravityHandle, this, &ARTJamCharacter::GravityEnd, 3.f, false);
}

void ARTJamCharacter::GravityEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "GravityNormal");
	ForceLength.Z = NormalImpulse;
	GetWorldTimerManager().ClearTimer(GravityHandle);
}

void ARTJamCharacter::DeathTimer()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("GameOver_Screen"));
	GetWorldTimerManager().ClearTimer(DeathHandle);
}

void ARTJamCharacter::InvincibilityTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Invincible");
	bIsInvincible = true;
	GetWorldTimerManager().SetTimer(InvincibilityHandle, this, &ARTJamCharacter::InvincibilityEnd, 2.f, false);
}

void ARTJamCharacter::InvincibilityEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "NotInvincible");
	bIsInvincible = false;
	GetWorldTimerManager().ClearTimer(InvincibilityHandle);
}

void ARTJamCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ARTJamCharacter::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	APickupBase *Item = Cast<APickupBase>(OtherActor);
	if (!Item)
	{
		bIsDead = true;
		DisableInput(GetWorld()->GetFirstPlayerController());
		GetWorldTimerManager().SetTimer(DeathHandle, this, &ARTJamCharacter::DeathTimer, 2.f, false);
	}
}

void ARTJamCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ARTJamCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

