// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Asteroid.h"

// Sets default values
AMissile::AMissile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MissileBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	RootComponent = MissileBox;
	
	MissileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MissileMesh->SetupAttachment(MissileBox);
}

void AMissile::SetMovement(FVector Direction)
{
	VectorMovement = Direction;
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
	this->OnActorBeginOverlap.AddDynamic(this, &AMissile::OnBeginOverlap);

}

void AMissile::OnBeginOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (auto asteroid = Cast<AAsteroid>(OtherActor))
	{
		asteroid->SetLifeMinusOne();
		Explosion(GetActorLocation());
		MyActor->Destroy();
	}
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + VectorMovement);
}
