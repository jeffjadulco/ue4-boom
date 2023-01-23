// Copyright (c) 2023 Jefferson Jadulco

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoomCrate.generated.h"

UCLASS()
class BOOM_API ABoomCrate : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABoomCrate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
