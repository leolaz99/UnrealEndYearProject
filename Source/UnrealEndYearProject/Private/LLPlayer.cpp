#include "LLPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Math/Vector.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "IDamagable.h"
#include "IInteractable.h"
#include "LLEnemy.h"
#include "LLAttributes.h"

ALLPlayer::ALLPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	normalSensitivity = 1.f;
	roll = false;
}

void ALLPlayer::BeginPlay()
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

void ALLPlayer::MoveForward(const float verticalAxis)
{
	if (attributes->GetCurrentHealth() > 0)
	{
		actualVerticalAxis = verticalAxis;

		const FRotator rotation = GetControlRotation();
		const FRotator direction = FRotator(0.f, rotation.Yaw, 0.f);

		const FVector directionVector = UKismetMathLibrary::GetForwardVector(direction);
		UCharacterMovementComponent* movComp = GetCharacterMovement();
		movComp->AddInputVector(directionVector * verticalAxis, false);
	}
}

void ALLPlayer::MoveCameraVertical(const float axisValue)
{
	const float verticalSpeed = axisValue * sensitivity;
	AddControllerPitchInput(verticalSpeed);
}

void ALLPlayer::MoveCameraHorizontal(const float axisValue)
{
	const float horizontalSpeed = axisValue * sensitivity;
	AddControllerYawInput(horizontalSpeed);
}

void ALLPlayer::MoveHorizontal(const float horizontalAxis)
{
	if (attributes->GetCurrentHealth() > 0)
	{
		actualHorizontalAxis = horizontalAxis;

		const FRotator rotation = GetControlRotation();
		const FRotator direction = FRotator(0.f, rotation.Yaw, 0.f);

		const FVector directionVector = UKismetMathLibrary::GetRightVector(direction);
		UCharacterMovementComponent* movComp = GetCharacterMovement();
		movComp->AddInputVector(directionVector * horizontalAxis, false);
	}
}

void ALLPlayer::CheckSprint(const float verticalAxisValue, const float horizontalAxisValue)
{
	if (verticalAxisValue == 0 && horizontalAxisValue == 0 && sprinting == true)
		StopSprint();
}

void ALLPlayer::StartCrouch()
{
	if (!GetCharacterMovement()->IsFalling()) 
	{
		crouched = true;		
		GetCharacterMovement()->bWantsToCrouch = true;
	}	
}

void ALLPlayer::StopCrouch()
{
	crouched = false;
	GetCharacterMovement()->bWantsToCrouch = false;
}

void ALLPlayer::Crouching()
{
	if (attributes->GetCurrentHealth() > 0)
	{
		if (!GetCharacterMovement()->IsCrouching())
			StartCrouch();
		else
			StopCrouch();
	}
}

void ALLPlayer::StartSprint()
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

void ALLPlayer::StopSprint()
{
	sprinting = false;

	if (!aiming)
		GetCharacterMovement()->MaxWalkSpeed = normalSpeed;
}

void ALLPlayer::Rolling()
{
	const FVector rollDirection = GetLastMovementInputVector();
	
	if (roll == false && !rollDirection.IsZero())
	{
		const FRotator MovementRotation = rollDirection.Rotation();
		SetActorRotation(MovementRotation);

		StopSprint();
		StopAim();
		roll = true;
	}
}

void ALLPlayer::StartAim()
{
	if (attributes->GetCurrentHealth() > 0)
	{
		aiming = true;
		StopSprint();
		GetCharacterMovement()->MaxWalkSpeed = aimingSpeed;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}

void ALLPlayer::StopAim()
{
	if(!sprinting)
		GetCharacterMovement()->MaxWalkSpeed = normalSpeed;
	
	bUseControllerRotationYaw = false;
	aiming = false;	
	sensitivity = normalSensitivity;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ALLPlayer::StartFire()
{
	if (aiming)
	{
		FireShot();
		GetWorldTimerManager().SetTimer(handle, this, &ALLPlayer::FireShot, fireRate, true);
	}
}

void ALLPlayer::StopFire()
{
	GetWorldTimerManager().ClearTimer(handle);
}

void ALLPlayer::FireShot()
{
	if (attributes->GetCurrentHealth() > 0)
	{
		PlayAnimMontage(fireMontage, 1.f, FName("Default"));
		
		if (shootSound)
			UGameplayStatics::PlaySound2D(GetWorld(), shootSound, 1.f, 1.f, 0.f, NULL);
		
		const float randomPitch = -0.1f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (-0.05f + 0.1f)));
		const float randomYaw = -0.2f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2f + 0.2f)));

		AddControllerPitchInput(randomPitch);
		AddControllerYawInput(randomYaw);

		const FVector cameraPos = PlayerCamera->GetActorForwardVector();
		const FTransform muzzlePos = rifleRef->GetSocketTransform("Muzzle");

		FHitResult outHit;
		const FVector start = PlayerCamera->GetTransform().GetLocation() + (PlayerCamera->GetActorForwardVector() * SpringArm->TargetArmLength);
		const FVector end = (PlayerCamera->GetActorForwardVector() * range) + start;
		const FCollisionQueryParams params;

		DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 1, 0, 1);
		bool isHit = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, params);

		const IIDamagable* isDamagable = Cast<IIDamagable>(outHit.Actor);

		if (isDamagable)
		{
			UGameplayStatics::ApplyDamage(outHit.GetActor(), attributes->GetDamage(), NULL, NULL, NULL);
		}
	}
}

void ALLPlayer::CheckLost(FName Map)
{
	UGameplayStatics::OpenLevel(this, Map);
}

void ALLPlayer::Interaction()
{
	if (inRange)
		OnInteract.Broadcast();
}

void ALLPlayer::PlayerInRange(const bool NewValue)
{
	inRange = NewValue;
}

void ALLPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckSprint(actualVerticalAxis, actualHorizontalAxis);

	if (aiming && !roll)
	{
		sensitivity = aimSensitivity;
		bUseControllerRotationYaw = true;
		const float NewFOV = FMath::FInterpTo(PlayerCamera->GetFOVAngle(), aimFOV, DeltaTime, fovChangeSpeed);
		PlayerCamera->SetFOV(NewFOV);	
	}

	if (!aiming || roll)
	{
		const float NewFOV = FMath::FInterpTo(PlayerCamera->GetFOVAngle(), normalFOV, DeltaTime, fovChangeSpeed);
		PlayerCamera->SetFOV(NewFOV);		
	}
}

void ALLPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}