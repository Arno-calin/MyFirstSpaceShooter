// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Components/BoxComponent.h"

void ASpawner::SetTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ASpawner::SpawnEnemy,
	                                       FMath::RandRange(MinDelayToSpawn, MaxDelayToSpawn));
}

void ASpawner::SetLevelTimer()
{
	GetWorld()->GetTimerManager().SetTimer(LevelTimer, this, &ASpawner::NextLevel,20);
}

void ASpawner::NextLevel()
{
	if (SpawnScale != FVector(0.5f,0.5f,0.5f))
		SetLevelTimer();
	SpawnScale.X-=0.10;
	SpawnScale.Y-=0.10;
	SpawnScale.Z-=0.10;
	if (MaxDelayToSpawn > 3)
		MaxDelayToSpawn-=0.5f;
}

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	RootComponent = SpawnerBox;
	SpawnScale = FVector(2.f,2.f,2.f);
}

void ASpawner::SpawnEnemy()
{
	// Récupérer la position centrale du BoxComponent
	FVector BoxCenter = SpawnerBox->GetComponentLocation();

	// Récupérer les dimensions (extensibilité) du BoxComponent
	FVector BoxExtent = SpawnerBox->GetScaledBoxExtent();

	FVector RandomPosition;

	if (SpawnDirection.X == 1 || SpawnDirection.X == -1)
	{
		RandomModificatorSpawnDirection = FVector(0, FMath::RandRange(-1,1), 0);
		// Calculer une position aléatoire à l'intérieur de la boîte
		float RandomX = FMath::RandRange(BoxCenter.X - BoxExtent.Y, BoxCenter.X + BoxExtent.Y);
		float RandomY = FMath::RandRange(BoxCenter.Y - BoxExtent.X, BoxCenter.Y + BoxExtent.X);
		float RandomZ = FMath::RandRange(BoxCenter.Z - BoxExtent.Z, BoxCenter.Z + BoxExtent.Z);
		// Créer un vecteur de position aléatoire
		RandomPosition = FVector (RandomX, RandomY, RandomZ);
	}
	else if (SpawnDirection.Y == 1 || SpawnDirection.Y == -1)
	{
		RandomModificatorSpawnDirection = FVector(FMath::RandRange(-1,1),0 , 0);
		// Calculer une position aléatoire à l'intérieur de la boîte
		float RandomX = FMath::RandRange(BoxCenter.X - BoxExtent.X, BoxCenter.X + BoxExtent.X);
		float RandomY = FMath::RandRange(BoxCenter.Y - BoxExtent.Y, BoxCenter.Y + BoxExtent.Y);
		float RandomZ = FMath::RandRange(BoxCenter.Z - BoxExtent.Z, BoxCenter.Z + BoxExtent.Z);
		// Créer un vecteur de position aléatoire
		RandomPosition = FVector (RandomX, RandomY, RandomZ);
	}
	// ensure the enemy class is valid
	if (IsValid(ClassToSpawn))
	{
		// spawn the enemy at the reference capsule's transform
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AAsteroid* asteroid = GetWorld()->SpawnActor<AAsteroid>(ClassToSpawn, RandomPosition, FRotator::ZeroRotator, SpawnParams);
		if (asteroid)
		{
			asteroid->SetScale(SpawnScale);
			asteroid->SetMovement(SpawnDirection + RandomModificatorSpawnDirection);
		}
	}
	SetTimer();
}
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	SetLevelTimer();
	SetTimer();
}
