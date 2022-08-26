// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Wraith.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AAIController_Wraith : public AAIController
{
	GENERATED_BODY()

public:
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

private:
	// UPROPERTY()
	APawn* Player;

	// UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	// FVector StartLocation;
	
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BehaviorTree;
};
