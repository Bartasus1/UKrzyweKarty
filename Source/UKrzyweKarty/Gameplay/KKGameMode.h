// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KKGameMode.generated.h"

class AKKCharacter;
class AKKPlayer;
/**
 * 
 */
UCLASS()
class UKRZYWEKARTY_API AKKGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AKKGameMode();

	UPROPERTY(Transient, BlueprintReadWrite)
		TArray<class AKKPlayerController*> Players;

	bool bIsPlayerOneTurn = false;
	bool bIsPlayerTwoTurn = true;

	//UFUNCTION(BlueprintCallable)
	void ChangeInput();

	void OnWin(AKKPlayer* Winner) const;

	UFUNCTION()
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
};
