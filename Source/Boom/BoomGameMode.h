// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BoomSpawnPoint.h"
#include "GameFramework/GameMode.h"
#include "BoomGameMode.generated.h"

class ABoomCrate;
class ABoomEnemyCharacter;
class ABoomPowerup;

/**
 * 
 */
UCLASS()
class BOOM_API ABoomGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void GameOver();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void GameWon();

protected:
	virtual void BeginPlay() override;
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;
	

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spawning")
	int32 InitialCrateCount = 32;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spawning")
	int32 InitialEnemyCount = 3;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spawning")
	TSubclassOf<ABoomCrate> CrateClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spawning")
	TSubclassOf<ABoomEnemyCharacter> EnemyClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spawning")
	TSubclassOf<ABoomPowerup> PortalClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spawning")
	TArray<TSubclassOf<ABoomPowerup>> PowerupClasses;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="State")
	float GameOverRestartDelay = 3.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Debug")
	bool bSpawnCrates = true;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Debug")
	bool bSpawnEnemies = true;
	
private:
	/**
	 * Spawn destructible crates in random spawn points
	 * Returns - Remaining available spawn points
	 */
	TArray<ABoomSpawnPoint*> SpawnCrates(TArray<ABoomSpawnPoint*> &SpawnPoints);

	/**
	 * Spawn enemies in random spawn points
	 */
	void SpawnEnemies(TArray<ABoomSpawnPoint*> &SpawnPoints);
	
	UFUNCTION()
	void OnEnemyDie();

	void AssignPortalAndPowerups();

	int32 DeadEnemyCount = 0;
};
