// Fill out your copyright notice in the Description page of Project Settings.


#include "Zakon_Grid.h"

// Sets default values
AZakon_Grid::AZakon_Grid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	for (int8 i = 0; i < 7; i++)
	{
		start_position[i] = (FVector( -(420/14) + i * 80, 650.f, 1.f));
	}
	SpawnCards.Init(nullptr,7);
}

// Called when the game starts or when spawned
void AZakon_Grid::BeginPlay()
{
	Super::BeginPlay();
	
	for(uint8 i = 0; i < 7; i++)
	{
		SpawnActors.AddUnique(GetWorld()->SpawnActor<AZakon>(SpawnCards[i], start_position[i], start_rotation));
		
		SpawnActors[i]->SetActorScale3D(FVector(0.5, 0.5, 0.5));
		SpawnActors[i]->TextName->SetTextRenderColor(FColor::Red);
		SpawnActors[i]->TextName->SetText(SpawnActors[i]->Name);
		SpawnActors[i]->SetReplicates(true);
		SpawnActors[i]->TextName->SetRelativeLocationAndRotation(FVector(42, 18, 170),FRotator(0,-90,0));
	}

	/*
	SpawnCards.push_back(Rycerz);
	SpawnCards.push_back(Halabardzista);
	SpawnCards.push_back(Kaplan);
	SpawnCards.push_back(Kawalerzysta);
	SpawnCards.push_back(Kusznik);
	SpawnCards.push_back(Lucznik);
	SpawnCards.push_back(Paladyn);
	for (auto &c : cards)
	{
		c->SetActorScale3D(FVector(0.55, 0.55, 0.55));
	}
	*/
}

// Called every frame
void AZakon_Grid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

