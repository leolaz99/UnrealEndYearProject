#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LLCharacter.h"
#include "LLAnimInstance.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ULLAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	ULLAnimInstance();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = LL)
	void CheckRoll();

	void AimingAimOffset(float deltaTime);

	UPROPERTY(BlueprintReadOnly, Category = LL)
	float ActualSpeed;

	UPROPERTY(BlueprintReadOnly, Category = LL)
	float ActualDirection;

	UPROPERTY(BlueprintReadOnly, Category = LL)
	bool isCrouching;

	UPROPERTY(BlueprintReadOnly, Category = LL)
	bool isAiming;

	UPROPERTY(BlueprintReadOnly, Category = LL)
	float ActualPitch;

	UPROPERTY(BlueprintReadOnly, Category = LL)
	bool isRolling;

	float oldRotation;

	ALLCharacter* characterInstance;
	APawn* pawnOwner;
};
