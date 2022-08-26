// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Custom_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ACustom_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	 
	virtual void GameHasEnded(AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5;

	UPROPERTY(EditAnywhere)
	USoundBase* StartSound;

	// UPROPERTY()
	FTimerHandle RestartTimer;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LooseScreenClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY()
	UUserWidget* HUD;
};
