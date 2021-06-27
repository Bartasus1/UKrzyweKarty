// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "KKGameState.generated.h"

class AKKPlayer;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWinnerFound);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCreateMap);


/**
 * 
 */
UCLASS()
class UKRZYWEKARTY_API AKKGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AKKGameState();

	UPROPERTY(ReplicatedUsing = OnRep_Winner, Transient, BlueprintReadOnly)
		AKKPlayer* Winner;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
		TSubclassOf<class ATileMap> TileMapClass;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Tile")
		class ATileMap* TileMap;

	//UPROPERTY(Replicated)
	//	bool EndOfGame = false;

	UFUNCTION()
		void OnRep_Winner();

	UPROPERTY(BlueprintAssignable)
		FWinnerFound WinnerFound;

	UPROPERTY(BlueprintAssignable)
		FCreateMap CreateMap;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;

};
