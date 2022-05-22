// Copyright Epic Games, Inc. All Rights Reserved.

#include "FightingGameCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AFightingGameCharacter::AFightingGameCharacter(): bIsAttacking(false) {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

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

	MaxHealth = 1.f;
	Health = 1.f;

	MaxEX = 1.f;
	EX = 1.f;
}

void AFightingGameCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFightingGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFightingGameCharacter::MoveRight);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFightingGameCharacter::Crouching);

	PlayerInputComponent->BindAction("Input1", IE_Pressed, this, &AFightingGameCharacter::StartInput1);
	PlayerInputComponent->BindAction("Input2", IE_Pressed, this, &AFightingGameCharacter::StartInput2);
	PlayerInputComponent->BindAction("Input3", IE_Pressed, this, &AFightingGameCharacter::StartInput3);
	PlayerInputComponent->BindAction("Input4", IE_Pressed, this, &AFightingGameCharacter::StartInput4);

	PlayerInputComponent->BindAction("Super1", IE_Pressed, this, &AFightingGameCharacter::StartSuper1);
	PlayerInputComponent->BindAction("Super2", IE_Pressed, this, &AFightingGameCharacter::StartSuper2);

	PlayerInputComponent->BindAction("Input1", IE_Released, this, &AFightingGameCharacter::StopInput1);
	PlayerInputComponent->BindAction("Input2", IE_Released, this, &AFightingGameCharacter::StopInput2);
	PlayerInputComponent->BindAction("Input3", IE_Released, this, &AFightingGameCharacter::StopInput3);
	PlayerInputComponent->BindAction("Input4", IE_Released, this, &AFightingGameCharacter::StopInput4);

	PlayerInputComponent->BindAction("Super1", IE_Released, this, &AFightingGameCharacter::StopSuper1);
	PlayerInputComponent->BindAction("Super2", IE_Released, this, &AFightingGameCharacter::StopSuper2);
}

void AFightingGameCharacter::TakeDamage(float DamageAmount) {
	Health -= DamageAmount;

	UE_LOG(LogTemp, Warning, TEXT("Take Damage: %f Current Health: %f"), DamageAmount, Health);

	if (Health < 0.f) {
		Health = 0.f;
	}

}

void AFightingGameCharacter::MoveRight(float Value) {
	// add movement in that direction
	AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
}

void AFightingGameCharacter::Crouching() {
	UE_LOG(LogTemp, Warning, TEXT("Crouch"))
}

void AFightingGameCharacter::StartInput1() {
	UE_LOG(LogTemp, Warning, TEXT("Input1 bIsAttacking %s bInput1 %s"), bIsAttacking ? TEXT("true"): TEXT("false"),
	       bInput1 ? TEXT("true") : TEXT("false"))
	if (bIsAttacking && bInput1)
		return;
	bIsAttacking = true;
	bInput1 = true;
	UE_LOG(LogTemp, Warning, TEXT("Input1"))
}

void AFightingGameCharacter::StartInput2() {
	UE_LOG(LogTemp, Warning, TEXT("Input1 bIsAttacking %s bInput2 %s"), bIsAttacking ? TEXT("true") : TEXT("false"),
	       bInput2 ? TEXT("true") : TEXT("false"))
	if (bIsAttacking && bInput2)
		return;
	bIsAttacking = true;
	bInput2 = true;
	UE_LOG(LogTemp, Warning, TEXT("Input2"))
}

void AFightingGameCharacter::StartInput3() {
	UE_LOG(LogTemp, Warning, TEXT("Input1 bIsAttacking %s bInput3 %s"), bIsAttacking ? TEXT("true") : TEXT("false"),
	       bInput3 ? TEXT("true") : TEXT("false"))
	if (bIsAttacking && bInput3)
		return;
	bIsAttacking = true;
	bInput3 = true;
	UE_LOG(LogTemp, Warning, TEXT("Input3"))
}

void AFightingGameCharacter::StartInput4() {
	UE_LOG(LogTemp, Warning, TEXT("Input1 bIsAttacking %s bInput4 %s"), bIsAttacking ? TEXT("true") : TEXT("false"),
	       bInput4 ? TEXT("true") : TEXT("false"))
	if (bIsAttacking && bInput4)
		return;
	bIsAttacking = true;
	bInput4 = true;
	UE_LOG(LogTemp, Warning, TEXT("Input4"))
}

void AFightingGameCharacter::StartSuper1() {
	bIsAttacking = true;
	UE_LOG(LogTemp, Warning, TEXT("Super1"))
}

void AFightingGameCharacter::StartSuper2() {
	bIsAttacking = true;

	UE_LOG(LogTemp, Warning, TEXT("Super2"))
}

void AFightingGameCharacter::StopInput1() {
	// bIsAttacking = false;
	// bInput1 = false;
}

void AFightingGameCharacter::StopInput2() {
	// bIsAttacking = false;
	// bInput2 = false;
}

void AFightingGameCharacter::StopInput3() {
	// bIsAttacking = false;
	// bInput3 = false;
}

void AFightingGameCharacter::StopInput4() {
	// bIsAttacking = false;
	// bInput4 = false;
}

void AFightingGameCharacter::StopSuper1() {
	// bIsAttacking = false;
}

void AFightingGameCharacter::StopSuper2() {
	// bIsAttacking = false;
}
