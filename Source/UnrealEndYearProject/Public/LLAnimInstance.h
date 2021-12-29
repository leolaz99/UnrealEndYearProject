#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LLAnimInstance.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ULLAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	ULLAnimInstance();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, Category = LL)
	float ActualSpeed;

	UPROPERTY(BlueprintReadOnly, Category = LL)
	float Direction;
};
