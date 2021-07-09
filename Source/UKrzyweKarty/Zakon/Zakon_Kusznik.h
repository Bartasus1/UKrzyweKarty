// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Zakon.h"
#include "Zakon_Kusznik.generated.h"

/**
 * 
 */
UCLASS()
class UKRZYWEKARTY_API AZakon_Kusznik : public AZakon
{
	GENERATED_BODY()
public:
	AZakon_Kusznik();

	virtual void ActiveAbility(UGameObject* GameObject) override; //Przycelowanie
	virtual void ActiveAbility2(UGameObject* GameObject) override; //Wyczerpanie
	virtual void PassiveAbility(UGameObject* GameObject) override; //Wrzaca Krew
};
