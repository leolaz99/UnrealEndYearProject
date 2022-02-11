#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LLPlayerController.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ALLPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable, Category = LL)
	void CheckGamepad(struct FKey pressedKey);

	UPROPERTY(BlueprintReadOnly)
	bool isUsingGamepad;
};
