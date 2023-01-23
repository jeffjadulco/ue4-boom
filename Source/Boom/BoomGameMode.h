// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BoomSpawnPoint.h"
#include "GameFramework/GameMode.h"
#include "BoomGameMode.generated.h"

class ABoomCrate;
class ABoomEnemyCharacter;


/**
 * 
 */
UCLASS()
class BOOM_API ABoomGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	void GameOver();

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

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="State")
	float GameOverRestartDelay = 3.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Debug")
	bool bSpawnCrates = false;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Debug")
	bool bSpawnEnemies = false;
	
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
};
