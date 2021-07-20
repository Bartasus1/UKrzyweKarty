// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KKCharacter.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "SpawnGrid.generated.h"

UCLASS(ABSTRACT)
class UKRZYWEKARTY_API ASpawnGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnGrid();

protected:

	

	
	UPROPERTY(VisibleAnywhere)
	int32 CardNumber;

	UPROPERTY(VisibleAnywhere)
	int32 ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards")
	TArray <TSubclassOf<AKKCharacter>> SpawnCards;

public:

	
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Cards")
	TArray <AKKCharacter*> SpawnActors;

	void MakeCardsSpawn(int32 OwnerID);

	UFUNCTION()
		void SpawnBase();



	//virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
