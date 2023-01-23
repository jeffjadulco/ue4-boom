// Copyright (c) 2023 Jefferson Jadulco


#include "BoomEnemyBase.h"


// Sets default values
ABoomEnemyBase::ABoomEnemyBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABoomEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoomEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABoomEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

