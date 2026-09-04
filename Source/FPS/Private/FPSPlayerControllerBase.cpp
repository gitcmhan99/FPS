// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerControllerBase.h"
#include "FPS/FPS.h"

AFPSPlayerControllerBase::AFPSPlayerControllerBase()
{
    MYLOG("Start AFPSPlayerControllerBase()");

    PrimaryActorTick.bCanEverTick = true;

    MYLOG("End AFPSPlayerControllerBase()");

}

void AFPSPlayerControllerBase::PostInitializeComponents()
{
    MYLOG("Start AFPSPlayerControllerBase PostInitializeComponents()");

    Super::PostInitializeComponents();

    MYLOG("End AFPSPlayerControllerBase PostInitializeComponents()");
}

void AFPSPlayerControllerBase::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);


}

void AFPSPlayerControllerBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    MYLOG("Start AFPSPlayerControllerBase EndPlay() EndPlayReason: %d", EndPlayReason);

    Super::EndPlay(EndPlayReason);

    MYLOG("End AFPSPlayerControllerBase EndPlay() EndPlayReason: %d", EndPlayReason);
}

void AFPSPlayerControllerBase::OnPossess(APawn* aPawn)
{
    MYLOG("Start AFPSPlayerControllerBase OnPossess: %s", *aPawn->GetName());

    Super::OnPossess(aPawn);

    MYLOG("End AFPSPlayerControllerBase OnPossess: %s", *aPawn->GetName());
}

void AFPSPlayerControllerBase::OnUnPossess()
{
    MYLOG("Start AFPSPlayerControllerBase OnUnPossess");

    Super::OnUnPossess();

    MYLOG("End AFPSPlayerControllerBase OnUnPossess");
}

void AFPSPlayerControllerBase::BeginPlay()
{
    MYLOG("Start AFPSPlayerControllerBase BeginPlay()");

    Super::BeginPlay();

    MYLOG("End AFPSPlayerControllerBase BeginPlay()");

}

void AFPSPlayerControllerBase::SetupInputComponent()
{
    Super::SetupInputComponent();

  //  InputComponent->BindAxis(TEXT("LeftRight"), this, &ThisClass::LeftRight);
}

void AFPSPlayerControllerBase::LeftRight(float InAxis)
{
    MYSCREENLOG(" AFPSPlayerControllerBase  LeftRight %f", InAxis);
}
