// Copyright (c) 2023 Jefferson Jadulco


#include "BoomPowerup.h"

#include "Components/BoxComponent.h"


ABoomPowerup::ABoomPowerup()
{
	PrimaryActorTick.bCanEverTick = false;

	const auto SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = SceneComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	Mesh->SetupAttachment(SceneComponent);

	BoxOverlapComponent = CreateDefaultSubobject<UBoxComponent>("Box Overlap");
	BoxOverlapComponent->SetCollisionProfileName("OverlapAllDynamic");
	BoxOverlapComponent->SetupAttachment(SceneComponent);
	BoxOverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &ABoomPowerup::OnOverlapBegin);

}

void ABoomPowerup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABoomPowerup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		Activate();
	}
}

void ABoomPowerup::Activate()
{
	OnActivate.ExecuteIfBound(this);
	UE_LOG(LogTemp, Log, TEXT("Powerup activated!"))
}

