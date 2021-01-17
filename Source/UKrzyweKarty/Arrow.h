// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Arrow.generated.h"

UCLASS()
class UKRZYWEKARTY_API AArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrow();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, AdvancedDisplay)
		class UProjectileMovementComponent* ArrowMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, AdvancedDisplay)
		class USphereComponent* Capsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, AdvancedDisplay)
		class UStaticMeshComponent* Arrow;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
