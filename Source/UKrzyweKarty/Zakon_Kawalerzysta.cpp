// Fill out your copyright notice in the Description page of Project Settings.


#include "Zakon_Kawalerzysta.h"
#include "GameObject.h"
#include "Tile.h"

AZakon_Kawalerzysta::AZakon_Kawalerzysta()
{
	this->Strength = 16;
	this->MaxStrength = Strength;
	this->Defense = 7;
	this->MaxDefense = Defense;
	this->Health = 28;
	this->MaxHealth = Health;
	this->Mana = 6;
	this->MaxMana = Mana;
	this->Name = "Kawalerzysta";
}


void AZakon_Kawalerzysta::ActiveAbility(UGameObject* GO)
{
	if (bIsAllowedToUseAbility)
	{
		if (GO->TargetCharacter != nullptr && GO->TargetCharacter->bIsPlacedOnTheMap)
		{
			if (Mana >= 2)
			{
				//First we need to get the direction - CurrentCharacter is in the center
				int32 Direction = GO->CurrentCharacter->OwnedTile->GetTileID() - GO->TargetCharacter->OwnedTile->GetTileID();
				// Forward - Direction == 4
				// Backward - Direction == -4
				// Left - Direction == 1
				// Right - Direction == -1

				int32 TileID = GO->CurrentCharacter->OwnedTile->GetTileID();
				bool bIsOnTheLeftBorder = (TileID % 4 == 0);
				bool bIsOnTheRightBorder = (TileID % 4 == 3);
				bool bIsOnTheTopBorder = (TileID > 15);
				bool bIsOnTheBottomBorder = (TileID < 4);
				
				//Check to prevent Strengths from the other side of map e.g(TileID = 11, TargetTileID = 12)
				switch (Direction)
				{
				case 1:
					if (bIsOnTheLeftBorder)
					{
						Direction = 0;
					}
					break;
				case -1:
					if (bIsOnTheRightBorder)
					{
						Direction = 0;
					}
					break;
				case 4:
					if (bIsOnTheTopBorder)
					{
						Direction = 0;
					}
					break;
				case -4:
					if (bIsOnTheBottomBorder)
					{
						Direction = 0;
					}
					break;
				default:
					break;
				}

				int32 Destination = TileID + (Direction * 2);
			
				if (Direction != 0 && Destination >= 0 && Destination < 20 && GO->TileMap->Tiles[Destination] == nullptr)
				{
					this->Strength = 13;
					this->AttackDistance = 2;
					Attack(GO);
					GO->TileMap->Tiles[TileID]->SetOwningCharacter(nullptr);
					GO->CurrentCharacter->OwnedTile = GO->TileMap->Tiles[Destination];
					GO->TileMap->Tiles[Destination]->SetOwningCharacter(GO->CurrentCharacter);

					Mana -= 2;
				}
			}
		}
	}
}



void AZakon_Kawalerzysta::ActiveAbility2(UGameObject* GO)
{
	if (bIsAllowedToUseAbility)
	{
		int32 TileID = GO->CurrentCharacter->OwnedTile->GetTileID();
		if (TileID > 3)
		{
			if (Mana >= 3)
			{
				GO->TargetCharacter = GO->TileMap->Tiles[TileID - 4]->GetOwningCharacter();
				this->Strength = 21;
				Attack(GO);

				Mana -= 3;
			}
		}
	}
}

void AZakon_Kawalerzysta::PassiveAbility(UGameObject* GO)
{
}
