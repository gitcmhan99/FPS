// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "UBTDecorator_IsAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UUBTDecorator_IsAttackRange : public UBTDecorator
{
	GENERATED_BODY()

public:
    UUBTDecorator_IsAttackRange();

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

public:
    static const float AttackRange;
};
