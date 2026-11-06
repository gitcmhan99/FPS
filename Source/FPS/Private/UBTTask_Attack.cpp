// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTTask_Attack.h"
#include "FPSAIControllerBase.h"
#include "FPSNonCharacter.h"

UUBTTask_Attack::UUBTTask_Attack()
{
    bNotifyTick = true;
}

void UUBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AFPSAIControllerBase* AIController = Cast<AFPSAIControllerBase>(OwnerComp.GetAIOwner());
    checkf(IsValid(AIController) == true, TEXT("Invalid AIController."));

    AFPSNonCharacter* NPC = Cast<AFPSNonCharacter>(AIController->GetPawn());
    checkf(IsValid(NPC) == true, TEXT("Invalid NPC."));

    if (NPC->bIsNowAttacking == false)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}

EBTNodeResult::Type UUBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AFPSAIControllerBase* AIController = Cast<AFPSAIControllerBase>(OwnerComp.GetAIOwner());
    checkf(IsValid(AIController) == true, TEXT("Invalid AIController."));

    AFPSNonCharacter* NPC = Cast<AFPSNonCharacter>(AIController->GetPawn());
    checkf(IsValid(NPC) == true, TEXT("Invalid NPC."));

    NPC->BeginAttack();

    return EBTNodeResult::InProgress;
}
