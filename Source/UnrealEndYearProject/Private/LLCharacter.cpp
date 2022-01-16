#include "LLCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Math/Vector.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "IDamagable.h"
#include "LLEnemy.h"
#include "LLAttributes.h"

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
	TArray<UActorComponent*> rifles = GetComponentsByTag(USkeletalMeshComponent::StaticClass(), "Muzzle");
	if (rifles.Num() > 0) 
		rifleRef = Cast<USkeletalMeshComponent>(rifles[0]);

	GetCharacterMovement()->MaxWalkSpeed = normalSpeed;
	
	sensitivity = normalSensitivity;
	normalFOV = PlayerCamera->GetFOVAngle();

	attributes = FindComponentByClass<ULLAttributes>();
}

void ALLCharacter::MoveForward(float verticalAxis)
{
	actualVerticalAxis = verticalAxis;

	FRotator rotation = GetControlRotation();
	FRotator direction = FRotator(0.f, rotation.Yaw, 0.f);

	FVector directionVector = UKismetMathLibrary::GetForwardVector(direction);
	UCharacterMovementComponent* movComp = GetCharacterMovement();
	movComp->AddInputVector(directionVector * verticalAxis, false);
}

void ALLCharacter::MoveCameraVertical(float axisValue)
{
	float verticalSpeed = axisValue * sensitivity;
	AddControllerPitchInput(verticalSpeed);
}

void ALLCharacter::MoveCameraHorizontal(float axisValue)
{
	float horizontalSpeed = axisValue * sensitivity;
	AddControllerYawInput(horizontalSpeed);
}

void ALLCharacter::MoveHorizontal(float horizontalAxis)
{
	actualHorizontalAxis = horizontalAxis;

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

void ALLCharacter::StartFire()
{
	if (aiming)
	{
		FireShot();
		GetWorldTimerManager().SetTimer(handle, this, &ALLCharacter::FireShot, fireRate, true);
	}
}

void ALLCharacter::StopFire()
{
	GetWorldTimerManager().ClearTimer(handle);
}

void ALLCharacter::FireShot()
{
	float randomPitch = -0.1f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (-0.05f + 0.1f)));
	float randomYaw = -0.2f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2f + 0.2f)));

	AddControllerPitchInput(randomPitch);
	AddControllerYawInput(randomYaw);

	FVector cameraPos = PlayerCamera->GetActorForwardVector();
	FTransform muzzlePos = rifleRef->GetSocketTransform("Muzzle");

	FHitResult outHit;
	FVector start = PlayerCamera->GetTransform().GetLocation();
	FVector end = (PlayerCamera->GetActorForwardVector() * range) + start;
	FCollisionQueryParams params;

	DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 1, 0, 1);
	bool isHit = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, params);

	if (isHit)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, FString::Printf(TEXT("HIT")));
	}

	IIDamagable* isDamagable = Cast<IIDamagable>(outHit.Actor);
	
	if(isDamagable)
	{
		ULLAttributes* enemyAttribute = outHit.GetActor()->FindComponentByClass<ULLAttributes>();
		enemyAttribute->CurrentHealth = enemyAttribute->CurrentHealth - attributes->Damage;
		
		if (enemyAttribute->CurrentHealth <= 0)
		{
			outHit.GetActor()->Destroy();
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("vita a 0")));
		}
			
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Damage")));
	}		
}

void ALLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckSprint(actualVerticalAxis, actualHorizontalAxis);

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