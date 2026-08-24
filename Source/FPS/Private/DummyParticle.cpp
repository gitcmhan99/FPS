// Fill out your copyright notice in the Description page of Project Settings.


#include "DummyParticle.h"
#include "Particles/ParticleSystemComponent.h"

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
}
