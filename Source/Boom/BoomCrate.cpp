// Copyright (c) 2023 Jefferson Jadulco


#include "BoomCrate.h"


// Sets default values
ABoomCrate::ABoomCrate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABoomCrate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoomCrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

