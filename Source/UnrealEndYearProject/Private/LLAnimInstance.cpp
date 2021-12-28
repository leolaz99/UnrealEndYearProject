#include "LLAnimInstance.h"
#include "GameFramework\CharacterMovementComponent.h"

ULLAnimInstance::ULLAnimInstance()
{
	ActualSpeed = 0.f;
}

void ULLAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void ULLAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	const APawn* pawnOwner = TryGetPawnOwner();

	if (pawnOwner != nullptr) 
	{
		const UCharacterMovementComponent* charMov = pawnOwner->FindComponentByClass<UCharacterMovementComponent>();
		if (charMov) 
		{
			const FVector speed = pawnOwner->GetVelocity();
			const float maxSpeed = charMov->GetMaxSpeed();
			const float currentSpeed = speed.Size();
			ActualSpeed = currentSpeed;

			const FVector velocity = pawnOwner->GetVelocity();
			const FRotator rotation = pawnOwner->GetActorRotation();
			Direction = CalculateDirection(velocity, rotation);
		}
	}

	else
		UE_LOG(LogTemp, Error, TEXT("Missing Pawn Owner! - UDTAnimInstance::NativeUpdateAnimation"));
}
