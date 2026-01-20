// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"


//GameMode只存在于服务器上 
void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	int32 NumberOfPlayer = GameState.Get()->PlayerArray.Num();//Get() return AGameStateBase 指针
	if (NumberOfPlayer == 2)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			bUseSeamlessTravel = true;  
			World->ServerTravel(FString("/Game/Maps/GameBeginMap?listen"));
		}
	}
}
