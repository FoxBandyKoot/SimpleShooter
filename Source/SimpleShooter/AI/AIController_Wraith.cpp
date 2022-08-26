// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Wraith.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Actors/ShooterCharacter.h"


void AAIController_Wraith::BeginPlay()
{
    Super::BeginPlay();
    Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    // SightRadius = 500;
    if(BehaviorTree)
    {
        RunBehaviorTree(BehaviorTree);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
        AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
        GetBlackboardComponent()->SetValueAsVector(TEXT("EndLocation"), ControlledCharacter->GetEndLocation());

    }
}
bool AAIController_Wraith::IsDead() const
{
    AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
    if(ControlledCharacter)
    {
        return ControlledCharacter->IsDead;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AAIController_Wraith : Impossible to cast AShooterCharacter"));
    }
    return true;
}
