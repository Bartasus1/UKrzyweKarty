// Fill out your copyright notice in the Description page of Project Settings.


#include "Zakon_Lucznik.h"
#include "../Gameplay/GameObject.h"


AZakon_Lucznik::AZakon_Lucznik()
{
	this->Strength = 7;
	this->MaxStrength = Strength;
	this->Defense = 4;
	this->MaxDefense = Defense;
	this->Health = 14;
	this->MaxHealth = Health;
	this->Mana = 4;
	this->MaxMana = Mana;
	this->bIsRanged = true;
	this->AttackDistance = 3;
	this->Name = "Lucznik";
}




bool AZakon_Lucznik::Attack(UGameObject *GameObject, bool bIsInLine)
{
	//GameObject.TargetCharacter = FirstTarget(GameObject.TargetCharacter, GameObject.Position);
	return AKKCharacter::Attack(GameObject);

	//float alpha = AKKCharacter::LookRotationBasedOnLocation(this, GameObject.TargetCharacter);
	//FRotator rotation = FRotator(0, alpha , 0);

	//GetWorld()->SpawnActor<AArrow>(Arrow, GetActorLocation() + FVector(0,0, 50), rotation);
}


void AZakon_Lucznik::ActiveAbility(UGameObject* GameObject)
{

	if (bIsAllowedToUseAbility)
	{
		if (Mana >= 2)
		{
			Mana -= 2;
		}
	}
}

void AZakon_Lucznik::PassiveAbility(UGameObject* GameObject)
{
	if (bIsAllowedToUseAbility)
	{
		if (GameObject->TargetCharacter != nullptr)
		{
			if (bAttacked)
			{
				CountAttacks++;
				bAttacked = false;
			}

			if (CountAttacks == 2)
			{
				if (GameObject->TargetCharacter->Defense > 1)
				{
					GameObject->TargetCharacter->Defense -= 1;
				}

				CountAttacks = 0;
			}
		}
	}
}
