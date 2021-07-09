// Fill out your copyright notice in the Description page of Project Settings.


#include "KKGameState.h"
#include "KKGameMode.h"
#include "KKPlayerState.h"
#include "KKPlayer.h"
#include "KKPlayerController.h"
#include "Engine\World.h"
#include "Engine\Engine.h"
#include "TileMap.h"
#include "Kismet/KismetSystemLibrary.h"



AKKGameState::AKKGameState()
{
	bReplicates = true;
}

void AKKGameState::OnRep_Winner()
{
	WinnerFound.Broadcast();
}

void AKKGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AKKGameState, TileMap);
	DOREPLIFETIME(AKKGameState, Winner);
	//DOREPLIFETIME(AKKGameState, EndOfGame);
}

void AKKGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		TileMap = GetWorld()->SpawnActor<ATileMap>(TileMapClass, FVector::ZeroVector, FRotator::ZeroRotator);
		CreatedMap.Broadcast();
	}
}

