// Fill out your copyright notice in the Description page of Project Settings.


#include "Zakon_Kaplan.h"
#include "../Gameplay/GameObject.h"

AZakon_Kaplan::AZakon_Kaplan()
{
	this->Strength = 12;
	this->MaxStrength = Strength;
	this->Defense = 10;
	this->MaxDefense = Defense;
	this->Health = 31;
	this->MaxHealth = Health;
	this->Mana = 15;
	this->MaxMana = Mana;
	this->Name = "Kaplan";
}

	

void AZakon_Kaplan::ActiveAbility(UGameObject* GameObject)
{
	if (bIsAllowedToUseAbility)
	{
		AZakon* Ally = Cast<AZakon>(GameObject->TargetCharacter);

		if (Ally)
		{
			if (Mana >= 5)
			{
				if (Ally->Health < Ally->MaxHealth - 3)
				{
					Ally->Health += 3;
				}
				if (Ally->Mana < Ally->MaxMana - 4)
				{
						Ally->Mana += 4;
				}

				Mana -= 5;
			}

		}
	}
}

void AZakon_Kaplan::ActiveAbility2(UGameObject* GameObject)
{
	if (bIsAllowedToUseAbility)
	{
		if (GameObject->TargetCharacter != nullptr)
		{
			if (Mana >= 5)
			{
				this->Strength = 17;
				this->AttackDistance = 5;
				Attack(GameObject, false);
				this->AttackDistance = 1;

				Mana -= 5;
			}
		}
	}
}

void AZakon_Kaplan::PassiveAbility(UGameObject* GameObject)
{
	if (bAttacked)
	{
		Mana += 3;
		bAttacked = false;
	}

	if (Mana >= MaxMana)
	{
		Mana = MaxMana;
	}

}
