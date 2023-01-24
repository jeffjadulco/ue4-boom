// Copyright Epic Games, Inc. All Rights Reserved.


#include "BoomGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "BoomCrate.h"
#include "BoomEnemyCharacter.h"
#include "GameFramework/PlayerStart.h"

void ABoomGameMode::GameOver()
{
	EndMatch();
	
	FTimerHandle GameOverTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(GameOverTimerHandle, FTimerDelegate::CreateUObject(this, &ABoomGameMode::RestartGame), GameOverRestartDelay, false);

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, "Game Over!");
}

void ABoomGameMode::GameWon()
{
	EndMatch();
	
	FTimerHandle GameOverTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(GameOverTimerHandle, FTimerDelegate::CreateUObject(this, &ABoomGameMode::RestartGame), GameOverRestartDelay, false);

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, "Game Won!");
}

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

AActor* ABoomGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	TArray<AActor*> PlayerStartActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStartActors);

	const int32 RandomIndex = FMath::RandRange(0, PlayerStartActors.Num() - 1);
	if (PlayerStartActors.IsValidIndex(RandomIndex))
	{
		return PlayerStartActors[RandomIndex];
	}

	UE_LOG(LogTemp, Warning, TEXT("Cannot find a APlayerStart!"))
	return nullptr;
}

TArray<ABoomSpawnPoint*> ABoomGameMode::SpawnCrates(TArray<ABoomSpawnPoint*>& SpawnPoints)
{
	UE_LOG(LogTemp, Log, TEXT("SpawnCrates"))
	for (int32 i = 0; i < InitialCrateCount; i++)
	{
		const int32 RandomIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		if (SpawnPoints.IsValidIndex(RandomIndex))
		{
			ABoomSpawnPoint* RandomSpawnPoint = SpawnPoints[RandomIndex];
			if (GetWorld() && RandomSpawnPoint)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				FTransform SpawnTransform = RandomSpawnPoint->GetActorTransform();

				// UE_LOG(LogTemp, Log, TEXT("SpawnCrates: Index=%d"), i);

				const auto SpawnedCrate = GetWorld()->SpawnActor<ABoomCrate>(CrateClass, SpawnTransform, SpawnParams);
				RandomSpawnPoint->SetSpawnedActor(SpawnedCrate);
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
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				FTransform SpawnTransform = RandomSpawnPoint->GetActorTransform();
				
				ABoomEnemyCharacter* NewEnemy = GetWorld()->SpawnActor<ABoomEnemyCharacter>(EnemyClass, SpawnTransform, SpawnParams);
				if (NewEnemy)
				{
					if (NewEnemy->Controller == nullptr)
					{
						NewEnemy->SpawnDefaultController();
					}

					NewEnemy->OnDie.BindDynamic(this, &ABoomGameMode::OnEnemyDie);
				}
			}

			SpawnPoints.RemoveAt(RandomIndex);
		}
	}
}

void ABoomGameMode::OnEnemyDie()
{
	DeadEnemyCount++;
	if (DeadEnemyCount >= InitialEnemyCount)
	{
		AssignPortalAndPowerups();
	}
}

void ABoomGameMode::AssignPortalAndPowerups()
{
	// Set random portal + powerup to available crates
	TArray<AActor*> SpawnPointActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoomSpawnPoint::StaticClass(), SpawnPointActors);

	TArray<ABoomCrate*> AvailableCrates;
	for (AActor* SpawnPointActor : SpawnPointActors)
	{
		if (const auto SpawnPoint = Cast<ABoomSpawnPoint>(SpawnPointActor))
		{
			if (const auto CrateRef = Cast<ABoomCrate>(SpawnPoint->SpawnedActorReference))
			{
				AvailableCrates.Add(CrateRef);
			}
		}
	}

	if (AvailableCrates.Num() > 0)
	{
		// Assign a loot/powerup on destroy
		const int32 RandomIndex = FMath::RandRange(0, AvailableCrates.Num() - 1);
		if (AvailableCrates.IsValidIndex(RandomIndex))
		{
			const auto RandomCrate = AvailableCrates[RandomIndex];
			RandomCrate->SetPowerupToSpawnOnDestroy(PortalClass);
			RandomCrate->Highlight();
		}
	}
	else
	{
		// If there are no available crates, spawn random portal
		const int32 RandomIndex = FMath::RandRange(0, SpawnPointActors.Num() - 1);
		// TODO: Spawn portal 
	}
}
