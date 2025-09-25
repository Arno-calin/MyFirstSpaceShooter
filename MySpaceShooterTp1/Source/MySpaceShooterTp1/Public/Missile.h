// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Missile.generated.h"

UCLASS()
class MYSPACESHOOTERTP1_API AMissile : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class UStaticMeshComponent* MissileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	class UBoxComponent* MissileBox;

	FVector VectorMovement = FVector(0, 0, 0);
	

public:	
	// Sets default values for this actor's properties
	AMissile();
	
	void SetMovement(FVector Direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* MyActor, AActor* OtherActor);

	UFUNCTION(BlueprintImplementableEvent)
	void Explosion(FVector ExplosionPosition);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
