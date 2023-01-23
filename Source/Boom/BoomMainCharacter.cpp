// Copyright (c) 2023 Jefferson Jadulco


#include "BoomMainCharacter.h"

#include "BoomBomb.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ABoomMainCharacter::ABoomMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
}

void ABoomMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABoomMainCharacter::OnMoveHorizontal(float AxisValue)
{
	AddMovementInput(FVector(1, 0, 0), AxisValue, false);
}

void ABoomMainCharacter::OnMoveVertical(float AxisValue)
{
	
	AddMovementInput(FVector(0, 1, 0), AxisValue, false);
}

void ABoomMainCharacter::OnSkill1Pressed()
{
	SpawnBomb();
}

void ABoomMainCharacter::PostInitializeComponents()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ABoomMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &ABoomMainCharacter::OnMoveHorizontal);
	PlayerInputComponent->BindAxis("MoveY", this, &ABoomMainCharacter::OnMoveVertical);

	PlayerInputComponent->BindAction("Skill1", IE_Pressed, this, &ABoomMainCharacter::OnSkill1Pressed);
}

void ABoomMainCharacter::ReceiveInstaKill()
{
	Die();
}

void ABoomMainCharacter::SpawnBomb()
{
	// TODO: This function is expensive when spammed. Optimize.
	TArray<AActor*> BombActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoomBomb::StaticClass(), BombActors);
	if (BombActors.Num() >= BombLimit)
	{
		UE_LOG(LogTemp, Log, TEXT("Cannot spawn more than %d bomb/s!"), BombLimit);
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const float GridSize = 100.0f;
	const FVector SpawnLocation = GetActorLocation().GridSnap(GridSize);

	// TODO: Call this on server. But this is okay for now.
	GetWorld()->SpawnActor<ABoomBomb>(BombClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
}

