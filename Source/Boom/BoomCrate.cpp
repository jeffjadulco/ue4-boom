// Copyright (c) 2023 Jefferson Jadulco


#include "BoomCrate.h"


ABoomCrate::ABoomCrate()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABoomCrate::TakeDamage_Implementation()
{
	Destroy();	
}

void ABoomCrate::BeginPlay()
{
	Super::BeginPlay();
	
}

