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

	if(pawnOwner != nullptr)
		charMov = pawnOwner->FindComponentByClass<UCharacterMovementComponent>();
}

void ULLAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (pawnOwner != nullptr)
	{
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
