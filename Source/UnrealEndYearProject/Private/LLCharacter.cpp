#include "LLCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
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
	if (attributes->GetCurrentHealth() > 0)
	{
		actualVerticalAxis = verticalAxis;

		FRotator rotation = GetControlRotation();
		FRotator direction = FRotator(0.f, rotation.Yaw, 0.f);

		FVector directionVector = UKismetMathLibrary::GetForwardVector(direction);
		UCharacterMovementComponent* movComp = GetCharacterMovement();
		movComp->AddInputVector(directionVector * verticalAxis, false);
	}
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
	if (attributes->GetCurrentHealth() > 0)
	{
		actualHorizontalAxis = horizontalAxis;

		FRotator rotation = GetControlRotation();
		FRotator direction = FRotator(0.f, rotation.Yaw, 0.f);

		FVector directionVector = UKismetMathLibrary::GetRightVector(direction);
		UCharacterMovementComponent* movComp = GetCharacterMovement();
		movComp->AddInputVector(directionVector * horizontalAxis, false);
	}
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
	if (attributes->GetCurrentHealth() > 0)
	{
		if (!GetCharacterMovement()->IsCrouching())
			StartCrouch();
		else
			StopCrouch();
	}
}

void ALLCharacter::StartSprint()
{
	if (attributes->GetCurrentHealth() > 0)
	{
		sprinting = true;
		StopAim();

		if (!aiming)
		{
			StopCrouch();
			GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
		}
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
	if (attributes->GetCurrentHealth() > 0)
	{
		aiming = true;
		StopSprint();
		GetCharacterMovement()->MaxWalkSpeed = aimingSpeed;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}

void ALLCharacter::StopAim()
{
	if(!sprinting)
		GetCharacterMovement()->MaxWalkSpeed = normalSpeed;
	
	bUseControllerRotationYaw = false;
	aiming = false;	
	sensitivity = normalSensitivity;

	GetCharacterMovement()->bOrientRotationToMovement = true;
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
	if (attributes->GetCurrentHealth() > 0)
	{
		PlayAnimMontage(fireMontage, 1.f, FName("Default"));
		float randomPitch = -0.1f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (-0.05f + 0.1f)));
		float randomYaw = -0.2f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2f + 0.2f)));

		AddControllerPitchInput(randomPitch);
		AddControllerYawInput(randomYaw);

		FVector cameraPos = PlayerCamera->GetActorForwardVector();
		FTransform muzzlePos = rifleRef->GetSocketTransform("Muzzle");

		FHitResult outHit;
		const FVector start = PlayerCamera->GetTransform().GetLocation() + (PlayerCamera->GetActorForwardVector() * SpringArm->TargetArmLength);
		const FVector end = (PlayerCamera->GetActorForwardVector() * range) + start;
		FCollisionQueryParams params;

		DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 1, 0, 1);
		bool isHit = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, params);

		IIDamagable* isDamagable = Cast<IIDamagable>(outHit.Actor);

		if (isDamagable)
		{
			UGameplayStatics::ApplyDamage(outHit.GetActor(), attributes->Damage, NULL, NULL, NULL);
		}
	}
}

void ALLCharacter::CheckLost(FName Map)
{
	if (FMath::IsNearlyEqual(attributes->GetCurrentHealth(), 0, 0.001f))
		UGameplayStatics::OpenLevel(this, Map);
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