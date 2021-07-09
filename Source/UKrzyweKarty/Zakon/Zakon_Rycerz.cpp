// Fill out your copyright notice in the Description page of Project Settings.


#include "Zakon_Rycerz.h"
#include "../Gameplay/GameObject.h"

AZakon_Rycerz::AZakon_Rycerz()
{
	this->Strength = 5;
	this->MaxStrength = Strength;
	this->Defense = 7;
	this->MaxDefense = Defense;
	this->Health = 20;
	this->MaxHealth = Health;
	this->Mana = 6;
	this->MaxMana = Mana;
	this->Name = "Rycerz";
}

void AZakon_Rycerz::ActiveAbility(UGameObject* GameObject)
{
	if (Mana >= 2 && Health < MaxHealth)
	{
		Health += 4;
		Mana -= 2;

		if (Health >= MaxHealth)
			Health = MaxHealth;
	}
}


void AZakon_Rycerz::PassiveAbility(UGameObject* GameObject)
{
	if (GameObject->TargetCharacter == this)
	{
		if (CountAttacks == 2) // blocking
		{
			GameObject->CurrentCharacter->bIsAllowedToAttack = false;
			CountAttacks = 0;

		}
		else //setting back to normal		
		{
			GameObject->CurrentCharacter->bIsAllowedToAttack = true;
		}
	}
}
