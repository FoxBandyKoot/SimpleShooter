// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Custom_GameModeBase.h"
#include "KillThemAll_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillThemAll_GameMode : public ACustom_GameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;
	void EndGame(bool bIsPlayerWinner);
};
