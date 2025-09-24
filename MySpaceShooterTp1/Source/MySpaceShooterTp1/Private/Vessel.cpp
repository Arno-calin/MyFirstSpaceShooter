// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Vessel.h"

#include "Asteroid.h"
#include "Missile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

class UFloatingPawnMovement;
// Sets default values
AVessel::AVessel()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VesselBox = CreateDefaultSubobject<UBoxComponent>(TEXT("VesselBox"));
	RootComponent = VesselBox;
	
	VesselMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VesselMesh"));
	VesselMesh->SetupAttachment(VesselBox);

	VesselMovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("VesselMovementComponent"));
	VesselMovementComponent->UpdatedComponent = VesselMesh;

	ConstructorHelpers::FClassFinder<AActor> ActorToSpawn (TEXT("/Game/SpaceShooter/Blueprint/BP_Missile"));
	if (ActorToSpawn.Class)
		MissileToSpawn = ActorToSpawn.Class;

	VesselCurrentLife = 3;
	VesselCurrentScore = 0;
}

int AVessel::getVesselCurrentLife()
{
	return VesselCurrentLife;
}

int AVessel::getVesselCurrentScore()
{
	return VesselCurrentScore;
}

// Called when the game starts or when spawned
void AVessel::BeginPlay()
{
	Super::BeginPlay();
	SetScoreTimer();
	this->OnActorBeginOverlap.AddDynamic(this, &AVessel::OnBeginOverlap);
}

// Called every frame
void AVessel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVessel::MovementHorizontally(float Valeur)
{
	if (Valeur != 0)
	{
		FRotator CurrentRotator = VesselMesh->GetComponentRotation();
		FRotator TargetRotator = CurrentRotator;
		TargetRotator.Yaw = Valeur > 0.f ? 0.f: 180.f;
		FRotator NewRotator = FMath::RInterpTo(CurrentRotator, TargetRotator, GetWorld()->GetDeltaSeconds(), 5.f);
		VesselMesh->SetWorldRotation(NewRotator);
		AddMovementInput(FVector(0.f, Valeur, 0.f), VesselMovementComponent->GetMaxSpeed()); // Move in the Y axe 
	}
}

void AVessel::MovementVertically(float Valeur)
{
	if (Valeur != 0)
	{
		FRotator CurrentRotator  = VesselMesh->GetComponentRotation();
		FRotator TargetRotator = CurrentRotator ;
		TargetRotator.Yaw = Valeur > 0.f ? -90.f: 90.f;
		FRotator NewRotator = FMath::RInterpTo(CurrentRotator, TargetRotator, GetWorld()->GetDeltaSeconds(), 10.f);
		VesselMesh->SetWorldRotation(NewRotator);
		AddMovementInput(FVector(Valeur, 0.f, 0.f), VesselMovementComponent->GetMaxSpeed()); // Move in the X axe 
	}
}

// Called to bind functionality to input
void AVessel::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// Link input with function 
	PlayerInputComponent->BindAxis("MoveHorizontally", this, &AVessel::MovementHorizontally);
	PlayerInputComponent->BindAxis("MoveVertically", this, &AVessel::MovementVertically);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AVessel::Spawn);
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AVessel::Spawn()
{
	AMissile* newMissle = GetWorld()->SpawnActor<AMissile>(MissileToSpawn, VesselMovementComponent->GetActorLocation()+VesselMesh->GetUpVector()*100,VesselMesh->GetComponentRotation());
	if (newMissle)
		newMissle->SetMovement(VesselMesh->GetUpVector()*10);
}

bool AVessel::isAlife()
{
	return VesselCurrentLife > 0;
}

void AVessel::OnBeginOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (auto asteroid = Cast<AAsteroid>(OtherActor))
	{
		asteroid->Destroy();
		VesselCurrentLife--;
		if (!isAlife())
			Destroy();
	}
}

void AVessel::SetScoreTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AVessel::AddScore,1);
}
