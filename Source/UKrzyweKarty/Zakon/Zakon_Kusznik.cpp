// Fill out your copyright notice in the Description page of Project Settings.


#include "Zakon_Kusznik.h"

AZakon_Kusznik::AZakon_Kusznik()
{
	this->Strength = 15;
	this->MaxStrength = Strength;
	this->Defense = 4;
	this->MaxDefense = Defense;
	this->Health = 22;
	this->MaxHealth = Health;
	this->Mana = 4;
	this->MaxMana = Mana;
	this->bIsRanged = true;
	this->AttackDistance = 3;
	this->Name = "Kusznik";
}

void AZakon_Kusznik::ActiveAbility(UGameObject* GameObject)
{
}

void AZakon_Kusznik::ActiveAbility2(UGameObject * GameObject)
{
}

void AZakon_Kusznik::PassiveAbility(UGameObject* GameObject)
{
}
