// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGrid.h"
#include "KKCharacter.h"
#include "KKGameState.h"
#include "TileMap.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASpawnGrid::ASpawnGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);
}

void ASpawnGrid::MakeCardsSpawn(int32 OwnerID) // Called on the server
{
	float X = GetActorLocation().X;
	float Y = GetActorLocation().Y;

	for (uint8 i = 0; i < CardNumber; i++)
	{
		if (i < CardNumber - 1)
		{
			int32 Spacing = (OwnerID == 1) ? 80 : -80;
			SpawnActors.AddUnique(GetWorld()->SpawnActor<AKKCharacter>(SpawnCards[i], FVector(X + i * Spacing, Y, 1.f), GetActorRotation()));
		}
		else
		{
			int32 Location = (OwnerID == 1) ? 282 : -282;
			AKKCharacter* Base = GetWorld()->SpawnActor<AKKCharacter>(SpawnCards[i], FVector(0, Location, 1.f), GetActorRotation() + FRotator(0, 90, 0) );
			SpawnActors.AddUnique(Base);
			
			auto SetBase = [this, OwnerID, Base]()
			{
				if (HasAuthority())
				{
					if (AKKGameState* GS = Cast<AKKGameState>(GetWorld()->GetGameState()))
					{
						if (OwnerID == 1)
						{
							if (GS->TileMap->Tiles.IsValidIndex(20))
							{
								Base->OwnedTile = GS->TileMap->Tiles[20];
								GS->TileMap->Tiles[20]->SetOwningCharacter(SpawnActors[SpawnActors.Num() - 1]);
							}
						}
						else if (OwnerID == 2)
						{
							if (GS->TileMap->Tiles.IsValidIndex(21))
							{
								Base->OwnedTile = GS->TileMap->Tiles[21];
								GS->TileMap->Tiles[21]->SetOwningCharacter(SpawnActors[SpawnActors.Num() - 1]);
							}
						}
					}
				}
			};
			FTimerHandle Handle;
			GetWorldTimerManager().SetTimer(Handle, SetBase, 1.f, false);
		}
		
		SpawnActors[i]->SetActorScale3D(FVector(0.55));
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
