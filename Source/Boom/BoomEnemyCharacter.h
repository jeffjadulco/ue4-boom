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
	ABoomEnemyCharacter();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Movement")
	float WalkSpeed = 20.0f;

	void SetLastForwardDirection(FVector Direction);

private:
	/*
	 * Change direction to an available direction, excluding LastForwardDirection
	 */
	void ChangeDirection();

	/*
	 * Checks if the pawn "collided" by performing a line trace in front (forward direction)
	 */
	bool CheckCollision();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	FVector LastForwardDirection;
	bool IsCheckingDirection = false;
};
