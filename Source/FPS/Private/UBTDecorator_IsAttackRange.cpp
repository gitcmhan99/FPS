// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTDecorator_IsAttackRange.h"
#include "FPSNonCharacter.h"
#include "FPSAIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"

const float UUBTDecorator_IsAttackRange::AttackRange(200.f);

UUBTDecorator_IsAttackRange::UUBTDecorator_IsAttackRange()
{
    NodeName = TEXT("IsAttackRange");
}

bool UUBTDecorator_IsAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
    checkf(bResult == true, TEXT("Super::CalculateRawConditionValue() function has returned false."));

    AFPSAIControllerBase* AIController = Cast<AFPSAIControllerBase>(OwnerComp.GetAIOwner());
    checkf(IsValid(AIController) == true, TEXT("Invalid AIController."));

    AFPSNonCharacter* NPC = Cast<AFPSNonCharacter>(AIController->GetPawn());
    checkf(IsValid(NPC) == true, TEXT("Invalid NPC."));

    AFPSCharacterBase* TargetPlayerCharacter = Cast<AFPSCharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AFPSAIControllerBase::TargetKey));
    if (IsValid(TargetPlayerCharacter) == true && TargetPlayerCharacter->IsPlayerControlled() == true)
    {
        return NPC->GetDistanceTo(TargetPlayerCharacter) <= AttackRange;
    }

    return false;
}
