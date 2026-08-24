// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DummyParticle.generated.h"

class UParticleSystemComponent;

UCLASS()
class FPS_API ADummyParticle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADummyParticle();

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DummyParticle", meta = (AllowPrivateAccess))
    TObjectPtr<UStaticMeshComponent> staticMeshComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DummyParticle", meta = (AllowPrivateAccess))
    TObjectPtr<UParticleSystemComponent> particleSystem;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "DummyParticle", meta = (AllowPrivateAccess))
    int64 testNumber;
};
