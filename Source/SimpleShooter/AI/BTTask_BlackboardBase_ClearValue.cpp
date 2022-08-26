// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BlackboardBase_ClearValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_BlackboardBase_ClearValue::UBTTask_BlackboardBase_ClearValue()
{
    NodeName = TEXT("Clear BlackBoard Value");
}

EBTNodeResult::Type UBTTask_BlackboardBase_ClearValue::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    return EBTNodeResult::Succeeded;
}
