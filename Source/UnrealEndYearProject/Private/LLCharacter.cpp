#include "LLCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ALLCharacter::ALLCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	normalSensitivity = 1.f;
}

void ALLCharacter::BeginPlay()
{
	Super::BeginPlay();	
	
	PlayerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	SpringArm = FindComponentByClass<USpringArmComponent>();
	GetCharacterMovement()->MaxWalkSpeed = normalSpeed;
	
	sensitivity = normalSensitivity;
	normalFOV = PlayerCamera->GetFOVAngle();
	originalArmLenght = SpringArm->TargetArmLength;
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
	sprinting = true;

	if (!aiming) 
	{
		StopCrouch();
		GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
	}	
}

void ALLCharacter::StopSprint()
{
	sprinting = false;

	if (!aiming)
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
	aiming = true;
	StopSprint();
	GetCharacterMovement()->MaxWalkSpeed = aimingSpeed;	
	sensitivity = aimSensitivity;
	SpringArm->AddLocalOffset(cameraOffset);
}

void ALLCharacter::StopAim()
{
	bUseControllerRotationYaw = false;
	aiming = false;
	GetCharacterMovement()->MaxWalkSpeed = normalSpeed;
	sensitivity = normalSensitivity;
	SpringArm->AddLocalOffset(OriginalOffset);
}

void ALLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (aiming)
	{
		float NewFOV = FMath::FInterpTo(PlayerCamera->GetFOVAngle(), aimFOV, DeltaTime, fovChangeSpeed);
		PlayerCamera->SetFOV(NewFOV);	
	}

	if (!aiming)
	{
		float NewFOV = FMath::FInterpTo(PlayerCamera->GetFOVAngle(), normalFOV, DeltaTime, fovChangeSpeed);
		PlayerCamera->SetFOV(NewFOV);		
	}

	if (sprinting)
	{
		float NewArmLenght = FMath::FInterpTo(SpringArm->TargetArmLength, sprintArmLenght, DeltaTime, armLenghtChangeSpeed);
		SpringArm->TargetArmLength = NewArmLenght;
	}

	if (!sprinting)
	{
		float NewArmLenght = FMath::FInterpTo(SpringArm->TargetArmLength, originalArmLenght, DeltaTime, armLenghtChangeSpeed);
		SpringArm->TargetArmLength = NewArmLenght;
	}
}

void ALLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

