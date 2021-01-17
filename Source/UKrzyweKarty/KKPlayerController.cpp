// Fill out your copyright notice in the Description page of Project Settings.


#include "KKPlayerController.h"
#include "KKPlayer.h"
#include "Engine/Engine.h"

AKKPlayerController::AKKPlayerController()
{
	bShowMouseCursor = true;
	SetReplicates(true);
	//bEnableClickEvents = true;
	//bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AKKPlayerController::SetPlayerID(int32 ID)
{
	PlayerID = ID;
}

int32 AKKPlayerController::GetPlayerID()
{
	return PlayerID;
}

void AKKPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AKKPlayerController, PlayerID);
}

void AKKPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
}
