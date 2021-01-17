// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Kismet/GameplayStatics.h"
#include "Zakon.h"
#include "Zakon_Rycerz.h"
#include "Zakon_Halabardzista.h"
#include "Zakon_Kaplan.h"
#include "Zakon_Kawalerzysta.h"
#include "Zakon_Kusznik.h"
#include "Zakon_Lucznik.h"
#include "Zakon_Paladyn.h"

#include "Zakon_Grid.generated.h"


UCLASS()
class UKRZYWEKARTY_API AZakon_Grid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZakon_Grid();

protected:
	FRotator start_rotation = { 0, 0, -90 };
	FVector start_position[7];

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cards")
	TArray <TSubclassOf<AZakon>> SpawnCards;

	TArray <AZakon*> SpawnActors;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
