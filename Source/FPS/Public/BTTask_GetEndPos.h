// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GetEndPos.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UBTTask_GetEndPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTTask_GetEndPos();

private:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) override;
};
