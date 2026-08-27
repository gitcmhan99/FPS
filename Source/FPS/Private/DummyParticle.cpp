// Fill out your copyright notice in the Description page of Project Settings.


#include "DummyParticle.h"
#include "Particles/ParticleSystemComponent.h"
#include "FPS/FPS.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
ADummyParticle::ADummyParticle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMeshComponent"));
    SetRootComponent(staticMeshComponent);

    particleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("particleSystem"));
    particleSystem->SetupAttachment(GetRootComponent());
    particleSystem->SetRelativeLocation(FVector(0.f, 0.f, 600.f));

    //Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Sparks.P_Sparks'
    //static ConstructorHelpers::FObjectFinder<UParticleSystem> pSpark
    static ConstructorHelpers::FObjectFinder<UParticleSystem> pSpark(TEXT("/Game/StarterContent/Particles/P_Sparks.P_Sparks"));
    if (pSpark.Succeeded())
    {
        //(class UParticleSystem* NewTemplate)
        particleSystem->SetTemplate(pSpark.Object);
    }
    else
    {
        MYSCREENLOG("/Game/StarterContent/Particles/P_Sparks.P_Sparks");
    }

    RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
}

void ADummyParticle::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    MYLOG("ADummyParticle::PostInitializeComponents");
}

void ADummyParticle::BeginPlay()
{
    Super::BeginPlay();

    MYLOG("ADummyParticle::BeginPlay");
    RotatingMovementComponent->RotationRate = FRotator(0.f, 10, 0.f);
    //RotatingMovementComponent->bRotationInLocalSpace = false;
}

void ADummyParticle::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ADummyParticle::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    MYLOG("ADummyParticle::EndPlay %d", EndPlayReason);
}
