// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Net/UnrealNetwork.h"
#include "KKPlayer.generated.h"


class AKKCharacter;

UCLASS()
class UKRZYWEKARTY_API AKKPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKKPlayer();

	void SelectCurrent();
	void SelectTarget();
	void DoAttack();
	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();
	
	void AddOnPosition0();
	void AddOnPosition1();
	void AddOnPosition2();
	void AddOnPosition3();
	
	void GetIDFromController();

	UFUNCTION(BlueprintCallable)
		void GetMapFromGameState();

	UFUNCTION(Server, Reliable)
		void AddOnPosition(int32 position);

	UFUNCTION(Server, Reliable)
		void ServerSetCurrentCharacter(AKKCharacter* Character);
	UFUNCTION(Server, Reliable)
		void ServerSetTargetCharacter(AKKCharacter* Character);
	UFUNCTION(Server, Reliable)
		void MakeCharacterAttack();

	UFUNCTION(NetMulticast, Reliable)
		void PlayAttackAnimation();
	UFUNCTION(NetMulticast, Reliable)
		void PlaySpawnAnimation();

	UFUNCTION(Server, Reliable)
		void MoveCharacterForward();
	UFUNCTION(Server, Reliable)
		void MoveCharacterBackward();
	UFUNCTION(Server, Reliable)
		void MoveCharacterLeft();
	UFUNCTION(Server, Reliable)
		void MoveCharacterRight();

	UFUNCTION(Server, Reliable)
		void ChangeInput();
	UFUNCTION(Client, Reliable)
		void MakeMove();

	UFUNCTION()
		void OnRep_IsMyTurn();

	void ZoomIn();
	void ZoomOut();

	void MoveToTile(class ATile* InTile);

	void ActiveAbility();
	void FindPlayerCards();

	UFUNCTION(BlueprintCallable)
	AKKCharacter* CastRayForCharacter(); // returns clicked KKCharacter

public:
	UPROPERTY(EditAnywhere, AdvancedDisplay)
		class UCameraComponent* PlayerCamera;
	UPROPERTY(EditAnywhere, AdvancedDisplay)
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameObjects")
		class UGameObject* GO;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> ChangeTurnWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> CurrentCharacterWidgetClass;
	UUserWidget* CurrentCharacterWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> TargetCharacterWidgetClass;
	UUserWidget* TargetCharacterWidget;

	TArray<AKKCharacter*> PlayerCards;



	UPROPERTY(ReplicatedUsing=OnRep_IsMyTurn, BlueprintReadWrite)
		bool bIsMyTurn = false;

	UPROPERTY(Replicated, BlueprintReadWrite)
		int32 PlayerID = 0;

	int32 Moves = 0;



	//bool HighlightCard= false;
	//void ShowGreenFields();
	//void RemoveGreenFields();
	//void ShowRedFields();
	//void RemoveRedFields();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	float CameraZoom = 90;
};
