// Copyright Epic Games, Inc. All Rights Reserved.


#include "BoomGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "BoomCrate.h"
#include "BoomEnemyCharacter.h"

void ABoomGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> SpawnPointActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoomSpawnPoint::StaticClass(), SpawnPointActors);

	TArray<ABoomSpawnPoint*> SpawnPoints;
	for (AActor* SpawnPointActor : SpawnPointActors)
	{
		SpawnPoints.Add(Cast<ABoomSpawnPoint>(SpawnPointActor));
	}

#if !UE_BUILD_SHIPPING
	TArray<ABoomSpawnPoint*> RemainingSpawnPoints = SpawnPoints; 
	if (bSpawnCrates)
	{
		RemainingSpawnPoints = SpawnCrates(SpawnPoints);
	}
	if (bSpawnEnemies)
	{
		SpawnEnemies(RemainingSpawnPoints);
	}
#else
	auto RemainingSpawnPoints = SpawnCrates(SpawnPoints);
	SpawnEnemies(RemainingSpawnPoints);
#endif
}

TArray<ABoomSpawnPoint*> ABoomGameMode::SpawnCrates(TArray<ABoomSpawnPoint*>& SpawnPoints)
{
	UE_LOG(LogTemp, Log, TEXT("SpawnCrates"))
	for (int32 i = 0; i < InitialCrateCount; i++)
	{
		const int32 RandomIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		if (SpawnPoints.IsValidIndex(RandomIndex))
		{
			const ABoomSpawnPoint* RandomSpawnPoint = SpawnPoints[RandomIndex];
			if (GetWorld() && RandomSpawnPoint)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				// SpawnParams.Name = TEXT("BoomCrate %d", RandomIndex);

				FTransform SpawnTransform = RandomSpawnPoint->GetActorTransform();

				UE_LOG(LogTemp, Log, TEXT("SpawnCrates: Index=%d"), i);
				
				GetWorld()->SpawnActor<ABoomCrate>(CrateClass, SpawnTransform, SpawnParams);
			}

			SpawnPoints.RemoveAt(RandomIndex);
		}
	}
	return SpawnPoints;
}

void ABoomGameMode::SpawnEnemies(TArray<ABoomSpawnPoint*>& SpawnPoints)
{
	for (int32 i = 0; i < InitialEnemyCount; i++)
	{
		const int32 RandomIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		if (SpawnPoints.IsValidIndex(RandomIndex))
		{
			const ABoomSpawnPoint* RandomSpawnPoint = SpawnPoints[RandomIndex];
			if (GetWorld() && RandomSpawnPoint)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Name = "BoomEnemy" + RandomIndex;

				FTransform SpawnTransform = RandomSpawnPoint->GetActorTransform();
				
				ABoomEnemyCharacter* NewEnemy = GetWorld()->SpawnActor<ABoomEnemyCharacter>(EnemyClass, SpawnTransform, SpawnParams);
				if (NewEnemy)
				{
					if (NewEnemy->Controller == nullptr)
					{
						NewEnemy->SpawnDefaultController();
					}
				}
			}

			SpawnPoints.RemoveAt(RandomIndex);
		}
	}
}
