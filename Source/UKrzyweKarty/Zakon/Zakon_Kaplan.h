// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Zakon.h"
#include "Zakon_Kaplan.generated.h"

/**
 * 
 */
UCLASS()
class UKRZYWEKARTY_API AZakon_Kaplan : public AZakon
{
	GENERATED_BODY()
public:
	AZakon_Kaplan();

	virtual void ActiveAbility(UGameObject* GO) override; //Modlitwa
	virtual void ActiveAbility2(UGameObject* GO) override; //Wola Boga
	virtual void PassiveAbility(UGameObject* GO) override; //Moc Duchowa

};
