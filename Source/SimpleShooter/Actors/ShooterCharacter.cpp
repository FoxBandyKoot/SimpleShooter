// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Riffle.h"
#include "Components/CapsuleComponent.h"
#include "../Meta/Custom_GameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Riffle = GetWorld()->SpawnActor<ARiffle>(RiffleClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None); // We hide the weapon of the animation to replace it by the reels weapons.
	Riffle->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_rSocket"));
	Riffle->SetOwner(this);
	Riffle->SetActorScale3D(FVector(1, 1.4, 1));
	Riffle->SetActorRelativeLocation(FVector(0, -10.90, -3));

	RotationRate = 20; // Speed rotation for the gamepad
	CurrentHealth = MaxHealth;
	IsDead = false;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LateralMovement"), this, &AShooterCharacter::LateralMove);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput); // For keyboard
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate); // For gamepad
	PlayerInputComponent->BindAxis(TEXT("LateralLook"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookLateralRate"), this, &AShooterCharacter::LookLateralRate); // For gamepad

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(CurrentHealth, DamageToApply);
	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("CurrentHealth %f"), CurrentHealth);
	if(CurrentHealth == 0)
	{
		IsDead = true;
		ACustom_GameModeBase* Custom_GameModeBase = GetWorld()->GetAuthGameMode<ACustom_GameModeBase>();
		if(Custom_GameModeBase)
		{
			Custom_GameModeBase->PawnKilled(this);
		}
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DetachFromControllerPendingDestroy();
	}
	return DamageToApply;
}

float AShooterCharacter::GetHealth() const
{
	return CurrentHealth / MaxHealth;
}

FVector AShooterCharacter::GetEndLocation() const
{
	return EndLocation;
}

void AShooterCharacter::Shoot()
{
	Riffle->PullTriger();
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::LateralMove(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);

}

// For gamepad
void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds()); 
}

// For gamepad
void AShooterCharacter::LookLateralRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds()); 
}