// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Asteroid.h"
#include "Spawner.generated.h"

/**
 * 
 */
UCLASS(abstract)
class MYSPACESHOOTERTP1_API ASpawner : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UBoxComponent* SpawnerBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Spawner", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AAsteroid> ClassToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Spawner", meta = (AllowPrivateAccess = "true"))
	FVector SpawnDirection;
	
	FVector RandomModificatorSpawnDirection = FVector::ZeroVector;
	void SpawnEnemy();
	FTimerHandle SpawnTimer;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Spawner", meta = (AllowPrivateAccess = "true"))
	float MinDelayToSpawn = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Spawner", meta = (AllowPrivateAccess = "true"))
	float MaxDelayToSpawn = 10.0f;
	void SetTimer();

public:
	ASpawner();
	/** Initialization */
	virtual void BeginPlay() override;

};
