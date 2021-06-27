// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "Tile.generated.h"


class AKKCharacter;

UCLASS()
class UKRZYWEKARTY_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	int32 GetTileID();
	AKKCharacter* GetOwningCharacter();
	void SetOwningCharacter(class AKKCharacter* Character);
	void SetTileID(int32 ID);


protected:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
		int32 TileID = 0;

	UPROPERTY(Replicated, BlueprintReadWrite)
		AKKCharacter* OwningCharacter = nullptr;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	class UTextRenderComponent* NumberText;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
