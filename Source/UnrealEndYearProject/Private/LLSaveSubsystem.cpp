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
	//const APlayerController* playerControl = UGameplayStatics::GetPlayerController(this, 0);

	if (pawn && SaveGameObject)
	{
		const ULLAttributes* attributesComp = pawn->FindComponentByClass<ULLAttributes>();
		//const UQuestComponent* questComp = playerControl->FindComponentByClass<UQuestComponent>();

		ULLSave* LLsaveGame = Cast<ULLSave>(SaveGameObject);

		if (LLsaveGame)
		{
			if (attributesComp)
				LLsaveGame->HP = attributesComp->GetCurrentHealth();
			
			LLsaveGame->playerTransform = pawn->GetActorTransform();						
		}

		//if(questComp && LLsaveGame)
		//{
		//	questComp->quest.GetKeys(LLsaveGame->keys);
		//
		//	for (int i = 0; i < questComp->quest.Num(); i++)
		//	{
		//		const FQuestParam* savePar = questComp->quest.Find(LLsaveGame->keys[i]);
		//		LLsaveGame->questValues.Insert(savePar->questCounter, i);
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
	const APlayerController* playerControl = UGameplayStatics::GetPlayerController(this, 0);
	USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(saveName, index);
	APawn* pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	
	if (pawn && SaveGameObject) 
	{
		//UQuestComponent* questComp = playerControl->FindComponentByClass<UQuestComponent>();

		ULLAttributes* attributesComp = pawn->FindComponentByClass<ULLAttributes>();
		ULLSave* LLsaveGame = Cast<ULLSave>(SaveGameObject);

		//if (questComp && LLsaveGame)
		//{
		//	for (int i = 0; i < questComp->quest.Num(); i++)
		//	{
		//		questComp->SetCounter(LLsaveGame->keys[i], LLsaveGame->questValues[i]);
		//	}			
		//}
		
		if (LLsaveGame) 
		{
			if (attributesComp)
				attributesComp->SetHealth(LLsaveGame->HP);
			
			pawn->SetActorTransform(LLsaveGame->playerTransform);
			
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("LOAD SUCCEDED!"));
		}
	}
	
	else
		if (GEngine) 
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("LOAD FAILED!"));
}
