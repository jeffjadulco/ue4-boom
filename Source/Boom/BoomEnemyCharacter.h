// Copyright (c) 2023 Jefferson Jadulco

#pragma once

#include "CoreMinimal.h"
#include "BoomCharacterBase.h"
#include "BoomEnemyCharacter.generated.h"

UCLASS(BlueprintType)
class BOOM_API ABoomEnemyCharacter : public ABoomCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABoomEnemyCharacter();
};
