// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Zakon.h"
#include "Zakon_Lucznik.generated.h"


class UGameObjects;
/**
 * 
 */
UCLASS()
class UKRZYWEKARTY_API AZakon_Lucznik : public AZakon
{
	GENERATED_BODY()
public:
	AZakon_Lucznik();

	virtual bool Attack(UGameObject *GO, bool bIsInLine) override;

	virtual void ActiveAbility(UGameObject* GO) override; //Tr�jstrza�
	virtual void PassiveAbility(UGameObject* GO) override; //Strza�y Rozrywaj�ce

protected:
	//UPROPERTY(EditAnywhere)
	//	TSubclassOf<AArrow> Arrow;
	
	int32 CountAttacks = 0;
};
