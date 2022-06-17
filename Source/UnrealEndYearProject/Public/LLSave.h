#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LLSave.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ULLSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = Save)
	float HP;
};
