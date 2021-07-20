// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include "KKGameState.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}


int ASpawnPoint::GetPlayerID() const
{
	return PlayerID;
}

ASpawnGrid * ASpawnPoint::GetSpawnGrid() const
{
	return SpawnGrid;
}

void ASpawnPoint::MakeSpawnGrid()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, "Spawnpoint" + FString::FromInt(PlayerID));
		
		SpawnGrid = GetWorld()->SpawnActor<ASpawnGrid>(SpawnGridClass, GetActorLocation(), GetActorRotation());
		SpawnGrid->MakeCardsSpawn(PlayerID);

		CardsSpawned.Broadcast();
	}
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, "Spawnpoint" + FString::FromInt(PlayerID));
	
		GetWorld()->GetGameState<AKKGameState>()->CreatedMap.AddDynamic(this, &ASpawnPoint::MakeSpawnGrid);
	}
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
