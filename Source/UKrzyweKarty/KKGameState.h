// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "KKGameState.generated.h"

/**
 * 
 */
UCLASS()
class UKRZYWEKARTY_API AKKGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AKKGameState();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
		TSubclassOf<class ATileMap> TileMapClass;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Tile")
		class ATileMap* TileMap;


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;

};
