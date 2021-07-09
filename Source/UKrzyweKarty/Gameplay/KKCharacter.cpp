// Fill out your copyright notice in the Description page of Project Settings.


#include "KKCharacter.h"
#include "KKGameMode.h"
#include "KKPlayer.h"
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

	bReplicates = true;
    SetReplicateMovement(true);
	SetActorScale3D(FVector(0.5));
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

	if (MyX == 1 || MyX == 2)
	{
		if (TargetTile->GetTileID() < 0)
		{
			return 0;
		}
	}

	int32 Distance = FMath::Sqrt(( FMath::Pow(MyX - TargetX, 2) + FMath::Pow(MyY - TargetY, 2) ));

	return Distance;
}

void AKKCharacter::KillCharacter(UGameObject * GameObject)
{
	Health = 0;
	bIsDead = true;

	if (Name.Contains("Baza")) // Change it to BaseInterface in the future
	{
		if (HasAuthority())
		{
			AKKGameMode* GM = Cast<AKKGameMode>(GetWorld()->GetAuthGameMode());
			GM->OnWin(Cast<AKKPlayer>(GameObject->GetOwner()));
		}
	}
	else
	{
		GameObject->TileMap->Tiles[OwnedTile->GetTileID()]->SetOwningCharacter(nullptr);
		GameObject->TargetCharacter = nullptr;
	}

	Destroy();
}

void AKKCharacter::CalculateDamage(UGameObject *GameObject)
{
	if (bIsAllowedToAttack)// we need to make sure, that its not parried
	{
		//attacker
		bAttacked = true; // e.g Lucznik -> StrzalyRozrywajace

		//victim
		GameObject->TargetCharacter->CountAttacks++; // e.g Rycerz->Fechtunek

		////////////   Calculating damage   /////////////

		if (GameObject->TargetCharacter->Defense > 0)
		{
			GameObject->TargetCharacter->Defense--;

			if (Strength > GameObject->TargetCharacter->Defense)
			{
				GameObject->TargetCharacter->Health -= (Strength - GameObject->TargetCharacter->Defense);
			}
		}
		else
		{
			GameObject->TargetCharacter->Defense = 0;
			GameObject->TargetCharacter->Health -= Strength;
		}

		if (GameObject->TargetCharacter->Health <= 0)
		{
			GameObject->TargetCharacter->KillCharacter(GameObject);
		}
	}
	else
	{
		bAttacked = false;
	}
}

bool AKKCharacter::Attack(UGameObject *GameObject, bool bIsInLine)
{
	if (GameObject->TargetCharacter != nullptr && GameObject->TargetCharacter != this)
	{
		if ( GameObject->TargetCharacter->Health > 0 && Distance(GameObject->TargetCharacter) <= AttackDistance)
		{
			if (Distance(GameObject->TargetCharacter) == 0)
			{
				bIsInLine = false;
			}

			if (bIsInLine)
			{
				int32 TileID = GameObject->CurrentCharacter->OwnedTile->GetTileID();
				int32 TargetTileID = GameObject->TargetCharacter->OwnedTile->GetTileID();
				
				if (TileID % 4 == TargetTileID % 4 || TileID / 4 == TargetTileID / 4) // X || Y
				{
					CalculateDamage(GameObject);
				}
			}
			else // Cards don't have to be in line
			{
				CalculateDamage(GameObject);
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
	TextName->SetText(FText::FromString(Name));
	TextName->SetTextRenderColor(FColor::Red);
	TextName->SetRelativeLocationAndRotation(FVector(42, 18, 170), FRotator(0, -90, 0));
}


void AKKCharacter::ActiveAbility(UGameObject* GameObject)
{
}

void AKKCharacter::ActiveAbility2(UGameObject* GameObject)
{
}


void AKKCharacter::PassiveAbility(UGameObject* GameObject)
{
}

void AKKCharacter::PassiveAbility2(UGameObject* GameObject)
{
}


void AKKCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AKKCharacter, Name);
	DOREPLIFETIME(AKKCharacter, OwnedTile);

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