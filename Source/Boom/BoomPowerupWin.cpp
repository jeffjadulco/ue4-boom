// Copyright (c) 2023 Jefferson Jadulco


#include "BoomPowerupWin.h"

#include "BoomGameMode.h"

ABoomPowerupWin::ABoomPowerupWin()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABoomPowerupWin::Activate()
{
	Super::Activate();

	if (auto GM = Cast<ABoomGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GM->GameWon();
	}
}

