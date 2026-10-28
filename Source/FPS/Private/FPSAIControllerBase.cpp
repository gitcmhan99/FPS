// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIControllerBase.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "FPS/FPS.h"

const FName AFPSAIControllerBase::Pos_StartKey(TEXT("Pos_Srart"));
const FName AFPSAIControllerBase::Pos_EndKey(TEXT("Pos_End"));


AFPSAIControllerBase::AFPSAIControllerBase()
{

}

void AFPSAIControllerBase::BeginPlay()
{
    Super::BeginPlay();

   /* GetWorld()->GetTimerManager().SetTimer(TimerHandle_Patrol, this, &ThisClass::OnPatrol, 2.f, true);*/

    APawn* FPSPawn = GetPawn();
    if (true == IsValid(FPSPawn))
    {
        StartAI(FPSPawn);
    }
}

void AFPSAIControllerBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    //GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Patrol);

    Super::EndPlay(EndPlayReason);

    FinishedAI();
}

void AFPSAIControllerBase::StartAI(APawn* FPSPawn)
{
    MYSCREENLOG("StartAI");
}

void AFPSAIControllerBase::FinishedAI()
{
    MYLOG("FinishedAI");
}

/*
void AFPSAIControllerBase::OnPatrol()
{
    //TODO: 타이머에서 호출되는 함수
    APawn* controlPawn = GetPawn();
    if (false == IsValid(controlPawn))
    {
        return;
    }

    UNavigationSystemV1* navigationSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
    if (false == IsValid(navigationSystem))
    {
        return;
    }

    FVector controlPawnPos = controlPawn->GetActorLocation();
    FNavLocation ResultLocation;

    bool foundPos = navigationSystem->GetRandomPointInNavigableRadius(controlPawnPos, 600.f, ResultLocation);
    if (true == foundPos)
    {
        MYSCREENLOG("OnPatrol > foundPos");

        UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, ResultLocation.Location);
    }
}
*/
