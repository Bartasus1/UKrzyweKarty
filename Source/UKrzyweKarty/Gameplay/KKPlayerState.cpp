// Fill out your copyright notice in the Description page of Project Settings.


#include "KKPlayerState.h"
#include "KKPlayer.h"
#include "KKPlayerController.h"
#include "GameFramework\Pawn.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

AKKPlayerState::AKKPlayerState()
{
	bReplicates = true;
}

