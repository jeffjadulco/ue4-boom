// Copyright (c) 2023 Jefferson Jadulco

#pragma once

#include "CoreMinimal.h"
#include "BoomIDamageable.h"
#include "GameFramework/Actor.h"
#include "BoomCrate.generated.h"

class ABoomPowerup;

UCLASS(Blueprintable)
class BOOM_API ABoomCrate : public AActor, public IBoomIDamageable
{
	GENERATED_BODY()

public:
	ABoomCrate();

	virtual void TakeDamage_Implementation() override;

	void SetPowerupToSpawnOnDestroy(TSubclassOf<ABoomPowerup> PowerupClass);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Spawn")
	TSubclassOf<ABoomPowerup> PowerupToSpawnOnDestroy;

	UFUNCTION(BlueprintImplementableEvent, Category="Gameplay")
	void Highlight();

protected:
	virtual void BeginPlay() override;
};
