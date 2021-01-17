// Fill out your copyright notice in the Description page of Project Settings.


#include "KKCharacter.h"
#include "TileMap.h"
#include "Tile.h"
#include "GameObject.h"

// Sets default values
AKKCharacter::AKKCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Pedestal = CreateDefaultSubobject<UStaticMeshComponent>("Pedestal");
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	TextName = CreateDefaultSubobject<UTextRenderComponent>("Name");

	SetRootComponent(Pedestal);
	Mesh->SetupAttachment(Pedestal);
	TextName->SetupAttachment(Mesh);

	SetReplicates(true);
	SetReplicateMovement(true);

}

//float AKKCharacter::LookRotationBasedOnLocation(AKKCharacter* One, AKKCharacter* Two)
//{
//	//FVector one = One->GetActorLocation();
//	//FVector two = Two->GetActorLocation();
//	//
//	//float distance = FVector::Distance(one, two);
//	//float dir = (one.X - two.X);
//	//float x = dir / distance;
//	//float alpha = (FMath::Asin(x) * 180) / 3.14;
//	//alpha = (one.Y <= two.Y) ? alpha : -180;
//	//
//	//return alpha;
//}

bool AKKCharacter::CanCharacterMove()
{

	if (bIsPlacedOnTheMap && bIsAbleToMove && !bIsDead)
		return true;
	else
		return false;

}

int32 AKKCharacter::Distance(AKKCharacter * Target)
{
	ATile* MyTile = OwnedTile;
	ATile* TargetTile = Target->OwnedTile;

	int32 MyX = MyTile->GetTileID() % 4;
	int32 MyY = MyTile->GetTileID() / 4;

	int32 TargetX = TargetTile->GetTileID() % 4;
	int32 TargetY = TargetTile->GetTileID() / 4;

	int32 Distance = FMath::Sqrt(( FMath::Pow(MyX - TargetX, 2) + FMath::Pow(MyY - TargetY, 2) ));

	return Distance;
}

void AKKCharacter::KillCharacter(UGameObject * GO)
{
	Health = 0;
	bIsDead = true;

	GO->TileMap->Tiles[OwnedTile->GetTileID()]->SetOwningCharacter(nullptr);
	GO->TargetCharacter = nullptr;

	Destroy();
}

void AKKCharacter::CalculateDamage(UGameObject *GO)
{
	if (bIsAllowedToAttack)// we need to make sure, that its not parried
	{
		//attacker
		bAttacked = true; // e.g Lucznik -> StrzalyRozrywajace

		//victim
		GO->TargetCharacter->CountAttacks++; // e.g Rycerz->Fechtunek

		////////////   Calculating damage   /////////////

		if (GO->TargetCharacter->Defense > 0)
		{
			GO->TargetCharacter->Defense--;

			if (Strength > GO->TargetCharacter->Defense)
			{
				GO->TargetCharacter->Health -= (Strength - GO->TargetCharacter->Defense);
			}
		}
		else
		{
			GO->TargetCharacter->Defense = 0;
			GO->TargetCharacter->Health -= Strength;
		}

		if (GO->TargetCharacter->Health <= 0)
		{
			GO->TargetCharacter->KillCharacter(GO);
		}
	}
	else
	{
		bAttacked = false;
	}
}

bool AKKCharacter::Attack(UGameObject *GO, bool bIsInLine)
{
	if (GO->TargetCharacter != nullptr && GO->TargetCharacter != this)
	{
		if ( GO->TargetCharacter->Health > 0 && Distance(GO->TargetCharacter) <= AttackDistance)
		{
			if (bIsInLine)
			{
				int32 TileID = GO->CurrentCharacter->OwnedTile->GetTileID();
				int32 TargetTileID = GO->TargetCharacter->OwnedTile->GetTileID();
				
				if (TileID % 4 == TargetTileID % 4 || TileID / 4 == TargetTileID / 4) // X || Y
				{
					CalculateDamage(GO);
				}
			}
			else // Cards don't have to be in line
			{
				CalculateDamage(GO);
			}

			Strength = MaxStrength;
			return true;
		}
		else
		{
			Strength = MaxStrength;
		}
	}

	return false;
}

void AKKCharacter::SetCharacterName_Implementation()
{
	TextName->SetText(FText::FromString(name));
	TextName->SetTextRenderColor(FColor::Red);
	TextName->SetRelativeLocationAndRotation(FVector(42, 18, 170), FRotator(0, -90, 0));
}


void AKKCharacter::ActiveAbility(UGameObject* GO)
{
}

void AKKCharacter::ActiveAbility2(UGameObject* GO)
{
}


void AKKCharacter::PassiveAbility(UGameObject* GO)
{
}

void AKKCharacter::PassiveAbility2(UGameObject* GO)
{
}


void AKKCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AKKCharacter, name);

	DOREPLIFETIME(AKKCharacter, Strength);
	DOREPLIFETIME(AKKCharacter, Defense);
	DOREPLIFETIME(AKKCharacter, Health);
	DOREPLIFETIME(AKKCharacter, Mana);

	DOREPLIFETIME(AKKCharacter, CountAttacks);

	DOREPLIFETIME(AKKCharacter, bAttacked);
	DOREPLIFETIME(AKKCharacter, bIsDead);
	DOREPLIFETIME(AKKCharacter, bIsPlacedOnTheMap);
}


// Called when the game starts or when spawned
void AKKCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetCharacterName();
}

/*
AKKCharacter * AKKCharacter::FirstTarget(AKKCharacter * target, AKKCharacter * positioning[4][5])
{
	
}
*/