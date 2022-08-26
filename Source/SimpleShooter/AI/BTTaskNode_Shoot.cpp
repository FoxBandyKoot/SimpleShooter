// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"
#include "AIController.h"
#include "AIController_Wraith.h"
#include "../Actors/ShooterCharacter.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner())
    {
        
        AShooterCharacter* AIShooterCharacter = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
        if(AIShooterCharacter)
        {
            AIShooterCharacter->Shoot();
        }
        
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
    
}
