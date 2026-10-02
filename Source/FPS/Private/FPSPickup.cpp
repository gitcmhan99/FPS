// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPickup.h"
#include "FPSCharacterBase.h"

UFPSPickup::UFPSPickup()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UFPSPickup::BeginPlay()
{
    Super::BeginPlay();

    //
    OnComponentBeginOverlap.AddDynamic(this, &ThisClass::CallBackBeginOverlap);
}

void UFPSPickup::CallBackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AFPSCharacterBase* castFPSChar = Cast<AFPSCharacterBase>(OtherActor);
    if (IsValid(castFPSChar))
    {
        OnPickUp.Broadcast(castFPSChar);
        OnComponentBeginOverlap.RemoveAll(this);
    }
}

