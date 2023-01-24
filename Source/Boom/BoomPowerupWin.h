// Copyright (c) 2023 Jefferson Jadulco

#pragma once

#include "CoreMinimal.h"
#include "BoomPowerup.h"
#include "GameFramework/Actor.h"
#include "BoomPowerupWin.generated.h"

UCLASS()
class BOOM_API ABoomPowerupWin : public ABoomPowerup
{
	GENERATED_BODY()

public:
	ABoomPowerupWin();

	virtual void Activate() override;
};
