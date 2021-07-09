// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Zakon.h"
#include "Zakon_Rycerz.generated.h"

/**
 * 
 */
UCLASS()
class UKRZYWEKARTY_API AZakon_Rycerz : public AZakon
{
	GENERATED_BODY()
	
public:
	AZakon_Rycerz();

	virtual void ActiveAbility(UGameObject* GameObject) override; //Regeneracja
	virtual void PassiveAbility(UGameObject* GameObject) override; //Fechtunek
};
