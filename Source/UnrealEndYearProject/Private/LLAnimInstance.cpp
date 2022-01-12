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

	APawn* pawnOwner = TryGetPawnOwner();

	if (pawnOwner != nullptr) 
	{
		UCharacterMovementComponent* charMov = pawnOwner->FindComponentByClass<UCharacterMovementComponent>();
		ALLCharacter* characterInstance = Cast<ALLCharacter>(pawnOwner);
		
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

	else
		UE_LOG(LogTemp, Error, TEXT("Missing Pawn Owner! - ULLAnimInstance::NativeUpdateAnimation"));
}

void ULLAnimInstance::CheckRoll()
{
	APawn* pawnOwner = TryGetPawnOwner();
	ALLCharacter* characterInstance = Cast<ALLCharacter>(pawnOwner);
	characterInstance->roll = false;
}
