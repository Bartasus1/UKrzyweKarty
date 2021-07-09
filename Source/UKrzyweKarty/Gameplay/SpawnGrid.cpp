// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGrid.h"
#include "KKCharacter.h"
#include "KKGameState.h"
#include "TileMap.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASpawnGrid::ASpawnGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	CardNumber = SpawnCards.Num();
}

void ASpawnGrid::MakeCardsSpawn(int32 OwnerID) // Called on the server
{
	ID = OwnerID;
	CardNumber = SpawnCards.Num();
	const float X = GetActorLocation().X;
	const float Y = GetActorLocation().Y;
	
	for (int32 i = 0; i <  CardNumber - 1; i++)
	{
		const int32 Spacing = (ID == 1) ? 80 : -80;
		SpawnActors.AddUnique(GetWorld()->SpawnActor<AKKCharacter>(SpawnCards[i], FVector(X + i * Spacing, Y, 1.f), GetActorRotation()));
	}

	SpawnBase();
}

void ASpawnGrid::SpawnBase()
{
	if (HasAuthority())
    {
		const int32 Location = (ID == 1) ? 282 : -282;
		AKKCharacter* Base = GetWorld()->SpawnActor<AKKCharacter>(SpawnCards[CardNumber - 1], FVector(0, Location, 1.f), GetActorRotation() + FRotator(0, 90, 0) );
		SpawnActors.AddUnique(Base);
		
	
		if (AKKGameState* GS = Cast<AKKGameState>(GetWorld()->GetGameState()))
		{
			if (ID == 1)
			{
				if (GS->TileMap->Tiles.IsValidIndex(20))
				{
					Base->OwnedTile = GS->TileMap->Tiles[20];
					GS->TileMap->Tiles[20]->SetOwningCharacter(SpawnActors[SpawnActors.Num() - 1]);
				}
			}
			else if (ID == 2)
			{
				if (GS->TileMap->Tiles.IsValidIndex(21))
				{
					Base->OwnedTile = GS->TileMap->Tiles[21];
					GS->TileMap->Tiles[21]->SetOwningCharacter(SpawnActors[SpawnActors.Num() - 1]);
				}
			}
		}

		for (int32 i = 0; i <  CardNumber; i++)
		{
			SpawnActors[i]->Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
			SpawnActors[i]->SetActorScale3D(FVector(0.55));
		}
		
	}
}

// Called when the game starts or when spawned
void ASpawnGrid::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ASpawnGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void ASpawnGrid::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
//{
//	Super::PostEditChangeProperty(PropertyChangedEvent);
//
//	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(ASpawnGrid, SpawnCards))
//	{
//		if (SpawnCards.Num() > CardNumber)
//		{
//			SpawnCards.SetNum(CardNumber);
//		}
//	}
//}

void ASpawnGrid::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASpawnGrid, SpawnActors);
}
