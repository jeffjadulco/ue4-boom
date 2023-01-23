// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BoomSpawnPoint.h"
#include "GameFramework/GameMode.h"
#include "BoomGameMode.generated.h"

class ABoomCrate;
class ABoomEnemyBase;


/**
 * 
 */
UCLASS()
class BOOM_API ABoomGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spawning")
	int32 InitialCrateCount = 32;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spawning")
	int32 InitialEnemyCount = 3;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spawning")
	TSubclassOf<ABoomCrate> CrateClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Spawning")
	TSubclassOf<ABoomEnemyBase> EnemyClass;
	
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
