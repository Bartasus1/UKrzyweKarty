// Fill out your copyright notice in the Description page of Project Settings.


#include "Zakon_Halabardzista.h"
#include "GameObject.h"

AZakon_Halabardzista::AZakon_Halabardzista()
{
	this->Strength = 8;
	this->MaxStrength = Strength;
	this->Defense = 6;
	this->MaxDefense = Defense;
	this->Health = 18;
	this->MaxHealth = Health;
	this->Mana = 4;
	this->MaxMana = Mana;
	this->name = "Pikinier";
}

void AZakon_Halabardzista::ActiveAbility(UGameObject* GO)
{
	if (bIsAllowedToUseAbility)
	{
		if (GO->TargetCharacter != nullptr)
		{
			if (Mana >= 2)
			{
				//TODO
				// Implement this bad boy

				AttackDistance = 1;
				Mana -= 2;
			}
		}
	}
}

void AZakon_Halabardzista::PassiveAbility(UGameObject* GO)
{

}
