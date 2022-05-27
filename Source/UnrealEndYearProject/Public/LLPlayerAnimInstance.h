#pragma once

#include "CoreMinimal.h"
#include "LLAnimInstance.h"
#include "LLPlayer.h"
#include "LLPlayerAnimInstance.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ULLPlayerAnimInstance : public ULLAnimInstance
{
	GENERATED_BODY()

protected:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = LL)
	void CheckRoll();

	void AimingAimOffset(const float deltaTime);

	UPROPERTY(BlueprintReadOnly, Category = LL)
	bool isCrouching;

	UPROPERTY(BlueprintReadOnly, Category = LL)
	bool isAiming;

	UPROPERTY(BlueprintReadOnly, Category = LL)
	float ActualPitch;

	UPROPERTY(BlueprintReadOnly, Category = LL)
	bool isRolling;

	float oldRotation;

	ALLPlayer* characterInstance;
};
