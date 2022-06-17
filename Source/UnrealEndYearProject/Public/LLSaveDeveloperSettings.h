#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LLSave.h"
#include "LLSaveDeveloperSettings.generated.h"

UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Save Game Settings"))
class UNREALENDYEARPROJECT_API ULLSaveDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Config, BlueprintReadOnly, Category = Config)
	TSubclassOf<ULLSave> SaveGameClass;

public:
	UFUNCTION(BlueprintCallable, Category = Config)
	TSubclassOf<ULLSave> GetSaveGameClass() const 
	{
		return SaveGameClass;
	}
};
