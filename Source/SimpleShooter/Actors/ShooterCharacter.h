// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class ARiffle;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();
	void Shoot();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(BlueprintReadOnly)
	bool IsDead;

	UFUNCTION(BlueprintPure)
	float GetHealth() const;
	FVector GetEndLocation() const;

private:
	
	void MoveForward(float AxisValue);
	void LateralMove(float AxisValue);
	void LookUpRate(float AxisValue); // For gamepad
	void LookLateralRate(float AxisValue); // For gamepad

	UPROPERTY(EditAnywhere);
	float RotationRate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ARiffle> RiffleClass;

	UPROPERTY()
	ARiffle* Riffle;

	UPROPERTY(EditAnywhere)
	float MaxHealth;

	UPROPERTY()
	float CurrentHealth;

	UPROPERTY(EditAnywhere);
	FVector EndLocation;
};
