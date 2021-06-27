// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "Tile.h"
#include "TileMap.generated.h"


UCLASS()
class UKRZYWEKARTY_API ATileMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileMap();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tiles")
		TSubclassOf<ATile> TileClass;

	UPROPERTY(Replicated, BlueprintReadWrite)
		TArray<ATile*> Tiles;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
