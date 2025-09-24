// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class MYSPACESHOOTERTP1_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* AsteroidMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class UBoxComponent* AsteroidBox;

	FVector VectorMovement = FVector(0, 0, 0);
	float Speed = 0;
	FRotator ContinueRotator = FRotator(0, 0, 0);
	
	UFUNCTION()
	void OnBeginOverlap(AActor* MyActor, AActor* OtherActor);

	int CurrentLife;
	bool isAlife();
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

	void SetMovement(const FVector& Movement);
	void SetLifeMinusOne();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
