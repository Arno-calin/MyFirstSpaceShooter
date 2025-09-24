// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Vessel.generated.h"

UCLASS()
class MYSPACESHOOTERTP1_API AVessel : public APawn
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* VesselMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class UBoxComponent* VesselBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Movement");
	UPawnMovementComponent* VesselMovementComponent;

	TSubclassOf<AActor> MissileToSpawn;

	int VesselCurrentLife;
	int VesselCurrentScore;
	bool isAlife();

	int test = 0;

	UFUNCTION()
	void OnBeginOverlap(AActor* MyActor, AActor* OtherActor);

	FTimerHandle SpawnTimer;
	void SetScoreTimer();

	void AddScore()
	{
		VesselCurrentScore++;
		SetScoreTimer();
	}

public:
	// Sets default values for this pawn's properties
	AVessel();
	UFUNCTION(BlueprintCallable)
	int getVesselCurrentLife();
	UFUNCTION(BlueprintCallable)
	int getVesselCurrentScore();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the player move with the keyboard 
	void MovementHorizontally(float Valeur);
	void MovementVertically(float Valeur);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Spawn();
};
