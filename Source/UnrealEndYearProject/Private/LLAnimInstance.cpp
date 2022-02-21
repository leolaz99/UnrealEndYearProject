#include "LLAnimInstance.h"
#include "GameFramework\CharacterMovementComponent.h"

ULLAnimInstance::ULLAnimInstance()
{
}

void ULLAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	pawnOwner = TryGetPawnOwner();

	if(pawnOwner != nullptr)
		charMov = pawnOwner->FindComponentByClass<UCharacterMovementComponent>();
}

void ULLAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (charMov)
	{
		FVector speed = pawnOwner->GetVelocity();
		FRotator rotation = pawnOwner->GetActorRotation();

		float currentSpeed = speed.Size();
		ActualSpeed = currentSpeed;
		ActualDirection = CalculateDirection(speed, rotation);
	}	
}
