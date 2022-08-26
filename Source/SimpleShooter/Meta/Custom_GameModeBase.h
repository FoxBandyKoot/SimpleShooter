// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Custom_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ACustom_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void PawnKilled(APawn* PawnKilled);
};
