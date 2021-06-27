// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KKGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UKRZYWEKARTY_API UKKGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void StartSession();
	
};
