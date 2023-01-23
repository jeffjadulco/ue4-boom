// Copyright (c) 2023 Jefferson Jadulco

#pragma once

#include "CoreMinimal.h"
#include "BoomCharacterBase.h"
#include "BoomIInstaKillable.h"
#include "BoomMainCharacter.generated.h"

class ABoomBomb;

UCLASS(Blueprintable)
class BOOM_API ABoomMainCharacter : public ABoomCharacterBase, public IBoomIInstaKillable
{
	GENERATED_BODY()

public:
	ABoomMainCharacter();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	int32 BombLimit = 1;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<ABoomBomb> BombClass;

protected:
	virtual void BeginPlay() override;

	void OnMoveHorizontal(float AxisValue);

	void OnMoveVertical(float AxisValue);

	void OnSkill1Pressed();

public:
	virtual void PostInitializeComponents() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void ReceiveInstaKill() override;

private:
	void SpawnBomb();
};
