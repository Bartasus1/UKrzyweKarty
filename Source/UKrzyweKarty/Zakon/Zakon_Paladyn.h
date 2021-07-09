// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Zakon.h"
#include "Zakon_Paladyn.generated.h"

/**
 * 
 */
UCLASS()
class UKRZYWEKARTY_API AZakon_Paladyn : public AZakon
{
	GENERATED_BODY()
public:
	AZakon_Paladyn();

	virtual void ActiveAbility(UGameObject* GameObject) override; //Boska Moc
	virtual void ActiveAbility2(UGameObject* GameObject) override; //Z drogi!
	virtual void PassiveAbility(UGameObject* GameObject) override; //Ochrona
	virtual void PassiveAbility2(UGameObject* GameObject) override; //Œwieta Tarcza
};
