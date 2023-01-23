// Copyright (c) 2023 Jefferson Jadulco

#pragma once

#include "CoreMinimal.h"
#include "BoomIDamageable.h"
#include "GameFramework/Character.h"
#include "BoomCharacterBase.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnDieEvent);

UCLASS()
class BOOM_API ABoomCharacterBase : public ACharacter, public IBoomIDamageable
{
	GENERATED_BODY()

public:
	ABoomCharacterBase();

	UPROPERTY(BlueprintReadOnly, Category="Gameplay")
	bool IsDead = false;

	FOnDieEvent OnDie;

protected:
	virtual void BeginPlay() override;

public:
	void TakeDamage_Implementation() override;
	
	virtual void Die();
};
