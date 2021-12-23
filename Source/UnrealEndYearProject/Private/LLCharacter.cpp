#include "LLCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ALLCharacter::ALLCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALLCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void ALLCharacter::MoveForward(float value)
{
	FRotator rotation = GetControlRotation();
	FRotator YawRotation = FRotator(0.f, rotation.Yaw, 0.f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(Direction * value);
}

void ALLCharacter::MoveHorizontal(float value)
{
	FRotator rotation = GetControlRotation();
	FRotator YawRotation = FRotator(0.f, rotation.Yaw, 0.f);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Direction * value);
}

void ALLCharacter::StartCrouch()
{
	if (!GetCharacterMovement()->IsFalling()) 
	{
		GetCharacterMovement()->bWantsToCrouch = true;
		GetCharacterMovement()->Crouch();
	}	
}

void ALLCharacter::StopCrouch()
{
	GetCharacterMovement()->bWantsToCrouch = false;
	GetCharacterMovement()->UnCrouch();		
}

void ALLCharacter::Crouching()
{
	if (!GetCharacterMovement()->IsCrouching())
		StartCrouch();
	else
		StopCrouch();
}

void ALLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

