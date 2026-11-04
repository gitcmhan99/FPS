// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DetectTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/OverlapResult.h"
#include "FPSAIControllerBase.h"
#include "FPSNonCharacter.h"

UBTService_DetectTarget::UBTService_DetectTarget(const FObjectInitializer& ObjectInitializer)
{
    NodeName = TEXT("DetectTarget");
    Interval = 1.0f;
}

void UBTService_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AFPSAIControllerBase* FPSAIControl = Cast<AFPSAIControllerBase>(OwnerComp.GetAIOwner());
    if (IsValid(FPSAIControl))
    {
        AFPSNonCharacter* FPSNonCharacter = Cast<AFPSNonCharacter>(FPSAIControl->GetPawn());
        if (IsValid(FPSNonCharacter))
        {
            UWorld* world =  FPSNonCharacter->GetWorld();
            if (IsValid(world))
            {
                FVector CenterPosition = FPSNonCharacter->GetActorLocation();
                float DetectRadius = 300.f;
                TArray<FOverlapResult> OverlapResults;
                FCollisionQueryParams CollisionQueryParams(NAME_None, false, FPSNonCharacter);
                bool bResult = world->OverlapMultiByChannel(
                    OverlapResults,
                    CenterPosition,
                    FQuat::Identity,
                    ECollisionChannel::ECC_GameTraceChannel2,
                    FCollisionShape::MakeSphere(DetectRadius),
                    CollisionQueryParams
                );

                if (bResult)
                {
                    for (auto const& OverlapResult : OverlapResults)
                    {
                        AFPSCharacterBase* Character = Cast<AFPSCharacterBase>(OverlapResult.GetActor());

                        if (IsValid(Character) && Character->GetController()->IsPlayerController())
                        {
                            OwnerComp.GetBlackboardComponent()->SetValueAsObject(AFPSAIControllerBase::TargetKey, Character);

                            {
                                DrawDebugSphere(world, CenterPosition, DetectRadius, 16, FColor::Red, false, 0.5f);
                                DrawDebugPoint(world, Character->GetActorLocation(), 10.f, FColor::Red, false, 0.5f);
                                DrawDebugLine(world, FPSNonCharacter->GetActorLocation(), Character->GetActorLocation(), FColor::Red, false, 0.5f, 0u, 3.f);
                            }

                            break;
                        }
                        else
                        {
                            OwnerComp.GetBlackboardComponent()->SetValueAsObject(AFPSAIControllerBase::TargetKey, nullptr);
                        }
                    } //for (auto const& OverlapResult : OverlapResults)
                } //if (bResult)
                else
                {
                    OwnerComp.GetBlackboardComponent()->SetValueAsObject(AFPSAIControllerBase::TargetKey, nullptr);
                }

                DrawDebugSphere(world, CenterPosition, DetectRadius, 16, FColor::Green, false, 0.5f);
            }
        }
    }

}
