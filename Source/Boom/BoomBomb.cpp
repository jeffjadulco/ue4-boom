// Copyright (c) 2023 Jefferson Jadulco


#include "BoomBomb.h"

#include "BoomIDamageable.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


ABoomBomb::ABoomBomb()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	RootComponent = Mesh;

	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>("Box Blocker");
	BoxCollisionComponent->SetCollisionProfileName("BlockAll");
	BoxCollisionComponent->SetupAttachment(Mesh);

	BoxOverlapComponent = CreateDefaultSubobject<UBoxComponent>("Box Overlap");
	BoxOverlapComponent->SetCollisionProfileName("OverlapAllDynamic");
	BoxOverlapComponent->SetupAttachment(Mesh);
	BoxOverlapComponent->OnComponentEndOverlap.AddDynamic(this, &ABoomBomb::OnOverlapEnd);

	// Gameplay
	NumTicks = 0;
}

void ABoomBomb::BeginPlay()
{
	Super::BeginPlay();

	BoxCollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	const FTimerDelegate BombTimerDelegate = FTimerDelegate::CreateUObject(this, &ABoomBomb::TickBomb);
	GetWorld()->GetTimerManager().SetTimer(BombTimerHandle, BombTimerDelegate, TickIntervalInSeconds, true, TickIntervalInSeconds);
}


void ABoomBomb::TickBomb_Implementation()
{
	NumTicks++;

	if (NumTicks >= NumOfTicksBeforeExplode)
	{
		GetWorld()->GetTimerManager().ClearTimer(BombTimerHandle);

		// Add delay for the slight animation
		GetWorld()->GetTimerManager().SetTimer(
			BombTimerHandle,
			FTimerDelegate::CreateUObject(this, &ABoomBomb::Explode),
			0.25f,
			false
			);
	}
}

void ABoomBomb::Explode_Implementation()
{
	auto DamageableActors = DetectDamageables();

	for (const auto DamageableActor : DamageableActors)
	{
		IBoomIDamageable::Execute_TakeDamage(DamageableActor);
	}

	Destroy();
}

TArray<AActor*> ABoomBomb::DetectDamageables()
{
	TArray<AActor*> DamageableActors;

	// For every direction, do a line trace from bomb location to 100 units further
	for (int32 i = 0; i < 4; i++)
	{
		FRotator AngledRotation = FRotator(0, 90 * i, 0);
		const FVector TraceStartLoc = GetActorLocation();
		const float TraceLength = 100.0f; // 100 units, Grid size
		const FVector ForwardVector = GetActorRotation().Vector();
		const FVector RotatedForwardVector = AngledRotation.RotateVector(ForwardVector);
		const FVector TraceEndLoc = TraceStartLoc + RotatedForwardVector * TraceLength;
		
		FHitResult OutHit;
		FCollisionQueryParams CollisionParams = FCollisionQueryParams::DefaultQueryParam;
		CollisionParams.AddIgnoredActor(this);
		
		if (GetWorld()->LineTraceSingleByChannel(
			OutHit,
			TraceStartLoc,
			TraceEndLoc,
			ExplosionTraceChannel,
			CollisionParams
			))
		{
			if (OutHit.Actor->GetClass()->ImplementsInterface(UBoomIDamageable::StaticClass()))
			{
				DamageableActors.Add(OutHit.Actor.Get());	
			}
		}
	}
	
	return DamageableActors;
}

void ABoomBomb::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		BoxCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

