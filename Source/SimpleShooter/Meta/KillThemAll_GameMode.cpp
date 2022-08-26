// Fill out your copyright notice in the Description page of Project Settings.


#include "KillThemAll_GameMode.h"
#include "Custom_PlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "../AI/AIController_Wraith.h"

void AKillThemAll_GameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);
    
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerController)
    {
        EndGame(false);
    }
    else
    {
        for(AAIController_Wraith* AIController : TActorRange<AAIController_Wraith>(GetWorld()))
        {
            if(!AIController->IsDead())
            { // The player has not won yet because some IA are alive
                return;    
            }
        }
        // The player has won because all IA are dead
        EndGame(true);
        
    }
    // UE_LOG(LogTemp, Error, TEXT("KillThemAll_GameMode : Impossible to cast APlayerController"));
}

void AKillThemAll_GameMode::EndGame(bool bIsPlayerWinner)
{
    for(AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner); // 1 parameter : the contoller focus himself to keep a look on him
    }
}
