// Fill out your copyright notice in the Description page of Project Settings.


#include "Zakon_Baza.h"
#include "../Gameplay/KKGameState.h"
#include "../Gameplay/TileMap.h"

AZakon_Baza::AZakon_Baza()
{
	Health = 50;

	bIsPlacedOnTheMap = true;
	bIsAbleToMove = false;
	bIsAllowedToAttack = false;

	Name = "Baza Zakonu";
}

