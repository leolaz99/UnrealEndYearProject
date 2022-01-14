#include "LLCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Math/Vector.h"
#include "GameFramework/SpringArmComponent.h"

ALLCharacter::ALLCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	normalSensitivity = 1.f;
	roll = false;
}

void ALLCharacter::BeginPlay()
{
	Super::BeginPlay();	
	
	PlayerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	SpringArm = FindComponentByClass<USpringArmComponent>();
	GetCharacterMovement()->MaxWalkSpeed = normalSpeed;
	
	sensitivity = normalSensitivity;
	normalFOV = PlayerCamera->GetFOVAngle();
}

void ALLCharacter::MoveForward(float verticalAxis)
{
	FRotator rotation = GetControlRotation();
	FRotator direction = FRotator(0.f, rotation.Yaw, 0.f);

	FVector directionVector = UKismetMathLibrary::GetForwardVector(direction);
	UCharacterMovementComponent* movComp = GetCharacterMovement();
	movComp->AddInputVector(directionVector * verticalAxis, false);
}

void ALLCharacter::MoveHorizontal(float horizontalAxis)
{
	FRotator rotation = GetControlRotation();
	FRotator direction = FRotator(0.f, rotation.Yaw, 0.f);
	
	FVector directionVector = UKismetMathLibrary::GetRightVector(direction);
	UCharacterMovementComponent* movComp = GetCharacterMovement();
	movComp->AddInputVector(directionVector * horizontalAxis, false);
}

void ALLCharacter::CheckSprint(float verticalAxisValue, float horizontalAxisValue)
{
	if (verticalAxisValue == 0 && horizontalAxisValue == 0 && sprinting == true)
		StopSprint();
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
	StopAim();

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
	FVector rollDirection = GetLastMovementInputVector();
	
	if (roll == false && !rollDirection.IsZero())
	{
		FRotator MovementRotation = rollDirection.Rotation();
		SetActorRotation(MovementRotation);

		StopSprint();
		StopAim();
		roll = true;
	}
}

void ALLCharacter::StartAim()
{
	aiming = true;
	StopSprint();
	GetCharacterMovement()->MaxWalkSpeed = aimingSpeed;	
}

void ALLCharacter::StopAim()
{
	if(!sprinting)
		GetCharacterMovement()->MaxWalkSpeed = normalSpeed;
	
	bUseControllerRotationYaw = false;
	aiming = false;	
	sensitivity = normalSensitivity;
}

void ALLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (aiming && !roll)
	{
		sensitivity = aimSensitivity;
		bUseControllerRotationYaw = true;
		float NewFOV = FMath::FInterpTo(PlayerCamera->GetFOVAngle(), aimFOV, DeltaTime, fovChangeSpeed);
		PlayerCamera->SetFOV(NewFOV);	
	}

	if (!aiming || roll)
	{
		float NewFOV = FMath::FInterpTo(PlayerCamera->GetFOVAngle(), normalFOV, DeltaTime, fovChangeSpeed);
		PlayerCamera->SetFOV(NewFOV);		
	}
}

void ALLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}