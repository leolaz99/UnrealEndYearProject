#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LLSave.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ULLSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, SaveGame, Category = Save)
	float HP;

	UPROPERTY(BlueprintReadOnly, SaveGame, Category = Save)
	FTransform playerTransform;

	UPROPERTY(BlueprintReadOnly, SaveGame, Category = Save)
	TArray<int32> questValues;

	UPROPERTY(BlueprintReadOnly, SaveGame, Category = Save)
	TArray<int32> EnemyID;

	UPROPERTY(BlueprintReadOnly, SaveGame, Category = Save)
	TArray<int32> saveInteractableID;

	UPROPERTY(BlueprintReadOnly, SaveGame, Category = Save)
	TArray<int32> savePointOfInterestID;
};
