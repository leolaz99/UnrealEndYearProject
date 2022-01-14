#include "LLAnimInstance.h"
#include "GameFramework\CharacterMovementComponent.h"

ULLAnimInstance::ULLAnimInstance()
{
	ActualSpeed = 0.f;
}

void ULLAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	pawnOwner = TryGetPawnOwner();
	characterInstance = Cast<ALLCharacter>(pawnOwner);

	if(characterInstance != nullptr)
		oldRotation = characterInstance->GetControlRotation().Pitch;	
}

void ULLAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (pawnOwner != nullptr) 
	{
		UCharacterMovementComponent* charMov = pawnOwner->FindComponentByClass<UCharacterMovementComponent>();
		
		isCrouching = characterInstance->crouched;
		isAiming = characterInstance->aiming;

		if (charMov) 
		{
			FVector speed = pawnOwner->GetVelocity();
			FRotator rotation = pawnOwner->GetActorRotation();

			float currentSpeed = speed.Size();	
			ActualSpeed = currentSpeed;	
			ActualDirection = CalculateDirection(speed, rotation);
		}

		isRolling = characterInstance->roll;

		AimingAimOffset(DeltaSeconds);
	}
}

void ULLAnimInstance::CheckRoll()
{
	characterInstance->roll = false;
}

void ULLAnimInstance::AimingAimOffset(float deltaTime)
{
	FRotator controlRotation = characterInstance->GetControlRotation();
	controlRotation.Normalize();
	ActualPitch = FMath::FInterpTo(controlRotation.Pitch, oldRotation, deltaTime, 1.f);
	oldRotation = ActualPitch;
}
