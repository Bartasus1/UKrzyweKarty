// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnGrid.h"
#include "Net/UnrealNetwork.h"
#include "SpawnPoint.generated.h"

UCLASS()
class UKRZYWEKARTY_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

	int GetPlayerID();
	ASpawnGrid* GetSpawnGrid();

	UFUNCTION()
	void MakeSpawnGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PlayerID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ASpawnGrid> SpawnGridClass;
	UPROPERTY(Replicated, BlueprintReadWrite)
		ASpawnGrid* SpawnGrid;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



};
