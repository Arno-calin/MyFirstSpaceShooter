// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Asteroid.h"

#include "Components/BoxComponent.h"



// Sets default values
AAsteroid::AAsteroid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AsteroidBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	RootComponent = AsteroidBox;
	
	AsteroidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	AsteroidMesh->SetupAttachment(AsteroidBox);
	Speed = FMath::FRandRange(0.5f, 5.f);
	ContinueRotator = FRotator(0, FMath::FRandRange(-1.f, 1.f), 0);
	CurrentLife = FMath::RandRange(1, 3);
}

void AAsteroid::SetMovement(const FVector& Movement)
{
	VectorMovement = Movement;
}

void AAsteroid::SetLifeMinusOne()
{
	CurrentLife--;
	if (!isAlife())
		Destroy();
}
bool AAsteroid::isAlife()
{
	return CurrentLife > 0;
}

void AAsteroid::OnBeginOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (Cast<AAsteroid>(OtherActor))
	{
		Explosion();
		OtherActor->Destroy();
		MyActor->Destroy();
	}
}
// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	this->OnActorBeginOverlap.AddDynamic(this, &AAsteroid::OnBeginOverlap);
	}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + VectorMovement);
	SetActorRotation(GetActorRotation() + ContinueRotator);
}

