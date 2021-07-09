// Fill out your copyright notice in the Description page of Project Settings.


#include "Zakon_Paladyn.h"
#include "../Gameplay/GameObject.h"

AZakon_Paladyn::AZakon_Paladyn()
{
	this->Strength = 20;
	this->MaxStrength = Strength;
	this->Defense = 10;
	this->MaxDefense = Defense;
	this->Health = 50;
	this->MaxHealth = Health;
	this->Mana = 10;
	this->MaxMana = Mana;
	this->Name = "Paladyn";
}

void AZakon_Paladyn::ActiveAbility(UGameObject* GameObject)
{
	
	auto StrengthOrHeal =  [this, GameObject] () 
	{
		if (GameObject->TargetCharacter != nullptr)
		{
			AZakon* Ally = Cast<AZakon>(GameObject->TargetCharacter);

			if (Ally)
			{
				Ally->Health += 4;

				if (Ally->Health >= Ally->MaxHealth)
					Ally->Health = Ally->MaxHealth;
			}
			else
			{
				this->Strength = 10;
				Attack(GameObject, false);
			}
		}
	};


}

void AZakon_Paladyn::ActiveAbility2(UGameObject * GameObject)
{
}

void AZakon_Paladyn::PassiveAbility(UGameObject* GameObject)
{

	if (Health < 15)
	{
		GameObject->TargetCharacter->bIsAllowedToUseAbility = false;
	}
	else
	{
		GameObject->TargetCharacter->bIsAllowedToUseAbility = true;
	}

}

void AZakon_Paladyn::PassiveAbility2(UGameObject * GameObject)
{
}
