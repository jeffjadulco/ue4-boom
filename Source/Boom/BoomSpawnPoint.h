// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoomSpawnPoint.generated.h"

UENUM()
enum class ESpawnPointState : uint8
{
	Available,
	Unavailable
};

UCLASS(Blueprintable)
class BOOM_API ABoomSpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	ABoomSpawnPoint();

	/*
	 * State which helps the game mode determine which spawn points are available
	 */
	UPROPERTY(BlueprintReadOnly, Category="Gameplay")
	ESpawnPointState State = ESpawnPointState::Available;

	/*
	 * Reference to spawned actor if State is Unavailable
	 */
	UPROPERTY(BlueprintReadOnly, Category="Gameplay")
	AActor* SpawnedActorReference;

	void SetSpawnedActor(AActor* SpawnedActor);

protected:
	virtual void BeginPlay() override;
};
