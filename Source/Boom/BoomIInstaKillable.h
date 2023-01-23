// Copyright (c) 2023 Jefferson Jadulco

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BoomIInstaKillable.generated.h"

UINTERFACE(Blueprintable)
class UBoomIInstaKillable : public UInterface
{
	GENERATED_BODY()
};

class BOOM_API IBoomIInstaKillable
{
	GENERATED_BODY()

public:
	virtual void ReceiveInstaKill() =0;
};