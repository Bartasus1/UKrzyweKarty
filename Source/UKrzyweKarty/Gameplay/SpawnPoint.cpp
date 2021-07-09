// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"

#include "KKGameState.h"


// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	if(GetWorld())
	{
		GetWorld()->GetGameState<AKKGameState>()->CreatedMap.AddDynamic(this, &ASpawnPoint::MakeSpawnGrid);
	}
    
}


int ASpawnPoint::GetPlayerID()
{
	return PlayerID;
}

ASpawnGrid * ASpawnPoint::GetSpawnGrid()
{
	return SpawnGrid;
}

void ASpawnPoint::MakeSpawnGrid()
{
	if (HasAuthority())
	{
		SpawnGrid = GetWorld()->SpawnActor<ASpawnGrid>(SpawnGridClass, GetActorLocation(), GetActorRotation());
		SpawnGrid->MakeCardsSpawn(PlayerID);
	}
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnPoint::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASpawnPoint, SpawnGrid);
}
