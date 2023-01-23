// Copyright (c) 2023 Jefferson Jadulco

#pragma once

#include "CoreMinimal.h"
#include "BoomIDamageable.h"
#include "GameFramework/Actor.h"
#include "BoomCrate.generated.h"

UCLASS()
class BOOM_API ABoomCrate : public AActor, public IBoomIDamageable
{
	GENERATED_BODY()

public:
	ABoomCrate();

	virtual void TakeDamage_Implementation() override;

protected:
	virtual void BeginPlay() override;
};
