// Fill out your copyright notice in the Description page of Project Settings.


#include "KKPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "KKPlayerController.h"
#include "GameObject.h"
#include "TileMap.h"
#include "Tile.h"
#include "KKGameState.h"
#include "KKGameMode.h"
#include "SpawnPoint.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"



// Sets default values
AKKPlayer::AKKPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bUseControllerRotationYaw = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SetRootComponent(SpringArm);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	PlayerCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	GameObject = CreateDefaultSubobject<UGameObject>("GameObjects");
	GameObject->SetIsReplicated(true);

	SpringArm->TargetArmLength = 700.f;
	SpringArm->SocketOffset = {0,0,200.f};
	PlayerCamera->SetRelativeRotation(FRotator(-10,0,0));


}


void AKKPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetIDFromController();
	
	if (!HasAuthority())
	{
		DisableInput(Cast<AKKPlayerController>(GetController()));
		ChangeInput();
	}

	if(HasAuthority())
	{
		GetWorld()->GetGameState<AKKGameState>()->CreatedMap.AddDynamic(this, &AKKPlayer::GetMapFromGameState);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(1));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(2));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(3));
		//TArray<AActor*> FoundActors;
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass(), FoundActors);
		//
		//for (auto &Point : FoundActors)
		//{
		//	if(ASpawnPoint* SpawnPoint = Cast<ASpawnPoint>(Point))
		//	{
		//		SpawnPoint->CardsSpawned.AddDynamic(this, &AKKPlayer::FindPlayerCards);
		//	}
		//
		//}
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Player" + FString::FromInt(PlayerID));
	}

}


void AKKPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayerCamera->SetFieldOfView(CameraZoom);

	//CheckTurn();
}

void AKKPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &AKKPlayer::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &AKKPlayer::ZoomOut);

	PlayerInputComponent->BindAction("SelectCurrentCharacter", IE_Pressed, this, &AKKPlayer::SelectCurrent);
	PlayerInputComponent->BindAction("SelectTargetCharacter", IE_Pressed, this, &AKKPlayer::SelectTarget);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AKKPlayer::MakeAttack);
	PlayerInputComponent->BindAction("ActiveAbility", IE_Pressed, this, &AKKPlayer::ActiveAbility);

	PlayerInputComponent->BindAction("MoveForward", IE_Pressed, this, &AKKPlayer::MoveForward);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &AKKPlayer::MoveRight);
	PlayerInputComponent->BindAction("MoveBackward", IE_Pressed, this, &AKKPlayer::MoveBackward);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &AKKPlayer::MoveLeft);

	PlayerInputComponent->BindAction("AddOnPosition0", IE_Pressed, this, &AKKPlayer::AddOnPosition0);
	PlayerInputComponent->BindAction("AddOnPosition1", IE_Pressed, this, &AKKPlayer::AddOnPosition1);
	PlayerInputComponent->BindAction("AddOnPosition2", IE_Pressed, this, &AKKPlayer::AddOnPosition2);
	PlayerInputComponent->BindAction("AddOnPosition3", IE_Pressed, this, &AKKPlayer::AddOnPosition3);
}

void AKKPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AKKPlayer, PlayerID);
	DOREPLIFETIME(AKKPlayer, bIsMyTurn);
}



void AKKPlayer::SelectCurrent()
{
	GameObject->CurrentCharacter = CastRayForCharacter(); //Client side selecting Character

	if (GameObject->CurrentCharacter && GameObject->CurrentCharacter->GetOwner() == this)
	{
		ServerSetCurrentCharacter(GameObject->CurrentCharacter); //Server side selecting Character

		if (CurrentCharacterWidget)
		{
			CurrentCharacterWidget->RemoveFromParent();
		}
		CurrentCharacterWidget = CreateWidget(GetWorld(), CurrentCharacterWidgetClass);
		CurrentCharacterWidget->AddToViewport();

		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, GameObject->CurrentCharacter->Name);
	}
	else
	{
		GameObject->CurrentCharacter = nullptr;
	}
}

void AKKPlayer::SelectTarget()
{
	GameObject->TargetCharacter = CastRayForCharacter();

	if (GameObject->TargetCharacter && GameObject->TargetCharacter->GetOwner() != this)
	{
		ServerSetTargetCharacter(GameObject->TargetCharacter);
		if (TargetCharacterWidget)
		{
			TargetCharacterWidget->RemoveFromParent();
		}
		TargetCharacterWidget = CreateWidget(GetWorld(), TargetCharacterWidgetClass);
		TargetCharacterWidget->AddToViewport();
	}
	else
	{
		GameObject->TargetCharacter = nullptr;
	}
}

void AKKPlayer::MakeAttack()
{
	if (GameObject->CurrentCharacter != nullptr && GameObject->TargetCharacter != nullptr)
	{
		MakeCharacterAttack();
		//float alpha = AKKCharacter::LookRotationBasedOnLocation(GameObject->CurrentCharacter, GameObject->TargetCharacter);
		//GameObject->CurrentCharacter->Mesh->SetRelativeRotation(FRotator(-alpha, 0, 90));
	}
}

void AKKPlayer::MoveForward()
{
	if (PlayerID % 2 == 0)
	{
		MoveCharacterForward();
	}
	else
	{
		MoveCharacterBackward();
	}	
}

void AKKPlayer::MoveBackward()
{
	if (PlayerID % 2 == 0)
	{
		MoveCharacterBackward();
	}
	else
	{
		MoveCharacterForward();
	}
}

void AKKPlayer::MoveRight()
{
	if (PlayerID % 2 == 0)
	{
		MoveCharacterRight();
	}
	else
	{
		MoveCharacterLeft();
	}
}

void AKKPlayer::MoveLeft()
{
	if (PlayerID % 2 == 0)
	{
		MoveCharacterLeft();
	}
	else
	{
		MoveCharacterRight();
	}
}


void AKKPlayer::AddOnPosition0()
{
	AddOnPosition(0);
}

void AKKPlayer::AddOnPosition1()
{
	AddOnPosition(1);
}

void AKKPlayer::AddOnPosition2()
{
	AddOnPosition(2);
}

void AKKPlayer::AddOnPosition3()
{
	AddOnPosition(3);
}

void AKKPlayer::MakeCharacterAttack_Implementation()
{
	if (GameObject->CurrentCharacter != nullptr && GameObject->TargetCharacter != nullptr)
	{
		if (GameObject->CurrentCharacter->Attack(GameObject))
		{
			PlayAttackAnimation();
			MakeMove();
		}
	}
}

void AKKPlayer::AddOnPosition_Implementation(int32 Position)
{
	if (HasAuthority())
	{
		AKKCharacter* Character = GameObject->CurrentCharacter;
		const int32 StartLine = (PlayerID % 2 == 0) ? 0 : 19;

		if (Character != nullptr && !(Character->bIsPlacedOnTheMap))
		{
			Position = (StartLine == 0) ? Position : -Position;
			ATile* Tile = GameObject->TileMap->Tiles[(StartLine + Position)];

			if (Tile->GetOwningCharacter() == nullptr)
			{
				MoveToTile(Tile);
				Character->bIsPlacedOnTheMap = true;
				PlaySpawnAnimation();
				//GameObject->CurrentCharacter = nullptr;
				MakeMove();
			}
		}
	}
}

void AKKPlayer::MoveCharacterForward_Implementation()
{
	if (HasAuthority())
	{
		if (GameObject->CurrentCharacter && GameObject->CurrentCharacter->CanCharacterMove())
		{
			ATile* Tile = GameObject->CurrentCharacter->OwnedTile;
			const int32 TileId = Tile->GetTileID();

			if (TileId < 16)
			{
				ATile* NewTile = GameObject->TileMap->Tiles[TileId + 4];
				if (NewTile->GetOwningCharacter() == nullptr)
				{
					Tile->SetOwningCharacter(nullptr); // CurrentCharacter no longer occupies this tile
					MoveToTile(NewTile);
					MakeMove();
				}
			}
		}
	}
}

void AKKPlayer::MoveCharacterBackward_Implementation()
{
	if (HasAuthority())
	{
		if (GameObject->CurrentCharacter && GameObject->CurrentCharacter->CanCharacterMove())
		{
			ATile* Tile = GameObject->CurrentCharacter->OwnedTile;
			const int32 TileId = Tile->GetTileID();

			if (TileId > 3)
			{
				ATile* NewTile = GameObject->TileMap->Tiles[TileId - 4];
				if (NewTile->GetOwningCharacter() == nullptr)
				{
					Tile->SetOwningCharacter(nullptr); // CurrentCharacter no longer occupies this tile
					MoveToTile(NewTile);
					MakeMove();
				}
			}
		}
	}
}

void AKKPlayer::MoveCharacterLeft_Implementation()
{
	if (HasAuthority())
	{
		if (GameObject->CurrentCharacter && GameObject->CurrentCharacter->CanCharacterMove())
		{
			ATile* Tile = GameObject->CurrentCharacter->OwnedTile;
			const int32 TileId = Tile->GetTileID();

			if (TileId % 4 != 3)
			{
				ATile* NewTile = GameObject->TileMap->Tiles[TileId + 1];
				if (NewTile->GetOwningCharacter() == nullptr)
				{
					Tile->SetOwningCharacter(nullptr); // CurrentCharacter no longer occupies this tile
					MoveToTile(NewTile);
					MakeMove();
				}
			}
		}
	}
}

void AKKPlayer::MoveCharacterRight_Implementation()
{
	if (HasAuthority())
	{
		if (GameObject->CurrentCharacter && GameObject->CurrentCharacter->CanCharacterMove())
		{
			ATile* Tile = GameObject->CurrentCharacter->OwnedTile;
			const int32 TileId = Tile->GetTileID();

			if (TileId % 4 != 0)
			{
				ATile* NewTile = GameObject->TileMap->Tiles[TileId - 1];
				if (NewTile->GetOwningCharacter() == nullptr)
				{
					Tile->SetOwningCharacter(nullptr); // CurrentCharacter no longer occupies this tile
					MoveToTile(NewTile);
					MakeMove();
				}
			}
		}
	}
}

void AKKPlayer::MakeMove_Implementation()
{
	Moves++;
	if (Moves >= 3)
	{
		DisableInput(Cast<AKKPlayerController>(GetController()));
		Moves = 0;
		ChangeInput();
	}
	//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, FString::FromInt(Moves));
}

void AKKPlayer::ChangeInput_Implementation()
{
	if (HasAuthority())
	{
		AKKGameMode* GameMode = Cast<AKKGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->ChangeInput();
	}
	//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, FString::FromInt(bIsMyTurn));	
}

void AKKPlayer::OnRep_IsMyTurn()
{
	if (bIsMyTurn)
	{
		EnableInput(Cast<AKKPlayerController>(GetController()));
	}
	else
	{
		DisableInput(Cast<AKKPlayerController>(GetController()));
	}

	//if (!(Cast<AKKGameState>(GetWorld()->GetGameState())->EndOfGame))
	//{
	CreateWidget(GetWorld(), ChangeTurnWidgetClass)->AddToViewport();
	//}
	//if(HasAuthority())
	//	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Cyan, "Server: " + FString::FromInt(bIsMyTurn));
	//else
	//	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Cyan, "Client: " + FString::FromInt(bIsMyTurn));
}

void AKKPlayer::ZoomIn()
{
	if (CameraZoom > 40)
		CameraZoom -= 4;
}

void AKKPlayer::ZoomOut()
{
	if (CameraZoom < 120)
		CameraZoom += 4;
}

void AKKPlayer::MoveToTile(class ATile* InTile)
{	
	GameObject->CurrentCharacter->SetActorLocation(InTile->GetActorLocation());
	InTile->SetOwningCharacter(GameObject->CurrentCharacter);
	GameObject->CurrentCharacter->OwnedTile = InTile;
}

void AKKPlayer::ActiveAbility()
{
	if (GameObject->CurrentCharacter != nullptr && GameObject->TargetCharacter != nullptr)
	{
		//GameObject->CurrentCharacter->ActiveAbility(GameObject->CurrentCharacter, GameObject->TargetCharacter, GameObject->Position);
	}
}

void AKKPlayer::FindPlayerCards()
{
	AKKPlayerController* PlayerController = Cast<AKKPlayerController>(GetController());
	if (PlayerController)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass(), FoundActors);
		
		for (auto &Point : FoundActors)
		{
			ASpawnPoint* SpawnPoint = Cast<ASpawnPoint>(Point);
			if (SpawnPoint && PlayerController->GetPlayerID() == SpawnPoint->GetPlayerID())
			{
				PlayerCards = SpawnPoint->GetSpawnGrid()->SpawnActors;
				for (auto &Card : PlayerCards)
				{
					if (Card)
					{
						Card->SetOwner(this);
					}
				}
				break;
			}
		}
	}
}

AKKCharacter * AKKPlayer::CastRayForCharacter()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FVector Start, Dir;
		PC->DeprojectMousePositionToWorld(Start, Dir);
		const FVector End = Start + (Dir * 8000.0f);

		FHitResult HitResult;

		GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

		if (HitResult.Actor.IsValid())
		{
			if (AKKCharacter* KKCharacter = Cast<AKKCharacter>(HitResult.Actor.Get()))
				return KKCharacter;
		}
	}

	return nullptr;
}

void AKKPlayer::PlayAttackAnimation_Implementation()
{
	if (GameObject->CurrentCharacter->AttackAnimation != nullptr)
	{
		UAnimInstance* AnimInstance = GameObject->CurrentCharacter->Mesh->GetAnimInstance();
		if (AnimInstance != nullptr)
			AnimInstance->Montage_Play(GameObject->CurrentCharacter->AttackAnimation);
	}
}

void AKKPlayer::PlaySpawnAnimation_Implementation()
{
	if (GameObject->CurrentCharacter->SummonAnimation)
	{
		UAnimInstance* AnimInstance = GameObject->CurrentCharacter->Mesh->GetAnimInstance();

		if (AnimInstance)
			AnimInstance->Montage_Play(GameObject->CurrentCharacter->SummonAnimation);
	}
}

void AKKPlayer::ServerSetTargetCharacter_Implementation(AKKCharacter * Character)
{
	GameObject->TargetCharacter = Character;
}

void AKKPlayer::ServerSetCurrentCharacter_Implementation(AKKCharacter * Character)
{
	GameObject->CurrentCharacter = Character;
}

void AKKPlayer::GetIDFromController()
{
	if (AKKPlayerController* KKController = Cast<AKKPlayerController>(GetController()))
	{
		PlayerID = KKController->GetPlayerID();
		//GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, (FString::FromInt(PlayerID)));
	}
}

void AKKPlayer::GetMapFromGameState()
{
	if (AKKGameState* GameState = Cast<AKKGameState>(GetWorld()->GetGameState()))
	{
		GameObject->TileMap = GameState->TileMap;
	}
}
