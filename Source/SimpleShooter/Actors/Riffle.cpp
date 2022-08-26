// Fill out your copyright notice in the Description page of Project Settings.


#include "Riffle.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ARiffle::ARiffle()
{
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponentCustom = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponentCustom"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	
	SetRootComponent(RootComponentCustom);
	Mesh->SetupAttachment(RootComponentCustom);	
}

void ARiffle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARiffle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARiffle::PullTriger()
{

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("weapon_rSocket"), FVector(0, 100, 0));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("weapon_rSocket"));
	FHitResult Hit;
	FVector ShotDirection;
	if(RiffleTrace(Hit, ShotDirection))
	{
		// Apply visual effects
		FRotator SpawnRotation = ShotDirection.Rotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactShoot, Hit.ImpactPoint - FVector(0, 10, 0), SpawnRotation);		
		UGameplayStatics::SpawnSoundAttached(ImpactSound, Mesh, TEXT("weapon_rSocket"), Hit.ImpactPoint, SpawnRotation);

		// Create a Damage event
		if(Hit.GetActor())
		{
			FPointDamageEvent DammageEvent(Dammage, Hit, ShotDirection, nullptr);
			AController* OwnerController = GetController();
			Hit.GetActor()->TakeDamage(Dammage, DammageEvent, OwnerController, this);
			
			// DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 50, FColor::Red, true);
			// UE_LOG(LogTemp, Warning, TEXT("HIT"));
		}
	}
}

// Shoot where the camera point and not where the riffle point	
bool ARiffle::RiffleTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetController();
	if(OwnerController)
	{
		// Get the player camera
		FVector PlayerLocation;
		FRotator PlayerRotation;
		OwnerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
		// DrawDebugCamera(GetWorld(), PlayerLocation, PlayerRotation, 90, 1, FColor::Red, true);
		ShotDirection =  -PlayerRotation.Vector();
		
		FVector EndPoint = PlayerLocation + PlayerRotation.Vector() * MaxRange;

		// Compute the position of the impact
		FCollisionQueryParams collisionParameters;
		collisionParameters.AddIgnoredActor(this);
		collisionParameters.AddIgnoredActor(GetOwner()); 
		// ECC_GameTraceChannel1 is our custom trace channel "Bullet" create in Project Settings -> Collision
		return GetWorld()->LineTraceSingleByChannel(Hit, PlayerLocation, EndPoint, ECollisionChannel::ECC_GameTraceChannel1, collisionParameters);
	}	
	return false;
}

AController* ARiffle::GetController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn)
	{
		return OwnerPawn->GetController();
	}	 
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ARiffle : Impossible to cast APawn"));
		return nullptr;
	}
}