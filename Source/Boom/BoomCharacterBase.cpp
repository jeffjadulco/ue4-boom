// Copyright (c) 2023 Jefferson Jadulco


#include "BoomCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

ABoomCharacterBase::ABoomCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABoomCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABoomCharacterBase::TakeDamage_Implementation()
{
	Die();
}

void ABoomCharacterBase::Die()
{
	IsDead = true;
	SetActorEnableCollision(false);
	GetCharacterMovement()->DisableMovement();

	OnDie.ExecuteIfBound();
}

