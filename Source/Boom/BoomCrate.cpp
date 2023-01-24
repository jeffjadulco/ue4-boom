// Copyright (c) 2023 Jefferson Jadulco


#include "BoomCrate.h"

#include "BoomPowerup.h"


ABoomCrate::ABoomCrate()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABoomCrate::TakeDamage_Implementation()
{
	// Spawn assigned actor before destroy
	if (PowerupToSpawnOnDestroy)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<ABoomPowerup>(PowerupToSpawnOnDestroy, GetActorTransform(), SpawnParams);
	}
	
	Destroy();	
}

void ABoomCrate::SetPowerupToSpawnOnDestroy(TSubclassOf<ABoomPowerup> ActorClass)
{
	PowerupToSpawnOnDestroy = ActorClass;
}

void ABoomCrate::BeginPlay()
{
	Super::BeginPlay();
	
}

