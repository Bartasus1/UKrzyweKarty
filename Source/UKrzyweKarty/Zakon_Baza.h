// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Zakon.h"
#include "Zakon_Baza.generated.h"

/**
 * 
 */
UCLASS()
class UKRZYWEKARTY_API AZakon_Baza : public AZakon
{
	GENERATED_BODY()

public:
	AZakon_Baza();

	virtual void BeginPlay() override;
	
};
