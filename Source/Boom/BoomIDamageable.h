// Copyright (c) 2023 Jefferson Jadulco

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BoomIDamageable.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class UBoomIDamageable : public UInterface
{
	GENERATED_BODY()
};
class BOOM_API IBoomIDamageable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Damage")
	void TakeDamage(); // No arguments for now	
};
