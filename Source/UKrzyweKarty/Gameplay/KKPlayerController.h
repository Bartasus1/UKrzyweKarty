// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KKPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UKRZYWEKARTY_API AKKPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AKKPlayerController();

	void SetPlayerID(int32 ID);
	int32 GetPlayerID();

protected:

	UPROPERTY(Replicated, BlueprintReadWrite)
	int32 PlayerID = 0;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;


};
