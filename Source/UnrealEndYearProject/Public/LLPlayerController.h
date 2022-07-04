#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LLPlayerController.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ALLPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	TArray<int32> enemyID;
	TArray<int32> interactableID;
	TArray<int32> pointOfInterestID;

	UFUNCTION(BlueprintCallable, Category = Save)
	void AddEnemyID(const int32 id);

	UFUNCTION(BlueprintCallable, Category = Save)
	void AddInteractableID(const int32 id);

	UFUNCTION(BlueprintCallable, Category = Save)
	void AddPointOfInterestID(const int32 id);
};
