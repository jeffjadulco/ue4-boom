// Copyright (c) 2023 Jefferson Jadulco

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BoomPowerup.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnActivateEvent, ABoomPowerup*, Powerup);

UCLASS(Blueprintable)
class BOOM_API ABoomPowerup : public AActor
{
	GENERATED_BODY()

public:
	ABoomPowerup();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision")
	UBoxComponent* BoxOverlapComponent;

	FOnActivateEvent OnActivate;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Activate();
};
