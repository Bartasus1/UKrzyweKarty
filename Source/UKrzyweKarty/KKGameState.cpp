// Fill out your copyright notice in the Description page of Project Settings.


#include "KKGameState.h"
#include "KKGameMode.h"
#include "KKPlayerState.h"
#include "KKPlayerController.h"
#include "Engine\World.h"
#include "Engine\Engine.h"
#include "TileMap.h"
#include "Net/UnrealNetwork.h"


AKKGameState::AKKGameState()
{
	SetReplicates(true);
}

void AKKGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AKKGameState, TileMap);

}

void AKKGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		TileMap = GetWorld()->SpawnActor<ATileMap>(TileMapClass, FVector::ZeroVector, FRotator::ZeroRotator);
	}
}

