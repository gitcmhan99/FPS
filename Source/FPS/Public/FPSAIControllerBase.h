// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSAIControllerBase.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class FPS_API AFPSAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
    AFPSAIControllerBase();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

//protected:
//    FTimerHandle TimerHandle_Patrol;
//
//private:
//    void OnPatrol();

    void StartAI(APawn* FPSPawn);
    void FinishedAI();

public:
    static const FName Pos_StartKey;
    static const FName Pos_EndKey;

#pragma region AI
private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    TObjectPtr<UBlackboardData> BlackboardDataAsset;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    TObjectPtr<UBehaviorTree> BehaviorTree;


    TObjectPtr<UBlackboardComponent> Blackboard;
    TObjectPtr<UBehaviorTreeComponent> TreeComponent;
#pragma endregion
};
