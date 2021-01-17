// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Net/UnrealNetwork.h"
#include "Internationalization/Text.h"

#include "KKCharacter.generated.h"

class UGameObject;

UCLASS(BlueprintType, Abstract)
class UKRZYWEKARTY_API AKKCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKKCharacter();



protected:

	UPROPERTY(VisibleDefaultsOnly, Category = "PedestalMesh")
		class UStaticMeshComponent* Pedestal;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		class UTextRenderComponent* TextName;

	UPROPERTY(EditAnywhere, Category = "EventAnimation")
		class UAnimMontage* AttackAnimation;
	UPROPERTY(EditAnywhere, Category = "EventAnimation")
		class UAnimMontage* SummonAnimation;



	UPROPERTY(Replicated, BlueprintReadWrite)
		class ATile* OwnedTile = nullptr;

	UPROPERTY(Replicated, BlueprintReadWrite)
		FString Name;

	UPROPERTY(Replicated, BlueprintReadWrite)
		int32 Strength = 0;
	UPROPERTY(Replicated, BlueprintReadWrite)
		int32 Defense = 0;
	UPROPERTY(Replicated, BlueprintReadWrite)
		int32 Health = 0;
	UPROPERTY(Replicated, BlueprintReadWrite)
		int32 Mana = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MaxStrength = Strength;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MaxDefense = Defense;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MaxHealth = Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MaxMana = Mana;


	bool bIsRanged = false;
	int32 AttackDistance = 1;

	//FString fraction;

	UPROPERTY(Replicated, BlueprintReadWrite)
		int32 CountAttacks = 0;
	UPROPERTY(Replicated, BlueprintReadWrite)
		bool bAttacked = false;
	UPROPERTY(Replicated, BlueprintReadWrite)
		bool bIsDead = false;
	UPROPERTY(Replicated, BlueprintReadWrite)
		bool bIsPlacedOnTheMap = false; // is character already on map?

	bool bIsAllowedToAttack = true; // used when character block Strength
	bool bIsAllowedToUseAbility = true; // used when character block ability
	bool bIsAbleToMove = true;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//static float LookRotationBasedOnLocation(AKKCharacter* One, AKKCharacter* Two);
	bool CanCharacterMove();
	int32 Distance(AKKCharacter* Target);


	UFUNCTION(NetMulticast, Reliable)
	void SetCharacterName();

	void KillCharacter(UGameObject* GO);

	void CalculateDamage(UGameObject *GO);

	virtual bool Attack(UGameObject *GO, bool bIsInLine = true);

	virtual void ActiveAbility(UGameObject* GO);
	virtual void ActiveAbility2(UGameObject* GO);
	virtual void PassiveAbility(UGameObject* GO);
	virtual void PassiveAbility2(UGameObject* GO);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	friend class AKKPlayer;
	friend class UGameObject;
	friend class ASpawnGrid;

	friend class AZakon_Grid;
	friend class AZakon;
	friend class AZakon_Halabardzista;
	friend class AZakon_Kaplan;
	friend class AZakon_Kawalerzysta;
	friend class AZakon_Kusznik;
	friend class AZakon_Lucznik;
	friend class AZakon_Paladyn;
	friend class AZakon_Rycerz;
};
