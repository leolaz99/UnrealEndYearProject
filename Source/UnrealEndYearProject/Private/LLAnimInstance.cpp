#include "LLAnimInstance.h"
#include "GameFramework\CharacterMovementComponent.h"

ULLAnimInstance::ULLAnimInstance()
{
	ActualSpeed = 0.f;
}

void ULLAnimInstance::NativeInitializeAnimation()
{
	pawnOwner = TryGetPawnOwner();
	characterInstance = Cast<ALLCharacter>(pawnOwner);
	Super::NativeInitializeAnimation();
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
			const FVector speed = pawnOwner->GetVelocity();
			const FRotator rotation = pawnOwner->GetActorRotation();

			const float currentSpeed = speed.Size();	
			ActualSpeed = currentSpeed;	
			Direction = CalculateDirection(speed, rotation);
		}

		isRolling = characterInstance->roll;
	}
}

void ULLAnimInstance::CheckRoll()
{
	characterInstance->roll = false;
}
