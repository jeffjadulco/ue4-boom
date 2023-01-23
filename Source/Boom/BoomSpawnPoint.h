// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoomSpawnPoint.generated.h"

UCLASS(Blueprintable)
class BOOM_API ABoomSpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	ABoomSpawnPoint();

protected:
	virtual void BeginPlay() override;
};
