// Fill out your copyright notice in the Description page of Project Settings.


#include "Custom_PlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ACustom_PlayerController::BeginPlay()
{
        HUD = CreateWidget(GetWorld(),  HUDClass);
        if(HUD)
        {
            HUD->AddToViewport();
        }
        
        UGameplayStatics::PlaySound2D(GetWorld(), StartSound);
}


void ACustom_PlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    RestartDelay = 5;
    HUD->RemoveFromViewport();
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

    // Deal with End Screen
    if(bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(GetWorld(),  WinScreenClass);
        if(WinScreen)
        {
            WinScreen->AddToViewport();
        }
    }
    else
    {
        UUserWidget* LooseScreen = CreateWidget(GetWorld(), LooseScreenClass);
        if(LooseScreen)
        {
            LooseScreen->AddToViewport();
        }
    }

}


// UE_LOG(LogTemp, Warning, TEXT("CustomplayerController"));
