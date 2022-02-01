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
}

void ULLAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (pawnOwner != nullptr)
	{
		UCharacterMovementComponent* charMov = pawnOwner->FindComponentByClass<UCharacterMovementComponent>();

		if (charMov)
		{
			FVector speed = pawnOwner->GetVelocity();
			FRotator rotation = pawnOwner->GetActorRotation();

			float currentSpeed = speed.Size();
			ActualSpeed = currentSpeed;
			ActualDirection = CalculateDirection(speed, rotation);
		}
	}
}
