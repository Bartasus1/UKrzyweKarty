// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObject.h"

// Sets default values for this component's properties
UGameObject::UGameObject()
{
	
}


void UGameObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UGameObject, CurrentCharacter);
	DOREPLIFETIME(UGameObject, TargetCharacter);
	DOREPLIFETIME(UGameObject, TileMap);
}

// Called when the game starts
void UGameObject::BeginPlay()
{
	Super::BeginPlay();
}


