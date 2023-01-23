// Copyright (c) 2023 Jefferson Jadulco


#include "BoomEnemyCharacter.h"

#include "BoomIInstaKillable.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ABoomEnemyCharacter::ABoomEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABoomEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetLastForwardDirection(GetActorRotation().Vector());

	ChangeDirection();
}

void ABoomEnemyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsDead) { return; }

	// Walk in front
	GetCharacterMovement()->AddInputVector(DeltaSeconds * WalkSpeed * LastForwardDirection);

	// Only check collision if current forward direction is same as LastForwardDirection to avoid triggering ChangeDirection per tick
	if (!GetActorRotation().Vector().Equals(LastForwardDirection, 0.01))
	{
		return;
	}

	// Change direction if bumped/collided with something
	if (CheckCollision())
	{
		ChangeDirection();
	}
}

void ABoomEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// TODO: Use default collider for now. 
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABoomEnemyCharacter::OnOverlapBegin);
	}
}

void ABoomEnemyCharacter::SetLastForwardDirection(FVector Direction)
{
	LastForwardDirection = Direction;

	UE_LOG(LogTemp, Log, TEXT("ABoomEnemyCharacter: New direction=%s"), *LastForwardDirection.ToString());
}

void ABoomEnemyCharacter::ChangeDirection()
{
	IsCheckingDirection = true;

	TArray<FVector> ValidDirections;

	// For every direction, do a line trace from bomb location to 100 units further
	for (int32 i = 0; i < 4; i++)
	{
		FRotator AngledRotation = FRotator(0, 90 * i, 0);
		const FVector TraceStartLoc = GetActorLocation();
		const float TraceLength = 100.0f; // 100 units, Grid size
		const FVector ForwardVector = GetActorRotation().Vector();
		const FVector RotatedForwardVector = AngledRotation.RotateVector(ForwardVector);
		const FVector TraceEndLoc = TraceStartLoc + RotatedForwardVector * TraceLength;

		// Exclude last direction
		if (RotatedForwardVector.Equals(LastForwardDirection, 0.01))
		{
			continue;
		}
		
		FHitResult OutHit;
		FCollisionQueryParams CollisionParams = FCollisionQueryParams::DefaultQueryParam;
		CollisionParams.AddIgnoredActor(this);

		// If no collision, valid path
		if (!GetWorld()->LineTraceSingleByChannel(
			OutHit,
			TraceStartLoc,
			TraceEndLoc.GridSnap(100.0f), // Unsure if GridSnap is still needed
			ECC_Visibility,
			CollisionParams
			))
		{
			ValidDirections.Add(RotatedForwardVector);
		}
	}

	// Get random direction from ValidDirections
	const int32 RandomIndex = FMath::RandRange(0, ValidDirections.Num() - 1);
	if (ValidDirections.IsValidIndex(RandomIndex))
	{
		SetLastForwardDirection(ValidDirections[RandomIndex]);
	}

	IsCheckingDirection = false;
}

bool ABoomEnemyCharacter::CheckCollision()
{
	// Do not check collision if currently changing direction
	if (IsCheckingDirection) { return false; }

	const float TraceLength = 65.0f;
	const FVector TraceStartLoc = GetActorLocation();
	const FVector TraceEndLoc = TraceStartLoc + GetActorRotation().Vector() * TraceLength;
	
	FHitResult OutHit;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	
	return GetWorld()->LineTraceSingleByChannel(
		OutHit,
		TraceStartLoc,
		TraceEndLoc,
		ECC_Visibility,
		CollisionQueryParams
		);
}

void ABoomEnemyCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->ImplementsInterface(UBoomIInstaKillable::StaticClass()))
	{
		IBoomIInstaKillable::Execute_ReceiveInstaKill(OtherActor);
	}
}

