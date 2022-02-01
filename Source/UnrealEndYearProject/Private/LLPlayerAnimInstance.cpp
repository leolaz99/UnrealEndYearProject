#include "LLPlayerAnimInstance.h"
#include "GameFramework\CharacterMovementComponent.h"

void ULLPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	pawnOwner = TryGetPawnOwner();
	characterInstance = Cast<ALLCharacter>(pawnOwner);

	if (characterInstance != nullptr)
		oldRotation = characterInstance->GetControlRotation().Pitch;
}

void ULLPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (pawnOwner != nullptr)
	{
		UCharacterMovementComponent* charMov = pawnOwner->FindComponentByClass<UCharacterMovementComponent>();

		isCrouching = characterInstance->crouched;
		isAiming = characterInstance->aiming;
		isRolling = characterInstance->roll;

		AimingAimOffset(DeltaSeconds);
	}
}

void ULLPlayerAnimInstance::CheckRoll()
{
	characterInstance->roll = false;
}

void ULLPlayerAnimInstance::AimingAimOffset(float deltaTime)
{
	FRotator controlRotation = characterInstance->GetControlRotation();
	controlRotation.Normalize();
	ActualPitch = FMath::FInterpTo(controlRotation.Pitch, oldRotation, deltaTime, 1.f);
	oldRotation = ActualPitch;
}
