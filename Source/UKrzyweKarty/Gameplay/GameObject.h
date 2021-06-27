// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TileMap.h"
#include "KKCharacter.h"
#include "GameObject.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UKRZYWEKARTY_API UGameObject : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameObject();

	UPROPERTY(Replicated, BlueprintReadWrite, Category ="Character")
		AKKCharacter* CurrentCharacter;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Character")
		AKKCharacter* TargetCharacter;

	UPROPERTY(Replicated, BlueprintReadWrite, AdvancedDisplay)
		ATileMap* TileMap;

		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		

	friend class AKKPlayer;
	friend class AKKCharacter;
};
