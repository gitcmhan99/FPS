// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPawnBase.h"
#include "FPS/FPS.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameUtil.h"

// Sets default values
AFPSPawnBase::AFPSPawnBase()
{
    MYLOG("Start AFPSPawnBase()");

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CapsuleComponent = GameUtil::CreateRootComponent<UCapsuleComponent>(this);
    SkeletalMeshComponent = GameUtil::CreateComponent<USkeletalMeshComponent>(
        this,
        true,
        CapsuleComponent);
    SpringArmComponent =
        GameUtil::CreateComponent<USpringArmComponent>(this, true, CapsuleComponent);
    CameraComponent = GameUtil::CreateComponent<UCameraComponent>(this, true, SpringArmComponent);

    FloatingPawnMovement = GameUtil::CreateActorComponent<UFloatingPawnMovement>(this);

    MYLOG("End AFPSPawnBase()");
}

// Called when the game starts or when spawned
void AFPSPawnBase::BeginPlay()
{
    MYLOG("Start AFPSPawnBase::BeginPlay()");

	Super::BeginPlay();

    MYLOG("End AFPSPawnBase::BeginPlay()");

}

// Called every frame
void AFPSPawnBase::Tick(float DeltaTime)
{
    static bool doOnce = false;

    if (false == doOnce)
    {
        MYLOG("Start AFPSPawnBase::Tick()");

        Super::Tick(DeltaTime);

        MYLOG("End AFPSPawnBase::Tick()");

        doOnce = true;
    }
}

// Called to bind functionality to input
void AFPSPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    MYLOG("Start AFPSPawnBase::SetupPlayerInputComponent()");

	Super::SetupPlayerInputComponent(PlayerInputComponent);

    MYLOG("End AFPSPawnBase::SetupPlayerInputComponent()");
}

void AFPSPawnBase::PostInitializeComponents()
{
    MYLOG("Start AFPSPawnBase::PostInitializeComponents()");

    Super::PostInitializeComponents();

    MYLOG("End AFPSPawnBase::PostInitializeComponents()");
}

void AFPSPawnBase::PossessedBy(AController* NewController)
{
    MYLOG("Start AFPSPawnBase::PossessedBy() %s", *NewController->GetName());

    Super::PossessedBy(NewController);

    MYLOG("End AFPSPawnBase::PossessedBy() %s", *NewController->GetName());
}

void AFPSPawnBase::UnPossessed()
{
    MYLOG("Start AFPSPawnBase::UnPossessed()");

    Super::UnPossessed();

    MYLOG("End AFPSPawnBase::UnPossessed()");
}

void AFPSPawnBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    MYLOG("Start AFPSPawnBase::EndPlay() EndPlayReason: %d", EndPlayReason);

    Super::EndPlay(EndPlayReason);

    MYLOG("End AFPSPawnBase::EndPlay() EndPlayReason: %d", EndPlayReason);
}

