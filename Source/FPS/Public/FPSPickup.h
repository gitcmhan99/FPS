// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "FPSPickup.generated.h"

class AFPSCharacterBase;

/**
 * 
 */
UCLASS()
class FPS_API UFPSPickup : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    UFPSPickup();


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()
    void CallBackBeginOverlap(UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
