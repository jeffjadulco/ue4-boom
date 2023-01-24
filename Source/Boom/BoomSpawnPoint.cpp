// Copyright (c) 2023 Jefferson Jadulco


#include "BoomSpawnPoint.h"

ABoomSpawnPoint::ABoomSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABoomSpawnPoint::SetSpawnedActor(AActor* SpawnedActor)
{
	State = ESpawnPointState::Unavailable;
	SpawnedActorReference = SpawnedActor;
}

void ABoomSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

