#include "LLCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ALLCharacter::ALLCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALLCharacter::BeginPlay()
{
	Super::BeginPlay();	

	GetCharacterMovement()->MaxWalkSpeed = normalSpeed;
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

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Direction * value);
}

void ALLCharacter::StartCrouch()
{
	if (!GetCharacterMovement()->IsFalling()) 
	{
		crouched = true;		
		GetCharacterMovement()->bWantsToCrouch = true;
	}	
}

void ALLCharacter::StopCrouch()
{
	crouched = false;
	GetCharacterMovement()->bWantsToCrouch = false;		
}

void ALLCharacter::Crouching()
{	
	if (!GetCharacterMovement()->IsCrouching())
		StartCrouch();
	else
		StopCrouch();
}

void ALLCharacter::StartSprint()
{
	StopCrouch();
	GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
}

void ALLCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = normalSpeed;
}

void ALLCharacter::Rolling()
{
	if (!GetCharacterMovement()->IsCrouching()) 
	{
		FVector RollDirection = this->GetLastMovementInputVector();
		LaunchCharacter(RollDirection * rollingDistance, true, true);
	}	
}

void ALLCharacter::StartAim()
{
	bUseControllerRotationYaw = true;
}

void ALLCharacter::StopAim()
{
	bUseControllerRotationYaw = false;
}

void ALLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

