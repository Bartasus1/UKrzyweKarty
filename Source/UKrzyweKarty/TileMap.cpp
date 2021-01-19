// Fill out your copyright notice in the Description page of Project Settings.


#include "TileMap.h"
#include "Engine\World.h"

// Sets default values
ATileMap::ATileMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Tiles.Init(nullptr, 20);
	SetReplicates(true);
}


// Called when the game starts or when spawned
void ATileMap::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		for (int32 i = 0; i < 20; i++)
		{
			int PositionX = -129.5 + (i % 4) * 86.f;
			int PositionY = -203 + (i / 4) * 101.f;

			Tiles[i] = GetWorld()->SpawnActor<ATile>(TileClass, FVector(PositionX, PositionY, /* PositionZ */ 0.5), GetActorRotation());
			Tiles[i]->SetTileID(i);
		}

		ATile* BaseTile1 = GetWorld()->SpawnActor<ATile>(TileClass, FVector(0, 282, 0.5), GetActorRotation());
		ATile* BaseTile2 = GetWorld()->SpawnActor<ATile>(TileClass, FVector(0, -282, 0.5), GetActorRotation());
		BaseTile1->SetTileID(18);
		BaseTile2->SetTileID(2);
		Tiles.Push(BaseTile1);
		Tiles.Push(BaseTile2);
	}

}

void ATileMap::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATileMap, Tiles);
}

// Called every frame
void ATileMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

