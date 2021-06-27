// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "KKCharacter.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	SetReplicateMovement(true);

	//NumberText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Number"));
	//SetRootComponent(NumberText);
}

int32 ATile::GetTileID()
{
	return TileID;
}

AKKCharacter * ATile::GetOwningCharacter()
{
	if (OwningCharacter)
	{
		return OwningCharacter;
	}
	return nullptr;
}

void ATile::SetOwningCharacter(AKKCharacter * Character)
{
	OwningCharacter = Character;
}

void ATile::SetTileID(int32 ID)
{
	TileID = ID;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATile, TileID);
	DOREPLIFETIME(ATile, OwningCharacter);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

