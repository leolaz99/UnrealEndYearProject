#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LLSaveSubsystem.generated.h"

UCLASS()
class UNREALENDYEARPROJECT_API ULLSaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Save)
	bool Save(const FString& saveName, const int32 index);

	UFUNCTION(BlueprintCallable, Category = Save)
	void Load(const FString& saveName, const int32 index);

	UFUNCTION(BlueprintCallable, Category = Save)
	void RestartMap(const FName map);

	UFUNCTION(BlueprintCallable, Category = Save)
	bool GetIDEnemy(const FString& saveName, const int32 index, const int32 id);

	UFUNCTION(BlueprintCallable, Category = Save)
	bool GetIDPointOfInterest(const FString& saveName, const int32 index, const int32 id);

	UFUNCTION(BlueprintCallable, Category = Save)
	bool GetIDInteractable(const FString& saveName, const int32 index, const int32 id);

	UPROPERTY(BlueprintReadOnly)
	bool isRestart;
};
