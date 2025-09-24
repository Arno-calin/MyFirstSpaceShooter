// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/KillZone.h"

#include "Components/BoxComponent.h"

// Sets default values
AKillZone::AKillZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	RootComponent = MyBox;
}

// Called when the game starts or when spawned
void AKillZone::BeginPlay()
{
	Super::BeginPlay();
	this->OnActorBeginOverlap.AddDynamic(this, &AKillZone::OnBeginOverlap);
}

void AKillZone::OnBeginOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (!Cast<AKillZone>(MyActor))
		OtherActor->Destroy();
}

// Called every frame
void AKillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}