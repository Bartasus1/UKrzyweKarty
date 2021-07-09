// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Zakon.h"
#include "Zakon_Halabardzista.generated.h"

/**
 * 
 */
UCLASS()
class UKRZYWEKARTY_API AZakon_Halabardzista : public AZakon
{
	GENERATED_BODY()
	
public:
	AZakon_Halabardzista();

	virtual void ActiveAbility(UGameObject* GameObject) override; //Przedluzenie
	virtual void PassiveAbility(UGameObject* GameObject); //Pika
};
