// Copyright (c) 2023 Jefferson Jadulco

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BoomBomb.generated.h"

UCLASS(Blueprintable)
class BOOM_API ABoomBomb : public AActor
{
	GENERATED_BODY()

public:
	ABoomBomb();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision")
	UBoxComponent* BoxCollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision")
	UBoxComponent* BoxOverlapComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Gameplay")
	int32 NumOfTicksBeforeExplode = 3;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Gameplay")
	float TickIntervalInSeconds = 1.0f;

	FTimerHandle BombTimerHandle;
	
	UFUNCTION(BlueprintNativeEvent)
	void TickBomb();
	
	UFUNCTION(BlueprintNativeEvent)
	void Explode();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Explosion")
	TEnumAsByte<ECollisionChannel> ExplosionTraceChannel;

protected:
	virtual void BeginPlay() override;

	TArray<AActor*> DetectDamageables();

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
private:
	int32 NumTicks = 0;
};
