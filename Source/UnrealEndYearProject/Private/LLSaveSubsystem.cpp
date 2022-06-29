#include "LLSaveSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "LLAttributes.h"
#include "QuestComponent.h"
#include "LLSave.h"
#include "GameFramework/Pawn.h"
#include "LLSaveDeveloperSettings.h"

bool ULLSaveSubsystem::Save(const FString& saveName, const int32 index)
{
	ULLSaveDeveloperSettings* devSettings = GetMutableDefault<ULLSaveDeveloperSettings>();

	TSubclassOf<ULLSave> savegameType = devSettings->GetSaveGameClass();
	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(savegameType);

	const APawn* pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	const APlayerController* playerControl = UGameplayStatics::GetPlayerController(this, 0);

	if (pawn && SaveGameObject)
	{
		const ULLAttributes* attributesComp = pawn->FindComponentByClass<ULLAttributes>();
		UQuestComponent* questComp = playerControl->FindComponentByClass<UQuestComponent>();

		ULLSave* LLsaveGame = Cast<ULLSave>(SaveGameObject);

		if (LLsaveGame)
		{
			if (attributesComp)
				LLsaveGame->HP = attributesComp->GetCurrentHealth();
			
			LLsaveGame->playerTransform = pawn->GetActorTransform();						
		}

		//if (questComp)
		//{
		//	for (int i = 0; i < questComp->GetQuestLenght()  ;i++)
		//	{
		//		LLsaveGame->questValues[i] = questComp->GetQuestCounter(i);
		//	}
		//}

		if (UGameplayStatics::SaveGameToSlot(LLsaveGame, saveName, index))
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("SAVE SUCCEDED!"));

			return true;
		}
	}

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SAVE FAILED!"));
	
	return false;
}

void ULLSaveSubsystem::Load(const FString& saveName, const int32 index)
{
	if (isRestart)
	{
		const APlayerController* playerControl = UGameplayStatics::GetPlayerController(this, 0);
		USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(saveName, index);
		APawn* pawn = UGameplayStatics::GetPlayerPawn(this, 0);

		if (pawn && SaveGameObject)
		{
			UQuestComponent* questComp = playerControl->FindComponentByClass<UQuestComponent>();

			ULLAttributes* attributesComp = pawn->FindComponentByClass<ULLAttributes>();
			ULLSave* LLsaveGame = Cast<ULLSave>(SaveGameObject);

			if (LLsaveGame)
			{
				if (attributesComp)
					attributesComp->SetHealth(LLsaveGame->HP);

				pawn->SetActorTransform(LLsaveGame->playerTransform);

				//if (questComp)
				//{
				//	for (int i = 0; i < questComp->GetQuestLenght(); i++)
				//	{
				//		questComp->SetQuestCounter(i, LLsaveGame->questValues[i]);
				//	}
				//}

				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("LOAD SUCCEDED!"));
			}
		}

		isRestart = false;
	}
	
	else
		if (GEngine) 
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("LOAD FAILED!"));
}

void ULLSaveSubsystem::RestartMap(const FName map)
{
	UGameplayStatics::OpenLevel(this, map);
	isRestart = true;
}
