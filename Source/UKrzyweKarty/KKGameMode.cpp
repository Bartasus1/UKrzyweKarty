// Fill out your copyright notice in the Description page of Project Settings.


#include "KKGameMode.h"
#include "Engine\Engine.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerStart.h"
#include "KKPlayerController.h"
#include "KKPlayerState.h"
#include "KKPlayer.h"

AKKGameMode::AKKGameMode()
{
	
}

void AKKGameMode::ChangeInput()
{	
	bIsPlayerOneTurn = !bIsPlayerOneTurn;
	bIsPlayerTwoTurn = !bIsPlayerTwoTurn;

	if (Players.IsValidIndex(0))
		if (AKKPlayer* PlayerOne = Cast<AKKPlayer>(Players[0]->PlayerState->GetPawn()))
		{
			PlayerOne->bIsMyTurn = bIsPlayerOneTurn;
			PlayerOne->OnRep_IsMyTurn();
		}

	if (Players.IsValidIndex(1))
		if (AKKPlayer* PlayerTwo = Cast<AKKPlayer>(Players[1]->PlayerState->GetPawn()))
		{
			PlayerTwo->bIsMyTurn = bIsPlayerTwoTurn;
			PlayerTwo->OnRep_IsMyTurn();
		}
	//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Black, "Done");
}


AActor * AKKGameMode::ChoosePlayerStart_Implementation(AController * Player)
{
	if (AKKPlayerController* KKController = Cast<AKKPlayerController>(Player))
	{	
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
		for (auto & StartPoint : FoundActors)
		{
			if (APlayerStart* Start = Cast<APlayerStart>(StartPoint))
			{
				if ((Start->PlayerStartTag).ToString() == FString::FromInt(KKController->GetPlayerID()))
				{
					return Start;
				}
			}
		}
	}

	return nullptr;
}

APlayerController * AKKGameMode::Login(UPlayer * NewPlayer, ENetRole InRemoteRole, const FString & Portal, const FString & Options, const FUniqueNetIdRepl & UniqueId, FString & ErrorMessage)
{
	ErrorMessage = GameSession->ApproveLogin(Options);
	if (!ErrorMessage.IsEmpty())
	{
		return nullptr;
	}

	APlayerController* const NewPlayerController = SpawnPlayerController(InRemoteRole, Options);
	if (NewPlayerController == nullptr)
	{
		// Handle spawn failure.
		UE_LOG(LogGameMode, Log, TEXT("Login: Couldn't spawn player controller of class %s"), PlayerControllerClass ? *PlayerControllerClass->GetName() : TEXT("NULL"));
		ErrorMessage = FString::Printf(TEXT("Failed to spawn player controller"));
		return nullptr;
	}

	if (AKKPlayerController* Player = Cast<AKKPlayerController>(NewPlayerController))
	{
		Players.Add(Player);
		Player->SetPlayerID(Players.Num());
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::FromInt(Player->GetPlayerID()));
	}


	// Customize incoming player based on URL options
	ErrorMessage = InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
	if (!ErrorMessage.IsEmpty())
	{
		NewPlayerController->Destroy();
		return nullptr;
	}

	return NewPlayerController;
}

