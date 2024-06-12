// Fill out your copyright notice in the Description page of Project Settings.


#include "SSaveGame.h"

#include "ActionRoguelike.h"
#include "GameFramework/PlayerState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SSaveGame)


FPlayerSaveData* USSaveGame::GetPlayerData(APlayerState* PlayerState)
{
	if (PlayerState == nullptr)
	{
		return nullptr;
	}

	
	if (PlayerState->GetWorld()->IsPlayInEditor())
	{
		UE_LOGFMT(LogGame, Log, "During PIE we cannot use PlayerID to retrieve Saved Player data. Using first entry in array if available.");

		if (SavedPlayers.IsValidIndex(0))
		{
			return &SavedPlayers[0];
		}

		// No saved player data available
		return nullptr;
	}

	FString PlayerID = PlayerState->GetUniqueId().ToString();

	return SavedPlayers.FindByPredicate([&](const FPlayerSaveData& Data) { return Data.PlayerID == PlayerID; });
}
