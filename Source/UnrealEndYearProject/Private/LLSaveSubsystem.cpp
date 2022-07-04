#include "LLSaveSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "LLAttributes.h"
#include "QuestComponent.h"
#include "LLSave.h"
#include "GameFramework/Pawn.h"
#include "LLSaveDeveloperSettings.h"
#include "LLPlayerController.h"

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

			const ALLPlayerController* LLPlayercont = Cast<ALLPlayerController>(playerControl);

			for (int i = 0; i < LLPlayercont->enemyID.Num(); i++)
			{
				LLsaveGame->EnemyID.Add(LLPlayercont->enemyID[i]);
			}

			for (int i = 0; i < LLPlayercont->pointOfInterestID.Num(); i++)
			{
				LLsaveGame->savePointOfInterestID.Add(LLPlayercont->pointOfInterestID[i]);
			}

			for (int i = 0; i < LLPlayercont->interactableID.Num(); i++)
			{
				LLsaveGame->saveInteractableID.Add(LLPlayercont->interactableID[i]);
			}

			if (questComp)
			{
				for (int i = 0; i < questComp->GetQuestLenght(); i++)
				{
					LLsaveGame->questValues.Add(questComp->GetQuestCounter(i));
				}
			}
		}

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
		APlayerController* playerControl = UGameplayStatics::GetPlayerController(this, 0);
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

				if (questComp)
				{
					for (int i = 0; i < questComp->GetQuestLenght(); i++)
					{
						questComp->SetQuestCounter(i, LLsaveGame->questValues[i]);
					}
				}

				ALLPlayerController* LLPlayercont = Cast<ALLPlayerController>(playerControl);

				for (int i = 0; i < LLsaveGame->EnemyID.Num(); i++)
				{
					LLPlayercont->AddEnemyID(LLsaveGame->EnemyID[i]);
				}

				for (int i = 0; i < LLsaveGame->saveInteractableID.Num(); i++)
				{
					LLPlayercont->AddInteractableID(LLsaveGame->saveInteractableID[i]);
				}

				for (int i = 0; i < LLsaveGame->savePointOfInterestID.Num(); i++)
				{
					LLPlayercont->AddPointOfInterestID(LLsaveGame->savePointOfInterestID[i]);
				}

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

bool ULLSaveSubsystem::GetIDEnemy(const FString& saveName, const int32 index, const int32 id)
{
	const APlayerController* playerControl = UGameplayStatics::GetPlayerController(this, 0);
	USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(saveName, index);
	if (SaveGameObject)
	{
		ULLSave* LLsaveGame = Cast<ULLSave>(SaveGameObject);
		if (LLsaveGame && LLsaveGame->EnemyID.Contains(id))
		{
			return true;
		}
	}

	return false;
}

bool ULLSaveSubsystem::GetIDPointOfInterest(const FString& saveName, const int32 index, const int32 id)
{
	const APlayerController* playerControl = UGameplayStatics::GetPlayerController(this, 0);
	USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(saveName, index);
	if (SaveGameObject)
	{
		ULLSave* LLsaveGame = Cast<ULLSave>(SaveGameObject);
		if (LLsaveGame && LLsaveGame->savePointOfInterestID.Contains(id))
		{
			return true;
		}
	}

	return false;
}

bool ULLSaveSubsystem::GetIDInteractable(const FString& saveName, const int32 index, const int32 id)
{
	const APlayerController* playerControl = UGameplayStatics::GetPlayerController(this, 0);
	USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(saveName, index);
	if (SaveGameObject)
	{
		ULLSave* LLsaveGame = Cast<ULLSave>(SaveGameObject);
		if (LLsaveGame && LLsaveGame->saveInteractableID.Contains(id))
		{
			return true;
		}
	}

	return false;
}
