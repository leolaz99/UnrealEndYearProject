#include "LLSaveSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "LLAttributes.h"
#include "LLSave.h"
#include "GameFramework/Pawn.h"
#include "LLSaveDeveloperSettings.h"

bool ULLSaveSubsystem::Save(const FString& saveName, const int32 index)
{
	ULLSaveDeveloperSettings* devSettings = GetMutableDefault<ULLSaveDeveloperSettings>();

	TSubclassOf<ULLSave> savegameType = devSettings->GetSaveGameClass();
	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(savegameType);

	const APawn* pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (pawn && SaveGameObject)
	{
		const ULLAttributes* attributesComp = pawn->FindComponentByClass<ULLAttributes>();
		ULLSave* LLsaveGame = Cast<ULLSave>(SaveGameObject);

		if (LLsaveGame)
		{
			if (attributesComp)
				LLsaveGame->HP = attributesComp->GetCurrentHealth();
			
			LLsaveGame->playerTransform = pawn->GetActorTransform();
		}

		if (UGameplayStatics::SaveGameToSlot(SaveGameObject, saveName, index))
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SAVE SUCCEDED!"));

			return true;
		}
	}

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SAVE FAILED!"));
	
	return false;
}

void ULLSaveSubsystem::Load(const FString& saveName, const int32 index)
{
	USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(saveName, index);
	APawn* pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	
	if (pawn && SaveGameObject) 
	{
		ULLAttributes* attributesComp = pawn->FindComponentByClass<ULLAttributes>();
		ULLSave* LLsaveGame = Cast<ULLSave>(SaveGameObject);
		
		if (LLsaveGame) 
		{
			if (attributesComp)
				attributesComp->SetHealth(LLsaveGame->HP);
			
			pawn->SetActorTransform(LLsaveGame->playerTransform);
			
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("LOAD SUCCEDED!"));
		}
	}
	
	else
		if (GEngine) 
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("LOAD FAILED!"));
}
