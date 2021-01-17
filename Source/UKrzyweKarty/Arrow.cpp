// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"

// Sets default values
AArrow::AArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Arrow = CreateDefaultSubobject<UStaticMeshComponent>("Arrow");
	ArrowMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ArrowMovement");
	Capsule = CreateDefaultSubobject<USphereComponent>("Capsule");

	Arrow->SetupAttachment(Capsule);
	ArrowMovement->InitialSpeed = 100;
	ArrowMovement->MaxSpeed = 100;
	ArrowMovement->ProjectileGravityScale = 0.f;
	ArrowMovement->bRotationFollowsVelocity = true;
	ArrowMovement->UpdatedComponent = Capsule;
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

