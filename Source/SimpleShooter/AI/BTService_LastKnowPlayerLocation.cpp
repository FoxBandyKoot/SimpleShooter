// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LastKnowPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTService_LastKnowPlayerLocation::UBTService_LastKnowPlayerLocation()
{
    NodeName = "Update Last Know Player Location";
}

void UBTService_LastKnowPlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(PlayerPawn)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
        // UE_LOG(LogTemp, Warning, TEXT("UBTService_LastKnowPlayerLocation : GetActorLocation() %f"), PlayerPawn->GetActorLocation().X);
    }
}
