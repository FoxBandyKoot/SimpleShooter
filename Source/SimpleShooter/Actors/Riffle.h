// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Riffle.generated.h"

UCLASS()
class SIMPLESHOOTER_API ARiffle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARiffle();
	void PullTriger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	bool RiffleTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetController() const;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComponentCustom;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* MuzzleFlash;
	
	UPROPERTY(EditAnywhere)
	class UParticleSystem* ImpactShoot;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;
	
	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere)
	float MaxRange = 10000;

	UPROPERTY(EditAnywhere)
	float Dammage = 10;
};