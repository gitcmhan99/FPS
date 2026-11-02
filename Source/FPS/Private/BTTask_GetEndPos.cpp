// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetEndPos.h"
#include "FPSNonCharacter.h"
#include "FPSAIControllerBase.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <FPS/FPS.h>

UBTTask_GetEndPos::UBTTask_GetEndPos()
{
    NodeName = TEXT("GetEndPos");
}

EBTNodeResult::Type UBTTask_GetEndPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    if (EBTNodeResult::Type::Failed == Result)
    {
        return Result;
    }

    AFPSAIControllerBase* AIController = Cast<AFPSAIControllerBase>(OwnerComp.GetAIOwner());
    AFPSNonCharacter* NPC = Cast<AFPSNonCharacter>(AIController->GetPawn());;
    UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetNavigationSystem(NPC->GetWorld());

    if (!IsValid(AIController) ||
        !IsValid(NPC) ||
        !IsValid(NavigationSystem))
    {
        return EBTNodeResult::Type::Failed;
    }

    FVector startPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AFPSAIControllerBase::Pos_StartKey);
    FNavLocation randomPos;

    MYSCREENLOG("%f, %f, %f", startPos.X, startPos.Y, startPos.Z);

    bool isRandomPos = NavigationSystem->GetRandomPointInNavigableRadius(startPos, 500.0f, randomPos);
    if (isRandomPos)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(AFPSAIControllerBase::Pos_EndKey, randomPos);
        Result = EBTNodeResult::Type::Succeeded;
    }

    return Result;

}
